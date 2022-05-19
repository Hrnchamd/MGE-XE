// Underwater Effects
// Light rays and distortion wobble
// Hrnchamd
// v2

// Compatibility: MGE XE 0
int mgeflags = 17;


texture lastshader;
texture depthframe;
texture watertexture;

sampler s0 = sampler_state { texture = <lastshader>; magfilter = linear; minfilter = linear; };
sampler s1 = sampler_state { texture = <depthframe>; magfilter = point; minfilter = point; };
sampler s2 = sampler_state { texture = <watertexture>; magfilter = linear; minfilter = linear; };


matrix mview;
matrix mproj;
float3 eyepos;
float3 eyevec;
float3 sunpos;
float3 suncol;
float sunvis;
float time;

static float lf = (0.2 + 0.8*sunvis) * (0.32*suncol.r + 0.47*suncol.g + 0.21*suncol.b);
static const float4 lightcolour = float4(0.6, 0.91, 1.0, 0);



float4 sample0(sampler2D s, float2 t)
{
    return tex2Dlod(s, float4(t, 0, 0));
}

float3 toWorld(float2 tex)
{
    float3 v = float3(mview[0][2], mview[1][2], mview[2][2]);
    v += (1/mproj[0][0] * (2*tex.x-1)).xxx * float3(mview[0][0], mview[1][0], mview[2][0]);
    v += (-1/mproj[1][1] * (2*tex.y-1)).xxx * float3(mview[0][1], mview[1][1], mview[2][1]);
    return v;
}

float fetch(float3 tex, float uw)
{
    float c = tex3D(s2, float3(tex.xy / 3308, 0.22 * time)).b;
    return pow(c, 0.25) * saturate(exp(tex.z/90)) * saturate(1 + tex.z/uw);
}

float4 rays(float2 tex : TEXCOORD0) : COLOR
{
    float2 wobble = 0.01 * (2 * tex3D(s2, float3(0.25*tex, 0.2*time)).rg - 1);
    wobble *= 1 - pow(2*tex - 1, 32);
    tex += wobble;

    float4 c = sample0(s0, tex);
    float d = sample0(s1, tex).r;
    float3 v = toWorld(tex);
    float3 e = float3(0.1, 0.1, 1) * eyepos;
    float2 r;
    
    d = min(d, -eyepos.z/max(1e-5, v.z));
    v = v / length(v.xy);
    r = -sunpos.xy - v.xy * dot(-sunpos.xy, v.xy);

    float3 shellpos = e + 800 * v;
    shellpos.xy += 0.8 * r * shellpos.z;
    float rayz = fetch(shellpos, min(eyepos.z, 400)) * saturate(d/800) * 0.294;
    
    float3 shellpos2 = e + 1400 * v;
    shellpos2.xy += 1.0 * r * shellpos2.z;
    rayz += fetch(shellpos2, 2*eyepos.z) * saturate(d/800 - 1) * 0.132;
    
    float3 shellpos3 = e + 2000 * v;
    shellpos3.xy += 1.2 * r * shellpos3.z;
    rayz += fetch(shellpos3, 3*eyepos.z) * saturate(d/800 - 2) * 0.065;

    return c + rayz * lf * lightcolour;
}

technique T0  < string MGEinterface = "MGE XE 0"; string category = "scene"; >
{
    pass { PixelShader = compile ps_3_0 rays(); }
}
