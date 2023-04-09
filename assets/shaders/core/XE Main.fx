
// XE Main.fx
// MGE XE 0.16.0
// Main render sequence

#include "XE Common.fx"


//------------------------------------------------------------
// Core-mod code is inserted here

#include "XE Mod Shadow.fx"
#include "XE Mod Statics.fx"
#include "XE Mod Landscape.fx"
#include "XE Mod Grass.fx"
#include "XE Mod Sky.fx"
#include "XE Mod Water.fx"
#include "XE Mod Caustics.fx"

//------------------------------------------------------------
// Morrowind/MGE blending

DeferredOut MGEBlendVS(float4 pos : POSITION, float2 tex : TEXCOORD0, float2 ndc : TEXCOORD1) {
    DeferredOut OUT;

    // Fix D3D9 half pixel offset
    OUT.pos = float4(ndc.x - rcpRes.x, ndc.y + rcpRes.y, 0, 1);
    OUT.tex = float4(tex, 0, 0);

    // Eye space reconstruction vector
    OUT.eye = float3(ndc.x / proj[0][0], ndc.y / proj[1][1], 1);
    return OUT;
}

float4 MGEBlendPS(DeferredOut IN) : COLOR0 {
    const float zone = 512.0, bound = nearViewRange - zone;
    float v, w = tex2Dlod(sampDepthPoint, IN.tex).r;

    if(w > bound) {
        // tex2Dlod allows texld to be moved into the branch, as grad calculation is not required
        w = min(w, tex2Dlod(sampDepthPoint, IN.tex + float4(-rcpRes.x, 0, 0, 0)).r);
        w = min(w, tex2Dlod(sampDepthPoint, IN.tex + float4(0, -rcpRes.y, 0, 0)).r);
        w = min(w, tex2Dlod(sampDepthPoint, IN.tex + float4(rcpRes.x, 0, 0, 0)).r);
        w = min(w, tex2Dlod(sampDepthPoint, IN.tex + float4(0, rcpRes.y, 0, 0)).r);
    }

    //w *= length(IN.eye);   // causes some errors with distant land
    v = (w - bound) / zone;
    clip(v);

    return float4(tex2Dlod(sampBaseTex, IN.tex).rgb, saturate(v));
}

//------------------------------------------------------------
// Dynamic waves simulation

struct WaveVertOut
{
    float4 pos : POSITION;
    float2 texcoord : TEXCOORD0;
};

WaveVertOut WaveVS(float4 pos : POSITION, float2 texcoord : TEXCOORD0)
{
    WaveVertOut OUT;
    OUT.pos = mul(pos, proj);
    OUT.texcoord = texcoord;
    return OUT;
}

float4 WaveStepPS(float2 tex : TEXCOORD0) : COLOR0
{
    // Texture content is now float16 in range [-1, 1]
    float4 tc = float4(tex, 0, 0);
    float4 c = tex2Dlod(sampRain, tc);
    float4 ret = {0, c.r, 0, 0};

    float4 n = {
        tex2D(sampRain, tc + float4(waveTexRcpRes, 0, 0, 0)).r,
        tex2D(sampRain, tc + float4(-waveTexRcpRes, 0, 0, 0)).r,
        tex2D(sampRain, tc + float4(0, waveTexRcpRes, 0, 0)).r,
        tex2D(sampRain, tc + float4(0, -waveTexRcpRes, 0, 0)).r
    };
    float4 n2 = {
        tex2D(sampRain, tc + float4(1.5 * waveTexRcpRes, 0, 0, 0)).r,
        tex2D(sampRain, tc + float4(-1.5 * waveTexRcpRes, 0, 0, 0)).r,
        tex2D(sampRain, tc + float4(0, 1.5 * waveTexRcpRes, 0, 0)).r,
        tex2D(sampRain, tc + float4(0, -1.5 * waveTexRcpRes, 0, 0)).r
    };

    // dampened discrete two-dimensional wave equation
    // red channel: u(t)
    // green channel: u(t - 1)
    // u(t + 1) = (1 - udamp) * u(t) + a * (nsum - 4 * u(t)) + (1 - vdamp) * (u(t) - u(t - 1))
    //        = a * nsum + ((2 - udamp - vdamp) - 4 * a) * u(t) - (1 - vdamp) * u(t - 1);
    float nsum = n.x + n.y + n.z + n.w;
    ret.r = 0.14 * nsum + (1.96 - 0.56) * c.r - 0.98 * c.g;

    // calculate normal map
    ret.ba = 2 * (n.xy - n.zw) + 0.5 * (n2.xy - n2.zw);
    return ret;
}

