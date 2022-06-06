//Author: peachykeen
//Title: trueBloom g6 - intermediate dev copy (g6.6)
//Pack: MGE Shader Library
//Desc:
//        Adds complex bloom. Simulates the glare of bright areas.

// Compatibility: MGE XE 0, partially working >> Differences underwater

// USER VARS

// Switches
#define BLOOM_QUALITY 3
// This controls the quality of the bloom. 1 is basic, cheap bloom (twice-blurred), 2 is standard g6 quality, and 3 is SM3.0 high-quality bloom.
#define BLOOM_FX_WATER 0
// This turns underwatever effects on (1) and off (0)
#define BLOOM_FX_SKY 0
// Enables/disables blooming the sky (0 excludes sky)
#define BLOOM_FX_DARK 1
// Darkens/lightens scene. On is default (same as previous versions), off will brighten the scene but uses a more accurate divisor
#define BLOOM_FX_HANDS 0
// Enables/disables blooming the player's hands (and usually weapon) (0 excludes these)
#define BLOOM_FX_IWATER 0
// Enables/disables using the underwater and interior multipliers together. As interior water is usually darker, you may want to leave this off



// Bloom
//
// Most of these multipliers are exclusive, except for bloom_mult_global and bloom_mult_uwater. Uwater can combine with all others.

static const float bloom_mult_global = 0.22f; // The overall multiplier for bloom. Effects all areas.
static const float bloom_mult_uwater = 1.2f; // Underwater mutliplier for bloom. Only takes effect when the camera is underwater.
static const float bloom_mult_inside = 1.1f; // Interior multiplier for bloom. Can combine with bloom_mult_uwater when both are true.
static const float bloom_mult_outside = 0.8f; // Exterior multiplier for bloom. Can combine with bloom_mult_uwater when both are true.

static const float bloom_cutoff = 0.72f; // Effects the strength and focus of highlights (higher produces softer, weaker highlights).
static const float bloom_power = 1.1f; // Effects the focus and hue of highlights (higher creates more narrow, single-color highlights).



texture lastpass;
texture lastshader;

float3 eyepos;
vector rcpres;
float fogrange, fogstart;
bool isInterior, isUnderwater;

sampler s0 = sampler_state { texture = <lastshader>; minfilter = linear; magfilter = linear; addressu = mirror; addressv = mirror; };
sampler s1 = sampler_state { texture = <lastpass>; minfilter = linear; magfilter = linear; addressu = mirror; addressv = mirror; };

#if ( ( BLOOM_FX_SKY != 1 ) || ( BLOOM_FX_HANDS != 1 ) )
    texture depthframe;
    sampler sDepth = sampler_state { texture = <depthframe>; minfilter = point; magfilter = point; addressu = clamp; addressv = clamp; };
#endif


float4 sample0(sampler2D s, float2 t)
{
    return tex2Dlod(s, float4(t, 0, 0));
}

