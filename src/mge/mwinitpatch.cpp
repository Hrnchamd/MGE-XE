
#include "mge/mwinitpatch.h"
#include "mge/configuration.h"
#include "mge/mwbridge.h"



// Override UI scaling call: set new UI scaling and mouse bounds
static void _stdcall onUIScaleInit()
{
    DECLARE_MWBRIDGE
    mwBridge->setUIScale(Configuration.UIScale);
}


void MWInitPatch::patchUIScale()
{
    // User interface still needs to be scaled, normally done by the D3DDevice proxy
    // Without the proxy, patch Morrowind UI creation instead
    DECLARE_MWBRIDGE
    mwBridge->patchUIConfigure(onUIScaleInit);
}
