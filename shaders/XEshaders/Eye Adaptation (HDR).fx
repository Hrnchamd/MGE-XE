// "HDR" Eye Adaptation, tuned for Morrowind lighting
// Simulates exposure adjustment
// Hrnchamd
// v3

// Compatibility: MGE XE 0, fully working


float4 HDR;
static float exposure = (1 + 1.4 * (0.32 - HDR.x)) * sqrt(HDR.y/HDR.x);

texture lastshader;
sampler s0 = sampler_state { texture = <lastshader>; minfilter = none; magfilter = none; };


float4 tone(float2 tex : TEXCOORD) : COLOR0
{
    float3 c = tex2D(s0, tex).rgb;
    
    // Increase dynamic range in low light
    float3 g = exposure * c + (1-exposure) * pow(c, 8);

    // Film response toe/knee contrast
    // 0.727408x^4 - 2.05477x^3 + 1.63747x^2 + 0.712032x
    g = (((0.727408 * g + -2.05477) * g + 1.63747) * g + 0.712032) * g;

    // Exposure meter 
    //if(tex.x < HDR.x && tex.y > 0.9) g = lerp(g, 1, 0.4);
    return float4(saturate(g), 1);
}

technique T0 < string MGEinterface = "MGE XE 0"; bool requiresHDR = true; >
{
    pass { PixelShader = compile ps_3_0 tone(); }
}
