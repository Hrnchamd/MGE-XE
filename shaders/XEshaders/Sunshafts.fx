// Sun shaft rays by phal v0.02a

// Compatibility: MGE XE 0, fully working
int mgeflags = 9;

// tweakables
#define N 20                     // Number of iterations
#define raysunradius 0.25         // Radius around sun center that emits rays
#define raystrength 1.7         // Brightness of sun rays
#define rayfalloff 1.10         // Falloff of sun rays
#define rayfalloffconst 0.125     // Increase to increase minimum 'length' of sun rays
#define raysunfalloff 1.5         // Ray strength falloff exponent
#define centervis 0.3             // Ray opacity at center of sun
#define sunrayocclude 0.75         // How much sun rays will 'overwrite' original image
#define brightnessadd 1.25         // Additional sun ray color brightness for very bright rays
#define offscreenrange 0.5         // Maximum offscreen position of sun before rays vanish
#define sundisc 1                 // Draws additional sun disc. 0 disables
#define sundiscradius 0.025       // Radius of sun disc
#define sundiscbrightness 1.4    // Brightness of sun disc
#define sundiscdesaturate 0.4    // Desaturation of sun disc color, negative values for more saturation
#define sundiscocclude 0.75        // How much the sun disc will 'overwrite' original image
#define horizonclipping 1         // Prevents the sun disc from being drawn below the horizon. Might cause an FPS hit.
// end

texture depthframe;
texture lastshader;
texture lastpass;


sampler s0 = sampler_state { texture = <depthframe>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = clamp; addressv = clamp; };
sampler s1 = sampler_state { texture = <lastshader>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = clamp; addressv = clamp; };
sampler s2 = sampler_state { texture = <lastpass>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = clamp; addressv = clamp; };

float3 suncol;
float3 eyevec;
float3 eyepos;
float3 sunpos;
float sunvis;
float2 rcpres;
float waterlevel;
float fogrange;
float fov;

matrix mview;
matrix mproj;

static const float raspect = rcpres.x / rcpres.y;

static const float3 sundir = -normalize(sunpos);

static const float forward = dot(sundir,eyevec);

static const float2 texproj = 0.5f * float2(1, -rcpres.y / rcpres.x ) / tan(radians(fov * 0.5));

static const float d = dot(eyevec,sunpos);
static const float3 sunview_v = mul(sunpos/d, mview);
static const float2 sunview = (0.5).xx + sunview_v.xy * texproj;
static const float2 sunviewhalf = sunview*0.5f;

static const float light = 1-pow(1-sunvis,2);

static const float strength = raystrength * light * smoothstep(-offscreenrange,0,0.5-abs(sunview.x-0.5)) * smoothstep(-offscreenrange,0,0.5-abs(sunview.y-0.5));
static const float oneminuscentervis = 1-centervis;

static const float3 suncoldisc = float3(1, 0.76+0.24*sunpos.z, 0.37+0.63*sunpos.z) * saturate(suncol/max(suncol.r,max(suncol.g,suncol.b)) * (1-sundiscdesaturate) + float3(sundiscdesaturate,sundiscdesaturate,sundiscdesaturate));

static const float aziHorizon = normalize( float2(4*fogrange, waterlevel-eyepos.z) ).y;


#define scale 2.0
#define rscale 0.5
#define rscale2 0.25
#define threshold 1e7

float4 stretch( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float depth = 0;
    if(forward < 0)
    {
        depth = step(threshold,tex2D(s0, float2(Tex.x*scale, Tex.y*scale)).r);
        depth += step(threshold,tex2D(s0, float2(Tex.x*scale + rcpres.x, Tex.y*scale)).r);
        depth += step(threshold,tex2D(s0, float2(Tex.x*scale, Tex.y*scale + rcpres.y)).r);
        depth += step(threshold,tex2D(s0, float2(Tex.x*scale + rcpres.x, Tex.y*scale + rcpres.y)).r);
        depth *= rscale2;
    }    
    return float4(0,0,0,depth);
}

float4 blurRHalf( float2 Tex : TEXCOORD0 ) : COLOR0
{
    if(forward >= 0)
        return 0;

    float2 radial = normalize(Tex-sunviewhalf).xy*float2(rcpres.y,rcpres.x);

    float alpha = 0.3333*tex2D(s2, Tex).a;
    alpha += 0.2222*tex2D(s2, Tex + radial).a;
    alpha += 0.2222*tex2D(s2, Tex - radial).a;
    alpha += 0.1111*tex2D(s2, Tex + 2*radial).a;
    alpha += 0.1111*tex2D(s2, Tex - 2*radial).a;

    return float4(0,0,0,alpha);
}

