
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


    const std::array<unsigned int, 21> featureToFlagMap = {
		FPS_COUNTER,
		DISPLAY_MESSAGES,
		USE_MENU_CACHING,
		NO_MW_MGE_BLEND,
		NO_MW_SUNGLARE,
		USE_HW_SHADER,
		TRANSPARENCY_AA,
		USE_HDR,
		EXP_FOG,
		USE_ATM_SCATTER,
		USE_GRASS,
		USE_SHADOWS,
		USE_DISTANT_WATER,
		USE_DISTANT_LAND,
		USE_DISTANT_STATICS,
		REFLECTIVE_WATER,
		REFLECT_NEAR,
		REFLECT_INTERIOR,
		REFLECT_SKY,
		BLUR_REFLECTIONS,
		DYNAMIC_RIPPLES,
    };

    bool MGEAPIv1::featureGetEnabled(RenderFeature feature) {
        int i = static_cast<int>(feature);
        if (i >= 0 && i < featureToFlagMap.size()) {
            auto flag = featureToFlagMap[i];
            return (Configuration.MGEFlags & flag) != 0;
        }
        return false;
    }

    void MGEAPIv1::featureSetEnabled(RenderFeature feature, bool enable) {
        int i = static_cast<int>(feature);
        if (i >= 0 && i < featureToFlagMap.size()) {
            auto flag = featureToFlagMap[i];
            if (enable) {
                Configuration.MGEFlags |= flag;
            }
            else {
                Configuration.MGEFlags &= ~flag;
            }
        }
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
        Configuration.CameraEffects.zoomRate = rate;
        Configuration.CameraEffects.zoomRateTarget = rateTarget;
    }

    void MGEAPIv1::zoomStop() const {
        Configuration.CameraEffects.zoomRate = 0;
        Configuration.CameraEffects.zoomRateTarget = 0;
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
        // Check if shader is not already loaded
        auto s = PostShaders::findShader(id);
        if (!s) {
            // Try loading shader
            if (PostShaders::loadNewShader(id)) {
                s = PostShaders::findShader(id);
            }
        }
        return ShaderHandle(s);
    }

    bool MGEAPIv1::shaderReload(ShaderHandle handle) {
        auto shader = static_cast<MGEShader*>(handle);
        shader->timestamp = 0;
        return PostShaders::updateShaderChain();
    }

    ShaderHandle MGEAPIv1::shaderGetShader(const char* id) {
        return ShaderHandle(PostShaders::findShader(id));
    }

    ShaderHandle MGEAPIv1::shaderListShaders(size_t index) {
        const auto& shaders = PostShaders::listShaders();
        if (index < shaders.size()) {
            MGEShader *s = &*shaders[index];
            return ShaderHandle(s);
        }
        return nullptr;
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

    int MGEAPIv1::shaderGetPriority(ShaderHandle handle) {
        auto shader = static_cast<MGEShader*>(handle);
        return shader->priority;
    }

    void MGEAPIv1::shaderSetPriority(ShaderHandle handle, int value) {
        auto shader = static_cast<MGEShader*>(handle);
        shader->priority = value;
        PostShaders::orderShaders();
    }

    bool MGEAPIv1::shaderGetVariableInfo(ShaderHandle handle, size_t index, ShaderVariableInfo* out_info) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameter(0, index);

        if (param_handle) {
            D3DXPARAMETER_DESC desc;
            if (SUCCEEDED(shader->effect->GetParameterDesc(param_handle, &desc))) {
                // Initially label variable as unknown type 'x'
                std::snprintf(out_info->name, sizeof(out_info->name), "%s", desc.Name);
                char valueType = 'x';

                if (desc.Class == D3DXPC_SCALAR) {
                    if (desc.Elements <= 1) {
                        switch (desc.Type) {
                        case D3DXPT_BOOL:
                            valueType = 'b';
                            break;
                        case D3DXPT_INT:
                            valueType = 'i';
                            break;
                        case D3DXPT_FLOAT:
                            valueType = 'f';
                            break;
                        case D3DXPT_STRING:
                            valueType = 's';
                            break;
                        }
                    }
                    else if (desc.Type == D3DXPT_FLOAT) {
                        valueType = 'a';
                    }
                }
                else if (desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT) {
                    switch (desc.Columns) {
                    case 2:
                        valueType = '2';
                        break;
                    case 3:
                        valueType = '3';
                        break;
                    case 4:
                        valueType = '4';
                        break;
                    }
                }
                else if (desc.Class == D3DXPC_MATRIX_ROWS && desc.Type == D3DXPT_FLOAT) {
                    valueType = 'm';
                }

                out_info->valueType = valueType;
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

    bool MGEAPIv1::shaderGetFloatArray(ShaderHandle handle, const char* variableName, float* out_values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            D3DXPARAMETER_DESC desc;
            shader->effect->GetParameterDesc(param_handle, &desc);

            // Check if array fits into array provided.
            if (desc.Elements <= *count) {
                *count = desc.Elements;
                return shader->effect->GetFloatArray(param_handle, out_values, desc.Elements) == D3D_OK;
            }
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

    bool MGEAPIv1::shaderGetMatrix(ShaderHandle handle, const char* variableName, float* out_values) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->GetMatrix(param_handle, reinterpret_cast<D3DXMATRIX*>(out_values)) == D3D_OK;
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

    bool MGEAPIv1::shaderSetFloatArray(ShaderHandle handle, const char* variableName, const float* values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetFloatArray(param_handle, values, *count) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetVector(ShaderHandle handle, const char* variableName, const float* values, size_t count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetFloatArray(param_handle, values, count) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv1::shaderSetMatrix(ShaderHandle handle, const char* variableName, const float* values) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetMatrix(param_handle, reinterpret_cast<const D3DXMATRIX*>(values)) == D3D_OK;
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
