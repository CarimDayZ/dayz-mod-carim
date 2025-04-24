#ifndef CARIM_CarimManagerCompass
#define CARIM_CarimManagerCompass

class CarimManagerCompass extends Managed {
    ref CarimMenuCompass menu = new CarimMenuCompass;

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimCompassToggle")) {
                if (menu) {
                    menu.CarimToggleHeading();
                } else {
                    menu = new CarimMenuCompass;
                }
            }
        }
    }
}

#endif
