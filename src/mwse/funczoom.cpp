
#include <algorithm>
#include "funczoom.h"
#include "mge/configuration.h"



mwseInstruction::vtable_t mwseEnableZoom::vtable = { &mwseEnableZoom::destructor, &mwseEnableZoom::getOperands, &mwseEnableZoom::execute };

// EnableZoom
bool mwseEnableZoom::execute(mwseInstruction *_this)
{
    Configuration.MGEFlags |= ZOOM_ASPECT;
	return true;
}


mwseInstruction::vtable_t mwseDisableZoom::vtable = { &mwseDisableZoom::destructor, &mwseDisableZoom::getOperands, &mwseDisableZoom::execute };

// DisableZoom
bool mwseDisableZoom::execute(mwseInstruction *_this)
{
    Configuration.MGEFlags &= ~ZOOM_ASPECT;
	return true;
}


mwseInstruction::vtable_t mwseToggleZoom::vtable = { &mwseToggleZoom::destructor, &mwseToggleZoom::getOperands, &mwseToggleZoom::execute };

// ToggleZoom
bool mwseToggleZoom::execute(mwseInstruction *_this)
{
    Configuration.MGEFlags ^= ZOOM_ASPECT;
	return true;
}


mwseInstruction::vtable_t mwseZoomIn::vtable = { &mwseZoomIn::destructor, &mwseZoomIn::getOperands, &mwseZoomIn::execute };

// ZoomIn
bool mwseZoomIn::execute(mwseInstruction *_this)
{
    Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom + 0.0625f, 8.0f);
	return true;
}


mwseInstruction::vtable_t mwseZoomOut::vtable = { &mwseZoomOut::destructor, &mwseZoomOut::getOperands, &mwseZoomOut::execute };

// ZoomOut
bool mwseZoomOut::execute(mwseInstruction *_this)
{
    Configuration.Zoom.zoom = std::max(1.0f, Configuration.Zoom.zoom - 0.0625f);
	return true;
}


mwseInstruction::vtable_t mwseZoomInBy::vtable = { &mwseZoomInBy::destructor, &mwseZoomInBy::getOperands, &mwseZoomInBy::execute };

// ZoomInBy <float scale>
bool mwseZoomInBy::execute(mwseInstruction *_this)
{
	VMFLOAT x;
	if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.zoom = std::min(Configuration.Zoom.zoom + x, 8.0f);
	return true;
}


mwseInstruction::vtable_t mwseZoomOutBy::vtable = { &mwseZoomOutBy::destructor, &mwseZoomOutBy::getOperands, &mwseZoomOutBy::execute };

// ZoomOutBy <float scale>
bool mwseZoomOutBy::execute(mwseInstruction *_this)
{
	VMFLOAT x;
	if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.zoom = std::max(1.0f, Configuration.Zoom.zoom - x);
	return true;
}


mwseInstruction::vtable_t mwseSetZoom::vtable = { &mwseSetZoom::destructor, &mwseSetZoom::getOperands, &mwseSetZoom::execute };

// SetZoom <float scale>
bool mwseSetZoom::execute(mwseInstruction *_this)
{
	VMFLOAT x;
	if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.zoom = std::max(1.0f, x);
	return true;
}


mwseInstruction::vtable_t mwseZoom::vtable = { &mwseZoom::destructor, &mwseZoom::getOperands, &mwseZoom::execute };

// Zoom <float rate>
bool mwseZoom::execute(mwseInstruction *_this)
{
	VMFLOAT x;
	if(!_this->vmPop(&x)) return false;

    Configuration.Zoom.rateTarget = x;
    Configuration.Zoom.rate = 0;
	return true;
}


mwseInstruction::vtable_t mwseStopZoom::vtable = { &mwseStopZoom::destructor, &mwseStopZoom::getOperands, &mwseStopZoom::execute };

// StopZoom
bool mwseStopZoom::execute(mwseInstruction *_this)
{
    Configuration.Zoom.rateTarget = 0;
    Configuration.Zoom.rate = 0;
	return true;
}


mwseInstruction::vtable_t mwseGetZoom::vtable = { &mwseGetZoom::destructor, &mwseGetZoom::getOperands, &mwseGetZoom::execute };

// GetZoom -> returns <float scale>
bool mwseGetZoom::execute(mwseInstruction *_this)
{

	return _this->vmPush((VMFLOAT)Configuration.Zoom.zoom);
}

