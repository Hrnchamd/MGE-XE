
// XE Mod Grass.fx
// MGE XE 0.12.1
// Grass rendering. Can be used as a core mod.


//------------------------------------------------------------
// Grass, wind displacement function

float2 grassDisplacement(float4 worldpos, float h)
{
    float v = length(WindVec);
    float2 displace = 2 * WindVec + 0.1;
    float2 harmonics = 0;
    
    harmonics += (1 - 0.10*v) * sin(1.0*time + worldpos.xy / 1100);
    harmonics += (1 - 0.04*v) * cos(2.0*time + worldpos.xy / 750);
    harmonics += (1 + 0.14*v) * sin(3.0*time + worldpos.xy / 500);
    harmonics += (1 + 0.28*v) * sin(5.0*time + worldpos.xy / 200);

    float d = length(worldpos.xy - FootPos.xy);
    float2 stomp = 0;
    
    if(d < 150)
        stomp = (60 / d - 0.4) * (worldpos.xy - FootPos.xy);

    return saturate(0.02 * h) * (harmonics * displace + stomp);
}

//------------------------------------------------------------
// Grass

struct GrassVertOut
{
    float4 pos : POSITION;
    half2 texcoords : TEXCOORD0;
    half4 color : COLOR0;
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
    normal = instancedMul(normal, IN.world0, IN.world1, IN.world2);

    // Lighting for two-sided rendering, no emissive
    float lambert = dot(normal.xyz, -SunVec) * -sign(dot(eyevec, normal.xyz));
    // Backscatter through thin cover
    if(lambert < 0)
        lambert *= -0.3;
    
    // Ignoring vertex colour due to problem with some grass mods
    OUT.color.rgb = SunCol * lambert + SunAmb;

    // Non-standard shadow luminance, to create sufficient contrast when ambient is high
    OUT.color.a = shadowSunEstimate(lambert);

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
    OUT.alpha = 1;
    OUT.texcoords = IN.texcoords;

    return OUT;
}