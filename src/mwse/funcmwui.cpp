
#include "funcmwui.h"



namespace MWUI {

    typedef short Handle;

    struct Control {
        char tag_x;
        int unknown_4;
        char* name;
        size_t name_len;
        int unknown_10;
        Handle handle;
        int unknown_18;
        Control** childrenBegin;
        Control** childrenEnd;
        Control** childrenStorageEnd;
        Control* parent;
        int unknown_2c[86];
    };

    typedef Control* (__cdecl* GetMenu_t)(Handle);
    typedef Control* (__thiscall* GetMenuControl_t)(Control*, Handle);
    typedef void (__thiscall* SetVisible_t)(Control*, char);

    const GetMenu_t GetMenu = (GetMenu_t)0x595370;
    const GetMenuControl_t GetMenuControl = (GetMenuControl_t)0x582de0;
    const SetVisible_t SetVisible = (SetVisible_t)0x57f2a0;

    const Handle* pMenuMulti = (Handle*)0x7d4ab0;
    const Handle* pMenuMulti_bottom_row = (Handle*)0x7d4a38;
    const Handle* pMenuMulti_fillbars_layout = (Handle*)0x7d4b3e;
    const Handle* pMenuMulti_npc_health_bar = (Handle*)0x7d4b20;
    const Handle* pMenuMulti_weapon_layout = (Handle*)0x7d49fc;
    const Handle* pMenuMulti_magic_layout = (Handle*)0x7d4a74;
    const Handle* pMenuMulti_magic_icons_layout = (Handle*)0x7d4a28;
    const Handle* pMenuMap_panel = (Handle*)0x7d45ae;

    Control* selectControl(int n) {
        Control* menu = GetMenu(*pMenuMulti);
        if (menu) {
            if (n >= 0 && n <= 6) {
                const Handle* sel[] = {
                    pMenuMulti_bottom_row, pMenuMulti_fillbars_layout, pMenuMulti_npc_health_bar, pMenuMulti_weapon_layout,
                    pMenuMulti_magic_layout, pMenuMulti_magic_icons_layout, pMenuMap_panel
                };
                return GetMenuControl(menu, *sel[n]);
            }
        }
        return nullptr;
    }
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseUIShow)

// UIShow <control id>
bool mwseUIShow::execute(mwseInstruction* _this) {
    VMLONG controlId;

    if (!_this->vmPop(&controlId)) {
        return false;
    }

    MWUI::Control* c = MWUI::selectControl(controlId);
    if (c) {
        MWUI::SetVisible(c, 1);
    }

    return true;
}


MWSEINSTRUCTION_DECLARE_VTABLE(mwseUIHide)

// UIHide <control id>
bool mwseUIHide::execute(mwseInstruction* _this) {
    VMLONG controlId;

    if (!_this->vmPop(&controlId)) {
        return false;
    }

    MWUI::Control* c = MWUI::selectControl(controlId);
    if (c) {
        MWUI::SetVisible(c, 0);
    }

    return true;
}
