
// XE Shadowmap.fx
// MGE XE 0.16.0
// Shadow map rendering

#include "XE Common.fx"
#include "XE Mod Shadow Data.fx"



//------------------------------------------------------------
// Shadow caster rendering

struct ShadowVertOut {
    float4 pos : POSITION;
    float2 texcoords : TEXCOORD0;
    float depth : TEXCOORD1;
};

ShadowVertOut ShadowVS(StatVertIn IN) {
    ShadowVertOut OUT;

    OUT.pos = mul(IN.pos, world);
    OUT.pos = mul(OUT.pos, shadowViewProj[0]);

    // Clamp vertices to front plane to avoid clipping and shadow loss
    OUT.pos.z = max(0, OUT.pos.z);

    // Output depth (ortho projection is linear)
    OUT.depth = OUT.pos.z / OUT.pos.w;

    OUT.texcoords = IN.texcoords;
    return OUT;
}

ShadowVertOut ShadowClearVS(float4 pos : POSITION) {
    ShadowVertOut OUT;

    OUT.pos = pos;
    OUT.depth = 1.0f;
    OUT.texcoords = 0.0f;
    return OUT;
}

float4 ShadowPS(ShadowVertOut IN) : COLOR0 {
    // Sample alpha geometry if required
    if(hasAlpha) {
        float a = tex2D(sampBaseTex, IN.texcoords).a;
        clip(a - 180.0/255.0);
    }

    return ESM_scale * IN.depth;
}

float4 ShadowStencilPS(ShadowVertOut IN) : COLOR0 {
    return 1;
}

//------------------------------------------------------------
// Shadow map filtering

static const float2 shadowAtlasRcpRes = shadowRcpRes * float2(shadowCascadeSize, 1);

struct ShadowPostOut {
    float4 pos : POSITION;
    float2 texcoords : TEXCOORD0;
};

ShadowPostOut ShadowSoftenVS(float4 pos : POSITION) {
    ShadowPostOut OUT;

    OUT.pos = pos;
    OUT.texcoords = (0.5 + 0.5*shadowAtlasRcpRes) + float2(0.5, -0.5) * pos.xy;
    return OUT;
}

float4 ShadowSoftenPS(ShadowPostOut IN) : COLOR0 {
    // Filter entire atlas
    // Looks better without exp-space filtering, with a side effect of expanding silhouttes by about 1 pixel
    float4 t = float4(IN.texcoords, 0, 0);
    float d = tex2Dlod(sampDepth, t).r;
    const float filterScale = shadowRcpRes.x;

    if(!hasAlpha) {
        d += 0.2 * tex2Dlod(sampDepth, t + float4(-1.42*filterScale, 0, 0, 0)).r;
        d += 0.8 * tex2Dlod(sampDepth, t + float4(-0.71*filterScale, 0, 0, 0)).r;
        d += 0.8 * tex2Dlod(sampDepth, t + float4(0.71*filterScale, 0, 0, 0)).r;
        d += 0.2 * tex2Dlod(sampDepth, t + float4(1.42*filterScale, 0, 0, 0)).r;
    }
    else {
        d += 0.2 * tex2Dlod(sampDepth, t + float4(0, -1.42*filterScale, 0, 0)).r;
        d += 0.8 * tex2Dlod(sampDepth, t + float4(0, -0.71*filterScale, 0, 0)).r;
        d += 0.8 * tex2Dlod(sampDepth, t + float4(0, 0.71*filterScale, 0, 0)).r;
        d += 0.2 * tex2Dlod(sampDepth, t + float4(0, 1.42*filterScale, 0, 0)).r;
    }

    d = d / 3.0;
    return d.xxxx;
}

//-----------------------------------------------------------------------------

technique T0 {
    //------------------------------------------------------------
    // Used to clear the shadow map
    Pass P0 {
        ZEnable = false;
        ZWriteEnable = false;
        ZFunc = LessEqual;
        CullMode = CW;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        FogEnable = false;
        Lighting = false;

        VertexShader = compile vs_3_0 ShadowClearVS();
        PixelShader = compile ps_3_0 ShadowPS();
    }
    //------------------------------------------------------------
    // Used to render the view frustum into the stencil
    Pass P1 {
        ZEnable = false;
        ZWriteEnable = false;
        ColorWriteEnable = 0;
        CullMode = none;

        StencilEnable = true;
        StencilFunc = always;
        StencilPass = replace;
        StencilFail = keep;
        StencilRef = 1;
        StencilMask = 0xffffffff;

        VertexShader = compile vs_3_0 ShadowVS();
        PixelShader = compile ps_3_0 ShadowStencilPS();
    }
    //------------------------------------------------------------
    // Used to render the shadow map
    Pass P2 {
        ZEnable = true;
        ZWriteEnable = true;
        ColorWriteEnable = red|green|blue|alpha;
        CullMode = CW;

        StencilEnable = true;
        StencilFunc = notequal;
        StencilPass = keep;
        StencilFail = keep;
        StencilRef = 0;
        StencilMask = 0xffffffff;

        VertexShader = compile vs_3_0 ShadowVS();
        PixelShader = compile ps_3_0 ShadowPS();
    }
    //------------------------------------------------------------
    // Used to soften the shadow map
    Pass P3 {
        ZEnable = false;
        ZWriteEnable = false;

        StencilEnable = false;

        VertexShader = compile vs_3_0 ShadowSoftenVS();
        PixelShader = compile ps_3_0 ShadowSoftenPS();
    }
    //------------------------------------------------------------
}
