
// XE FixedFuncEmu.fx
// MGE XE 0.16.0
// Replacement shaders for Morrowind's object rendering

#include "XE Common.fx"

shared texture tex4, tex5;
shared matrix worldview;
shared float4 materialDiffuse, materialAmbient, materialEmissive;
shared float3 lightSceneAmbient, lightSunDiffuse, lightDiffuse[8];
shared float4 lightAmbient[2];
shared float3 lightSunDirection;
shared float4 lightPosition[6];
shared float4 lightFalloffQuadratic[2], lightFalloffLinear[2];
shared float lightFalloffConstant;
shared matrix texgenTransform;
shared float4 bumpMatrix;
shared float2 bumpLumiScaleBias;

sampler sampFFE0 = sampler_state { texture = <tex0>; };
sampler sampFFE1 = sampler_state { texture = <tex1>; };
sampler sampFFE2 = sampler_state { texture = <tex2>; };
sampler sampFFE3 = sampler_state { texture = <tex3>; };
sampler sampFFE4 = sampler_state { texture = <tex4>; };
sampler sampFFE5 = sampler_state { texture = <tex5>; };

//------------------------------------------------------------

#ifdef VERIFY
#define FFE_VB_COUPLING float2 texcoord0 : TEXCOORD0; float4 col : COLOR;
#define FFE_SHADER_COUPLING float4 texcoord01 : TEXCOORD0; float4 col : COLOR;
#define FFE_TRANSFORM_SKIN viewpos = rigidVertex(IN.pos); normal = rigidNormal(IN.nrm);
#define FFE_TEXCOORDS_TEXGEN float3 texgen = texgenReflection(viewpos, normal); texgen = mul(float4(texgen, 1), texgenTransform).xyz; OUT.texcoord01 = float4(IN.texcoord0, texgen.xy);
#define FFE_VERTEX_COLOUR OUT.col = IN.col;
#define FFE_LIGHTS_ACTIVE 8
#define FFE_VERTEX_MATERIAL diffuse = vertexMaterialDiffAmb(d, a, IN.col);
#define FFE_TEXTURING c = diffuse + bumpmapLumiStage(sampFFE1, IN.texcoord01.zw, tex2D(sampFFE0, IN.texcoord01.xy));
#define FFE_FOG_APPLICATION c.rgb = lerp(fogColNear, c.rgb, fog);
#endif

#ifdef FFE_ERROR_MATERIAL
#define FFE_VB_COUPLING
#define FFE_SHADER_COUPLING
#define FFE_TRANSFORM_SKIN viewpos = rigidVertex(IN.pos); normal = float3(0, 0, 1);
#define FFE_TEXCOORDS_TEXGEN
#define FFE_VERTEX_COLOUR
#define FFE_LIGHTS_ACTIVE 0
#define FFE_VERTEX_MATERIAL diffuse = float4(1, 0, 0.5, 1);
#define FFE_TEXTURING
#define FFE_FOG_APPLICATION c.rgb = lerp(fogColNear, c.rgb, fog);
#endif


//------------------------------------------------------------
// Transform library functions

// Vertex transform to view space, note that scaled normals are normalized in the pixel shader
float4 rigidVertex(float4 pos) { return mul(pos, worldview); }
float3 rigidNormal(float3 normal) { return mul(float4(normal, 0), worldview).xyz; }

float4 skinnedVertex(float4 pos, float4 weights) { return skin(pos, weights); }
float3 skinnedNormal(float3 normal, float4 weights) { return skin(float4(normal, 0), weights).xyz; }

// Texgens with view space inputs, normals must be normalized due to non-uniform scaling matrices
float3 texgenNormal(float3 normal) { return normalize(normal); }
float3 texgenPosition(float4 pos) { return pos.xyz; }
float3 texgenReflection(float4 pos, float3 normal) { return reflect(normalize(pos.xyz), normalize(normal)); }
float3 texgenSphere(float2 tex) { return float3(0.5 * tex + 0.5, 0); }

//------------------------------------------------------------
// Lighting library functions

// Number of light groups; lights are vectorized into groups of 4
static const int LGs = max(1, ceil(FFE_LIGHTS_ACTIVE / 4.0));

// Point lights
float4 calcLighting4(float4 lightvec[3*LGs], int group, float3 normal) {
    float4 dist2 = 0, lambert = 0;

    // Do four dot products as three mads
    for(int i = 0; i != 3; ++i)
        dist2 += pow(lightvec[3*group + i], 2);

    // Same for N.L
    for(int i = 0; i != 3; ++i)
        lambert += normal[i] * lightvec[3*group + i];

    // Normalize L after the fact
    float4 dist = sqrt(dist2);
    lambert = saturate(lambert / dist);

    // Attenuation
    float4 att = 1.0 / (lightFalloffQuadratic[group] * dist2 + lightFalloffConstant);
    // (slower) float4 att = 1.0 / (lightFalloffQuadratic[group] * dist2 + lightFalloffLinear[group] * dist + lightFalloffConstant);
    return (lambert + lightAmbient[group]) * att;
}

