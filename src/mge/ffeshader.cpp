
#include "ffeshader.h"
#include "support/log.h"

#include <algorithm>
#include <sstream>



using std::string;
using std::stringstream;
using std::unordered_map;

IDirect3DDevice* FixedFunctionShader::device;
ID3DXEffectPool* FixedFunctionShader::constantPool;
unordered_map<FixedFunctionShader::ShaderKey, ID3DXEffect*, FixedFunctionShader::ShaderKey::hasher> FixedFunctionShader::cacheEffects;
FixedFunctionShader::ShaderLRU FixedFunctionShader::shaderLRU;
ID3DXEffect* FixedFunctionShader::effectDefaultPurple;

D3DXHANDLE FixedFunctionShader::ehWorld, FixedFunctionShader::ehWorldView;
D3DXHANDLE FixedFunctionShader::ehVertexBlendState, FixedFunctionShader::ehVertexBlendPalette;
D3DXHANDLE FixedFunctionShader::ehTex0, FixedFunctionShader::ehTex1, FixedFunctionShader::ehTex2, FixedFunctionShader::ehTex3, FixedFunctionShader::ehTex4, FixedFunctionShader::ehTex5;
D3DXHANDLE FixedFunctionShader::ehMaterialDiffuse, FixedFunctionShader::ehMaterialAmbient, FixedFunctionShader::ehMaterialEmissive;
D3DXHANDLE FixedFunctionShader::ehLightSceneAmbient, FixedFunctionShader::ehLightSunDiffuse, FixedFunctionShader::ehLightDiffuse;
D3DXHANDLE FixedFunctionShader::ehLightSunDirection, FixedFunctionShader::ehLightPosition, FixedFunctionShader::ehLightAmbient;
D3DXHANDLE FixedFunctionShader::ehLightFalloffQuadratic, FixedFunctionShader::ehLightFalloffLinear, FixedFunctionShader::ehLightFalloffConstant;
D3DXHANDLE FixedFunctionShader::ehTexgenTransform, FixedFunctionShader::ehBumpMatrix, FixedFunctionShader::ehBumpLumiScaleBias;

float FixedFunctionShader::sunMultiplier, FixedFunctionShader::ambMultiplier;

static string buildArgString(DWORD arg, const string& mask, const string& sampler);



bool FixedFunctionShader::init(IDirect3DDevice* d, ID3DXEffectPool* pool) {
    device = d;
    constantPool = pool;

    // Create last resort shader when a generated shader fails somehow
    const D3DXMACRO generateDefault[] = { "FFE_ERROR_MATERIAL", "", 0, 0 };
    ID3DXEffect* effect;
    ID3DXBuffer* errors;

    HRESULT hr = D3DXCreateEffectFromFile(device, "Data Files\\shaders\\XE FixedFuncEmu.fx", generateDefault, 0, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, constantPool, &effect, &errors);
    if (hr != D3D_OK) {
        if (errors) {
            LOG::logline("!! %s", errors->GetBufferPointer());
            errors->Release();
        }
        return false;
    }

    // Use it to bind shared parameters too
    ehWorld = effect->GetParameterByName(0, "world");
    ehVertexBlendState = effect->GetParameterByName(0, "vertexblendstate");
    ehVertexBlendPalette = effect->GetParameterByName(0, "vertexblendpalette");
    ehTex0 = effect->GetParameterByName(0, "tex0");
    ehTex1 = effect->GetParameterByName(0, "tex1");
    ehTex2 = effect->GetParameterByName(0, "tex2");
    ehTex3 = effect->GetParameterByName(0, "tex3");
    ehTex4 = effect->GetParameterByName(0, "tex4");
    ehTex5 = effect->GetParameterByName(0, "tex5");

    ehWorldView = effect->GetParameterByName(0, "worldview");
    ehMaterialDiffuse = effect->GetParameterByName(0, "materialDiffuse");
    ehMaterialAmbient = effect->GetParameterByName(0, "materialAmbient");
    ehMaterialEmissive = effect->GetParameterByName(0, "materialEmissive");
    ehLightSceneAmbient = effect->GetParameterByName(0, "lightSceneAmbient");
    ehLightSunDiffuse = effect->GetParameterByName(0, "lightSunDiffuse");
    ehLightSunDirection = effect->GetParameterByName(0, "lightSunDirection");
    ehLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
    ehLightAmbient = effect->GetParameterByName(0, "lightAmbient");
    ehLightPosition = effect->GetParameterByName(0, "lightPosition");
    ehLightFalloffQuadratic = effect->GetParameterByName(0, "lightFalloffQuadratic");
    ehLightFalloffLinear = effect->GetParameterByName(0, "lightFalloffLinear");
    ehLightFalloffConstant = effect->GetParameterByName(0, "lightFalloffConstant");
    ehTexgenTransform = effect->GetParameterByName(0, "texgenTransform");
    ehBumpMatrix = effect->GetParameterByName(0, "bumpMatrix");
    ehBumpLumiScaleBias = effect->GetParameterByName(0, "bumpLumiScaleBias");

    effectDefaultPurple = effect;
    sunMultiplier = ambMultiplier = 1.0;

    shaderLRU.effect = NULL;
    shaderLRU.last_sk = ShaderKey();
    cacheEffects.clear();
    return true;
}

