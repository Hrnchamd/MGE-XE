#ifndef _DISTANT_LAND_H_
#define _DISTANT_LAND_H_

#include "quadtree.h"
#include "DLMath.h"
#include <string>
#include <tr1/unordered_map>

using namespace std::tr1;

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
    DWORD blendEnable, srcBlend, destBlend;
    DWORD alphaTest, alphaFunc, alphaRef;

    D3DPRIMITIVETYPE primType;
    UINT baseIndex, minIndex, vertCount, startIndex, primCount;
};

struct MGEShader;

class DistantLand
{
public:
    struct WorldSpace
    {
        QuadTree *NearStatics;
        QuadTree *FarStatics;
        QuadTree *VeryFarStatics;
        QuadTree *GrassStatics;
    };

    static const DWORD fvfWave = D3DFVF_XYZRHW | D3DFVF_TEX2;
    static const int waveTexResolution = 512;
    static const float waveTexWorldRes = 2.5f;
    static const int GrassInstStride = 48;
    static const int MaxGrassElements = 8192;

    static bool ready;
    static bool isRenderCached;
    static int numWaterVerts, numWaterTris;

    static IDirect3DDevice9 *device;
    static ID3DXEffect *effect;
    static ID3DXEffect *effectShadow;
    static ID3DXEffect *effectDepth;
    static ID3DXEffectPool *effectPool;
    static IDirect3DVertexDeclaration9 *LandDecl;
    static IDirect3DVertexDeclaration9 *StaticDecl;
    static IDirect3DVertexDeclaration9 *WaterDecl;
    static IDirect3DVertexDeclaration9 *GrassDecl;

    static unordered_map<string, WorldSpace> mapWorldSpaces;
    static const WorldSpace *currentWorldSpace;
    static QuadTree LandQuadTree;
    static VisibleSet visLand;
    static VisibleSet visDistant;
    static VisibleSet visGrass;

    static vector<RenderedState> recordMW;
    static vector<RenderedState> recordSky;
    static vector< pair<const QuadTreeMesh*, int> > batchedGrass;

    static IDirect3DTexture9 *texWorldColour, *texWorldNormals, *texWorldDetail;
    static IDirect3DTexture9 *texDepthFrame;
    static IDirect3DSurface9 *surfDepthDepth;
    static IDirect3DTexture9 *texDistantBlend;
    static IDirect3DTexture9 *texReflection;
    static IDirect3DVolumeTexture9 *texWater;
    static IDirect3DVertexBuffer9 *vbWater;
    static IDirect3DIndexBuffer9 *ibWater;
    static IDirect3DVertexBuffer9 *vbGrassInstances;

    static IDirect3DTexture9 *texRain, *texRipples, *texRippleBuffer;
    static IDirect3DSurface9 *surfRain, *surfRipples, *surfRippleBuffer;
    static IDirect3DVertexBuffer9 *vbWaveSim;

    static IDirect3DTexture9 *texShadow, *texSoftShadow;
    static IDirect3DSurface9 *surfShadowZ;
    static IDirect3DVertexBuffer9 *vbFullFrame;

    static D3DXMATRIX mwView, mwProj;
    static D3DXMATRIX smView[2], smProj[2], smViewproj[2];
    static D3DXVECTOR4 eyeVec, eyePos, sunVec, sunPos;
    static float sunVis;
    static RGBVECTOR sunCol, sunAmb, ambCol;
    static RGBVECTOR nearfogCol, horizonCol;
    static float fogStart, fogEnd;
    static float fogNearStart, fogNearEnd;
    static float windScaling, niceWeather;

    static D3DXHANDLE ehRcpRes;
    static D3DXHANDLE ehWorld, ehView, ehProj;
    static D3DXHANDLE ehShadowViewproj;
    static D3DXHANDLE ehVertexBlendState, ehVertexBlendPalette;
    static D3DXHANDLE ehAlphaRef;
    static D3DXHANDLE ehHasAlpha;
    static D3DXHANDLE ehTex0, ehTex1, ehTex2, ehTex3, ehTex4, ehTex5;
    static D3DXHANDLE ehEyePos;
    static D3DXHANDLE ehFootPos;
    static D3DXHANDLE ehSunCol, ehSunAmb, ehSunVec;
    static D3DXHANDLE ehSkyCol, ehFogCol1, ehFogCol2;
    static D3DXHANDLE ehSunPos, ehSunVis;
    static D3DXHANDLE ehFogStart, ehFogRange;
    static D3DXHANDLE ehFogNearStart, ehFogNearRange;
    static D3DXHANDLE ehWindVec;
    static D3DXHANDLE ehNiceWeather;
    static D3DXHANDLE ehTime;
    static D3DXHANDLE ehRippleOrigin;
    static D3DXHANDLE ehWaveHeight;

    static bool init(IDirect3DDevice9 *realDevice);
    static bool initShader();
    static bool initDepth();
    static bool initWater();
    static bool initDynamicWaves();
    static bool initLandscape();
    static bool initDistantStatics();
    static bool initShadow();
    static bool initGrass();
    static bool loadDistantStatics();
    static bool initDistantStaticsBVH();
    static void release();

    static void editProjectionZ(D3DMATRIX *m, float zn, float zf);
    static bool selectDistantCell();
    static bool isDistantCell();

    static void setView(const D3DMATRIX *m);
    static void setProjection(D3DMATRIX *proj);
    static void setHorizonColour(const D3DCOLOR c);
    static void setAmbientColour(const D3DCOLOR c);
    static void setSunLight(const D3DLIGHT8 *s);
    static void adjustFog();
    static bool inspectIndexedPrimitive(int sceneCount, const RenderedState* rs);

    static void renderSky();
    static void renderStage0();
    static void renderStage1();
    static void renderStage2();
    static void renderBlend();

    static void setupCommonEffect(const D3DXMATRIX *view,const  D3DXMATRIX *proj);

    static void renderDistantLand(ID3DXEffect *e, const D3DXMATRIX *view, const D3DXMATRIX *proj);
    static void renderDistantLandZ();
    static void cullDistantStatics(const D3DXMATRIX *view, const D3DXMATRIX *proj);
    static void renderDistantStatics();
    static void cullGrass(const D3DXMATRIX *view, const D3DXMATRIX *proj);
    static void buildGrassInstanceVB();
    static void renderGrassInst();
    static void renderGrassInstZ();
    static void renderGrassCommon(ID3DXEffect *e);

    static void renderWaterReflection(const D3DXMATRIX *view, const D3DXMATRIX *proj);
    static void renderReflectedSky();
    static void renderReflectedStatics(const D3DXMATRIX *view, const D3DXMATRIX *proj);
    static void clearReflection();
    static void simulateDynamicWaves();
    static void renderWaterPlane();

    static void renderDepth();
    static void renderDepthAdditional();
    static void renderDepthRecorded();

    static void renderShadowMap();
    static void renderShadowLayer(int layer, float radius);
    static void renderShadow();
    static void renderShadowDebug();

    static void postProcess();
    static void updatePostShader(MGEShader *shader);

    static IDirect3DSurface9 * captureScreen();
};

#endif
