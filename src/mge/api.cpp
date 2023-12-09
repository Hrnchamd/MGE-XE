
#include "api.h"

#include "configuration.h"
#include "distantland.h"
#include "mmefunctiondefs.h"
#include "mgeversion.h"
#include "postshaders.h"
#include "userhud.h"
#include "mwbridge.h"
#include "support/log.h"
#include "support/pngsave.h"

#include <array>



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


    bool MGEAPIv1::loadConfig() {
        auto prevFogFlags = Configuration.MGEFlags & (EXP_FOG | USE_ATM_SCATTER);
        auto prevUIScale = Configuration.UIScale;

        bool success = Configuration.LoadSettings();

        // Update components that are dependent on changed config values
        if (success) {
            auto currFogFlags = Configuration.MGEFlags & (EXP_FOG | USE_ATM_SCATTER);
            if (prevFogFlags != currFogFlags) {
                DistantLand::reloadShaders();
            }

            if (prevUIScale != Configuration.UIScale) {
                MWBridge::get()->setUIScale(Configuration.UIScale);
            }
        }
        return success;
    }

    bool MGEAPIv1::saveConfig() {
        return Configuration.SaveSettings();
    }

    const std::array<unsigned int, 22> featureToFlagMap = {
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
        CROSSHAIR_AUTOHIDE,
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

    float MGEAPIv1::guiGetScale() {
        return Configuration.UIScale;
    }

    void MGEAPIv1::guiSetScale(float scale) {
        Configuration.UIScale = scale;
        MWBridge::get()->setUIScale(scale);
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

    float MGEAPIv1::cameraGetFoV() {
        return Configuration.ScreenFOV;
    }

    void MGEAPIv1::cameraSetFoV(float fov) {
        Configuration.ScreenFOV = fov;
    }

    void MGEAPIv1::cameraThirdPersonGetOffset(float* out_values) {
        out_values[0] = Configuration.Offset3rdPerson.x;
        out_values[1] = Configuration.Offset3rdPerson.y;
        out_values[2] = Configuration.Offset3rdPerson.z;
    }

    void MGEAPIv1::cameraThirdPersonSetOffset(float* values) {
        Configuration.Offset3rdPerson.x = values[0];
        Configuration.Offset3rdPerson.y = values[1];
        Configuration.Offset3rdPerson.z = values[2];
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

    float MGEAPIv1::shaderGetHDRReactionSpeed() {
        return Configuration.HDRReactionSpeed;
    }

    void MGEAPIv1::shaderSetHDRReactionSpeed(float speed) {
        Configuration.HDRReactionSpeed = speed;
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
                    else {
                        switch (desc.Type) {
                        case D3DXPT_BOOL:
                            valueType = 'B';
                            break;
                        case D3DXPT_INT:
                            valueType = 'I';
                            break;
                        case D3DXPT_FLOAT:
                            valueType = 'F';
                            break;
                        }
                    }
                }
                else if (desc.Class == D3DXPC_VECTOR && desc.Type == D3DXPT_FLOAT) {
                    if (desc.Elements <= 1) {
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
                    else {
                        valueType = 'V';
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

    bool MGEAPIv3::shaderGetBoolArray(ShaderHandle handle, const char* variableName, int* out_values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            D3DXPARAMETER_DESC desc;
            shader->effect->GetParameterDesc(param_handle, &desc);

            // Check if array fits into array provided.
            if (desc.Elements <= *count) {
                *count = desc.Elements;
                return shader->effect->GetBoolArray(param_handle, reinterpret_cast<BOOL*>(out_values), desc.Elements) == D3D_OK;
            }
        }
        return false;
    }

    bool MGEAPIv3::shaderGetIntArray(ShaderHandle handle, const char* variableName, int* out_values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            D3DXPARAMETER_DESC desc;
            shader->effect->GetParameterDesc(param_handle, &desc);

            // Check if array fits into array provided.
            if (desc.Elements <= *count) {
                *count = desc.Elements;
                return shader->effect->GetIntArray(param_handle, out_values, desc.Elements) == D3D_OK;
            }
        }
        return false;
    }

    bool MGEAPIv3::shaderGetVectorArray(ShaderHandle handle, const char* variableName, float* out_values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            D3DXPARAMETER_DESC desc;
            shader->effect->GetParameterDesc(param_handle, &desc);

            // Check if array fits into array provided.
            if (desc.Elements <= *count) {
                *count = desc.Elements;
                return shader->effect->GetVectorArray(param_handle, reinterpret_cast<D3DXVECTOR4*>(out_values), desc.Elements) == D3D_OK;
            }
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

    bool MGEAPIv3::shaderSetBoolArray(ShaderHandle handle, const char* variableName, const int* values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetBoolArray(param_handle, reinterpret_cast<const BOOL*>(values), *count) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv3::shaderSetIntArray(ShaderHandle handle, const char* variableName, const int* values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetIntArray(param_handle, values, *count) == D3D_OK;
        }
        return false;
    }

    bool MGEAPIv3::shaderSetVectorArray(ShaderHandle handle, const char* variableName, const float* values, size_t* count) {
        auto shader = static_cast<MGEShader*>(handle);
        auto param_handle = shader->effect->GetParameterByName(0, variableName);

        if (param_handle) {
            return shader->effect->SetVectorArray(param_handle, reinterpret_cast<const D3DXVECTOR4*>(values), *count) == D3D_OK;
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

    //
    // MGEAPI v2
    //

    std::string saveScreenshotPath;
    static void saveScreenshotCallback(IDirect3DSurface9* surface);

    void MGEAPIv2::saveScreenshot(const char* path, bool captureWithUI) {
        // Requires distant land to be loaded
        if (!DistantLand::ready) {
            return;
        }
        if (!path) {
            return;
        }

        saveScreenshotPath = path;
        DistantLand::requestCapture(&saveScreenshotCallback, captureWithUI);
    }

    static void saveScreenshotCallback(IDirect3DSurface9* surface) {
        const std::array strImageExtensions{ ".bmp", ".jpg", ".dds", ".png", ".tga" };
        const std::array formats{ D3DXIFF_BMP, D3DXIFF_JPG, D3DXIFF_DDS, D3DXIFF_PNG, D3DXIFF_TGA };
        const char* path = saveScreenshotPath.c_str();
        D3DXIMAGE_FILEFORMAT outputFormat = D3DXIFF_PNG;

        if (!surface) {
            LOG::logline("mge.saveScreenshot failed - Surface error");
            return;
        }

        // Check for overwrite
        if (GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES) {
            LOG::logline("mge.saveScreenshot failed - %s already exists", path);
            return;
        }

        // Detect format from extension
        if (saveScreenshotPath.length() > 4) {
            auto ext = saveScreenshotPath.substr(saveScreenshotPath.length() - 4, 4);
            for (int i = 0; i < formats.size(); ++i) {
                if (ext == strImageExtensions[i]) {
                    outputFormat = formats[i];
                    break;
                }
            }
        }

        // Save screenshot to desired format
        if (outputFormat == D3DXIFF_PNG) {
            // D3DX PNG support does full compression which takes >1 sec to save an image
            // Use a non-compressing PNG encoder for reasonable screenshot times
            bool success = false;
            D3DSURFACE_DESC desc;
            D3DLOCKED_RECT rect;
            surface->GetDesc(&desc);

            if (surface->LockRect(&rect, NULL, D3DLOCK_READONLY) == D3D_OK) {
                success = pngSaveBGRA(path, rect.pBits, desc.Width, desc.Height, rect.Pitch);
                surface->UnlockRect();
            }
            if (!success) {
                LOG::logline("mge.saveScreenshot failed - pngSave error");
            }
        }
        else {
            HRESULT hr = D3DXSaveSurfaceToFile(path, outputFormat, surface, NULL, NULL);
            if (FAILED(hr)) {
                LOG::logline("mge.saveScreenshot failed - D3DX Error %lx", hr);
            }
        }
    }

    void MGEAPIv2::weatherScatteringSkylightGet(float* skylight) {
        memcpy(skylight, &DistantLand::atmSkylightScatter.x, 4 * sizeof(float));
    }

    void MGEAPIv2::weatherScatteringSkylightSet(float skylight[4]) {
        memcpy(&DistantLand::atmSkylightScatter.x, skylight, 4 * sizeof(float));
    }

    float MGEAPIv3::nearRenderDistanceGet() {
        return MWBridge::get()->GetViewDistance();
    }

    void MGEAPIv3::nearRenderDistanceSet(float distance) {
        distance = std::max(2500.0f, std::min(7168.0f, distance));
        MWBridge::get()->SetViewDistance(distance);
    }
}
