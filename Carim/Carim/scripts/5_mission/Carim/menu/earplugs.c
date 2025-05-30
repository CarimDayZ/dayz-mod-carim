
class CarimEarPlugs extends UIScriptedMenu {
    ImageWidget carimImage;
    bool carimIsVisible = false;
	float m_iconalpha = 0;

    override Widget Init() {
        if (!layoutRoot) {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/earplugs.layout");
            carimImage = ImageWidget.Cast(layoutRoot.FindAnyWidget("icon"));
			carimImage.LoadImageFile( 0, "Carim/Carim/gui/textures/EarPlugs_icon.edds" );
        }
        return layoutRoot;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);

        if (layoutRoot) {
            Mission mission = GetGame().GetMission();
            IngameHud hud = IngameHud.Cast(mission.GetHud());
            if (hud && hud.GetHudVisibility().IsContextFlagActive(IngameHudVisibility.HUD_HIDE_FLAGS)) {
                layoutRoot.Show(false);
            } else {
                if (carimIsVisible) {
                    GetGame().GetSoundScene().SetSoundVolume(0.1, 1);
					layoutRoot.Show(true);
                } else {
					GetGame().GetSoundScene().SetSoundVolume(1, 1);
					layoutRoot.Show(false);
				}
                layoutRoot.Show(carimIsVisible);
            }
        }
    }

    void CarimToggleHeading() {
        carimIsVisible = !carimIsVisible;
    }
}
