#pragma once

#include <stddef.h>

namespace api {
	static const int supported_api_version = 1;

	struct MGEAPI {
		virtual int getAPIVersion() const = 0;
		virtual int getMGEVersion() const = 0;
	};

    struct DistantLandRenderConfig {
		// API v1
        float DrawDist;
        float NearStaticEnd;
        float FarStaticEnd;
        float VeryFarStaticEnd;
        float FarStaticMinSize;
        float VeryFarStaticMinSize;
        float AboveWaterFogStart;
        float AboveWaterFogEnd;
        float BelowWaterFogStart;
        float BelowWaterFogEnd;
        float InteriorFogStart;
        float InteriorFogEnd;
        unsigned char WaterWaveHeight;
        unsigned char WaterCaustics;
        unsigned char WaterReflect;
        unsigned int ShadowResolution;
        float Wind[10];
        float FogDist[10];
        float FogOffsetDist[10];
    };

    enum struct LightingMode {
		// API v1
		Vertex = 0,
		PerPixelAll = 1,
		PerPixelInteriorOnly = 2
	};

	typedef void * ShaderHandle;

	struct ShaderVariableInfo {
		char valueType;
		char name[128];
	};

	struct MacroFunctions {
		typedef void (*Macro)();

		// API v1
		Macro TakeScreenshot;
		Macro ToggleStatusText;
		Macro ToggleFpsCounter;
		Macro ShowLastMessage;
		Macro ToggleBlending;
		Macro ToggleShaders;
		Macro ToggleDistantLand;
		Macro ToggleShadows;
		Macro ToggleGrass;
		Macro ToggleLightingMode;
		Macro ToggleTransparencyAA;
		Macro IncreaseViewRange;
		Macro DecreaseViewRange;
		Macro ToggleZoom;
		Macro ResetEnableZoom;
		Macro IncreaseZoom;
		Macro DecreaseZoom;
		Macro ToggleCrosshair;
		Macro NextTrack;
		Macro DisableMusic;
		Macro IncreaseFOV;
		Macro DecreaseFOV;
		Macro HaggleMore1;
		Macro HaggleMore10;
		Macro HaggleMore100;
		Macro HaggleMore1000;
		Macro HaggleMore10000;
		Macro HaggleLess1;
		Macro HaggleLess10;
		Macro HaggleLess100;
		Macro HaggleLess1000;
		Macro HaggleLess10000;
		Macro MoveForward3PCam;
		Macro MoveBack3PCam;
		Macro MoveLeft3PCam;
		Macro MoveRight3PCam;
		Macro MoveDown3PCam;
		Macro MoveUp3PCam;
	};

	struct MGEAPIv1 : public MGEAPI {
		virtual int getAPIVersion() const override;
		virtual int getMGEVersion() const override;

		virtual const MacroFunctions* macroFunctions();
		virtual bool reloadDistantLand();
		virtual DistantLandRenderConfig* getDistantLandRenderConfig();
		virtual LightingMode lightingModeGet();
		virtual void lightingModeSet(LightingMode mode);

		virtual bool zoomGetEnabled();
		virtual void zoomSetEnabled(bool enable);
		virtual void zoomIn(float amount);
		virtual void zoomOut(float amount);
		virtual float zoomGetZoom() const;
		virtual void zoomSetZoom(float amount);
		virtual void zoomSetZoomContinuous(float rate, float rateTarget);
		virtual void zoomStop() const;

		virtual bool cameraShakeGetEnabled();
		virtual void cameraShakeSetEnabled(bool enable);
		virtual float cameraShakeGetAcceleration();
		virtual void cameraShakeSetAcceleration(float value);
		virtual float cameraShakeGetMagnitude();
		virtual void cameraShakeSetMagnitude(float value);

		virtual void hudReset();
		virtual bool hudLoad(const char* name, const char* texture);
		virtual void hudFree(const char* name);
		virtual bool hudGetEnabled(const char* name);
		virtual void hudSetEnabled(const char* name, bool enable);
		virtual void hudPosition(const char* name, float x, float y);
		virtual void hudScale(const char* name, float scaleX, float scaleY);
		virtual void hudFullscreen(const char* name);
		virtual void hudSetEffect(const char* name, const char* effectPath);
		virtual void hudSetFloat(const char* name, const char* variableName, float value);
		virtual void hudSetInt(const char* name, const char* variableName, int value);
		virtual void hudSetVector4(const char* name, const char* variableName, float value[4]);
		virtual void hudSetTexture(const char* name, const char* texturePath);

		virtual ShaderHandle shaderLoad(const char* id);
		virtual bool shaderReload(ShaderHandle handle);
		virtual ShaderHandle shaderGetShader(const char* id);
		virtual ShaderHandle shaderListShaders(size_t index);
		virtual const char* shaderGetName(ShaderHandle handle);
		virtual bool shaderGetEnabled(ShaderHandle handle);
		virtual void shaderSetEnabled(ShaderHandle handle, bool enable);
		virtual bool shaderGetVariableInfo(ShaderHandle handle, size_t index, ShaderVariableInfo* out_info);
		virtual bool shaderGetBool(ShaderHandle handle, const char* variableName, bool* out_value);
		virtual bool shaderGetFloat(ShaderHandle handle, const char* variableName, float* out_value);
		virtual bool shaderGetInt(ShaderHandle handle, const char* variableName, int* out_value);
		virtual bool shaderGetString(ShaderHandle handle, const char* variableName, const char** out_value);
		virtual bool shaderGetVector(ShaderHandle handle, const char* variableName, float* out_values, size_t count);
		virtual bool shaderSetBool(ShaderHandle handle, const char* variableName, bool value);
		virtual bool shaderSetFloat(ShaderHandle handle, const char* variableName, float value);
		virtual bool shaderSetInt(ShaderHandle handle, const char* variableName, int value);
		virtual bool shaderSetString(ShaderHandle handle, const char* variableName, const char* value);
		virtual bool shaderSetVector(ShaderHandle handle, const char* variableName, float* values, size_t count);

		virtual void weatherScatteringGet(float* inscatter, float* outscatter);
		virtual void weatherScatteringSet(float inscatter[3], float outscatter[3]);
		virtual void weatherDistantFogGet(int weatherID, float* fogDistMult, float* fogOffset);
		virtual void weatherDistantFogSet(int weatherID, float fogDistMult, float fogOffset);
		virtual void weatherPerPixelLightGet(int weatherID, float* sunMult, float* ambMult);
		virtual void weatherPerPixelLightSet(int weatherID, float sunMult, float ambMult);
	};

	inline MGEAPIv1* api = nullptr;
	inline const MacroFunctions* macros = nullptr;
}
