// "HDR" Eye Adaptation, tuned for Morrowind lighting
// Simulates exposure adjustment
// Hrnchamd
// v4

// Compatibility: MGE XE 0, fully working


// #define EXPOSURE_METER

static const float neutral_point = 0.335;
static const float sensitivity = 0.11;
static const float max_exposure = 3.2;

float4 HDR;
static float exposure = clamp(lerp(1, neutral_point / HDR.x, sensitivity), 0.5, max_exposure) * sqrt(HDR.y/HDR.x);
static float scotopic = 0.5 * saturate(exposure / max_exposure - 0.66666);

texture lastshader;
sampler s0 = sampler_state { texture = <lastshader>; minfilter = point; magfilter = point; };


float4 sample0(sampler2D s, float2 t)
{
    return tex2Dlod(s, float4(t, 0, 0));
}

float4 tone(float2 tex : TEXCOORD) : COLOR0
{
    float3 c = sample0(s0, tex).rgb;

    // Increase dynamic range in low light
    float3 g = exposure * c + (1-exposure) * pow(c, 4);

    // Film response toe/knee contrast
    // 0.727408x^4 - 2.05477x^3 + 1.63747x^2 + 0.712032x
    g = (((0.727408 * g + -2.05477) * g + 1.63747) * g + 0.712032) * g;

    // Correct for over-saturation when exposure is high (scotopic vision)
    g = lerp(g, dot(g, 0.33333), scotopic);

    // Exposure meters
    #ifdef EXPOSURE_METER
    // HDR lumi meter
    if(tex.x < HDR.x && tex.y > 0.95) g = lerp(g, 1, 0.2);
    if(abs(tex.x - neutral_point) < 0.004 && tex.y > 0.95) g = lerp(g, 1, 0.14);
    // Exposure multiplier meter
    if(tex.x < exposure/max_exposure && tex.y > 0.9 && tex.y < 0.94) g = lerp(g, 1, 0.2);
    if(abs(tex.x - 1.0/max_exposure) < 0.004 && tex.y > 0.9 && tex.y < 0.94) g = lerp(g, 1, 0.14);
    #endif

    return float4(saturate(g), 1);
}

technique T0 < string MGEinterface = "MGE XE 0"; bool requiresHDR = true; string category = "tone"; >
{
    pass { PixelShader = compile ps_3_0 tone(); }
}