float4 PlayerWavePS(float2 tex : TEXCOORD0) : COLOR0
{
    float4 ret = tex2Dlod(sampRain, float4(tex, 0, 0));
    float wavesize = (1.0 + 0.055 * sin(16 * time) + 0.065 * sin(12.87645 * time)) * playerWaveSize;
    float displace = saturate(2 * abs(length(tex - rippleOrigin) / wavesize - 1));
    ret.rg = lerp(-1, ret.rg, displace);
    return ret;
}

//------------------------------------------------------------
// Minimal shader for clip plane bug workaround

float4 NullVS(float4 pos : POSITION) : POSITION {
    return float4(0, 0, 0, 1);
}

float4 NullPS() : COLOR0 {
    return float4(0, 0, 0, 1);
}

//------------------------------------------------------------
// Shadow map debug inset display

struct DebugOut {
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
 };

DebugOut ShadowDebugVS(float4 pos : POSITION) {
    DebugOut OUT;

    OUT.pos = float4(0, 0, 0, 1);
    OUT.pos.x = 1 + 0.25 * (rcpRes.x/rcpRes.y) * (pos.x - 1);
    OUT.pos.y = 1 + 1.0/512.0 + 0.5 * (pos.y - 1);
    OUT.tex = (0.5 + 0.5*shadowRcpRes) + float2(0.5, -0.5) * pos.xy;
    OUT.tex.y *= 2;

    return OUT;
}

float4 ShadowDebugPS(DebugOut IN) : COLOR0 {
    float z, red = 0;
    float4 shadowClip, eyeClip;

    [branch] if(IN.tex.y < 1) {
        // Sample depth
        float2 t = IN.tex;
        z = tex2Dlod(sampDepth, mapShadowToAtlas(t, 0)).r / ESM_scale;
        // Convert pixel position from shadow clip space directly to camera clip space
        shadowClip = float4(2*t.x - 1, 1 - 2*t.y, z, 1);
        eyeClip = mul(shadowClip, vertexBlendPalette[0]);
    }
    else {
        // Sample depth
        float2 t = IN.tex - float2(0, 1);
        z = tex2Dlod(sampDepth, mapShadowToAtlas(t, 1)).r / ESM_scale;
        // Convert pixel position from shadow clip space directly to camera clip space
        shadowClip = float4(2*t.x - 1, 1 - 2*t.y, z, 1);
        eyeClip = mul(shadowClip, vertexBlendPalette[1]);
    }

    // Do perspective divide and mark the pixel if it falls within the camera frustum
    eyeClip.xyz /= eyeClip.w;
    if(abs(eyeClip.x) <= 1 && abs(eyeClip.y) <= 1 && eyeClip.z >= 0 && eyeClip.z <= 1)
        red = saturate(1.5 - eyeClip.w / 8192);

    return float4(red, saturate(1-2*z), saturate(2-2*z), 1);
}

//-----------------------------------------------------------------------------

