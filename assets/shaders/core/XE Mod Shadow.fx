
// XE Mod Shadow.fx
// MGE XE 0.16.0
// Shadow receiver functions. Can be used as a core mod.

#include "XE Mod Shadow Data.fx"



//------------------------------------------------------------
// Texture atlas

// Clip space margin of 4 texels, to prevent bleeding from the filter kernel + adjacent textures
// Clip space limits are -1 to +1, so texel dimensions are multiplied by two here
static float3 atlasMargin = float3(1-2*4*shadowRcpRes, 1-2*4*shadowRcpRes, 1);

// Shadow UV to shadow atlas UV
float4 mapShadowToAtlas(float2 t, int layer) {
    // Result is intended for use with tex2Dlod
    return float4(t.x * shadowCascadeSize + layer * shadowCascadeSize, t.y, 0, 0);
}

//------------------------------------------------------------
// Incoming vertex sunlight estimation

float shadowSunEstimate(float lambert) {
    float x = lambert * dot(sunCol, float3(0.36, 0.53, 0.11));
    x *= 0.25 + 0.75 * sunVis;
    return x / (shade + x);
}

TransformedVert transformShadowVert(MorrowindVertIn IN) {
    TransformedVert v;
    float4 normal = float4(IN.normal.xyz, 0);

    // Skin mesh if required
    if(hasBones) {
        v.viewpos = skin(IN.pos, IN.blendweights);
        v.normal = normalize(skin(normal, IN.blendweights));
    }
    else {
        v.viewpos = mul(IN.pos, vertexBlendPalette[0]);
        v.normal = mul(normal, vertexBlendPalette[0]);
    }

    v.pos = mul(v.viewpos, proj);
    return v;
}

//------------------------------------------------------------
// 2 layer cascade ortho ESM lookup

float shadowDeltaZ(float4 shadow0pos, float4 shadow1pos) {
    float dz = 1e-6;

    [branch] if(all(saturate(atlasMargin - abs(shadow0pos.xyz)))) {
        // Layer 0, inner
        float2 shadowUV = (0.5 + 0.5*shadowRcpRes) + float2(0.5, -0.5) * shadow0pos.xy;
        dz = tex2Dlod(sampDepth, mapShadowToAtlas(shadowUV, 0)).r / ESM_scale - shadow0pos.z;
    }
    else if(all(saturate(atlasMargin - abs(shadow1pos.xyz)))) {
        // Layer 1
        float2 shadowUV = (0.5 + 0.5*shadowRcpRes) + float2(0.5, -0.5) * shadow1pos.xy;
        dz = tex2Dlod(sampDepth, mapShadowToAtlas(shadowUV, 1)).r / ESM_scale - shadow1pos.z;
    }

    return dz;
}

float shadowESM(float dz) {
    return 1 - saturate(exp(ESM_c * dz + ESM_bias));
}

//------------------------------------------------------------
// Shadow reciever rendering

struct RenderShadowVertOut {
    float4 pos: POSITION;
    half2 texcoords: TEXCOORD0;
    centroid float light: COLOR0;
    centroid float alpha: COLOR1;

    float4 shadow0pos: TEXCOORD1;
    float4 shadow1pos: TEXCOORD2;
};

RenderShadowVertOut RenderShadowsBaseVS(MorrowindVertIn IN) {
    RenderShadowVertOut OUT;
    TransformedVert v = transformShadowVert(IN);

    OUT.pos = v.pos;

    // Fragment colour routing
    OUT.alpha = vertexMaterial(IN.color).a;

    // Non-standard shadow luminance, to create sufficient contrast when ambient is high
    OUT.light = shadowSunEstimate(saturate(dot(v.normal.xyz, -sunVecView)));

    // Fog attenuation (shadow darkness and distance fade)
    float fogatt = pow(fogMWScalar(OUT.pos.w), 2);
    if(isAboveSeaLevel(eyePos))
        OUT.light *= fogatt;
    else
        OUT.light *= saturate(4 * fogatt);

    // Find position in light space, output light depth
    OUT.shadow0pos = mul(v.viewpos, shadowViewProj[0]);
    OUT.shadow1pos = mul(v.viewpos, shadowViewProj[1]);
    OUT.shadow0pos.z = OUT.shadow0pos.z / OUT.shadow0pos.w;
    OUT.shadow1pos.z = OUT.shadow1pos.z / OUT.shadow1pos.w;

    OUT.texcoords = IN.texcoords;
    return OUT;
}

RenderShadowVertOut RenderShadowsVS(MorrowindVertIn IN) {
    RenderShadowVertOut OUT = RenderShadowsBaseVS(IN);

    // Depth bias to mitigate difference between FFP and VS
    OUT.pos.z *= 1 - 2e-6;
    OUT.pos.z -= clamp(0.05 / OUT.pos.w, 0, 1e-3);
    return OUT;
}

RenderShadowVertOut RenderShadowsFFEVS(MorrowindVertIn IN) {
    return RenderShadowsBaseVS(IN);
}

float4 RenderShadowsPS(RenderShadowVertOut IN): COLOR0 {
    // Early reject unlit areas
    clip(IN.light - 2.0/255.0);

    // Respect alpha test
    float alpha = IN.alpha;
    if(hasAlpha) {
        alpha *= tex2D(sampBaseTex, IN.texcoords).a;
        clip(alpha - alphaRef);
    }

    // Soft shadowing
    float dz = shadowDeltaZ(IN.shadow0pos, IN.shadow1pos);
    clip(-dz);
    float v = shadowESM(dz) * IN.light * alpha;
    
    // Fade out shadows at map edges
    float2 fade = saturate(25 * (1 - abs(IN.shadow1pos.xy)));
    v = v * fade.x * fade.y;

    // Darken shadow area according to existing lighting (slightly towards blue)
    clip(v - 2.0/255.0);
    return float4(v * shadecolor, 1);
}
