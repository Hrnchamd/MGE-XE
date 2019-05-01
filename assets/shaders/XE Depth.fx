
// XE Depth.fx
// MGE XE 0.11
// Depth buffer render sequence

#include "XE Common.fx"



//------------------------------------------------------------
// Floating point clears

float4 DepthClearVS (float4 pos : POSITION) : POSITION
{
    return pos;
}

float4 DepthClearPS (float4 pos : POSITION) : COLOR0
{
    return 1.0e38;
}

//------------------------------------------------------------
// Depth render

struct DepthVertOut
{
	float4 pos : POSITION;
	half2 texcoords : TEXCOORD0;
    float depth : TEXCOORD1;
};

DepthVertOut DepthMWVS (in MorrowindVertIn IN)
{
    DepthVertOut OUT;
    float4 viewpos;

    // Skin mesh if required
    if(hasbones)
        viewpos = skin(IN.pos, IN.blendweights);
    else
        viewpos = mul(IN.pos, vertexblendpalette[0]);
    
    // Transform and output depth
    OUT.pos = mul(viewpos, proj);
    OUT.depth = OUT.pos.w;
    OUT.texcoords = IN.texcoords;

    return OUT;
}

DepthVertOut DepthLandVS (float4 pos: POSITION, float2 texcoord: TEXCOORD0)
{
    DepthVertOut OUT;

    // Move land down to avoid it appearing where reduced mesh doesn't match
    pos.z += landBias(length(pos.xyz - EyePos.xyz));

    OUT.pos = mul(pos, world);
    OUT.pos = mul(OUT.pos, view);
    OUT.pos = mul(OUT.pos, proj);
    
    OUT.depth = OUT.pos.w;
    OUT.texcoords = texcoord;

    return OUT;
}

DepthVertOut DepthStaticVS (StatVertIn IN)
{
    DepthVertOut OUT;

    OUT.pos = mul(IN.pos, world);
    OUT.pos = mul(OUT.pos, view);
    OUT.pos = mul(OUT.pos, proj);
    
    OUT.depth = OUT.pos.w;
    OUT.texcoords = IN.texcoords;

    return OUT;
}

DepthVertOut DepthGrassVS (StatVertIn IN)
{
    DepthVertOut OUT;

    // Transforms with wind displacement
    float4 worldpos = mul(IN.pos, world);
    worldpos.xy += grassDisplacement(worldpos, IN.pos.z);
    OUT.pos = mul(worldpos, view);
    OUT.pos = mul(OUT.pos, proj);

    OUT.depth = OUT.pos.w;
    OUT.texcoords = IN.texcoords;

    return OUT;
}

DepthVertOut DepthGrassInstVS (StatVertInstIn IN)
{
    DepthVertOut OUT;

    // Instancing
    float4 worldpos = instancedMul(IN.pos, IN.world0, IN.world1, IN.world2);

    // Transforms with wind displacement
    worldpos.xy += grassDisplacement(worldpos, IN.pos.z);
    OUT.pos = mul(worldpos, view);
    OUT.pos = mul(OUT.pos, proj);

    OUT.depth = OUT.pos.w;
    OUT.texcoords = IN.texcoords;

    return OUT;
}

float4 DepthLandPS (DepthVertOut IN) : COLOR0
{
    clip(IN.depth - nearViewRange);
    return IN.depth;
}

float4 DepthStaticPS (DepthVertOut IN) : COLOR0
{
    clip(IN.depth - nearViewRange);

    if(hasalpha)
    {
        float alpha = tex2D(sampBaseTex, IN.texcoords).a;
        clip(alpha - 133.0/255.0);
    }
    return IN.depth;
}

float4 DepthNearPS (DepthVertOut IN) : COLOR0
{
    clip(nearViewRange + 64.0 - IN.depth);

    // Respect alpha test
    if(hasalpha)
    {
        float alpha = tex2D(sampBaseTex, IN.texcoords).a;
        clip(alpha - alpharef);
    }

    return IN.depth;
}

//-----------------------------------------------------------------------------

Technique T0 {
    //------------------------------------------------------------
    // Used for clearing scene depth
    Pass D0 {
        ZEnable = false;
        ZWriteEnable = false;
        CullMode = CW;
        ClipPlaneEnable = 0;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        StencilEnable = false;
        FogEnable = false;
        Lighting = false;

        VertexShader = compile vs_3_0 DepthClearVS ();
        PixelShader = compile ps_3_0 DepthClearPS ();
    }
    //------------------------------------------------------------
    // Used for rendering scene depth
    Pass D1 {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;
        ClipPlaneEnable = 0;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        StencilEnable = false;
        FogEnable = false;
        Lighting = false;

        VertexShader = compile vs_3_0 DepthMWVS ();
        PixelShader = compile ps_3_0 DepthNearPS ();
    }
    //------------------------------------------------------------
    // Used for rendering distant land depth
    Pass D2 {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = CW;

        VertexShader = compile vs_3_0 DepthLandVS ();
        PixelShader = compile ps_3_0 DepthLandPS ();
    }
   //------------------------------------------------------------
   // Used for rendering distant statics depth
    Pass D3 {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = CW;

        VertexShader = compile vs_3_0 DepthStaticVS ();
        PixelShader = compile ps_3_0 DepthStaticPS ();
    }
   //------------------------------------------------------------
   // Used for rendering grass depth
    Pass D4 {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = none;
        
        VertexShader = compile vs_3_0 DepthGrassVS ();
        PixelShader = compile ps_3_0 DepthNearPS ();
    }
   //------------------------------------------------------------
   // Used for rendering grass depth
    Pass D4i {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = none;
        
        VertexShader = compile vs_3_0 DepthGrassInstVS ();
        PixelShader = compile ps_3_0 DepthNearPS ();
    }
   //------------------------------------------------------------
}
