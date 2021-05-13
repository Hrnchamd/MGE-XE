
// XE Mod Statics.fx
// MGE XE 0.12.1
// Distant statics rendering. Can be used as a core mod.


//------------------------------------------------------------
// Common functions

TransformedVert transformStaticVert(StatVertIn IN) {
    // Transforms with implicit depth bias
    TransformedVert v;
    
    v.worldpos = mul(IN.pos, world);
    v.viewpos = mul(v.worldpos, view);
    v.pos = mul(v.viewpos, proj);
    return v;
}

float4 lightStaticVert(StatVertIn IN) {
    // Decompress normal
    float4 normal = float4(normalize(2 * IN.normal.xyz - 1), 0);
    normal = mul(normal, world);
    
    // Lighting (worldspace)
    // Emissive is stored in the 4th value of the normal vector
    float emissive = IN.normal.w;
    float3 light = SunCol * saturate(dot(normal.xyz, -SunVec)) + SunAmb + emissive;

    return float4(IN.color.rgb * light, IN.color.a);
}

//------------------------------------------------------------
// Statics rendering

StatVertOut StaticExteriorVS(StatVertIn IN) {
    StatVertOut OUT;
    TransformedVert v = transformStaticVert(IN);
    OUT.pos = v.pos;
    OUT.color = lightStaticVert(IN);

    // Fogging (exterior)
    float3 eyevec = v.worldpos.xyz - EyePos.xyz;
    float dist = length(eyevec);
    OUT.fog = fogColour(eyevec / dist, dist);

    OUT.texcoords_range = float3(IN.texcoords, dist);
    return OUT;
}

StatVertOut StaticInteriorVS (StatVertIn IN) {
    StatVertOut OUT;
    TransformedVert v = transformStaticVert(IN);
    OUT.pos = v.pos;
    OUT.color = lightStaticVert(IN);

    // Fogging (interior)
    float dist = length(v.viewpos.xyz);
    OUT.fog = fogMWColour(dist);

    OUT.texcoords_range = float3(IN.texcoords, dist);
    return OUT;
}

float4 StaticPS (StatVertOut IN): COLOR0 {
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

DepthVertOut DepthStaticVS (StatVertIn IN) {
    DepthVertOut OUT;

    TransformedVert v = transformStaticVert(IN);
    OUT.pos = v.pos;

    OUT.depth = OUT.pos.w;
    OUT.alpha = 1;
    OUT.texcoords = IN.texcoords;

    return OUT;
}

float4 DepthStaticPS (DepthVertOut IN) : COLOR0 {
    clip(IN.depth - nearViewRange);

    if(hasalpha) {
        float alpha = tex2D(sampBaseTex, IN.texcoords).a;
        clip(alpha - 133.0/255.0);
    }
    return IN.depth;
}