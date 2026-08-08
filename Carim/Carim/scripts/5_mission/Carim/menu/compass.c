class CarimMenuCompass extends UIScriptedMenu {
    Widget carimFrame;
    ImageWidget carimImage;
    GridSpacerWidget carimSpacer;
    bool carimIsVisible = CfgGameplayHandler.GetCarimCompassShowOnSpawn();

    override Widget Init() {
        if (!layoutRoot) {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/compass.layout");
            carimFrame = layoutRoot.FindAnyWidget("FrameCompass");
            carimImage = ImageWidget.Cast(layoutRoot.FindAnyWidget("ImageCompass"));
            carimSpacer = GridSpacerWidget.Cast(layoutRoot.FindAnyWidget("spacer"));

            carimSpacer.SetColor(CfgGameplayHandler.GetCarimCompassColor());
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
                if (carimIsVisible && CarimHasNavItem()) {
                    CarimSetCompassPos();
                    layoutRoot.Update();
                }
                layoutRoot.Show(carimIsVisible && CarimHasNavItem());
            }
        }
    }

    bool CarimHasNavItem() {
        if (!CfgGameplayHandler.GetCarimCompassRequireNavItem()) {
            return true;
        }
        auto player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player) {
            auto mapNavigationBehaviour = player.GetMapNavigationBehaviour();
            if (mapNavigationBehaviour) {
                return mapNavigationBehaviour.GetNavigationType() > 0;
            }
        }
        return false;
    }

    void CarimSetCompassPos() {
        float angle = CarimGetAngle();
        float width, height, x, y;
        carimImage.GetPos(x, y);
        carimImage.GetSize(width, height);
        float center_offset = width / -2.0 + 0.5;
        if (angle > 180) {
            angle = angle - 360;
        }
        float offset = angle * (center_offset / 180.0) + center_offset;
        carimImage.SetPos(offset, y);
    }

    float CarimGetAngle() {
        vector direction = GetGame().GetCurrentCameraDirection();
        float angle = direction.VectorToAngles()[0];
        return angle;
    }

    void CarimToggleHeading() {
        carimIsVisible = !carimIsVisible;
    }
}