void FixedFunctionShader::updateLighting(float sunMult, float ambMult) {
    sunMultiplier = sunMult;
    ambMultiplier = ambMult;
}

void FixedFunctionShader::renderMorrowind(const RenderedState* rs, const FragmentState* frs, LightState* lightrs) {
    ID3DXEffect* effectFFE;

    // Check if state matches last used effect
    ShaderKey sk(rs, frs, lightrs);

    if (sk == shaderLRU.last_sk) {
        effectFFE = shaderLRU.effect;
    } else {
        // Read from shader cache / generate
        decltype(cacheEffects)::const_iterator iEffect = cacheEffects.find(sk);

        if (iEffect != cacheEffects.end()) {
            effectFFE = iEffect->second;
        } else {
            effectFFE = generateMWShader(sk);
        }

        shaderLRU.effect = effectFFE;
        shaderLRU.last_sk = sk;
    }

    // Set up material
    effectFFE->SetVector(ehMaterialDiffuse, (D3DXVECTOR4*)&frs->material.diffuse);
    effectFFE->SetVector(ehMaterialAmbient, (D3DXVECTOR4*)&frs->material.ambient);
    effectFFE->SetVector(ehMaterialEmissive, (D3DXVECTOR4*)&frs->material.emissive);

    // Set up lighting
    const size_t MaxLights = 8;
    D3DXVECTOR4 bufferDiffuse[MaxLights];
    float bufferAmbient[MaxLights];
    float bufferPosition[3 * MaxLights];
    float bufferFalloffQuadratic[MaxLights], bufferFalloffLinear[MaxLights], bufferFalloffConstant;

    memset(&bufferDiffuse, 0, sizeof(bufferDiffuse));
    memset(&bufferAmbient, 0, sizeof(bufferAmbient));
    memset(&bufferPosition, 0, sizeof(bufferPosition));
    memset(&bufferFalloffQuadratic, 0, sizeof(bufferFalloffQuadratic));
    memset(&bufferFalloffLinear, 0, sizeof(bufferFalloffLinear));
    bufferFalloffConstant = 0.33;

    // Check each active light
    RGBVECTOR sunDiffuse(0, 0, 0), ambient = lightrs->globalAmbient;
    size_t n = std::min(lightrs->active.size(), MaxLights), pointLightCount = 0;
    for (n; n --> 0; ) {
        DWORD i = lightrs->active[n];
        const LightState::Light* light = &lightrs->lights.find(i)->second;

        // Transform to view space if not transformed this frame
        if (lightrs->lightsTransformed.find(i) == lightrs->lightsTransformed.end()) {
            if (light->type == D3DLIGHT_DIRECTIONAL) {
                D3DXVec3TransformNormal((D3DXVECTOR3*)&light->viewspacePos, (D3DXVECTOR3*)&light->position, &rs->viewTransform);
            } else {
                D3DXVec3TransformCoord((D3DXVECTOR3*)&light->viewspacePos, (D3DXVECTOR3*)&light->position, &rs->viewTransform);
            }

            lightrs->lightsTransformed[i] = true;
        }

        if (light->type == D3DLIGHT_POINT) {
            memcpy(&bufferDiffuse[pointLightCount], &light->diffuse, sizeof(light->diffuse));

            // Scatter position vectors for vectorization
            bufferPosition[pointLightCount] = light->viewspacePos.x;
            bufferPosition[pointLightCount + MaxLights] = light->viewspacePos.y;
            bufferPosition[pointLightCount + 2*MaxLights] = light->viewspacePos.z;

            // Scatter attenuation factors for vectorization
            if (light->falloff.x > 0) {
                // Standard point light source (falloffConstant doesn't vary per light)
                bufferFalloffConstant = light->falloff.x;
                bufferFalloffLinear[pointLightCount] = light->falloff.y;
                bufferFalloffQuadratic[pointLightCount] = light->falloff.z;
            } else if (light->falloff.z > 0) {
                // Probably a magic light source patched by Morrowind Code Patch
                // Patched falloff calculation is quadratic only, which needs to be
                // modified to account for the standard falloffConstant
                // Diffuse colour is correctly specified with the patch
                // Some overbrightness is applied to diffuse to cause glowing
                bufferDiffuse[pointLightCount].x *= bufferFalloffConstant;
                bufferDiffuse[pointLightCount].y *= bufferFalloffConstant;
                bufferDiffuse[pointLightCount].z *= bufferFalloffConstant;
                bufferAmbient[pointLightCount] = 1.0f + 1e-4f / sqrt(light->falloff.z);
                bufferFalloffQuadratic[pointLightCount] = bufferFalloffConstant * light->falloff.z;
            } else if (light->falloff.y == 0.10000001f) {
                // Projectile light source, normally hard coded by Morrowind to { 0, 3 * (1/30), 0 }
                // This falloff value cannot be produced by other magic effects
                // Replacement falloff is significantly brighter to look cool
                // Avoids modifying colour or position
                bufferFalloffQuadratic[pointLightCount] = 5e-5;
            } else if (light->falloff.y > 0) {
                // Light magic effect, falloffs calculated by { 0, 3 / (22 * spell magnitude), 0 }
                // A mix of ambient (falloff but no N.L component) and over-bright diffuse lighting
                // It is approximated with a half-lambert weight + quadratic falloff
                // Light colour is altered to avoid variable brightness from Morrowind bugs
                // The point source is moved up slightly as it is often embedded in the ground
                float brightness = 0.25f + 1e-4f / light->falloff.y;
                bufferDiffuse[pointLightCount].x = brightness;
                bufferDiffuse[pointLightCount].y = brightness;
                bufferDiffuse[pointLightCount].z = brightness;
                bufferAmbient[pointLightCount] = 1.0;
                bufferFalloffQuadratic[pointLightCount] = 0.5555f * light->falloff.y * light->falloff.y;
                bufferPosition[pointLightCount + 2*MaxLights] += 25.0;
            }
            ++pointLightCount;
        } else if (light->type == D3DLIGHT_DIRECTIONAL) {
            effectFFE->SetFloatArray(ehLightSunDirection, (const float*)&light->viewspacePos, 3);

            sunDiffuse = light->diffuse;
            ambient.r += light->ambient.x;
            ambient.g += light->ambient.y;
            ambient.b += light->ambient.z;
        }
    }

    // Apply light multipliers, for HDR light levels
    sunDiffuse *= sunMultiplier;
    ambient *= ambMultiplier;

    // Special case, check if ambient state is pure white (distant land does not record this for a reason)
    // Morrowind temporarily sets this for full-bright particle effects, but just adding it
    // to other ambient sources above would cause over-brightness
    DWORD checkAmbient;
    device->GetRenderState(D3DRS_AMBIENT, &checkAmbient);
    if (checkAmbient == 0xffffffff) {
        // Set lighting to result in full-bright equivalent after tonemapping
        ambient.r = ambient.g = ambient.b = 1.25;
        sunDiffuse.r = sunDiffuse.g = sunDiffuse.b = 0.0;
    }

    effectFFE->SetFloatArray(ehLightSceneAmbient, ambient, 3);
    effectFFE->SetFloatArray(ehLightSunDiffuse, sunDiffuse, 3);
    effectFFE->SetVectorArray(ehLightDiffuse, bufferDiffuse, MaxLights);
    effectFFE->SetFloatArray(ehLightAmbient, bufferAmbient, MaxLights);
    effectFFE->SetFloatArray(ehLightPosition, bufferPosition, 3 * MaxLights);
    effectFFE->SetFloatArray(ehLightFalloffQuadratic, bufferFalloffQuadratic, MaxLights);
    effectFFE->SetFloatArray(ehLightFalloffLinear, bufferFalloffLinear, MaxLights);
    effectFFE->SetFloat(ehLightFalloffConstant, bufferFalloffConstant);

    // Bump mapping state
    if (sk.usesBumpmap) {
        const FragmentState::Stage* bumpStage = &frs->stage[sk.bumpmapStage];
        effectFFE->SetFloatArray(ehBumpMatrix, &bumpStage->bumpEnvMat[0][0], 4);
        effectFFE->SetFloatArray(ehBumpLumiScaleBias, &bumpStage->bumpLumiScale, 2);
    }

    // Texgen texture matrix
    if (sk.usesTexgen) {
        D3DXMATRIX m;
        device->GetTransform((D3DTRANSFORMSTATETYPE)(D3DTS_TEXTURE0 + sk.texgenStage), &m);
        effectFFE->SetMatrix(ehTexgenTransform, &m);
    }

    // Copy texture bindings from fixed function pipe
    const D3DXHANDLE ehIndex[] = { ehTex0, ehTex1, ehTex2, ehTex3, ehTex4, ehTex5 };
    for (n = 0; n != std::min((int)sk.activeStages, 6); ++n) {
        IDirect3DBaseTexture9* tex;
        device->GetTexture(n, &tex);
        effectFFE->SetTexture(ehIndex[n], tex);
        if (tex) {
            tex->Release();
        }
    }

    // Set common state and render
    effectFFE->SetInt(ehVertexBlendState, rs->vertexBlendState);
    if (rs->vertexBlendState) {
        effectFFE->SetMatrixArray(ehVertexBlendPalette, rs->worldViewTransforms, 4);
    } else {
        effectFFE->SetMatrix(ehWorld, &rs->worldTransforms[0]);
        effectFFE->SetMatrix(ehWorldView, &rs->worldViewTransforms[0]);
    }

    UINT passes;
    effectFFE->Begin(&passes, D3DXFX_DONOTSAVESTATE);
    effectFFE->BeginPass(0);
    device->DrawIndexedPrimitive(rs->primType, rs->baseIndex, rs->minIndex, rs->vertCount, rs->startIndex, rs->primCount);
    effectFFE->EndPass();
    effectFFE->End();

    device->SetVertexShader(NULL);
    device->SetPixelShader(NULL);
}

