
#include "api.h"

#include "configuration.h"
#include "distantland.h"
#include "mmefunctiondefs.h"
#include "mgeversion.h"
#include "postshaders.h"
#include "userhud.h"



static api::MacroFunctions macroFns = {
    MacroFunctions::TakeScreenshot,
    MacroFunctions::ToggleStatusText,
    MacroFunctions::ToggleFpsCounter,
    MacroFunctions::ShowLastMessage,
    MacroFunctions::ToggleBlending,
    MacroFunctions::ToggleShaders,
    MacroFunctions::ToggleDistantLand,
    MacroFunctions::ToggleShadows,
    MacroFunctions::ToggleGrass,
    MacroFunctions::ToggleLightingMode,
    MacroFunctions::ToggleTransparencyAA,
    MacroFunctions::IncreaseViewRange,
    MacroFunctions::DecreaseViewRange,
    MacroFunctions::ToggleZoom,
    MacroFunctions::ResetEnableZoom,
    MacroFunctions::IncreaseZoom,
    MacroFunctions::DecreaseZoom,
    MacroFunctions::ToggleCrosshair,
    MacroFunctions::NextTrack,
    MacroFunctions::DisableMusic,
    MacroFunctions::IncreaseFOV,
    MacroFunctions::DecreaseFOV,
    MacroFunctions::HaggleMore1,
    MacroFunctions::HaggleMore10,
    MacroFunctions::HaggleMore100,
    MacroFunctions::HaggleMore1000,
    MacroFunctions::HaggleMore10000,
    MacroFunctions::HaggleLess1,
    MacroFunctions::HaggleLess10,
    MacroFunctions::HaggleLess100,
    MacroFunctions::HaggleLess1000,
    MacroFunctions::HaggleLess10000,
    MacroFunctions::MoveForward3PCam,
    MacroFunctions::MoveBack3PCam,
    MacroFunctions::MoveLeft3PCam,
    MacroFunctions::MoveRight3PCam,
    MacroFunctions::MoveDown3PCam,
    MacroFunctions::MoveUp3PCam,
};

namespace api {
    int MGEAPIv1::getAPIVersion() const {
        return supported_api_version;
    }

    int MGEAPIv1::getMGEVersion() const {
        return MGE_MWSE_VERSION;
    }

    const MacroFunctions* MGEAPIv1::macroFunctions() {
        return &macroFns;
    }

    static_assert(sizeof(DistantLandRenderConfig) == sizeof(Configuration.DL));

	DistantLandRenderConfig* MGEAPIv1::getDistantLandRenderConfig() {
	    // Requires updating when Configuration.DL struct changes.
	    return reinterpret_cast<DistantLandRenderConfig*>(&Configuration.DL);
	}

    bool MGEAPIv1::reloadDistantLand() {
        return DistantLand::reloadShaders();
    }

    LightingMode MGEAPIv1::lightingModeGet() {
        if (Configuration.MGEFlags & USE_FFESHADER) {
            return (Configuration.PerPixelLightFlags == 0) ? LightingMode::PerPixelAll : LightingMode::PerPixelInteriorOnly;
        }
        return LightingMode::Vertex;
    }

    void MGEAPIv1::lightingModeSet(LightingMode mode) {
        switch (mode) {
            case LightingMode::Vertex:
                Configuration.MGEFlags &= ~USE_FFESHADER;
                Configuration.PerPixelLightFlags = 0;
                break;
            case LightingMode::PerPixelAll:
                Configuration.MGEFlags |= USE_FFESHADER;
                Configuration.PerPixelLightFlags = 0;
                break;
            case LightingMode::PerPixelInteriorOnly:
                Configuration.MGEFlags |= USE_FFESHADER;
                Configuration.PerPixelLightFlags = 1;
                break;
        }
    }

    bool MGEAPIv1::zoomGetEnabled() {
        return (Configuration.MGEFlags & ZOOM_ASPECT) != 0;
    }

    void MGEAPIv1::zoomSetEnabled(bool enable) {
        if (enable) {
            Configuration.MGEFlags |= ZOOM_ASPECT;
        }
        else {
            Configuration.MGEFlags &= ~ZOOM_ASPECT;
        }
    }

    void MGEAPIv1::zoomIn(float amount) {
        Configuration.CameraEffects.zoom = std::max(1.0f, std::min(Configuration.CameraEffects.zoom + amount, 40.0f));
    }

    void MGEAPIv1::zoomOut(float amount) {
        Configuration.CameraEffects.zoom = std::max(1.0f, std::min(Configuration.CameraEffects.zoom - amount, 40.0f));
    }

