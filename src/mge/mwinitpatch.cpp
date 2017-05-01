
#include "mge/mwinitpatch.h"
#include "mge/configuration.h"
#include "mge/mwbridge.h"


// Disable intro movies on initialization as the logo appears before game init
void MWInitPatch::disableIntroMovies()
{
    DECLARE_MWBRIDGE
    mwBridge->disableIntroMovies();
}


// Override UI scaling callback: set new UI scaling and mouse bounds
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