float3 calcPointLighting(uniform int lights, float4 lightvec[3*LGs], float3 normal) {
    float4 lambert[LGs];
    float3 l = 0;

    for(int i = 0; i != LGs; ++i)
        lambert[i] = calcLighting4(lightvec, i, normal);

    for(int i = 0; i != lights; ++i)
        l += lambert[i/4][i%4] * lightDiffuse[i];

    return l;
}

// Static tonemap
float3 tonemap(float3 c) {
    // Curve maps 0 -> 0, 1.0 -> 0.84, up to 2.2 -> 1.0
    c = clamp(c, 0, 2.2);
    c = (((0.0548303 * c - 0.189786) * c - 0.154732) * c + 1.12969) * c;
    return c;
}

// Vertex material routing
float4 vertexMaterialNone(float3 d, float3 a) {
    return float4(materialDiffuse.rgb * d + materialAmbient.rgb * a + materialEmissive.rgb, materialDiffuse.a);
}

float4 vertexMaterialDiffAmb(float3 d, float3 a, float4 col) {
    return float4(col.rgb * (d + a) + materialEmissive.rgb, col.a);
}

float4 vertexMaterialEmissive(float3 d, float3 a, float4 col) {
    return float4(materialDiffuse.rgb * d + materialAmbient.rgb * a + col.rgb, materialDiffuse.a);
}

// Bumpmap stages return dUdV alpha channel due to select1 alpha op
float4 bumpmapStage(sampler s, float2 tc, float4 dUdV) {
    float2 offset = mul(dUdV.rg, float2x2(bumpMatrix.xy, bumpMatrix.zw));
    return float4(tex2D(s, tc + offset).rgb, dUdV.a);
}

float4 bumpmapLumiStage(sampler s, float2 tc, float4 dUdVL) {
    float4 c = bumpmapStage(s, tc, dUdVL);
    c.rgb *= saturate(dUdVL.b * bumpLumiScaleBias.x + bumpLumiScaleBias.y);
    return c;
}

//------------------------------------------------------------
// Data coupling framework

struct FFEVertIn {
    float4 pos : POSITION;
    float3 nrm : NORMAL;

    /* template */ FFE_VB_COUPLING
};

struct FFEPixel {
    float4 pos : POSITION;
    centroid float4 nrm_fog : NORMAL;

    /* template */ FFE_SHADER_COUPLING

    float4 lightvec[3*LGs] : TEXCOORD2;
};

//------------------------------------------------------------
// Shader framework

// Relatively simple, notably passes lighting vectors in interpolators
FFEPixel PerPixelVS(FFEVertIn IN) {
    FFEPixel OUT;

    // Transforms
    float4 viewpos;
    float3 normal;
    /* template */ FFE_TRANSFORM_SKIN

    float dist = length(viewpos);
    OUT.pos = mul(viewpos, proj);
    OUT.nrm_fog = float4(normal, fogMWScalar(dist));

    // Texcoord routing and texgen
    /* template */ FFE_TEXCOORDS_TEXGEN

    // Vertex colour
    /* template */ FFE_VERTEX_COLOUR

    // Point lighting setup, vectorized
    for(int i = 0; i != LGs; ++i) {
        OUT.lightvec[3*i + 0] = lightPosition[i + 0] - viewpos.x;
        OUT.lightvec[3*i + 1] = lightPosition[i + 2] - viewpos.y;
        OUT.lightvec[3*i + 2] = lightPosition[i + 4] - viewpos.z;
    }

    return OUT;
}

// Per-pixel lighting augmented with semi-HDR tonemap instead of light clamping
float4 PerPixelPS(FFEPixel IN) : COLOR0 {
    float3 normal = normalize(IN.nrm_fog.xyz);
    float fog = IN.nrm_fog.w;

    // Standard morrowind lighting: sun, ambient, and point lights
    float3 d = lightSunDiffuse * saturate(dot(normal, -lightSunDirection));
    float3 a = lightSceneAmbient;
    d += calcPointLighting(FFE_LIGHTS_ACTIVE, IN.lightvec, normal);

    // Material
    float4 diffuse;
    /* template */ FFE_VERTEX_MATERIAL

    // Texturing and combinators
    float4 c = diffuse;
    /* template */ FFE_TEXTURING

    // Static tonemap and final fogging
    c.rgb = tonemap(c.rgb);
    /* template */ FFE_FOG_APPLICATION

    return c;
}

//-----------------------------------------------------------------------------

technique FFE {
    pass {
        VertexShader = compile vs_3_0 PerPixelVS();
        PixelShader = compile ps_3_0 PerPixelPS();
    }
}
