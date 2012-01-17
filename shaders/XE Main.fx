
// XE Main.fx
// MGE XE 0.9
// Main render sequence

#include "XE Common.fx"
#include "XE Water.fx"
#include "XE Shadow.fx"



//------------------------------------------------------------
// Distant statics

StatVertOut StaticExteriorVS (StatVertIn IN)
{
    StatVertOut OUT;

    // Transforms and implicit depth bias
    float4 worldpos = mul(IN.pos, world);
    OUT.pos = mul(worldpos, view);
    OUT.pos = mul(OUT.pos, proj);

    // Fogging (exterior)
    float3 eyevec = worldpos.xyz - EyePos.xyz;
    float dist = length(eyevec);
    OUT.fog = fogColour(eyevec / dist, dist);

    // Decompress normal
    float4 normal = float4(normalize(2 * IN.normal.xyz - 1), 0);
    normal = normalize(mul(normal, world));
    
    // Lighting
    float emissive = IN.normal.w; // Emissive stored in 4th value in normal vector
    float3 light = SunCol * saturate(dot(normal.xyz, -SunVec)) + SunAmb + emissive;
    OUT.color = float4(saturate(IN.color.rgb * light), IN.color.a);

    OUT.texcoords = IN.texcoords;
    return OUT;
}

StatVertOut StaticInteriorVS (StatVertIn IN)
{
    StatVertOut OUT;

    // Transforms and implicit depth bias
    float4 worldpos = mul(IN.pos, world);
    OUT.pos = mul(worldpos, view);
    OUT.pos = mul(OUT.pos, proj);

    // Fogging (interior)
    float3 eyevec = worldpos.xyz - EyePos.xyz;
    OUT.fog = fogMWColour(length(eyevec));

    // Decompress normal
    float4 normal = float4(normalize(2 * IN.normal.xyz - 1), 0);
    normal = normalize(mul(normal, world));
    
    // Lighting
    float emissive = IN.normal.w; // Emissive stored in 4th value in normal vector
    float3 light = SunCol * saturate(dot(normal.xyz, -SunVec)) + SunAmb + emissive;
    OUT.color = float4(saturate(IN.color.rgb * light), IN.color.a);

    OUT.texcoords = IN.texcoords;
    return OUT;
}

float4 StaticPS (StatVertOut IN): COLOR0
{
    float4 result = tex2D(sampBaseTex, IN.texcoords);
    result.rgb *= IN.color.rgb;
    result.rgb = fogApply(result.rgb, IN.fog);

    return result;
}

//------------------------------------------------------------
// Grass

struct GrassVertOut
{
    float4 pos : POSITION;
    half2 texcoords : TEXCOORD0;
    half4 colour : COLOR0;
    half4 fog : COLOR1;
    
    float4 shadow0pos : TEXCOORD1;
    float4 shadow1pos : TEXCOORD2;
};

GrassVertOut GrassInstVS (StatVertInstIn IN)
{
    GrassVertOut OUT;
    
    // Instancing
    float4 worldpos = instancedMul(IN.pos, IN.world0, IN.world1, IN.world2);

    // Transforms with wind displacement
    worldpos.xy += grassDisplacement(worldpos, IN.pos.z);
    OUT.pos = mul(worldpos, view);
    OUT.pos = mul(OUT.pos, proj);
    
    // Fogging
    float3 eyevec = worldpos.xyz - EyePos.xyz;
    OUT.fog = fogMWColour(length(eyevec));

    // Decompress normal
    float4 normal = float4(normalize(2 * IN.normal.xyz - 1), 0);
    normal = normalize(instancedMul(normal, IN.world0, IN.world1, IN.world2));
    
    // Lighting (with backface culling turned off, grass shading requires tweak factors)
    float3 light = 0.5 * SunCol * saturate(dot(normal.xyz, -SunVec)) + SunAmb; // + emissive; (some grass has it for no reason producing overbrightness)
    OUT.colour.rgb = saturate(light);    // vertex colour is also unreliable

    // Non-standard shadow luminance, to create sufficient contrast when ambient is high
    OUT.colour.a = shadowSunEstimate(0.5);

    // Find position in light space, output light depth
    OUT.shadow0pos = mul(worldpos, shadowviewproj[0]);
    OUT.shadow1pos = mul(worldpos, shadowviewproj[1]);
    OUT.shadow0pos.z = OUT.shadow0pos.z / OUT.shadow0pos.w;
    OUT.shadow1pos.z = OUT.shadow1pos.z / OUT.shadow1pos.w;

    OUT.texcoords = IN.texcoords;
    return OUT;
}

