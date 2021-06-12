
// XE Mod Sky.fx
// MGE XE 0.13.0
// Sky rendering. Can be used as a core mod.

//------------------------------------------------------------
// Sky and sky reflections

struct SkyVertOut {
    float4 pos : POSITION;
    float4 color : COLOR0;
    float2 texcoords : TEXCOORD0;
    float4 skypos : TEXCOORD1;
};

SkyVertOut SkyVS(StatVertIn IN) {
    SkyVertOut OUT;
    float4 pos = IN.pos;
    
    // Screw around with skydome, align default mesh with horizon
    if(!hasAlpha) {
        pos.z = 50 * (IN.pos.z + 200);
    }
    
    pos = mul(pos, world);
    OUT.skypos = float4(pos.xyz - eyePos, 1);

    pos = mul(pos, view);
    OUT.pos = mul(pos, proj);
    OUT.pos.z = 0.999999 * OUT.pos.w;   // Pin z to far plane so it renders to background
    OUT.color = IN.color;
    OUT.texcoords = IN.texcoords;
    
    return OUT;
}

// Ordered dithering matrix
static const float ditherSky[4][4] = { 0.001176, 0.001961, -0.001176, -0.001699, -0.000654, -0.000915, 0.000392, 0.000131, -0.000131, -0.001961, 0.000654, 0.000915, 0.001699, 0.001438, -0.000392, -0.001438 };

float4 SkyPS(SkyVertOut IN, float2 vpos : VPOS) : COLOR0 {
    float4 c = 0;
    
    if(hasAlpha) {
        // Sample texture at lod 0 avoiding mip blurring
        c = IN.color * tex2Dlod(sampBaseTex, float4(IN.texcoords, 0, 0));
    }
        
    if(hasBones) {
        // Use colour from scattering for sky (but preserves alpha)
        float4 f = fogColourSky(normalize(IN.skypos.xyz)) + ditherSky[vpos.x % 4][vpos.y % 4];
        c.rgb = f.rgb;
    }
        
    return c;
}
