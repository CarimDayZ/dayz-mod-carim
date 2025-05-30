class CarimManagerEarPlugs extends Managed {
    ref CarimEarPlugs menu;

    void CarimManagerEarPlugs() {
        menu = new CarimEarPlugs;
        menu.Init();
    }

    void OnUpdate(float timeslice) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimEarPlugsToggle")) {
                menu.CarimToggleHeading();
            }
        }
        menu.Update(timeslice);
    }
}