Technique T0 {
    //------------------------------------------------------------
    // Used to set up the render state
    Pass Zero {
        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        BlendOp = Add;
        FogEnable = false;
        Lighting = false;
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        StencilEnable = false;
        CullMode = CW;
    }
    //------------------------------------------------------------
    // Used for rendering grass with shadows
    Pass P1 {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 128;

        VertexShader = compile vs_3_0 GrassInstVS();
        PixelShader = compile ps_3_0 GrassPS();
    }
    //------------------------------------------------------------
    // Used for rendering shadows over fixed function output
    Pass P2 {
        ZEnable = true;
        ZWriteEnable = false;
        ZFunc = LessEqual;
        StencilEnable = false;
        CullMode = CW;

        AlphaBlendEnable = true;
        SrcBlend = Zero;
        DestBlend = InvSrcColor;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 RenderShadowsVS();
        PixelShader = compile ps_3_0 RenderShadowsPS();
    }
    //------------------------------------------------------------
    // Used for rendering shadows over FFE output
    Pass P2ffe {
        ZEnable = true;
        ZWriteEnable = false;
        ZFunc = LessEqual;
        StencilEnable = false;
        CullMode = CW;

        AlphaBlendEnable = true;
        SrcBlend = Zero;
        DestBlend = InvSrcColor;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 RenderShadowsFFEVS();
        PixelShader = compile ps_3_0 RenderShadowsPS();
    }
    //------------------------------------------------------------
    // Used to render the landscape
    Pass P3 {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 LandscapeVS();
        PixelShader = compile ps_3_0 LandscapePS();
    }
    //------------------------------------------------------------
    // Used to render the landscape reflection
    Pass P3r {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CCW;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 LandscapeReflVS();
        PixelShader = compile ps_3_0 LandscapePS();
    }
    //------------------------------------------------------------
    // Used for rendering distant statics in exteriors
    Pass P4ext {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;

        AlphaBlendEnable = false;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 133;

        VertexShader = compile vs_3_0 StaticExteriorVS();
        PixelShader = compile ps_3_0 StaticPS();
    }
    //------------------------------------------------------------
    // Used for rendering distant statics in interiors and underwater
    Pass P4int {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;

        AlphaBlendEnable = false;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 133;

        VertexShader = compile vs_3_0 StaticInteriorVS();
        PixelShader = compile ps_3_0 StaticPS();
    }
    //------------------------------------------------------------
    // Used for rendering sky scattering and sky reflection
    Pass P5 {
        ZEnable = true;
        ZWriteEnable = false;
        CullMode = CW;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 1;

        VertexShader = compile vs_3_0 SkyVS();
        PixelShader = compile ps_3_0 SkyPS();
    }
    //------------------------------------------------------------
    // Used for rendering clouds
    Pass P5clouds {
        ZEnable = true;
        ZWriteEnable = false;
        CullMode = CW;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 1;

        VertexShader = compile vs_3_0 CloudsVS();
        PixelShader = compile ps_3_0 CloudsPS();
    }
    //------------------------------------------------------------
    // Used for rendering water plane
    Pass P6 {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 WaterVS();
        PixelShader = compile ps_3_0 WaterPS();
    }
    //------------------------------------------------------------
    // Used for rendering underwater water plane
    Pass P7 {
        ZEnable = true;
        ZWriteEnable = true;
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 WaterVS();
        PixelShader = compile ps_3_0 UnderwaterPS();
    }
    //------------------------------------------------------------
    // Used for rendering caustics
    Pass P8 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;
        FillMode = Solid;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 CausticsVS();
        PixelShader = compile ps_3_0 CausticsPS();
    }
     //------------------------------------------------------------
    // Used for blending between Morrowind and MGE
    Pass P9 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = CW;
        FillMode = Solid;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 MGEBlendVS();
        PixelShader = compile ps_3_0 MGEBlendPS();
    }
    //------------------------------------------------------------
    // Used for rendering shadow debug
    Pass PX {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 ShadowDebugVS();
        PixelShader = compile ps_3_0 ShadowDebugPS();
    }
    //------------------------------------------------------------
    // Used for creating ripples around PC
    Pass P10 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 WaveVS();
        PixelShader = compile ps_3_0 PlayerWavePS();
    }
    //------------------------------------------------------------
    // Used for calculating waves
    Pass P11 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 WaveVS();
        PixelShader = compile ps_3_0 WaveStepPS();
    }
    //------------------------------------------------------------
    // Used for a clip plane bug workaround
    Pass P12 {
        ZEnable = false;
        ZWriteEnable = false;

        VertexShader = compile vs_3_0 NullVS();
        PixelShader = compile ps_3_0 NullPS();
    }
    //------------------------------------------------------------
}
