
// XE Mod Caustics.fx
// MGE XE 0.16.0
// Outdoor water caustics. Can be used as a core mod.


//------------------------------------------------------------
// Caustics post-process

// Note: causticsStrength may be defined in another fx file, so cannot be used here to avoid multiple declarations
static const float causticsSunlightFactor = 1 - pow(1 - sunVis, 2);
static const float causticsStrengthScalar = 0.05 * alphaRef * saturate(0.75 * causticsSunlightFactor + 0.35 * length(fogColFar));

DeferredOut CausticsVS(float4 pos : POSITION, float2 tex : TEXCOORD0, float2 ndc : TEXCOORD1)
{
    DeferredOut OUT;

    // Fix D3D9 half pixel offset
    OUT.pos = float4(ndc.x - rcpRes.x, ndc.y + rcpRes.y, 0, 1);
    OUT.tex = float4(tex, 0, 0);

    // World space reconstruction vector
    OUT.eye = float3(view[0][2], view[1][2], view[2][2]);
    OUT.eye += (ndc.x / proj[0][0]) * float3(view[0][0], view[1][0], view[2][0]);
    OUT.eye += (ndc.y / proj[1][1]) * float3(view[0][1], view[1][1], view[2][1]);
    return OUT;
}

float4 CausticsPS(DeferredOut IN) : COLOR0
{
    float3 c = tex2Dlod(sampBaseTex, IN.tex).rgb;
    float depth = tex2Dlod(sampDepthPoint, IN.tex).r;
    float fog = fogMWScalar(depth);

    clip(nearViewRange - depth);

    float3 uwpos = eyePos + IN.eye * depth;
    uwpos.z -= waterLevel;
    clip(-uwpos.z);

    float3 sunray = uwpos - sunVec * (uwpos.z / sunVec.z);
    float caust = causticsStrengthScalar * tex3D(sampWater3d, float3(sunray.xy / 1104, 0.4 * time)).b;
    caust *= saturate(125 / depth * min(fwidth(sunray.x), fwidth(sunray.y)));
    c *= 1 + (caust - 0.3) * saturate(exp(uwpos.z / 400)) * saturate(uwpos.z / -30) * fog;

    return float4(c, 1);
}
