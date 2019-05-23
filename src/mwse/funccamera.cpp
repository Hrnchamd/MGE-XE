
#include "funccamera.h"
#include "mge/configuration.h"

#include <algorithm>



MWSEINSTRUCTION_DECLARE_VTABLE(mwseEnableZoom)

// EnableZoom
bool mwseEnableZoom::execute(mwseInstruction* _this) {
    Configuration.MGEFlags |= ZOOM_ASPECT;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseDisableZoom)

// DisableZoom
bool mwseDisableZoom::execute(mwseInstruction* _this) {
    Configuration.MGEFlags &= ~ZOOM_ASPECT;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseToggleZoom)

// ToggleZoom
bool mwseToggleZoom::execute(mwseInstruction* _this) {
    Configuration.MGEFlags ^= ZOOM_ASPECT;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomIn)

// ZoomIn
bool mwseZoomIn::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.zoom = std::min(Configuration.CameraEffects.zoom + 0.0625f, 40.0f);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomOut)

// ZoomOut
bool mwseZoomOut::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.zoom = std::max(1.0f, Configuration.CameraEffects.zoom - 0.0625f);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomInBy)

// ZoomInBy <float scale>
bool mwseZoomInBy::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.zoom = std::min(Configuration.CameraEffects.zoom + x, 8.0f);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomOutBy)

// ZoomOutBy <float scale>
bool mwseZoomOutBy::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.zoom = std::max(1.0f, Configuration.CameraEffects.zoom - x);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetZoom)

// SetZoom <float scale>
bool mwseSetZoom::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.zoom = std::max(1.0f, x);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoom)

// Zoom <float rate>
bool mwseZoom::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.zoomRateTarget = x;
    Configuration.CameraEffects.zoomRate = (x < 0) ? x : 0;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseStopZoom)

// StopZoom
bool mwseStopZoom::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.zoomRateTarget = 0;
    Configuration.CameraEffects.zoomRate = 0;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetZoom)

// GetZoom -> returns <float scale>
bool mwseGetZoom::execute(mwseInstruction* _this) {
    return _this->vmPush((VMFLOAT)Configuration.CameraEffects.zoom);
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseEnableCameraShake)

// EnableCameraShake
bool mwseEnableCameraShake::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.shake = true;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseDisableCameraShake)

// DisableCameraShake
bool mwseDisableCameraShake::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.shake = false;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetCameraShakeMagnitude)

// SetCameraShakeMagnitude <float>
bool mwseSetCameraShakeMagnitude::execute(mwseInstruction* _this) {
    _this->vmPop(&Configuration.CameraEffects.shakeMagnitude);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseCameraShakeAccel)

// CameraShakeAccel <float>
bool mwseCameraShakeAccel::execute(mwseInstruction* _this) {
    _this->vmPop(&Configuration.CameraEffects.shakeAccel);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseStopCameraShakeAccel)

// StopCameraShakeAccel
bool mwseStopCameraShakeAccel::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.shakeAccel = 0;
	return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseRotateScreenBy)

// RotateScreenBy <float rads>
bool mwseRotateScreenBy::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.rotateUpdate = true;
    Configuration.CameraEffects.rotation += x;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetScreenRotation)

// SetScreenRotation <float rads>
bool mwseSetScreenRotation::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.rotateUpdate = true;
    Configuration.CameraEffects.rotation = x;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseScreenSpin)

// ScreenSpin
bool mwseScreenSpin::execute(mwseInstruction* _this) {
    VMFLOAT x;
    if (!_this->vmPop(&x)) { return false; }

    Configuration.CameraEffects.rotateUpdate = true;
    Configuration.CameraEffects.rotationRate = x;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseStopScreenSpin)

// StopScreenSpin
bool mwseStopScreenSpin::execute(mwseInstruction* _this) {
    Configuration.CameraEffects.rotateUpdate = true;
    Configuration.CameraEffects.rotationRate = 0;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetScreenRotation)

// GetScreenRotation -> <float rads>
bool mwseGetScreenRotation::execute(mwseInstruction* _this) {
    VMFLOAT x = Configuration.CameraEffects.rotation;
    return _this->vmPush(x);
}
