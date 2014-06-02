
#include <algorithm>
#include "funczoom.h"
#include "mge/configuration.h"



MWSEINSTRUCTION_DECLARE_VTABLE(mwseEnableZoom)

// EnableZoom
bool mwseEnableZoom::execute(mwseInstruction *_this)
{
    Configuration.MGEFlags |= ZOOM_ASPECT;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseDisableZoom)

// DisableZoom
bool mwseDisableZoom::execute(mwseInstruction *_this)
{
    Configuration.MGEFlags &= ~ZOOM_ASPECT;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseToggleZoom)

// ToggleZoom
bool mwseToggleZoom::execute(mwseInstruction *_this)
{
    Configuration.MGEFlags ^= ZOOM_ASPECT;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomIn)

// ZoomIn
bool mwseZoomIn::execute(mwseInstruction *_this)
{
    Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom + 0.0625f, 40.0f);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomOut)

// ZoomOut
bool mwseZoomOut::execute(mwseInstruction *_this)
{
    Configuration.Zoom.zoom = std::max(1.0f, Configuration.Zoom.zoom - 0.0625f);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomInBy)

// ZoomInBy <float scale>
bool mwseZoomInBy::execute(mwseInstruction *_this)
{
    VMFLOAT x;
    if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom + x, 8.0f);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoomOutBy)

// ZoomOutBy <float scale>
bool mwseZoomOutBy::execute(mwseInstruction *_this)
{
    VMFLOAT x;
    if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.zoom = std::max(1.0f, Configuration.Zoom.zoom - x);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseSetZoom)

// SetZoom <float scale>
bool mwseSetZoom::execute(mwseInstruction *_this)
{
    VMFLOAT x;
    if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.zoom = std::max(1.0f, x);
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseZoom)

// Zoom <float rate>
bool mwseZoom::execute(mwseInstruction *_this)
{
    VMFLOAT x;
    if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.rateTarget = x;
    Configuration.Zoom.rate = (x < 0) ? x : 0;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseStopZoom)

// StopZoom
bool mwseStopZoom::execute(mwseInstruction *_this)
{
    Configuration.Zoom.rateTarget = 0;
    Configuration.Zoom.rate = 0;
    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseGetZoom)

// GetZoom -> returns <float scale>
bool mwseGetZoom::execute(mwseInstruction *_this)
{

    return _this->vmPush((VMFLOAT)Configuration.Zoom.zoom);
}

