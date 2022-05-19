// Bloom, fine
// Hrnchamd
// v2

// Compatibility: MGE XE 0, fully working

//////////////
// Settings //
//////////////

static const float bloomThreshold = 0.48;     // 0.0 everything blooms <-> 1.0 nothing blooms
static const float bloomLevel = 0.23;         // 0.0 minimum glow <-> 1.0 nuclear shine
static const float bloomColourSens = 0.39;    // 0.0 monochrome <-> 1.0 oversaturated
static const float bloomGamma = 2.45;         // for linear domain mixing (Morrowind is somewhat dark)



float2 rcpres;
float fogstart, fogrange;

texture lastshader, lastpass, depthframe;

sampler s0 = sampler_state { texture = <lastshader>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };
sampler s1 = sampler_state { texture = <lastpass>; addressu = clamp; addressv = clamp; magfilter = linear; minfilter = linear; };
sampler s2 = sampler_state { texture = <depthframe>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };



float4 sample0(sampler2D s, float2 t)
{
    return tex2Dlod(s, float4(t, 0, 0));
}

float4 energyLevels(in float2 Tex : TEXCOORD) : COLOR0
{
    float4 radiance = sample0(s0, Tex);
    float depth = sample0(s2, Tex);
    float lum = dot(float3(0.27, 0.54, 0.19), radiance.rgb);

    // Mix with luminance to avoid oversaturated single channels
    radiance = lerp(lum, radiance, bloomColourSens);

    // Cut sky/distant illumination down
    radiance *= 1 - 0.45 * saturate(2 * (depth - fogstart) / (fogrange - fogstart));

    return saturate(radiance - bloomThreshold);
}

static const int N = 7;
static const float kernel[N] = { 0.05, 0.14, 0.31, 0.22, 0.31, 0.14, 0.05 };
static const float taps[N] = { -6.5, -4.5, -2.5, 0, 2.5, 4.5, 6.5 };

float4 blurVert(in float2 Tex : TEXCOORD) : COLOR0
{
    float4 radiance = 0;
    
    for(int i = 0; i < N; ++i)
        radiance += kernel[i] * sample0(s1, Tex + float2(0, rcpres.y * taps[i]));

    return radiance;
}

float4 blurHorzCombine(in float2 Tex : TEXCOORD) : COLOR0
{
    float4 base = sample0(s0, Tex);
    float4 radiance = 0;
    
    for(int i = 0; i < N; ++i)
        radiance += kernel[i] * sample0(s1, Tex + float2(rcpres.x * taps[i], 0));

    // Mix in linear space
    base = pow(base, bloomGamma);
    return pow(base + bloomLevel * radiance, 1.0/bloomGamma);
}

technique T0 < string MGEinterface = "MGE XE 0"; string category = "sensor"; >
{
    pass { PixelShader = compile ps_3_0 energyLevels(); }
    pass { PixelShader = compile ps_3_0 blurVert(); }
    pass { PixelShader = compile ps_3_0 blurHorzCombine(); }
}
