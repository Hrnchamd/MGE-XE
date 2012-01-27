// Screen Space Ambient Occlusion
// v09 by Knu
// High-quality version, full resolution, 16 sample taps

// Compatibility: MGE XE 0, fully working
int mgeflags = 8;

// **
// ** ADJUSTABLE VARIABLES

#define N 16 // Samples: 48, 32, 16, 10, 6. More means precision and performance hit.
#define BLUR // Enable AO blur.
#define ROTATE // Enable random rotation. Generally more precise, but might give noise or other artifacts.
//#define DEBUG // Enable debug mode: AO term only.

static const float R = 15.0; // Max ray radius, world units
static const float multiplier = 1.6; // Overall strength. 1.0 is the correct physical value
static const float occlusion_falloff = 15.0; // More means less precision, and more strength
static const float blur_falloff = 5.0; // Same for blur
static const float blur_radius = 4.0; // In pixels

// ** END OF
// **

float2 rcpres;
float3 eyepos;
float3 eyevec;
float fogstart;
float fogrange;
float waterlevel;
float fov;

texture lastshader;
texture lastpass;
texture depthframe;

sampler s0 = sampler_state {texture=<lastshader>; AddressU=Clamp; AddressV=Clamp;};
sampler s1 = sampler_state {texture=<lastpass>; AddressU=Clamp; AddressV=Clamp; MagFilter=Linear; MinFilter=Linear;};
sampler s4 = sampler_state {texture=<lastpass>; AddressU=Mirror; AddressV=Mirror;};
sampler s2 = sampler_state {texture=<depthframe>; AddressU=Clamp; AddressV=Clamp;};



static const float depth_scale = 10000;
static const float t =  2.0 * tan(0.5 * radians(fov));
static const float eps = 1e-6;
static const float sky = 1e6;

#ifdef ROTATE
texture tex1 < string src="noise8q.tga"; >;
sampler s3 = sampler_state { texture=<tex1>; AddressU=Wrap; AddressV=Wrap; };
#endif



