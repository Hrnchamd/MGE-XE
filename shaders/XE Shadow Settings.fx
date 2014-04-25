
// XE Shadow Settings.fx
// MGE XE 0.9
// Shared constants



//------------------------------------------------------------
// Shadow parameters

// Luminance reduction parameter for shadowed areas, recommend values in [0.25, 0.5]
static const float shade = 0.4;

// Shade colouration, how much each channel is affected by shadow
static const float3 shadecolour = float3(1.0, 0.97, 0.81);

// ESM exponent, affects shadow fade near shadow casters, bounded by float accuracy to ~88
// Higher means less fade at shadow root, but sharper shadows
static const float ESM_c = 60.0;

// ESM bias, for countering blurred depth pushing surface depth values through objects
static const float ESM_bias = 2e-3 * ESM_c;

// Scale stored depth to use (most of) FP16 range
static const float ESM_scale = 32768.0;

// Shadow map pixel dimension (fixed)
static const float shadowPixelSize = 1/1024.0;
