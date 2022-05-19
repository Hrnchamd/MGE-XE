// Screen Space Ambient Occlusion
// based on ssao v09 by Knu
// Fast version, 8 sample taps

// Compatibility: MGE XE 0, fully working
int mgeflags = 8;

// **
// ** ADJUSTABLE VARIABLES

#define N 8 // Samples: 16, 10, 8, 6. More means precision and performance hit.
#define BLUR // Enable AO blur.
#define ROTATE // Enable random rotation. Generally more precise, but might give noise or other artifacts.
//#define DEBUG // Enable debug mode: AO term only.

static const float R = 15.0; // Max ray radius, world units
static const float multiplier = 1.8; // Overall strength. 1.0 is the correct physical value
static const float occlusion_falloff = 20.0; // More means less depth precision, and more strength
static const float blur_falloff = 0.1; // Blur depth falloff, more means a larger depth range is blurred
static const float blur_radius = 5.0; // In pixels

// ** END OF
// **

float2 rcpres;
float3 eyepos, eyevec;
float3 fognearcol;
float fognearstart, fognearrange;
float waterlevel;
float fov;

texture lastshader;
texture lastpass;
texture depthframe;

sampler s0 = sampler_state { texture = <lastshader>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };
sampler s1 = sampler_state { texture = <lastpass>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };
sampler s4 = sampler_state { texture = <lastpass>; addressu = mirror; addressv = mirror; magfilter = linear; minfilter = linear; };
sampler s2 = sampler_state { texture = <depthframe>; addressu = clamp; addressv = clamp; magfilter = point; minfilter = point; };



static const float depth_scale = 10000;
static const float2 invproj =  2.0 * tan(0.5 * radians(fov)) * float2(1, rcpres.x / rcpres.y);
static const float eps = 1e-6;
static const float sky = 1e6;

#ifdef ROTATE
texture tex1 < string src="MGE/poisson_nrm.dds"; >;
sampler s3 = sampler_state { texture = <tex1>; addressu = wrap; addressv = wrap; magfilter = point; minfilter = point; };
#endif



static float3 dirs[N] = 
{
#if N >= 16
    float3(-0.00941, -0.00326, -0.05597),
    float3(0.11686, 0.00831, 0.04915),
    float3(-0.08125, -0.24638, 0.30141),
    float3(0.35193, 0.29639, 0.47544),
    float3(0.32063, -0.70203, -0.40622),
    float3(-0.37344, -0.18112, 0.37140),
#endif
#if N >= 10
    float3(-0.73605, -0.39320, 0.04992),
    float3(0.02274, 0.21583, 0.19429),
#endif
#if N >= 8
    float3(0.00762, -0.01247, 0.03311),
    float3(-0.61057, 0.20510, 0.58876),
#endif
    float3(0.55319, 0.67960, -0.19194),
    float3(-0.43533, 0.62404, 0.45133),
    float3(-0.02386, -0.03104, 0.01502),
    float3(-0.20990, 0.10082, 0.03849),
    float3(0.06331, -0.17620, -0.31359),
    float3(-0.12261, 0.00720, -0.12465)
};

#define M 8
static float2 taps[M] = 
{
    float2(-0.695914,0.457137), float2(-0.203345,0.620716),
    float2(0.96234,-0.194983), float2(0.473434,-0.480026),
    float2(0.507431,0.064425), float2(0.89642,0.412458),
    float2(-0.32194,-0.932615), float2(-0.791559,-0.59771)
};


float4 sample0(sampler2D s, float2 t)
{
    return tex2Dlod(s, float4(t, 0, 0));
}

float3 toView(float2 tex)
{
    float depth = sample0(s2, tex).r;
    float2 xy = depth * (tex - 0.5) * invproj;
    return float3(xy, depth);
}

float2 fromView(float3 view)
{
    return (view.xy / view.z) / invproj + float2(0.5, 0.5);
}