    float MGEAPIv1::zoomGetZoom() const {
        return Configuration.CameraEffects.zoom;
    }

    void MGEAPIv1::zoomSetZoom(float amount) {
        Configuration.CameraEffects.zoom = std::max(1.0f, amount);
    }

    void MGEAPIv1::zoomSetZoomContinuous(float rate, float rateTarget) {
        Configuration.CameraEffects.zoomRate = std::max(1.0f, rate);
        Configuration.CameraEffects.zoomRateTarget = std::max(1.0f, rateTarget);
    }

    void MGEAPIv1::zoomStop() const {
        Configuration.CameraEffects.zoomRateTarget = 0;
        Configuration.CameraEffects.zoomRate = 0;
    }

    bool MGEAPIv1::cameraShakeGetEnabled() {
        return Configuration.CameraEffects.shake;
    }

    void MGEAPIv1::cameraShakeSetEnabled(bool enable) {
        Configuration.CameraEffects.shake = enable;
    }

    float MGEAPIv1::cameraShakeGetAcceleration() {
        return Configuration.CameraEffects.shakeAccel;
    }

    void MGEAPIv1::cameraShakeSetAcceleration(float value) {
        Configuration.CameraEffects.shakeAccel = value;
    }

    float MGEAPIv1::cameraShakeGetMagnitude() {
        return Configuration.CameraEffects.shakeMagnitude;
    }

    void MGEAPIv1::cameraShakeSetMagnitude(float value) {
        Configuration.CameraEffects.shakeMagnitude = value;
    }

    void MGEAPIv1::hudReset() {
        MGEhud::reset();
    }

    bool MGEAPIv1::hudLoad(const char* name, const char* texture) {
        auto id = MGEhud::load(name, texture);
        return id != MGEhud::invalid_hud_id;
    }

