
// XE Mod Landscape.fx
// MGE XE 0.16.0
// Distant landscape rendering. Can be used as a core mod.


//------------------------------------------------------------
// Common functions

TransformedVert transformLandVert(float4 pos) {
    TransformedVert v;

    v.viewpos = mul(mul(pos, world), view);
    v.pos = mul(v.viewpos, proj);
    return v;
}

//------------------------------------------------------------
// Distant land height bias to prevent low lod meshes from clipping

float landBias(float dist) {
    float maxDist = nearViewRange - 1152;
    return -30 + -2 * max(0, maxDist - dist);
}

//------------------------------------------------------------
// Distant landscape rendering

struct LandVertOut {
    float4 pos: POSITION;
    float2 texcoord: TEXCOORD0;
    centroid float4 fog : TEXCOORD1;
};

LandVertOut LandscapeVS(float4 pos : POSITION, float2 texcoord : TEXCOORD0) {
    LandVertOut OUT;

    // Fogging
    float3 eyevec = mul(pos, world).xyz - eyePos.xyz;
    float dist = length(eyevec);
    OUT.fog = fogColour(eyevec / dist, dist);

    // Move land down to avoid it appearing where reduced mesh doesn't match
    pos.z += landBias(dist);

    // Transforms
    TransformedVert v = transformLandVert(pos);
    OUT.pos = v.pos;
    OUT.texcoord = texcoord;
    return OUT;
}

LandVertOut LandscapeReflVS(float4 pos : POSITION, float2 texcoord : TEXCOORD0) {
    LandVertOut OUT;

    // Fogging
    float3 eyevec = mul(pos, world).xyz - eyePos.xyz;
    float dist = length(eyevec);
    if(isAboveSeaLevel(eyePos))
        OUT.fog = fogColour(eyevec / dist, dist);
    else
        OUT.fog = fogMWColour(dist);

    // Sink land near waterline a small amount
    pos.z += -16 * saturate(1 - pos.z/16);

    // Transforms
    TransformedVert v = transformLandVert(pos);
    OUT.pos = v.pos;
    OUT.texcoord = texcoord;
    return OUT;
}

float4 LandscapePS(LandVertOut IN) : COLOR0 {
    // Expand and normalize normal map
    float3 normal = normalize(2 * tex2D(sampNormals, IN.texcoord).rgb - 1);

    // World texture
    float3 result = tex2D(sampBaseTex, IN.texcoord).rgb;

    // Detail texture
    float detail = tex2D(sampDetail, IN.texcoord * 333).g + 0.5;
    detail *= 0.5 * tex2D(sampDetail, IN.texcoord * 90).g + 0.75;

    // Lighting
    result *= sunCol * saturate(dot(-sunVec, normal)) + sunAmb;
    result *= detail;

    // Fogging
    result = fogApply(result, IN.fog);
    return float4(result, 1);
}

DepthVertOut DepthLandVS(float4 pos: POSITION, float2 texcoord: TEXCOORD0) {
    DepthVertOut OUT;

    // Move land down to avoid it appearing where reduced mesh doesn't match
    pos.z += landBias(length(pos.xyz - eyePos.xyz));

    TransformedVert v = transformLandVert(pos);
    OUT.pos = v.pos;
    OUT.depth = v.pos.w;
    OUT.alpha = 1;
    OUT.texcoords = texcoord;

    return OUT;
}

float4 DepthLandPS(DepthVertOut IN) : COLOR0 {
    clip(IN.depth - nearViewRange);
    return IN.depth;
}