float4 blurHorI(in float2 Tex : TEXCOORD) : COLOR0
{ // a simple 7-sample horizontal blur pass
    #if ( ( BLOOM_FX_SKY != 1 ) || ( BLOOM_FX_HANDS != 1 ) )
    #define TSAMP s1
    #else
    #define TSAMP s0
    #endif

    float4 Color = sample0(TSAMP, Tex);

    #if ( BLOOM_FX_DARK == 1 )
        float div = 4.7;
    #else
        float div = 4.2;
    #endif

    Color += sample0(TSAMP, float2(Tex.x-(rcpres.x*1), Tex.y)) * 0.8;
    Color += sample0(TSAMP, float2(Tex.x+(rcpres.x*1), Tex.y)) * 0.8;

    Color += sample0(TSAMP, float2(Tex.x-(rcpres.x*2), Tex.y)) * 0.65;
    Color += sample0(TSAMP, float2(Tex.x+(rcpres.x*2), Tex.y)) * 0.65;

    Color += sample0(TSAMP, float2(Tex.x-(rcpres.x*3), Tex.y)) * 0.4;
    Color += sample0(TSAMP, float2(Tex.x+(rcpres.x*3), Tex.y)) * 0.4;

    #if BLOOM_QUALITY >= 2
        Color += sample0(TSAMP, float2(Tex.x-(rcpres.x*4), Tex.y)) * 0.25;
        Color += sample0(TSAMP, float2(Tex.x+(rcpres.x*4), Tex.y)) * 0.25;
        #if ( BLOOM_FX_DARK == 1 )
            div = 5.2;
        #else
            div = 4.7;
        #endif
    
        #if BLOOM_QUALITY >= 3
            Color += sample0(TSAMP, float2(Tex.x-(rcpres.x*5), Tex.y)) * 0.15;
            Color += sample0(TSAMP, float2(Tex.x+(rcpres.x*5), Tex.y)) * 0.15;

            Color += sample0(TSAMP, float2(Tex.x-(rcpres.x*6), Tex.y)) * 0.10;
            Color += sample0(TSAMP, float2(Tex.x+(rcpres.x*6), Tex.y)) * 0.10;
            #if ( BLOOM_FX_DARK == 1 )
                div = 5.65;
            #else
                div = 5.2;
            #endif
        #endif
    #endif

    Color /= div;

    return Color*Color;
}

float4 blurHor2(in float2 Tex : TEXCOORD) : COLOR0
{ // a simple 7-sample horizontal blur pass   

    float4 Color = sample0(s1, Tex);

    #if ( BLOOM_FX_DARK == 1 )
        float div = 4.7;
    #else
        float div = 4.2;
    #endif

    float spread = 1-( Color.r * 0.3 ) + ( Color.g * 0.6 ) + ( Color.b * 0.1 );
    spread = ( smoothstep(0, 0.7, spread) * 4 ) + 1.0f;

    Color += sample0(s1, float2(Tex.x-(rcpres.x*spread*1), Tex.y)) * 0.8;
    Color += sample0(s1, float2(Tex.x+(rcpres.x*spread*1), Tex.y)) * 0.8;

    Color += sample0(s1, float2(Tex.x-(rcpres.x*spread*2), Tex.y)) * 0.65;
    Color += sample0(s1, float2(Tex.x+(rcpres.x*spread*2), Tex.y)) * 0.65;

    Color += sample0(s1, float2(Tex.x-(rcpres.x*spread*3), Tex.y)) * 0.4;
    Color += sample0(s1, float2(Tex.x+(rcpres.x*spread*3), Tex.y)) * 0.4;

    #if BLOOM_QUALITY >= 2
        Color += sample0(s1, float2(Tex.x-(rcpres.x*spread*4), Tex.y)) * 0.25;
        Color += sample0(s1, float2(Tex.x+(rcpres.x*spread*4), Tex.y)) * 0.25;
        #if ( BLOOM_FX_DARK == 1 )
            div = 5.2;
        #else
            div = 4.7;
        #endif
    #endif

    Color /= div;

    return Color;
}

