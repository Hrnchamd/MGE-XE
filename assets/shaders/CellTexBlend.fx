
// Used by distant land generator to create world ground texture

Matrix transform;

Texture t1;
Texture t2;
Texture t3;
Texture t4;

sampler s0 = sampler_state { texture = <t1>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = wrap; addressv = wrap; };
sampler s1 = sampler_state { texture = <t2>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = wrap; addressv = wrap; };
sampler s2 = sampler_state { texture = <t3>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = wrap; addressv = wrap; };
sampler s3 = sampler_state { texture = <t4>; minfilter = linear; magfilter = linear; mipfilter = linear; addressu = wrap; addressv = wrap; };

vector c1;
vector c2;
vector c3;
vector c4;


// sRGB <-> linear RGB
float toLinear1(float x) {
    if (x > 0.04045)
        return pow((x + 0.055) / 1.055, 2.4);
    else
        return x / 12.91;
}

float3 toLinear(float3 c) {
    return float3(toLinear1(c.r), toLinear1(c.g), toLinear1(c.b));
}

float tosRGB1(float x) {
    if (x > 0.0031308)
        return 1.055 * pow(x, 1/2.4) - 0.055;
    else
        return 12.92 * x;
}

float3 tosRGB(float3 c) {
    return float3(tosRGB1(c.r), tosRGB1(c.g), tosRGB1(c.b));
}

// Texture Blending
struct VSOutput {
	float4 pos: POSITION0;
	float2 texcoords: TEXCOORD0;
	float4 color: COLOR0;
	float3 normal: TEXCOORD1;
	float4 weights: COLOR1;
};

VSOutput CellTexBlendVS( float4 pos: POSITION0, float2 texcoords: TEXCOORD0, float4 color: COLOR0, float3 normal: NORMAL, float4 weights: COLOR1 ) {
	VSOutput OUT;
	
	OUT.pos = mul(pos, transform);
	OUT.texcoords = texcoords;
	OUT.color = color;
	OUT.normal = normal;	
	OUT.weights = weights;
	
	return OUT;
}

float4 CellTexBlendPS( in VSOutput IN ) : COLOR0 {
	
	// Sample all 4 textures, multiplying associated weight
	float3 color = toLinear(tex2D(s0, IN.texcoords).rgb) * IN.weights.b;
	color += toLinear(tex2D(s1, IN.texcoords).rgb) * IN.weights.g;
	color += toLinear(tex2D(s2, IN.texcoords).rgb) * IN.weights.r;
	color += toLinear(tex2D(s3, IN.texcoords).rgb) * IN.weights.a;

	return float4(tosRGB(color), 1);
}

// Vertex Colors
struct VSColorOutput {
	float4 pos: POSITION0;
	float4 color: COLOR0;
};

VSColorOutput CellVertColorVS( float4 pos: POSITION0, float4 color: COLOR0 ) {
	VSColorOutput OUT;

	OUT.pos = mul(pos, transform);
	OUT.color = color;
	
	return OUT;
}

float4 CellVertColorPS( in VSColorOutput IN ) : COLOR0 {
	// Return vertex color
	return float4(IN.color.rgb, 1);
}

// Normal Map
struct VSNormalOutput {
	float4 pos: POSITION0;
	float3 normal: TEXCOORD0;
};

VSNormalOutput CellNormalMapVS( float4 pos: POSITION0, float3 normal: NORMAL ) {
	VSNormalOutput OUT;

	OUT.pos = mul(pos, transform);
	OUT.normal = normal;
	
	return OUT;
}

float4 CellNormalMapPS( in VSNormalOutput IN ) : COLOR0 {
	
	IN.normal = normalize(IN.normal);
	IN.normal += 1;
	IN.normal /= 2;
	return float4(IN.normal.x, IN.normal.y, IN.normal.z, 1);
}


Technique T0
{
	Pass P0
	{
		AlphaBlendEnable = true;
		AlphaTestEnable = false;
		SrcBlend = One;
		DestBlend = One;

		Texture[0]=<t1>;
		Texture[1]=<t2>;
		Texture[2]=<t3>;
		Texture[3]=<t4>;
		
		VertexShader = compile vs_3_0 CellTexBlendVS();
		PixelShader = compile ps_3_0 CellTexBlendPS();
	}
	Pass P1
	{
		AlphaBlendEnable = false;
		AlphaTestEnable = false;
		
		VertexShader = compile vs_3_0 CellNormalMapVS();
		PixelShader = compile ps_3_0 CellNormalMapPS();
	}
	Pass P2
	{
		AlphaBlendEnable = true;
		AlphaTestEnable = false;
		SrcBlend = DestColor;
		DestBlend = Zero;
		
		VertexShader = compile vs_3_0 CellVertColorVS();
		PixelShader = compile ps_3_0 CellVertColorPS();
	}
}