float4 rays( float2 Tex : TEXCOORD0 ) : COLOR0
{
    if(forward >= 0)
        return 0;
        
    float l = 0;

    float2 screendir = (Tex-sunview);
    float screendist = length(screendir * float2(1,raspect));
    screendir /= screendist;
    float sunr = min(raysunradius,screendist);    
    float sundist = 0;

    for(int i=1; i <= N; i++)
    {
        sundist = (float)i / (float)N * sunr;
        l += tex2D(s2, (sunview + sundist * screendir)*rscale).a * exp(-((screendist-sundist)/(rayfalloffconst+sundist)) * rayfalloff) * pow(1-saturate(sundist/raysunradius),raysunfalloff);
    }

    l *= strength / (float)N * (screendist/raysunradius*oneminuscentervis+centervis);

    float4 col = float4(suncol.r, 0.8*suncol.g, 0.8*suncol.b, l);
    col.rgb *= 1 + brightnessadd * pow(col.a,3);
    return col;
}

float4 blurT( float2 Tex : TEXCOORD0 ) : COLOR0
{
    if(forward >= 0)
        return 0;

    float2 tangent = 1.0 * normalize(Tex-sunview).yx * float2(rcpres.y,-rcpres.x);

    float4 col = 0.3333*tex2D(s2, Tex);
    col += 0.2222*tex2D(s2, Tex + tangent);
    col += 0.2222*tex2D(s2, Tex - tangent);
    col += 0.1111*tex2D(s2, Tex + 2*tangent);
    col += 0.1111*tex2D(s2, Tex - 2*tangent);
    return col;
}

float4 blurR( float2 Tex : TEXCOORD0 ) : COLOR0
{
    if(forward >= 0)
        return 0;

    float2 radial = 3.0 * normalize(Tex-sunview).xy * float2(rcpres.y,rcpres.x);

    float4 col = 0.3333*tex2D(s2, Tex);
    col += 0.2222*tex2D(s2, Tex + radial);
    col += 0.2222*tex2D(s2, Tex - radial);
    col += 0.1111*tex2D(s2, Tex + 2*radial);
    col += 0.1111*tex2D(s2, Tex - 2*radial);
    return col;
}

float3 toWorld(float2 tex)
{
    float3 v = float3(mview[0][2], mview[1][2], mview[2][2]);
    v += (1/mproj[0][0] * (2*tex.x-1)).xxx * float3(mview[0][0], mview[1][0], mview[2][0]);
    v += (-1/mproj[1][1] * (2*tex.y-1)).xxx * float3(mview[0][1], mview[1][1], mview[2][1]);
    return v;
}

float4 combine( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 ray = tex2D(s2, Tex);
    float3 col = tex2D(s1, Tex);
    
    col *= saturate(1 - sunrayocclude*ray.a);
    col = saturate(col + ray.rgb*ray.a);

#if sundisc == 1
    if(forward < 0)
    {
        float2 screendir = Tex - sunview;
        screendir.y *= raspect;

        float occl = light * step(threshold, tex2D(s0, Tex).r);
        occl *= pow(saturate(sundiscradius/(length(screendir)+0.0001)),3);
        
        if(occl > 0.004)
        {
            float3 scol = suncoldisc*sundiscbrightness;
#if horizonclipping == 1
            float azi = normalize(toWorld(Tex)).z;
            occl *= smoothstep(-0.005, 0.010, azi - aziHorizon);
            scol.gb *= smoothstep(-0.04, 0.05, azi - aziHorizon);
#endif
            col = max(col,scol)*occl + col * (1 - sundiscocclude*occl);
        }
    }
#endif

    return float4(col,1);
}

float4 alpha( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float a = tex2D(s2, Tex).a;
    return float4(a,a,a,1);
}

technique T0 < string MGEinterface="MGE XE 0"; bool disableSunglare = true; >
{
    pass {PixelShader = compile ps_2_0 stretch();}
    pass {PixelShader = compile ps_2_0 blurRHalf();}
    
#if N > 24
    pass {PixelShader = compile ps_3_0 rays();}
#else
    pass {PixelShader = compile ps_2_b rays();}
#endif
    //pass {PixelShader = compile ps_2_0 blurR();}
    pass {PixelShader = compile ps_2_0 blurT();}
    pass {PixelShader = compile ps_2_0 combine();}
    //pass {PixelShader = compile ps_2_0 alpha();}
}