ID3DXEffect* FixedFunctionShader::generateMWShader(const ShaderKey& sk) {
    string genVBCoupling, genPSCoupling, genTransform, genTexcoords, genVertexColour, genLightCount, genMaterial, genTexturing, genFog;
    stringstream buf;

    // Identify output texcoords and check for texgen; supports max. one per shader
    int texGen = 0, texGenSrcIndex = 0, totalOutputCoords = sk.uvSets;
    if (sk.usesTexgen) {
        texGen = sk.stage[sk.texgenStage].texcoordGen;
        texGenSrcIndex = sk.stage[sk.texgenStage].texcoordIndex;
        ++totalOutputCoords;
    }

    if (totalOutputCoords > 4) {
        LOG::logline("!! Shader generator error: excessive texcoord usage (%d).", totalOutputCoords);
        sk.log();

        effectDefaultPurple->AddRef();
        cacheEffects[sk] = effectDefaultPurple;
        return effectDefaultPurple;
    }

    // Pack 2d texcoords into interpolators and map to stages
    const char* strInterpolators[] = { "01", "23" };
    const char* strTexcoordPacking[] = { ".xy", ".zw" };
    string texcoordNames[8], texSamplers[8];

    for (int i = 0; i != sk.activeStages; ++i) {
        int x = sk.stage[i].texcoordGen ? sk.uvSets : sk.stage[i].texcoordIndex;

        buf.str(string());
        buf << "texcoord" << strInterpolators[x >> 1] << strTexcoordPacking[x & 1];
        texcoordNames[i] = buf.str();
        buf.str(string());
        buf << "tex2D(sampFFE" << i << ", IN." << texcoordNames[i] << ")";
        texSamplers[i] = buf.str();
    }

    // Vertex format coupling, generate equivalent struct to input FVF
    buf.str(string());

    if (sk.usesSkinning) {
        buf << "float4 blendweights : BLENDWEIGHT; ";
    }
    if (sk.vertexColour) {
        buf << "float4 col : COLOR; ";
    }
    for (int i = 0; i != sk.uvSets; ++i) {
        buf << "float2 texcoord" << i << " : TEXCOORD" << i << "; ";
    }

    genVBCoupling = buf.str();

    // Pixel shader coupling, passes texcoords and colours
    buf.str(string());

    if (sk.vertexColour) {
        buf << "float4 col : COLOR; ";
    }
    if (totalOutputCoords == 1) {
        buf << "float2 texcoord01 : TEXCOORD0; ";
    } else if (totalOutputCoords > 1) {
        buf << "float4 texcoord01 : TEXCOORD0; ";
    }
    if (totalOutputCoords == 3) {
        buf << "float2 texcoord23 : TEXCOORD1; ";
    } else if (totalOutputCoords == 4) {
        buf << "float4 texcoord23 : TEXCOORD1; ";
    }

    genPSCoupling = buf.str();

    // Transform / skinning
    buf.str(string());

    if (sk.usesSkinning) {
        buf << "viewpos = skinnedVertex(IN.pos, IN.blendweights); normal = skinnedNormal(IN.nrm, IN.blendweights);";
    } else {
        buf << "viewpos = rigidVertex(IN.pos); normal = rigidNormal(IN.nrm);";
    }

    genTransform = buf.str();

    // Texcoord routing and texgen
    string texRouting[4];
    for (int i = 0; i != sk.uvSets; ++i) {
        buf.str(string());
        buf << "IN.texcoord" << i;
        texRouting[i] = buf.str();
    }

    buf.str(string());

    if (texGen) {
        buf << "float3 texgen = ";
        switch (texGen) {
        case D3DTSS_TCI_CAMERASPACENORMAL >> 16:
            buf << "texgenNormal(normal); ";
            break;
        case D3DTSS_TCI_CAMERASPACEPOSITION >> 16:
            buf << "texgenPosition(viewpos); ";
            break;
        case D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR >> 16:
            buf << "texgenReflection(viewpos, normal); ";
            break;
        case D3DTSS_TCI_SPHEREMAP >> 16:
            buf << "texgenSphere(" << texRouting[texGenSrcIndex] << "); ";
            break;
        }
        buf << "texgen = mul(float4(texgen, 1), texgenTransform).xyz; ";
        texRouting[sk.uvSets] = "texgen.xy";
    }

    if (totalOutputCoords == 1) {
        buf << "OUT.texcoord01 = " << texRouting[0] << ";";
    } else if (totalOutputCoords > 1) {
        buf << "OUT.texcoord01 = float4(" << texRouting[0] << ", " << texRouting[1] << "); ";
    }
    if (totalOutputCoords == 3) {
        buf << "OUT.texcoord23 = " << texRouting[2] << ";";
    } else if (totalOutputCoords == 4) {
        buf << "OUT.texcoord23 = float4(" << texRouting[2] << ", " << texRouting[3] << ");";
    }

    genTexcoords = buf.str();

    // Vertex colour routing
    buf.str(string());
    if (sk.vertexColour) {
        buf << "OUT.col = IN.col;";
    }
    genVertexColour = buf.str();

    // Lighting
    if (sk.vertexMaterial == 0) {
        genLightCount = "0";
    } else {
        genLightCount = sk.heavyLighting ? "8" : "4";
    }

    // Vertex material
    buf.str(string());
    switch (sk.vertexMaterial) {
    case 0:
        buf << "diffuse = " << (sk.vertexColour ? "IN.col;" : "1.0;");
        break;
    case 1:
        buf << "diffuse = vertexMaterialNone(d, a);";
        break;
    case 2:
        buf << "diffuse = vertexMaterialDiffAmb(d, a, IN.col);";
        break;
    case 3:
        buf << "diffuse = vertexMaterialEmissive(d, a, IN.col);";
        break;
    }
    genMaterial = buf.str();

    // Texture and shading operations
    buf.str(string());
    string arg1, arg2, arg3;

    for (int i = 0; i != sk.activeStages; ++i) {
        const ShaderKey::Stage* s = &sk.stage[i];
        const string dest = (i > 0) ? "c.rgb = " : "c = ";
        const string mask = (i > 0) ? ".rgb" : "";

        arg1 = buildArgString(s->colorArg1, mask, texSamplers[i]);
        arg2 = buildArgString(s->colorArg2, mask, texSamplers[i]);

        switch (s->colorOp) {
        case D3DTOP_SELECTARG1:
            buf << dest << arg1 << ";";
            break;

        case D3DTOP_SELECTARG2:
            buf << dest << arg2 << ";";
            break;

        case D3DTOP_MODULATE:
            buf << dest << arg1 << " * " << arg2 << ";";
            break;

        case D3DTOP_MODULATE2X:
            buf << dest << "2 * " << arg1 << " * " << arg2 << ";";
            break;

        case D3DTOP_MODULATE4X:
            buf << dest << "4 * " << arg1 << " * " << arg2 << ";";
            break;

        case D3DTOP_ADD:
            buf << dest << arg1 << " + " << arg2 << ";";
            break;

        case D3DTOP_ADDSIGNED:
            buf << dest << arg1 << " + " << arg2 << " - 0.5;";
            break;

        case D3DTOP_ADDSIGNED2X:
            buf << dest << "2 * (" << arg1 << "+" << arg2 << ") - 1;";
            break;

        case D3DTOP_SUBTRACT:
            buf << dest << arg1 << " - " << arg2 << ";";
            break;

        case D3DTOP_BLENDDIFFUSEALPHA:
            buf << dest << "lerp(" << arg1 << ", " << arg2 << ", diffuse.a);";
            break;

        case D3DTOP_BLENDTEXTUREALPHA:
            arg3 = buildArgString(D3DTA_TEXTURE, "", texSamplers[i]);
            buf << "float4 temp" << i << " = " << arg3 << "; lerp(" << arg1 << ", " << arg1 << ", temp" << i <<".a);";
            break;

        case D3DTOP_BUMPENVMAP:
            arg3 = buildArgString(D3DTA_TEXTURE, "", texSamplers[i]);
            buf << "float4 bump = bumpmapStage(sampFFE" << i+1 << ", IN." << texcoordNames[i+1] << ", " << arg3 << ");";
            texSamplers[i+1] = "bump";
            break;

        case D3DTOP_BUMPENVMAPLUMINANCE:
            arg3 = buildArgString(D3DTA_TEXTURE, "", texSamplers[i]);
            buf << "float4 bump = bumpmapLumiStage(sampFFE" << i+1 << ", IN." << texcoordNames[i+1] << ", " << arg3 << ");";
            texSamplers[i+1] = "bump";
            break;

        case D3DTOP_DOTPRODUCT3:
            arg1 = buildArgString(s->colorArg1, ".rgb", texSamplers[i]);
            arg2 = buildArgString(s->colorArg2, ".rgb", texSamplers[i]);
            buf << "c.rgb = dot(" << arg1 << ", " << arg2 << ");";
            break;

        case D3DTOP_MULTIPLYADD:
            arg1 = buildArgString(s->colorArg1, ".rgb", texSamplers[i]);
            arg2 = buildArgString(s->colorArg2, ".rgb", texSamplers[i]);
            arg3 = buildArgString(s->colorArg0, ".rgb", texSamplers[i]);
            buf << "c.rgb = " << arg1 << " * " << arg2 << " + " << arg3 << ";";
            break;

        default:
            buf << "unsupported";
            break;
        }
        buf << " \\\n";
    }

    genTexturing = buf.str();

    // Final fog application
    buf.str(string());

    switch (sk.fogMode) {
    case 0:     // Fog disabled
        break;
    case 1:     // Standard fog mode
        buf << "c.rgb = lerp(FogCol1, c.rgb, fog); ";
        break;
    case 2:     // Additive objects should fog towards black, which preserves the destination correctly
        buf << "c.rgb *= fog; ";
        break;
    }

    genFog = buf.str();

    // Compile HLSL through insertions into a template file
    const D3DXMACRO generatedCode[] = {
        "FFE_VB_COUPLING", genVBCoupling.c_str(),
        "FFE_SHADER_COUPLING", genPSCoupling.c_str(),
        "FFE_TRANSFORM_SKIN", genTransform.c_str(),
        "FFE_TEXCOORDS_TEXGEN", genTexcoords.c_str(),
        "FFE_VERTEX_COLOUR", genVertexColour.c_str(),
        "FFE_LIGHTS_ACTIVE", genLightCount.c_str(),
        "FFE_VERTEX_MATERIAL", genMaterial.c_str(),
        "FFE_TEXTURING", genTexturing.c_str(),
        "FFE_FOG_APPLICATION", genFog.c_str(),
        0, 0
    };

    // Create effect while pooling constants with everything else
    ID3DXEffect* effectFFE;
    ID3DXBuffer* errors;

    //LOG::logline("-- Generating replacement fixed function shader");
    //sk.log();

    HRESULT hr = D3DXCreateEffectFromFile(device, "Data Files\\shaders\\XE FixedFuncEmu.fx", generatedCode, 0, D3DXSHADER_OPTIMIZATION_LEVEL3|D3DXFX_LARGEADDRESSAWARE, constantPool, &effectFFE, &errors);

    if (hr != D3D_OK) {
        LOG::logline("!! Generating FFE shader: compile error %xh", hr);
        if (errors) {
            LOG::logline("!! %s", errors->GetBufferPointer());
            errors->Release();
        }
        LOG::logline("");
        effectDefaultPurple->AddRef();
        effectFFE = effectDefaultPurple;
    }

    cacheEffects[sk] = effectFFE;
    return effectFFE;
}

