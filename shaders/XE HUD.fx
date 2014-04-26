
// XE HUD.fx
// MGE XE 0.9
// Standard HUD shader

texture tex;
sampler s0 = sampler_state { texture = <tex>; minfilter = point; magfilter = point; addressu = clamp; addressv = clamp; };

float4 hud(float2 t : TEXCOORD) : COLOR0
{
    return tex2D(s0, t);
}

technique T
{
    Pass P
    {
        AlphaBlendEnable = true;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;

        AlphaTestEnable = true;
        AlphaFunc = Greater;
        AlphaRef = 0;
        
        PixelShader = compile ps_3_0 hud();
    }
}
