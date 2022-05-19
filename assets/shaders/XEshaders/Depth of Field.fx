// Depth of Field
// v12 by Knu
// tweaked to save your poor blurry hands by peachykeen
// includes distance blur in fog conditions

// Compatibility: MGE XE 0, fully working

float2 rcpres;
float fov;
float fogstart, fogrange;

static float t =  2.0 * tan(radians(0.5 * fov));
static float k = 0.00001;
static float unit2m = 0.0142;
static float eps = 0.000001;
static float fogoffset = saturate(-fogstart / (fogrange - fogstart));

// **
// ** ADJUSTABLE VARIABLES

#define SM ps_3_0 // Shader model: ps_3_0, ps_2_0
#define ROTATE // Random rotation on, if defined. ps_3_0 only

static const float fr = 60.0; // retina focal point, dpt
// set slightly lower than fp to simulate myopia or as an alternative to MGE's distant blur
// set slightly higher than fp+fpa to simulate hyperopia

static const float fp = 60.0; // eye relaxed focal power, dpt
static const float fpa = 10.0; // accomodation, dpt
// set lower to simulate presbyopia

static const float pupil = 0.006; // pupil diameter, m

static const float blur_radius = 0.273; // base blur radius;
// higher values mean more blur when out of DoF and shorter DoF
static const float blur_falloff = 2.0; // More means more blur and less respect for edges
static const float R = 6.0; // maximum blur radius in pixels
static float Rfixed = R / (1280 * rcpres.x); // standardize blur across resolutions

// ** END OF
// **


texture lastshader;
texture lastpass;
texture depthframe;

sampler s0 = sampler_state { texture = <lastshader>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };
sampler s1 = sampler_state { texture = <depthframe>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };
sampler s3 = sampler_state { texture = <lastpass>; addressu = mirror; addressv = mirror; magfilter = linear; minfilter = linear; };


#ifdef ROTATE
texture tex1 < string src="MGE/noise64.dds"; >;
sampler s2 = sampler_state { texture = <tex1>; addressu = wrap; addressv = wrap; magfilter = point; minfilter = point; };
#endif


#define M 12
static float2 taps[M] =
{
    float2(-0.326212,-0.40581),
    float2(-0.840144,-0.07358),
    float2(-0.695914,0.457137),
    float2(-0.203345,0.620716),
    float2(0.96234,-0.194983),
    float2(0.473434,-0.480026),
    float2(0.519456,0.767022),
    float2(0.185461,-0.893124),
    float2(0.507431,0.064425),
    float2(0.89642,0.412458),
    float2(-0.32194,-0.932615),
    float2(-0.791559,-0.59771)
};



float4 sample0(sampler2D s, float2 t)
{
    return tex2Dlod(s, float4(t, 0, 0));
}

float4 dof(float2 tex : TEXCOORD) : COLOR0
{
    float s = sample0(s1, float2(0.5, 0.5)).r * unit2m;

    float z_corr = length(float3((tex.x - 0.5) * t, (tex.y - 0.5) * t / rcpres.y * rcpres.x, 1));
    float z = z_corr * unit2m * sample0(s1, tex).r;
    float savemyhands = smoothstep(0.568, 0.781, z);
    
    float fpf = clamp(1 / s + fr, fp, fp + fpa);
    float c = pupil * (fr - fpf + 1 / z) / fr / k * blur_radius;
    float fog = fogoffset * saturate(z / (4 * fogrange * unit2m));
    
    c = min(abs(c / Rfixed) + fog, 1) * savemyhands;
    return float4(sample0(s0, tex).rgb, c);
}

float4 smartblur(float2 tex : TEXCOORD) : COLOR0
{
    float4 color = sample0(s3, tex);
    float c = color.a * Rfixed;

#ifdef ROTATE
    float2 rnd = normalize(sample0(s2, tex / rcpres / 64).xy * 2 + 1);
#endif

    float amount = 1.0;
    for(int i = 0; i < M; i++)
    {
#ifdef ROTATE
        float2 dir = reflect(taps[i], rnd);
#else
        float2 dir = taps[i];
#endif

        float2 s_tex = tex + rcpres * dir * c;
        float4 s_color = sample0(s3, s_tex);
        float s_c = s_color.a * Rfixed;
        float weight = exp2(-abs(c - s_c) / blur_falloff);

        color += s_color * weight;
        amount += weight;
    }

    return float4(color.rgb / amount, 1);
}



technique T0 < string MGEinterface = "MGE XE 0"; string category = "lens"; >
{
    pass { PixelShader = compile SM dof(); }
    pass { PixelShader = compile SM smartblur(); }
}