string buildArgString(DWORD arg, const string& mask, const string& sampler) {
    stringstream s;

    switch (arg) {
    case D3DTA_DIFFUSE:
        s << "diffuse" << mask;
        break;
    case D3DTA_CURRENT:
        s << "c" << mask;
        break;
    case D3DTA_TEXTURE:
        s << sampler << mask;
        break;
    default:
        s << "unsupported";
        break;
    }

    return s.str();
}

void FixedFunctionShader::release() {
    for (auto& i : cacheEffects) {
        if (i.second) {
            i.second->Release();
        }
    }

    shaderLRU.effect = NULL;
    shaderLRU.last_sk = ShaderKey();
    cacheEffects.clear();
    effectDefaultPurple->Release();
}



// ShaderKey - Captures a generatable shader configuration

FixedFunctionShader::ShaderKey::ShaderKey(const RenderedState* rs, const FragmentState* frs, const LightState* lightrs) {
    memset(this, 0, sizeof(ShaderKey));         // Clear padding bits for compares

    uvSets = (rs->fvf & D3DFVF_TEXCOUNT_MASK) >> D3DFVF_TEXCOUNT_SHIFT;
    usesSkinning = rs->vertexBlendState ? 1 : 0;
    vertexColour = (rs->fvf & D3DFVF_DIFFUSE) ? 1 : 0;

    // Match constant material, diffuse+ambient vcol, or emissive vcol
    if (rs->useLighting) {
        heavyLighting = (lightrs->active.size() > 4) ? 1 : 0;
        vertexMaterial = 1;

        if (vertexColour) {
            if (rs->matSrcDiffuse == D3DMCS_COLOR1) {
                vertexMaterial = 2;
            } else if (rs->matSrcEmissive == D3DMCS_COLOR1) {
                vertexMaterial = 3;
            }
        }
    }

    if (rs->useFog) {
        // Match premultipled alpha or additive blending
        if (rs->blendEnable && (rs->srcBlend == D3DBLEND_ONE || rs->destBlend == D3DBLEND_ONE)) {
            fogMode = 2;
        } else {
            fogMode = 1;
        }
    }

    for (int i = 0; i != 8; ++i) {
        const FragmentState::Stage* s = &frs->stage[i];

        if (s->colorOp == D3DTOP_DISABLE) {
            activeStages = i;
            break;
        }

        stage[i].colorOp = s->colorOp;
        stage[i].colorArg1 = s->colorArg1;
        stage[i].colorArg2 = s->colorArg2;
        stage[i].colorArg0 = s->colorArg0;
        stage[i].texcoordIndex = s->texcoordIndex & 3;
        stage[i].texcoordGen = s->texcoordIndex >> 16;

        if (s->colorOp == D3DTOP_BUMPENVMAP || s->colorOp == D3DTOP_BUMPENVMAPLUMINANCE) {
            usesBumpmap = 1;
            bumpmapStage = i;
        }
        if (stage[i].texcoordGen) {
            usesTexgen = 1;
            texgenStage = i;
        }
    }
}