float4 blurHor3(in float2 Tex : TEXCOORD) : COLOR0
{ // a simple 7-sample horizontal blur pass   
    float4 Color = sample0(s1, Tex);

    #if ( BLOOM_FX_DARK == 1 )
        float div = 4.7;
    #else
        float div = 4.2;
    #endif

    Color += sample0(s1, float2(Tex.x-(rcpres.x*1), Tex.y)) * 0.8;
    Color += sample0(s1, float2(Tex.x+(rcpres.x*1), Tex.y)) * 0.8;

    Color += sample0(s1, float2(Tex.x-(rcpres.x*2), Tex.y)) * 0.65;
    Color += sample0(s1, float2(Tex.x+(rcpres.x*2), Tex.y)) * 0.65;

    Color += sample0(s1, float2(Tex.x-(rcpres.x*3), Tex.y)) * 0.4;
    Color += sample0(s1, float2(Tex.x+(rcpres.x*3), Tex.y)) * 0.4;

    #if BLOOM_QUALITY >= 2
        Color += sample0(s1, float2(Tex.x-(rcpres.x*4), Tex.y)) * 0.25;
        Color += sample0(s1, float2(Tex.x+(rcpres.x*4), Tex.y)) * 0.25;
        #if ( BLOOM_FX_DARK == 1 )
            div = 5.2;
        #else
            div = 4.7;
        #endif
    
        #if BLOOM_QUALITY >= 3
            Color += sample0(s1, float2(Tex.x-(rcpres.y*5), Tex.y)) * 0.15;
            Color += sample0(s1, float2(Tex.x+(rcpres.y*5), Tex.y)) * 0.15;
        
            Color += sample0(s1, float2(Tex.x-(rcpres.y*6), Tex.y)) * 0.10;
            Color += sample0(s1, float2(Tex.x+(rcpres.y*6), Tex.y)) * 0.10;
            #if ( BLOOM_FX_DARK == 1 )
                div = 5.65;
            #else
                div = 5.2;
            #endif
        #endif
    #endif

    Color /= div;

    return Color;
}

float4 blurVertI(in float2 Tex : TEXCOORD) : COLOR0
{ // a simple 7-sample vertical blur pass
    float4 Color = sample0(s1, Tex);

    #if ( BLOOM_FX_DARK == 1 )
        float div = 4.7;
    #else
        float div = 4.2;
    #endif

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*1))) * 0.8;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*1))) * 0.8;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*2))) * 0.65;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*2))) * 0.65;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*3))) * 0.4;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*3))) * 0.4;

    #if BLOOM_QUALITY >= 2
        Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*4))) * 0.25;
        Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*4))) * 0.25;
        #if ( BLOOM_FX_DARK == 1 )
            div = 5.2;
        #else
            div = 4.7;
        #endif
    
        #if BLOOM_QUALITY >= 3
            Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*5))) * 0.15;
            Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*5))) * 0.15;
        
            Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*6))) * 0.10;
            Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*6))) * 0.10;
        
            #if ( BLOOM_FX_DARK == 1 )
                div = 5.65;
            #else
                div = 5.2;
            #endif
        #endif
    #endif

    Color /= div;

    return Color;
}

float4 blurVert2(in float2 Tex : TEXCOORD) : COLOR0
{ // a simple 7-sample vertical blur pass
    float4 Color = sample0(s1, Tex);

    #if ( BLOOM_FX_DARK == 1 )
        float div = 4.7;
    #else
        float div = 4.2;
    #endif

    float spread = 1-( Color.r * 0.3 ) + ( Color.g * 0.6 ) + ( Color.b * 0.1 );
    spread = ( smoothstep(0, 0.7, spread) * 4 ) + 1.0f;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*spread*1))) * 0.8;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*spread*1))) * 0.8;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*spread*2))) * 0.65;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*spread*2))) * 0.65;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*spread*3))) * 0.4;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*spread*3))) * 0.4;

    #if BLOOM_QUALITY >= 2
    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*spread*4))) * 0.25;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*spread*4))) * 0.25;
    #if ( BLOOM_FX_DARK == 1 )
        div = 5.2;
    #else
        div = 4.7;
    #endif
    #endif

    Color /= div;

    return Color;
}

float4 blurVert3(in float2 Tex : TEXCOORD) : COLOR0
{ // a simple 7-sample vertical blur pass
    float4 Color = sample0(s1, Tex);

    #if ( BLOOM_FX_DARK == 1 )
        float div = 4.7;
    #else
        float div = 4.2;
    #endif

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*1))) * 0.8;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*1))) * 0.8;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*2))) * 0.65;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*2))) * 0.65;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*3))) * 0.4;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*3))) * 0.4;

    #if BLOOM_QUALITY >= 2
    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*4))) * 0.25;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*4))) * 0.25;
    #if ( BLOOM_FX_DARK == 1 )
        div = 5.2;
    #else
        div = 4.7;
    #endif

    #if BLOOM_QUALITY >= 3
    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*5))) * 0.15;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*5))) * 0.15;

    Color += sample0(s1, float2(Tex.x, Tex.y-(rcpres.y*6))) * 0.10;
    Color += sample0(s1, float2(Tex.x, Tex.y+(rcpres.y*6))) * 0.10;
    #if ( BLOOM_FX_DARK == 1 )
        div = 5.65;
    #else
        div = 5.2;
    #endif
    #endif

    #endif

    Color /= div;

    return Color;
}