    void MGEAPIv1::hudFree(const char* name) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::free(id);
    }

    bool MGEAPIv1::hudGetEnabled(const char* name) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return false; }

        return MGEhud::getEnabled(id);
    }

    void MGEAPIv1::hudSetEnabled(const char* name, bool enable) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setEnabled(id, enable);
    }

    void MGEAPIv1::hudPosition(const char* name, float x, float y) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setPosition(id, x, y);
    }

    void MGEAPIv1::hudScale(const char* name, float scaleX, float scaleY) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setScale(id, scaleX, scaleY);
    }

    void MGEAPIv1::hudFullscreen(const char* name) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setFullscreen(id);
    }

    void MGEAPIv1::hudSetEffect(const char* name, const char* effectPath) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setEffect(id, effectPath);
    }

    void MGEAPIv1::hudSetFloat(const char* name, const char* variableName, float value) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setEffectFloat(id, variableName, value);
    }

    void MGEAPIv1::hudSetInt(const char* name, const char* variableName, int value) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setEffectInt(id, variableName, value);
    }

    void MGEAPIv1::hudSetVector4(const char* name, const char* variableName, float value[4]) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setEffectVec4(id, variableName, value);
    }

    void MGEAPIv1::hudSetTexture(const char* name, const char* texturePath) {
        MGEhud::hud_id id = MGEhud::resolveName(name);
        if (id == MGEhud::invalid_hud_id) { return; }

        MGEhud::setTexture(id, texturePath);
    }

    ShaderHandle MGEAPIv1::shaderLoad(const char* id) {
        // TODO
        return nullptr;
    }

    bool MGEAPIv1::shaderReload(ShaderHandle handle) {
        auto shader = static_cast<MGEShader*>(handle);
        // TODO
        return false;
    }

    ShaderHandle MGEAPIv1::shaderGetShader(const char* id) {
        return ShaderHandle(PostShaders::findShader(id));
    }

    ShaderHandle MGEAPIv1::shaderListShaders(size_t index) {
        auto shaders = PostShaders::listShaders();
        return (index < shaders.size()) ? ShaderHandle(&shaders[index]) : nullptr;
    }

    const char* MGEAPIv1::shaderGetName(ShaderHandle handle) {
        auto shader = static_cast<MGEShader*>(handle);
        return shader->name.c_str();
    }

    bool MGEAPIv1::shaderGetEnabled(ShaderHandle handle) {
        auto shader = static_cast<MGEShader*>(handle);
        return shader->enabled;
    }

    void MGEAPIv1::shaderSetEnabled(ShaderHandle handle, bool enable) {
        auto shader = static_cast<MGEShader*>(handle);
        shader->enabled = enable;
    }

    bool MGEAPIv1::shaderGetVariableInfo(ShaderHandle handle, size_t index, ShaderVariableInfo* out_info) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameter(0, index);

        if (param_handle) {
            D3DXPARAMETER_DESC desc;
            if (SUCCEEDED(shader->effect->GetParameterDesc(param_handle, &desc))) {
                // Initially label as unknown type 'x'
                strncpy_s(out_info->name, desc.Name, sizeof(out_info->name));
                out_info->valueType = 'x';

                if (desc.Class == D3DXPC_SCALAR) {
                    switch (desc.Type) {
                    case D3DXPT_BOOL:
                        out_info->valueType = 'b';
                        break;
                    case D3DXPT_INT:
                        out_info->valueType = 'i';
                        break;
                    case D3DXPT_FLOAT:
                        out_info->valueType = 'f';
                        break;
                    case D3DXPT_STRING:
                        out_info->valueType = 's';
                        break;
                    }
                }
                else if (desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT) {
                    switch (desc.Elements) {
                    case 2:
                        out_info->valueType = '2';
                        break;
                    case 3:
                        out_info->valueType = '3';
                        break;
                    case 4:
                        out_info->valueType = '4';
                        break;
                    }
                }
                else if (desc.Class == D3DXPC_MATRIX_COLUMNS && desc.Type == D3DXPT_FLOAT) {
                    out_info->valueType = 'm';
                }
                return true;
            }
        }

        // No more variables found.
        return false;
    }

    bool MGEAPIv1::shaderGetBool(ShaderHandle handle, const char* variableName, bool* out_value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            // Pointers to BOOL and bool aren't compatible.
            BOOL temp;
            auto success = shader->effect->GetBool(param_handle, &temp) == D3D_OK;
            *out_value = temp;

            return success;
        }
        return false;
    }

    bool MGEAPIv1::shaderGetFloat(ShaderHandle handle, const char* variableName, float* out_value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->GetFloat(param_handle, out_value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderGetInt(ShaderHandle handle, const char* variableName, int* out_value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->GetInt(param_handle, out_value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderGetString(ShaderHandle handle, const char* variableName, const char** out_value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->GetString(param_handle, out_value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderGetVector(ShaderHandle handle, const char* variableName, float* out_values, size_t count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->GetFloatArray(param_handle, out_values, count) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetBool(ShaderHandle handle, const char* variableName, bool value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetBool(param_handle, value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetFloat(ShaderHandle handle, const char* variableName, float value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetFloat(param_handle, value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetInt(ShaderHandle handle, const char* variableName, int value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetInt(param_handle, value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetString(ShaderHandle handle, const char* variableName, const char* value) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetString(param_handle, value) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetVector(ShaderHandle handle, const char* variableName, float* values, size_t count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetFloatArray(param_handle, values, count) == D3D_OK;
        }
        return false;
    }

    void MGEAPIv1::weatherScatteringGet(float* inscatter, float* outscatter) {
        memcpy(inscatter, &DistantLand::atmInscatter.r, 3 * sizeof(float));
        memcpy(outscatter, &DistantLand::atmOutscatter.r, 3 * sizeof(float));
    }

    void MGEAPIv1::weatherScatteringSet(float inscatter[3], float outscatter[3]) {
        memcpy(&DistantLand::atmInscatter.r, inscatter, 3 * sizeof(float));
        memcpy(&DistantLand::atmOutscatter.r, outscatter, 3 * sizeof(float));
    }

    void MGEAPIv1::weatherDistantFogGet(int weatherID, float* fogDistMult, float* fogOffset) {
        if (weatherID >= 0 && weatherID <= 9) {
            *fogDistMult = Configuration.DL.FogD[weatherID];
            *fogOffset = Configuration.DL.FgOD[weatherID];
        }
    }

    void MGEAPIv1::weatherDistantFogSet(int weatherID, float fogDistMult, float fogOffset) {
        if (weatherID >= 0 && weatherID <= 9) {
            Configuration.DL.FogD[weatherID] = fogDistMult;
            Configuration.DL.FgOD[weatherID] = fogOffset;
        }
    }

    void MGEAPIv1::weatherPerPixelLightGet(int weatherID, float* sunMult, float* ambMult) {
        if (weatherID >= 0 && weatherID <= 9) {
            *sunMult = Configuration.Lighting.SunMult[weatherID];
            *ambMult = Configuration.Lighting.AmbMult[weatherID];
        }
    }

    void MGEAPIv1::weatherPerPixelLightSet(int weatherID, float sunMult, float ambMult) {
        if (weatherID >= 0 && weatherID <= 9) {
            Configuration.Lighting.SunMult[weatherID] = sunMult;
            Configuration.Lighting.AmbMult[weatherID] = ambMult;
        }
    }
}
