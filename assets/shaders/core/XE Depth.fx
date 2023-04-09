
// XE Depth.fx
// MGE XE 0.16.0
// Depth buffer render sequence

#include "XE Common.fx"



//------------------------------------------------------------
// Core-mod code is inserted here

#include "XE Mod Shadow.fx"
#include "XE Mod Statics.fx"
#include "XE Mod Landscape.fx"
#include "XE Mod Grass.fx"

//------------------------------------------------------------
// Floating point clears

float4 DepthClearVS(float4 pos : POSITION) : POSITION {
    return pos;
}

float4 DepthClearPS(float4 pos : POSITION) : COLOR0 {
    return 1.0e38;
}

//------------------------------------------------------------
// Depth render

DepthVertOut DepthMWVS(MorrowindVertIn IN) {
    DepthVertOut OUT;
    float4 viewpos;

    // Skin mesh if required
    if(hasBones)
        viewpos = skin(IN.pos, IN.blendweights);
    else
        viewpos = mul(IN.pos, vertexBlendPalette[0]);

    // Fragment colour routing
    OUT.alpha = vertexMaterial(IN.color).a;

    // Transform and output depth
    OUT.pos = mul(viewpos, proj);
    OUT.depth = OUT.pos.w;
    OUT.texcoords = IN.texcoords;

    return OUT;
}

float4 DepthNearPS(DepthVertOut IN) : COLOR0 {
    clip(nearViewRange + 64.0 - IN.depth);

    // Respect alpha test
    if(hasAlpha) {
        float alpha = IN.alpha * tex2D(sampBaseTex, IN.texcoords).a;
        clip(alpha - alphaRef);
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
        FillMode = Solid;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        StencilEnable = false;
        FogEnable = false;
        Lighting = false;

        VertexShader = compile vs_3_0 DepthClearVS();
        PixelShader = compile ps_3_0 DepthClearPS();
    }
    //------------------------------------------------------------
    // Used for rendering scene depth
    Pass D1 {
        ZEnable = true;
        ZWriteEnable = true;
        ZFunc = LessEqual;
        CullMode = CW;
        ClipPlaneEnable = 0;
        FillMode = Solid;

        AlphaBlendEnable = false;
        AlphaTestEnable = false;
        StencilEnable = false;
        FogEnable = false;
        Lighting = false;

        VertexShader = compile vs_3_0 DepthMWVS();
        PixelShader = compile ps_3_0 DepthNearPS();
    }
    //------------------------------------------------------------
    // Used for rendering distant land depth
    Pass D2 {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = CW;

        VertexShader = compile vs_3_0 DepthLandVS();
        PixelShader = compile ps_3_0 DepthLandPS();
    }
   //------------------------------------------------------------
   // Used for rendering distant statics depth
    Pass D3 {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = CW;

        VertexShader = compile vs_3_0 DepthStaticVS();
        PixelShader = compile ps_3_0 DepthStaticPS();
    }
   //------------------------------------------------------------
   // Used for rendering grass depth
    Pass D4i {
        ZEnable = true;
        ZWriteEnable = true;
        CullMode = none;

        VertexShader = compile vs_3_0 DepthGrassInstVS();
        PixelShader = compile ps_3_0 DepthNearPS();
    }
   //------------------------------------------------------------
}
