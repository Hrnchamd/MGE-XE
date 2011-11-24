
// XE Shadowmap.fx
// MGE XE 0.9
// Shadow map rendering

#include "XE Common.fx"
#include "XE Shadow Settings.fx"



//------------------------------------------------------------
// Shadow caster rendering

struct ShadowVertOut
{
    float4 pos : POSITION;
    float depth : TEXCOORD0;
    float2 texcoords : TEXCOORD1;
};

ShadowVertOut ShadowVS (StatVertIn IN)
{
    ShadowVertOut OUT;

    OUT.pos = mul(IN.pos, world);
    OUT.pos = mul(OUT.pos, shadowviewproj[0]);

    // Clamp vertices to front plane to avoid clipping and shadow loss
    OUT.pos.z = max(0, OUT.pos.z);

    // Output depth (ortho projection is linear)
    OUT.depth = OUT.pos.z / OUT.pos.w;
    
    OUT.texcoords = IN.texcoords;
    return OUT;
}

ShadowVertOut ShadowClearVS (float4 pos : POSITION)
{
    ShadowVertOut OUT;
    
    OUT.pos = pos;
    OUT.depth = 1.0f;
    OUT.texcoords = 0.0f;
    return OUT;
}

float4 ShadowPS (ShadowVertOut IN) : COLOR0
{
    // Sample alpha geometry if required
    if(hasalpha)
    {
        float a = tex2D(sampBaseTex, IN.texcoords).a;
        clip(a - 180.0/255.0);
    }
    
    return ESM_scale * IN.depth;
}

//------------------------------------------------------------
// Shadow map filtering

struct ShadowPostOut
{
    float4 pos : POSITION;
    float2 texcoords : TEXCOORD0;
};

ShadowPostOut ShadowSoftenVS (float4 pos : POSITION)
{
    ShadowPostOut OUT;
    
    OUT.pos = pos;
    OUT.texcoords = (0.5 + 0.5*shadowPixelSize) + float2(0.5, -0.5) * pos.xy;
    return OUT;
}

float4 ShadowSoftenPS (ShadowPostOut IN) : COLOR0
{
    // Filter all channels at the same time
    // Looks better without exp-space filtering, with a side effect of expanding silhouttes by about 1 pixel
    float4 s = tex2D(sampDepth, IN.texcoords);
    if(hasalpha == 0)
    {
        s += 0.2 * tex2D(sampDepth, IN.texcoords + float2(-1.42*shadowPixelSize, 0));
        s += 0.8 * tex2D(sampDepth, IN.texcoords + float2(-0.71*shadowPixelSize, 0));
        s += 0.8 * tex2D(sampDepth, IN.texcoords + float2(0.71*shadowPixelSize, 0));
        s += 0.2 * tex2D(sampDepth, IN.texcoords + float2(1.42*shadowPixelSize, 0));
    }
    else
    {
        s += 0.2 * tex2D(sampDepth, IN.texcoords + float2(0, -1.42*shadowPixelSize));
        s += 0.8 * tex2D(sampDepth, IN.texcoords + float2(0, -0.71*shadowPixelSize));
        s += 0.8 * tex2D(sampDepth, IN.texcoords + float2(0, 0.71*shadowPixelSize));
        s += 0.2 * tex2D(sampDepth, IN.texcoords + float2(0, 1.42*shadowPixelSize));
    }

    return s / 3.0;
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

        VertexShader = compile vs_3_0 ShadowClearVS ();
        PixelShader = compile ps_3_0 ShadowPS ();
    }
    //------------------------------------------------------------
    // Used to render the shadow map
    Pass P1 {
        ZEnable = true;
        ZWriteEnable = true;
        
        VertexShader = compile vs_3_0 ShadowVS ();
        PixelShader = compile ps_3_0 ShadowPS ();
    }
    //------------------------------------------------------------
    // Used to soften the shadow map
    Pass P2 {
        ZEnable = false;
        ZWriteEnable = false;
        
        VertexShader = compile vs_3_0 ShadowSoftenVS ();
        PixelShader = compile ps_3_0 ShadowSoftenPS ();
    }
    //------------------------------------------------------------
}
