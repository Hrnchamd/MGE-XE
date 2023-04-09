
// XE Mod Grass.fx
// MGE XE 0.16.0
// Grass rendering. Can be used as a core mod.


//------------------------------------------------------------
// Grass displacement function, based on wind and player proximity

float2 grassDisplacement(float4 worldpos, float h) {
    float v = length(windVec);
    float2 displace = 2 * windVec + 0.1;
    float2 harmonics = 0;

    harmonics += (1 - 0.10*v) * sin(1.0*time + worldpos.xy / 1104);
    harmonics += (1 - 0.04*v) * cos(2.0*time + worldpos.xy / 751);
    harmonics += (1 + 0.14*v) * sin(3.0*time + worldpos.xy / 526);
    harmonics += (1 + 0.28*v) * sin(5.0*time + worldpos.xy / 209);

    float d = length(worldpos.xy - footPos.xy);
    d += pow(0.06 * max(0, footPos.z - worldpos.z - 60), 2);
    float2 stomp = 0;

    if(d < 150) {
        stomp = (60 / d - 0.4) * (worldpos.xy - footPos.xy);
    }

    return saturate(0.02 * h) * (harmonics * displace + stomp);
}

//------------------------------------------------------------
// Common functions

TransformedVert transformGrassVert(StatVertInstIn IN) {
    TransformedVert v;

    v.worldpos = instancedMul(IN.pos, IN.world0, IN.world1, IN.world2);

    // Transforms with wind displacement
    v.worldpos.xy += grassDisplacement(v.worldpos, IN.pos.z);
    v.viewpos = mul(v.worldpos, view);
    v.pos = mul(v.viewpos, proj);

    // Decompress normal
    float4 normal = float4(normalize(2 * IN.normal.xyz - 1), 0);
    v.normal = instancedMul(normal, IN.world0, IN.world1, IN.world2);
    return v;
}

//------------------------------------------------------------
// Grass

struct GrassVertOut {
    float4 pos : POSITION;
    half2 texcoords : TEXCOORD0;
    centroid half4 color : COLOR0;
    centroid half4 fog : COLOR1;

    float4 shadow0pos : TEXCOORD1;
    float4 shadow1pos : TEXCOORD2;
};

GrassVertOut GrassInstVS(StatVertInstIn IN) {
    GrassVertOut OUT;
    TransformedVert v = transformGrassVert(IN);
    float3 eyevec = v.worldpos.xyz - eyePos.xyz;

    OUT.pos = v.pos;
    OUT.fog = fogMWColour(length(eyevec));

    // Lighting for two-sided rendering, no emissive
    float lambert = dot(v.normal.xyz, -sunVec) * -sign(dot(eyevec, v.normal.xyz));
    // Backscatter through thin cover
    if(lambert < 0) {
        lambert *= -0.3;
    }

    // Ignoring vertex colour due to problem with some grass mods
    OUT.color.rgb = sunCol * lambert + sunAmb;

    // Non-standard shadow luminance, to create sufficient contrast when ambient is high
    OUT.color.a = shadowSunEstimate(lambert);

    // Find position in light space, output light depth
    OUT.shadow0pos = mul(v.worldpos, shadowViewProj[0]);
    OUT.shadow1pos = mul(v.worldpos, shadowViewProj[1]);
    OUT.shadow0pos.z = OUT.shadow0pos.z / OUT.shadow0pos.w;
    OUT.shadow1pos.z = OUT.shadow1pos.z / OUT.shadow1pos.w;

    OUT.texcoords = IN.texcoords;
    return OUT;
}

float4 GrassPS(GrassVertOut IN): COLOR0 {
    float4 result = tex2D(sampBaseTex, IN.texcoords);
    result.rgb *= IN.color.rgb;

    // Alpha test early
    // Note: clip is not used here because at certain optimization levels,
    // the texkill is pushed to the very end of the function
    if(result.a < 64.0/255.0)
        discard;

    // Soft shadowing
    float dz = shadowDeltaZ(IN.shadow0pos, IN.shadow1pos);
    float v = shadowESM(dz);

    // Darken shadow area according to existing lighting (slightly towards blue)
    v *= IN.color.a;
    result.rgb *= 1 - v * shadecolor;

    // Fogging
    result.rgb = fogApply(result.rgb, IN.fog);

    // Alpha to coverage conversion
    result.a = calc_coverage(result.a, 128.0/255.0, 4.0);

    return result;
}

//------------------------------------------------------------
// Depth buffer output


DepthVertOut DepthGrassInstVS(StatVertInstIn IN) {
    DepthVertOut OUT;
    TransformedVert v = transformGrassVert(IN);

    OUT.pos = v.pos;
    OUT.depth = v.pos.w;
    OUT.alpha = 1;
    OUT.texcoords = IN.texcoords;

    return OUT;
}