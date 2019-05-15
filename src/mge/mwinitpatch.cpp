
#include "mge/mwinitpatch.h"
#include "mge/configuration.h"
#include "mge/mwbridge.h"


// Disable intro movies on initialization as the logo appears before game init
void MWInitPatch::disableIntroMovies()
{
    MWBridge::get()->disableIntroMovies();
}


// Override UI scaling callback: set new UI scaling and mouse bounds
static void _stdcall onUIScaleInit()
{
    MWBridge::get()->setUIScale(Configuration.UIScale);
}

void MWInitPatch::patchUIScale()
{
    // User interface still needs to be scaled, normally done by the D3DDevice proxy
    // Without the proxy, patch Morrowind UI creation instead
    MWBridge::get()->patchUIConfigure(onUIScaleInit);
}
