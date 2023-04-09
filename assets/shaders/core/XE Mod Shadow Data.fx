
// XE Mod Shadow Data.fx
// MGE XE 0.16.0
// Shared constants



//------------------------------------------------------------
// Engine parameters

// Number of cascades that are rendered (this is hardcoded)
static const int shadowCascades = 2;

// Shadow atlas texture scaling factor
static const float shadowCascadeSize = 1. / shadowCascades;

//------------------------------------------------------------
// Shadow parameters

// Luminance reduction parameter for shadowed areas, recommend values in [0.25, 0.5]
static const float shade = 0.4;

// Shade colouration, how much each channel is affected by shadow
static const float3 shadecolor = float3(1.0, 0.97, 0.81);

// ESM exponent, affects shadow fade near shadow casters, bounded by float accuracy to ~88
// Higher means less fade at shadow root, but less effective softening of shadows
static const float ESM_c = 60.0;

// ESM bias, for countering blurred depth pushing surface depth values through objects
static const float ESM_bias = 2e-3 * ESM_c;

// Scale stored depth to use (most of) FP16 range
static const float ESM_scale = 32768.0;