bool FixedFunctionShader::ShaderKey::operator<(const ShaderKey& other) const {
    return memcmp(this, &other, sizeof(ShaderKey)) < 0;
}

bool FixedFunctionShader::ShaderKey::operator==(const ShaderKey& other) const {
    return memcmp(this, &other, sizeof(ShaderKey)) == 0;
}

std::size_t FixedFunctionShader::ShaderKey::hasher::operator()(const ShaderKey& k) const {
    DWORD z[9];
    memcpy(&z, &k, sizeof(z));
    return (z[0] << 16) ^ z[1] ^ z[2] ^ z[3] ^ z[4] ^ z[5] ^ z[6] ^ z[7] ^ z[8];
}

void FixedFunctionShader::ShaderKey::log() const {
    const char* opsymbols[] = { "?", "disable", "select1", "select2", "mul", "mul2x", "mul4x", "add", "addsigned", "addsigned2x", "sub", "?", "blend.diffuse", "blend.texture", "?", "?", "?", "?", "?", "?", "?", "?", "bump", "bump.l", "dp3", "mad", "?" };
    const char* argsymbols[] = { "diffuse", "current", "texture", "tfactor", "specular", "temp", "constant" };

    LOG::logline("   Input state: UVs:%d skin:%d vcol:%d lights:%d vmat:%d fogm:%d", uvSets, usesSkinning, vertexColour, vertexMaterial ? (heavyLighting ? 8 : 4) : 0, vertexMaterial, fogMode);
    LOG::logline("   Texture stages:");
    for (int i = 0; i != activeStages; ++i) {
        if (stage[i].colorOp != D3DTOP_MULTIPLYADD) { // or D3DTOP_LERP (unused)
            LOG::logline("    [%d] % 12s    %s, %s            uv %d texgen %d", i,
                         opsymbols[stage[i].colorOp], argsymbols[stage[i].colorArg1], argsymbols[stage[i].colorArg2],
                         stage[i].texcoordIndex, stage[i].texcoordGen);
        } else {
            LOG::logline("    [%d] % 12s    %s, %s, %s   uv %d texgen %d", i,
                         opsymbols[stage[i].colorOp], argsymbols[stage[i].colorArg1], argsymbols[stage[i].colorArg2], argsymbols[stage[i].colorArg0],
                         stage[i].texcoordIndex, stage[i].texcoordGen);
        }
    }
    LOG::logline("");
}
