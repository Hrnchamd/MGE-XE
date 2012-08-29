
#include <vector>
#include <map>
#include "proxydx/d3d8header.h"

struct RenderedState
{
    IDirect3DTexture9 *texture;
    IDirect3DVertexBuffer9 *vb;
    UINT vbOffset, vbStride;
    IDirect3DIndexBuffer9 *ib;
    DWORD ibBase;
    DWORD fvf;
    DWORD zWrite, cullMode;
    DWORD vertexBlendState;
    D3DXMATRIX worldTransforms[4];
    BYTE blendEnable, srcBlend, destBlend;
    BYTE alphaTest, alphaFunc, alphaRef;
    BYTE useLighting, matSrcDiffuse, matSrcEmissive;

    D3DPRIMITIVETYPE primType;
    UINT baseIndex, minIndex, vertCount, startIndex, primCount;
};

struct FragmentState
{
    struct Stage
    {
        BYTE colorOp, colorArg1, colorArg2;
        BYTE alphaOp, alphaArg1, alphaArg2;
        BYTE colorArg0, alphaArg0, resultArg;
        DWORD texcoordIndex;
        DWORD texTransformFlags;
        float bumpEnvMat[2][2];
        float bumpLumiScale, bumpLumiBias;
    } stage[8];

    struct Material
    {
        D3DCOLORVALUE diffuse, ambient, emissive;
    } material;
};

struct LightState
{
    struct Light
    {
        D3DLIGHTTYPE type;
        D3DCOLORVALUE diffuse;
        D3DVECTOR position;     // position / normalized direction
        union
        {
            D3DVECTOR falloff;      // constant, linear, quadratic
            D3DVECTOR ambient;  // for directional lights
        };
    };

    D3DCOLORVALUE globalAmbient;
    std::map<DWORD, Light> lights;
    std::vector<DWORD> active;
};

class FixedFunctionShader
{
    struct ShaderKey
    {
        DWORD uvSets : 2;
        DWORD usesSkinning : 1;
        DWORD vertexColour : 1;
        DWORD heavyLighting : 1;
        DWORD vertexMaterial : 2;
        DWORD fogMode : 1;
        DWORD activeStages : 3;
        DWORD usesBumpmap : 1;
        DWORD bumpmapStage : 3;
        DWORD usesTexgen : 1;
        DWORD texgenStage : 3;

        struct Stage
        {
            DWORD colorOp : 6;
            DWORD colorArg1 : 6;
            DWORD colorArg2 : 6;
            DWORD colorArg0 : 6;
            DWORD texcoordIndex : 4;
            DWORD texcoordGen : 4;
        } stage[8];

        ShaderKey() {}
        ShaderKey(const RenderedState *rs, const FragmentState *frs, const LightState *lightrs);
        bool operator<(const ShaderKey& other) const;
        bool operator==(const ShaderKey& other) const;
        void log() const;
    };

    static IDirect3DDevice *device;
    static ID3DXEffectPool *constantPool;
    static std::map<ShaderKey, ID3DXEffect *> cacheEffects;
    static ID3DXEffect *effectDefaultPurple;

    static D3DXHANDLE ehWorld, ehVertexBlendState, ehVertexBlendPalette;
    static D3DXHANDLE ehTex0, ehTex1, ehTex2, ehTex3;
    static D3DXHANDLE ehMaterialDiffuse, ehMaterialAmbient, ehMaterialEmissive;
    static D3DXHANDLE ehLightAmbient, ehLightSunDiffuse, ehLightSunDirection;
    static D3DXHANDLE ehLightDiffuse, ehLightPosition;
    static D3DXHANDLE ehLightFalloffQuadratic, ehLightFalloffLinear, ehLightFalloffConstant;
    static D3DXHANDLE ehTexgenTransform, ehBumpMatrix, ehBumpLumiScaleBias;

    static ID3DXEffect * generateMWShader(const ShaderKey& sk);

public:
    static bool init(IDirect3DDevice *d, ID3DXEffectPool *pool);
    static void renderMorrowind(const RenderedState *rs, const FragmentState *frs, const LightState *lightrs);
    static void release();
};
