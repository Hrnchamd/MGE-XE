// "HDR" Eye Adaptation, tuned for Morrowind lighting
// Simulates exposure adjustment
// Hrnchamd
// v2

// Compatibility: MGE XE 0, fully working


float4 HDR;
static float exposure = (1 + 1.3 * (0.22 - HDR.x)) * sqrt(HDR.y/HDR.x);

texture lastshader;
sampler s0 = sampler_state { texture = <lastshader>; minfilter = none; magfilter = none; };


float4 tone(float2 tex : TEXCOORD) : COLOR0
{
    float3 c = tex2D(s0, tex).rgb;
    
    // Increase dynamic range in low light
    float3 g = exposure * c + (1-exposure) * pow(c, 8);

    // Film response toe/knee contrast
    // 0.73546x^4 + -2.14391x^3 + 1.78635x^2 + 0.66211x
    g = (((0.73546 * g + -2.14391) * g + 1.78635) * g + 0.66211) * g;

    // exposure meter 
    //if(tex.x < HDR.x && tex.y > 0.9) g = lerp(g, 1, 0.4);
    return float4(saturate(g), 1);
}

technique T0 < string MGEinterface = "MGE XE 0"; bool requiresHDR = true; >
{
    pass { PixelShader = compile ps_3_0 tone(); }
}