float4 brightPass(in float2 Tex : TEXCOORD ) :COLOR0
{
    float4 c = sample0(s1, Tex);
    float4 cB = c;

    c = smoothstep(0, bloom_cutoff, c);
    c = pow(c, bloom_power);
    c += smoothstep(bloom_cutoff, 0.5+bloom_cutoff, cB);
    c.a = 1.0f;

    return c;
}

float4 recombA(in float2 Tex: TEXCOORD) : COLOR0
{
    #if ( ( BLOOM_FX_SKY != 1 ) || ( BLOOM_FX_HANDS != 1 ) )
        float d = sample0(sDepth, Tex).r;
        float4 cB = sample0(s0, Tex);
        #if ( BLOOM_FX_SKY != 1 )
            cB.rgb *= saturate((fogrange - d) / (fogrange - fogstart));
        #endif
        #if ( BLOOM_FX_HANDS != 1 )
            cB.rgb *= smoothstep(35, 50, d);
        #endif
    #else
        float4 cB = sample0(s0, Tex);
    #endif
    
    float4 c = sample0(s1, Tex);

    c = smoothstep(0, bloom_cutoff, c);
    c += smoothstep(bloom_cutoff-0.5, bloom_cutoff+0.5, cB);

    return saturate(c);
}

float4 tB0(in float2 Tex : TEXCOORD) : COLOR0
{
    // grab scene and blurred highlights
    float4 scene = sample0(s0, Tex);
    float4 blur = sample0(s1, Tex);
    float4 highlights = 0;
    
    // apply all needed mults
    blur *= bloom_mult_global;
    
    if ( isInterior )
        blur *= bloom_mult_inside;
    else
        blur *= bloom_mult_outside;
        
    if ( isUnderwater )
        blur *= bloom_mult_uwater;

    scene += blur;

    return scene;
}

#if ( ( BLOOM_FX_SKY != 1 ) || ( BLOOM_FX_HANDS != 1 ) )
float4 doDepthFix(in float2 Tex : TEXCOORD) : COLOR0
{
    float d = sample0(sDepth, Tex).r;
    float4 Color = sample0(s0, Tex);
    #if ( BLOOM_FX_SKY != 1 )
        Color.rgb *= saturate((fogrange - d) / (fogrange - fogstart));
    #endif
    #if ( BLOOM_FX_HANDS != 1 )
        Color.rgb *= smoothstep(35, 50, d);
    #endif
    return Color;
}
#endif

technique T0 < string MGEinterface = "MGE XE 0"; string category = "sensor"; >
{
    #if ( ( BLOOM_FX_SKY != 1 ) || ( BLOOM_FX_HANDS != 1 ) )
    pass fixSky { PixelShader = compile ps_3_0 doDepthFix(); }
    #endif
    pass blurHBA { PixelShader = compile ps_3_0 blurHorI(); }
    pass blurVBA { PixelShader = compile ps_3_0 blurVertI(); }
    pass filter_Bright { PixelShader = compile ps_3_0 brightPass(); }
    pass blurHA { PixelShader = compile ps_3_0 blurHor2(); }
    pass blurVA { PixelShader = compile ps_3_0 blurVert2(); }

    #if BLOOM_QUALITY >= 2
    pass recombine_A { PixelShader = compile ps_3_0 recombA(); }
    pass blurHB { PixelShader = compile ps_3_0 blurHor3(); }
    pass blurVB { PixelShader = compile ps_3_0 blurVert3(); }
    #endif

    pass BloomB { PixelShader = compile ps_3_0 tB0(); }
}