float4 GrassPS (GrassVertOut IN): COLOR0
{
    float4 result = tex2D(sampBaseTex, IN.texcoords);
    clip(result.a - 2.0/255.0);
    result.rgb *= IN.colour.rgb;

    // Soft shadowing
    float dz = shadowDeltaZ(IN.shadow0pos, IN.shadow1pos);
    float v = shadowESM(dz);
 
    // Darken shadow area according to existing lighting (slightly towards blue)
    v *= IN.colour.a;
    result.rgb *= 1 - v * shadecolour;
    
    // Fogging
    result.rgb = fogApply(result.rgb, IN.fog);
    
    return result;
}

//------------------------------------------------------------
// Distant landscape

struct LandVertOut
{
    float4 pos: POSITION;
    float2 texcoord: TEXCOORD0;
    float4 fog : TEXCOORD1;
};

LandVertOut LandscapeVS (float4 pos : POSITION, float2 texcoord : TEXCOORD0)
{
    LandVertOut OUT;

    // Fogging
    float3 eyevec = pos.xyz - EyePos.xyz;
    float dist = length(eyevec);
    OUT.fog = fogColour(eyevec / dist, dist);

    // Move land down to avoid it appearing where reduced mesh doesn't match
    pos.z += landBias(dist);
    
    // Transforms
    OUT.pos = mul(pos, world);
    OUT.pos = mul(OUT.pos, view);
    OUT.pos = mul(OUT.pos, proj);
    
    OUT.texcoord = texcoord;
    return OUT;
}

LandVertOut LandscapeReflVS (float4 pos : POSITION, float2 texcoord : TEXCOORD0)
{
    LandVertOut OUT;

    // Fogging
    float3 eyevec = pos.xyz - EyePos.xyz;
    float dist = length(eyevec);
    if(isAboveSeaLevel(EyePos))
        OUT.fog = fogColour(eyevec / dist, dist);
    else
        OUT.fog = fogMWColour(dist);

    // Sink land near waterline a small amount
    pos.z += -16 * saturate(1 - pos.z/16);
    
    // Transforms
    OUT.pos = mul(pos, world);
    OUT.pos = mul(OUT.pos, view);
    OUT.pos = mul(OUT.pos, proj);
    
    OUT.texcoord = texcoord;
    return OUT;
}

float4 LandscapePS (in LandVertOut IN) : COLOR0
{
    // Expand and normalize normal map
    float3 normal = normalize(2 * tex2D(sampNormals, IN.texcoord).rgb - 1);

    // World texture
    float3 result = tex2D(sampBaseTex, IN.texcoord).rgb;

    // Detail texture
    float detail = tex2D(sampDetail, IN.texcoord * 1064).g + 0.5;
    detail *= tex2D(sampDetail, IN.texcoord * 333).g + 0.5;
    detail *= tex2D(sampDetail, IN.texcoord * 90).g + 0.5;

    // Lighting
    result *= detail * saturate(saturate(dot(-SunVec, normal)) * SunCol + SunAmb);

    // Fogging
    result = fogApply(result, IN.fog);
    return float4(result, 1);
}

//------------------------------------------------------------
// Morrowind/MGE blending

DeferredOut MGEBlendVS (float4 pos : POSITION, float2 tex : TEXCOORD0, float2 ndc : TEXCOORD1)
{
    DeferredOut OUT;

    // Fix D3D9 half pixel offset    
    OUT.pos = float4(ndc.x - rcpres.x, ndc.y + rcpres.y, 0, 1);
    OUT.tex = float4(tex, 0, 0);
    
    // Eye space reconstruction vector
    OUT.eye = float3(ndc.x / proj[0][0], ndc.y / proj[1][1], 1);
    return OUT;
}

float4 MGEBlendPS (DeferredOut IN) : COLOR0
{
    const float zone = 512.0, bound = 7168.0 - zone;
    float v, w = tex2Dlod(sampDepth, IN.tex).r;
    
    if(w > bound)
    {
        // tex2Dlod allows texld to be moved into the branch, as grad calculation is not required
        w = min(w, tex2Dlod(sampDepth, IN.tex + float4(-rcpres.x, 0, 0, 0)).r);
        w = min(w, tex2Dlod(sampDepth, IN.tex + float4(0, -rcpres.y, 0, 0)).r);
        w = min(w, tex2Dlod(sampDepth, IN.tex + float4(rcpres.x, 0, 0, 0)).r);
        w = min(w, tex2Dlod(sampDepth, IN.tex + float4(0, rcpres.y, 0, 0)).r);
    }
    
    //w = length(w * IN.eye);   // causes some errors with distant land
    v = (w - bound) / zone;
    clip(v);
    
    return float4(tex2Dlod(sampBaseTex, IN.tex).rgb, saturate(v));
}

//------------------------------------------------------------
// Sky reflections

struct SkyVertOut
{
    float4 pos : POSITION;
    float4 color : COLOR0;
    float2 texcoords : TEXCOORD0;
    float4 skypos : TEXCOORD1;
};

