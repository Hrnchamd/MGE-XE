
#include "doublesurface.h"
#include <vector>

enum EffectVariableID {
    EV_lastshader, EV_lastpass, EV_depthframe, EV_watertexture,
    EV_eyevec, EV_eyepos, EV_sunvec, EV_suncol, EV_sunamb, EV_sunpos, EV_sunvis, EV_HDR,
    EV_mview, EV_mproj, EV_fogcol, EV_fogstart, EV_fogrange,
    EV_rcpres, EV_fov, EV_time, EV_waterlevel, EV_isinterior, EV_isunderwater
};

struct MGEShader
{
    ID3DXEffect* effect;
    int disableFlags;
    D3DXHANDLE ehVars[32];

    void SetTexture(EffectVariableID id, LPDIRECT3DBASETEXTURE9 tex);
    void SetMatrix(EffectVariableID id, const D3DXMATRIX *m);
    void SetFloatArray(EffectVariableID id, const float *x, int n);
    void SetFloat(EffectVariableID id, float x);
    void SetInt(EffectVariableID id, int x);
    void SetBool(EffectVariableID id, bool b);
};

typedef void (*MGEShaderUpdateFunc)(MGEShader *);

class PostShaders
{
    static IDirect3DDevice9 *device;
    static std::vector<MGEShader> shaders;
    static IDirect3DTexture9 *texLastShader;
    static IDirect3DSurface9 *surfaceLastShader;
    static SurfaceDoubleBuffer doublebuffer;
    static IDirect3DVertexBuffer9 *vbPost;
    static IDirect3DSurface9 *surfReadqueue, *surfReadback;
    static D3DXVECTOR4 adaptPoint;
    static float rcpRes[2];

public:
    static bool init(IDirect3DDevice9 *realDevice);
    static bool initShaderChain();
    static bool checkShaderVersion(MGEShader *shader);
    static void initShader(MGEShader *shader);
    static void loadShaderDependencies(MGEShader *shader);
    static bool initBuffers();
    static void release();

    static void evalAdaptHDR(IDirect3DSurface *source, int environmentFlags, float dt);
    static void shaderTime(MGEShaderUpdateFunc updateVarsFunc, int environmentFlags, float frameTime);
    static IDirect3DTexture9 * borrowBuffer(int n);
    static void applyBlend();
};
