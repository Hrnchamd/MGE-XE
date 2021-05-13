
// XE Mod Statics.fx
// MGE XE 0.12.1
// Distant statics rendering. Can be used as a core mod.


//------------------------------------------------------------
// Statics rendering

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
    normal = mul(normal, world);
    
    // Lighting
    float emissive = IN.normal.w; // Emissive stored in 4th value in normal vector
    float3 light = SunCol * saturate(dot(normal.xyz, -SunVec)) + SunAmb + emissive;
    OUT.color = float4(IN.color.rgb * light, IN.color.a);

    OUT.texcoords_range = float3(IN.texcoords, dist);
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
    float dist = length(eyevec);
    OUT.fog = fogMWColour(dist);

    // Decompress normal
    float4 normal = float4(normalize(2 * IN.normal.xyz - 1), 0);
    normal = mul(normal, world);
    
    // Lighting
    float emissive = IN.normal.w; // Emissive stored in 4th value in normal vector
    float3 light = SunCol * saturate(dot(normal.xyz, -SunVec)) + SunAmb + emissive;
    OUT.color = float4(IN.color.rgb * light, IN.color.a);

    OUT.texcoords_range = float3(IN.texcoords, dist);
    return OUT;
}

float4 StaticPS (StatVertOut IN): COLOR0
{
    float2 texcoords = IN.texcoords_range.xy;
    float range = IN.texcoords_range.z;
    
    float4 result = tex2D(sampBaseTex, texcoords);
    result.rgb *= IN.color.rgb;
    result.rgb = fogApply(result.rgb, IN.fog);
    
    // Alpha to coverage conversion
    result.a = calc_coverage(result.a, 133.0/255.0, 2.0);
    
    return result;
}

//------------------------------------------------------------
// Depth buffer output

DepthVertOut DepthStaticVS (StatVertIn IN)
{
    DepthVertOut OUT;

    OUT.pos = mul(IN.pos, world);
    OUT.pos = mul(OUT.pos, view);
    OUT.pos = mul(OUT.pos, proj);

    OUT.depth = OUT.pos.w;
    OUT.alpha = 1;
    OUT.texcoords = IN.texcoords;

    return OUT;
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