SkyVertOut SkyVS (StatVertIn IN)
{
    SkyVertOut OUT;

    // Screw around with skydome, align default mesh with horizon
    float4 pos = IN.pos;
    if(!hasalpha)
        pos.z = 50 * (IN.pos.z + 200);
        
    pos = mul(pos, world);
    OUT.skypos = pos - float4(world[3][0], world[3][1], world[3][2], world[3][3]);

    pos = mul(pos, view);
    OUT.pos = mul(pos, proj);
    OUT.pos.z = 0.999999 * OUT.pos.w;   // Pin z to far plane so it renders to background
    OUT.color = IN.color;
    OUT.texcoords = IN.texcoords;
    
    return OUT;
}

// Ordered dithering matrix
static const float ditherSky[4][4] = { 0.001176, 0.001961, -0.001176, -0.001699, -0.000654, -0.000915, 0.000392, 0.000131, -0.000131, -0.001961, 0.000654, 0.000915, 0.001699, 0.001438, -0.000392, -0.001438 };

float4 SkyPS (SkyVertOut IN, float2 vpos : VPOS) : COLOR0
{
    // Sample texture at lod 0 avoiding mip blurring, or return colour from scattering for sky
    if(hasalpha)
        return IN.color * tex2Dlod(sampBaseTex, float4(IN.texcoords, 0, 0));
    else
        return fogColourSky(normalize(IN.skypos.xyz)) + ditherSky[vpos.x % 4][vpos.y % 4];
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
        StencilEnable = false;
        CullMode = none;

        AlphaBlendEnable = false;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 128;
        
        VertexShader = compile vs_3_0 GrassInstVS ();
        PixelShader = compile ps_3_0 GrassPS ();
    }
    //------------------------------------------------------------
    // Used for rendering shadows
    Pass P2 {
        ZEnable = true;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = CW;
        FogEnable = false;

        AlphaBlendEnable = true;
        SrcBlend = Zero;
        DestBlend = InvSrcColor;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 RenderShadowsVS ();
        PixelShader = compile ps_3_0 RenderShadowsPS ();
    }
    //------------------------------------------------------------
    // Used to render the landscape
    Pass P3 {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        
        VertexShader = compile vs_3_0 LandscapeVS ();
        PixelShader = compile ps_3_0 LandscapePS ();
    }
    //------------------------------------------------------------
    // Used to render the landscape reflection
    Pass P3r {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CCW;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        
        VertexShader = compile vs_3_0 LandscapeReflVS ();
        PixelShader = compile ps_3_0 LandscapePS ();
    }
    //------------------------------------------------------------
    // Used for rendering distant statics in exteriors 
    Pass P4ext {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 133;
        
        VertexShader = compile vs_3_0 StaticExteriorVS ();
        PixelShader = compile ps_3_0 StaticPS ();
    }
    //------------------------------------------------------------
    // Used for rendering distant statics in interiors and underwater
    Pass P4int {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = true;
        AlphaFunc = GreaterEqual;
        AlphaRef = 133;
        
        VertexShader = compile vs_3_0 StaticInteriorVS ();
        PixelShader = compile ps_3_0 StaticPS ();
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
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 SkyVS ();
        PixelShader = compile ps_3_0 SkyPS ();
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
        StencilEnable = false;

        VertexShader = compile vs_3_0 WaterVS ();
        PixelShader = compile ps_3_0 WaterPS ();
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

        VertexShader = compile vs_3_0 WaterVS ();
        PixelShader = compile ps_3_0 UnderwaterPS ();
    }
    //------------------------------------------------------------
    // Used for rendering caustics
    Pass P8 {
        ZEnable = false;
        ZWriteEnable = false;
        CullMode = None;
        StencilEnable = false;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        
        VertexShader = compile vs_3_0 CausticsVS ();
        PixelShader = compile ps_3_0 CausticsPS ();
    }
     //------------------------------------------------------------
    // Used for blending between Morrowind and MGE
    Pass P9 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = CW;
        FogEnable = false;

        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 MGEBlendVS ();
        PixelShader = compile ps_3_0 MGEBlendPS ();
    }
    //------------------------------------------------------------
    // Used for rendering shadow debug
    Pass PX {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        
        VertexShader = compile vs_3_0 ShadowDebugVS ();
        PixelShader = compile ps_3_0 ShadowDebugPS ();
    }
    //------------------------------------------------------------
    // Used for creating ripples around PC
    Pass P10 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 WaveVS ();
        PixelShader = compile ps_3_0 PlayerWavePS ();
    }
    //------------------------------------------------------------
    // Used for calculating waves
    Pass P11 {
        ZEnable = false;
        ZWriteEnable = false;
        StencilEnable = false;
        CullMode = none;
        FogEnable = false;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;

        VertexShader = compile vs_3_0 WaveVS ();
        PixelShader = compile ps_3_0 WaveStepPS ();
    }
    //------------------------------------------------------------
}
