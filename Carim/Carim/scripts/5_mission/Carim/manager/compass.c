class CarimManagerCompass extends Managed {
    ref CarimMenuCompass menu;

    void CarimManagerCompass() {
        menu = new CarimMenuCompass;
        menu.Init();
    }

    void OnUpdate(float timeslice) {
        if (CarimUtil.CheckInput("UACarimCompassToggle")) {
            menu.CarimToggleHeading();
        }
        menu.Update(timeslice);
    }
}