static float3 dirs[N] = 
{
#if N >= 48
    float3(0.04556, 0.09479, -0.28152),
    float3(0.08758, -0.17459, 0.14837),
    float3(0.57190, 0.49847, -0.64101),
    float3(0.03734, 0.08883, 0.02760),
    float3(0.09542, 0.00860, -0.06100),
    float3(-0.09026, 0.10302, -0.19118),
    float3(0.54615, -0.08996, 0.65708),
    float3(0.10383, -0.02091, -0.00712),

    float3(-0.18331, -0.10469, -0.10359),
    float3(0.74090, 0.54747, 0.29408),
    float3(-0.00270, 0.00443, 0.00937),
    float3(0.57718, -0.34843, -0.46236),
    float3(-0.05405, -0.22931, -0.17499),
    float3(-0.30069, -0.47800, -0.09799),
    float3(-0.00606, -0.21609, -0.03372),
    float3(-0.87538, 0.02272, -0.20764),
#endif
#if N >= 32
    float3(-0.48710, 0.29981, -0.25607),
    float3(0.03163, 0.02985, 0.15875),
    float3(-0.18035, -0.06732, 0.58081),
    float3(0.17450, -0.02599, -0.33065),
    float3(0.06349, -0.03883, 0.03387),
    float3(0.10394, 0.69917, -0.16286),
    float3(0.04695, 0.36486, -0.33281),
    float3(0.31748, -0.27097, -0.03810),

    float3(-0.07172, 0.09571, -0.00005),
    float3(-0.06029, 0.38936, 0.07889),
    float3(0.13681, -0.30447, 0.04381),
    float3(-0.09649, -0.92119, 0.34473),
    float3(-0.56596, -0.03144, 0.18844),
    float3(-0.10715, 0.25182, -0.13061),
    float3(0.59962, 0.21747, -0.07792),
    float3(-0.03793, -0.03653, -0.06986),
#endif
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



#define M 12
static float2 taps[M] = 
{
    float2(-0.326212,-0.40581), float2(-0.840144,-0.07358),
    float2(-0.695914,0.457137), float2(-0.203345,0.620716),
    float2(0.96234,-0.194983), float2(0.473434,-0.480026),
    float2(0.519456,0.767022), float2(0.185461,-0.893124),
    float2(0.507431,0.064425), float2(0.89642,0.412458),
    float2(-0.32194,-0.932615), float2(-0.791559,-0.59771)
};



float3 toView(float2 tex)
{
    float depth = tex2D(s2, tex).r;
    float x = (tex.x - 0.5) * depth * t;
    float y = (tex.y - 0.5) * depth * t / rcpres.y * rcpres.x;
    return float3(x, y, depth);
}

float2 fromView(float3 view)
{
    float x = (view.x / t / view.z) + 0.5;
    float y = (view.y / t / view.z * rcpres.y / rcpres.x) + 0.5;
    return float2(x, y);
}

inline float2 pack2(float f)
{
    return float2(f, frac(f * 255.0 - 0.5));
}

inline float unpack2(float2 f)
{
    return f.x + ((f.y - 0.5) / 255.0);
}



float4 ssao(in float2 tex : TEXCOORD0) : COLOR0
{
    float3 pos = toView(tex);
    float water = pos.z * eyevec.z - pos.y * sqrt(1 - eyevec.z * eyevec.z) + eyepos.z;

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
    float3 rnd = normalize(tex2D(s3, tex / rcpres / 8).xyz * 2 - float3(1, 1, 1));
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

        occ = toView(fromView(pos + ray)) - pos;
        float diff = ray.z - occ.z - 1.0;    // -1 avoid self-occlusion

        amount += weight;
        AO += weight * step(0, diff) * exp2(-diff / occlusion_falloff);
    }

    return float4(AO / amount, pack2(pos.z / depth_scale), 1);
}



float4 smartblur(in float2 tex : TEXCOORD0) : COLOR
{
    float4 data = tex2D(s4, tex);
    float total = data.r;
    float depth = unpack2(data.gb);
    float rev = data.a * 2.0 - 1.0;
    float amount = 1;
    for (int i = 0; i < M; i++)
    {
        float2 s_tex = tex + rcpres * taps[i] * blur_radius * rev;
        float3 s_data = tex2D(s4, s_tex); 
        float s_depth = unpack2(s_data.gb);
        float weight = exp2(-abs(depth - s_depth) * depth_scale / blur_falloff);

        amount += weight;
        total += s_data.r * weight;
    }

    return float4(total / amount, data.gb, 1.0 - data.a);
}



float4 show(float2 tex : TEXCOORD0) : COLOR
{
    float4 result = (1.0 - multiplier * tex2D(s1, tex).r);

    result.a = 1;
    return result;	
} 



float4 combine(float2 tex : TEXCOORD0) : COLOR
{
    float dist = length(toView(tex));
    float final = multiplier * tex2D(s1, tex).r;

#ifdef USE_EXPFOG
    float fog = (dist - fogstart) / (fogrange - fogstart);
    fog = saturate(exp(-fog));
#else
    float fog = saturate((fogrange - dist) / (fogrange - fogstart));
#endif

    float4 result = tex2D(s0, tex) * (1 - final * fog * fog);
    return result;
} 



technique T0 < string MGEinterface="MGE XE 0"; >
{
    pass { PixelShader = compile ps_3_0 ssao(); }
#ifdef BLUR
    pass { PixelShader = compile ps_3_0 smartblur(); }
  #ifdef ROTATE //needs 2 passes
    pass { PixelShader = compile ps_3_0 smartblur(); }
  #endif
#endif

#ifdef DEBUG
    pass { PixelShader = compile ps_3_0 show(); }
#else
    pass { PixelShader = compile ps_3_0 combine(); }
#endif
}