inline float2 pack2(float f)
{
    return float2(f, frac(f * 255.0 - 0.5));
}

inline float unpack2(float2 f)
{
    return f.x + ((f.y - 0.5) / 255.0);
}



static const float xylength = sqrt(1 - eyevec.z * eyevec.z);
float4 ssao(in float2 tex : TEXCOORD0) : COLOR0
{
    float3 pos = toView(tex);
    float water = pos.z * eyevec.z - pos.y * xylength + eyepos.z;

    if(pos.z <= 0 || pos.z > sky || (water - waterlevel) < 0)
        return float4(0, 0, 0, 1);

    float3 left = pos - toView(tex + rcpres * float2(-1, 0));
    float3 right = toView(tex + rcpres * float2(1, 0)) - pos;
    float3 up = pos - toView(tex + rcpres * float2(0, -1));
    float3 down = toView(tex + rcpres * float2(0, 1)) - pos;

    float3 dx = length(left) < length(right) ? left : right;
    float3 dy = length(up) < length(down) ? up : down;

    float3 normal = normalize(cross(dy, dx));
    dy = normalize(cross(dx, normal));
    dx = normalize(dx);

#ifdef ROTATE
    float3 rnd = sample0(s3, tex / rcpres / 8).xyz * 2 - 1;
#endif

    float AO = 0, amount = 0;
    for (int j = 0; j < N; j++)
    {
        float3 ray, occ;

#ifdef ROTATE
        ray = reflect(dirs[j] * R, rnd);
#else
        ray = dirs[j] * R;
#endif

        ray *= sign(ray.z);
        ray = dx * ray.x + dy * ray.y + normal * ray.z;
        float weight = dot(normalize(ray), normal);

        occ = toView(fromView(pos + ray));
        // Bias occ.z to avoid self-occlusion errors from point sampling depth
        float diff = (pos.z + ray.z) - 1.00025 * occ.z;

        amount += weight;
        AO += weight * step(0, diff) * exp2(-diff / occlusion_falloff);
    }

    return float4(AO / amount, pack2(pos.z / depth_scale), 1);
}



float4 smartblur(in float2 tex : TEXCOORD0) : COLOR
{
    float4 data = sample0(s4, tex);
    float total = data.r;
    float depth = unpack2(data.gb);
    float rev = blur_radius * (2.0*data.a - 1.0);
    float amount = 1;
    for (int i = 0; i < M; i++)
    {
        float2 s_tex = tex + rcpres * taps[i] * rev;
        float3 s_data = sample0(s4, s_tex); 
        float s_depth = unpack2(s_data.gb);
        float weight = exp2(-abs(depth - s_depth) / depth / blur_falloff);

        amount += weight;
        total += s_data.r * weight;
    }

    return float4(total / amount, data.gb, 1.0 - data.a);
}



float4 show(float2 tex : TEXCOORD0) : COLOR
{
    float4 result = 1 - multiplier * sample0(s1, tex).r;
    result.a = 1;
    return result;
} 



float4 combine(float2 tex : TEXCOORD0) : COLOR
{
    float dist = length(toView(tex));
    float fog = saturate((fognearrange - dist) / (fognearrange - fognearstart));
    float final = fog * multiplier * sample0(s1, tex).r;
    float3 result = lerp(sample0(s0, tex).rgb, fognearcol * (1-fog), final);
    return float4(result, 1);
}



technique T0 < string MGEinterface = "MGE XE 0"; string category = "scene"; int priorityAdjust = -10000; >
{
    pass { PixelShader = compile ps_3_0 ssao(); }
#ifdef BLUR
    pass { PixelShader = compile ps_3_0 smartblur(); }
#ifdef ROTATE
    pass { PixelShader = compile ps_3_0 smartblur(); }
#endif
#endif

#ifdef DEBUG
    pass { PixelShader = compile ps_3_0 show(); }
#else
    pass { PixelShader = compile ps_3_0 combine(); }
#endif
}
