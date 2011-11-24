
#include "proxydx/directin8.h"

class MGEProxyDirectInput : public ProxyDirectInput
{
public:
    static bool mouseClick;

public:
    MGEProxyDirectInput(IDirectInput8* real) : ProxyDirectInput(real) {}

    IDirectInputDevice8* factoryProxyInput(IDirectInputDevice8* device, REFGUID g);
};
