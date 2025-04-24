#ifndef CARIM_CarimMenuPartyNametag
#define CARIM_CarimMenuPartyNametag

class CarimMenuPartyNametag extends CarimMenuPartyMarker {
    static const int CARIM_HEALTH_LEVELS[] = {GameConstants.STATE_PRISTINE, GameConstants.STATE_WORN, GameConstants.STATE_DAMAGED, GameConstants.STATE_BADLY_DAMAGED, GameConstants.STATE_RUINED};

    ref array<ref ImageWidget> carimHealths = new array<ref ImageWidget>;

    // TODO: double-check that this relates to the correct levels to show
    // as the hud shown to the player is different than the icon. Maybe
    // there are more granular levels in the hud?
    int carimHealthLevel = CARIM_HEALTH_LEVELS[0];

    override Widget Init() {
        super.Init();

        foreach(int level : CARIM_HEALTH_LEVELS) {
            carimHealths.Insert(ImageWidget.Cast(layoutRoot.FindAnyWidget("IconHealth" + level.ToString())));
        }
        carimIcon.Show(false);

        return layoutRoot;
    }

    override string CarimGetName() {
        if (carimPlayer && carimPlayer.GetIdentity()) {
            return carimPlayer.GetIdentity().GetName();
        } else {
            return super.CarimGetName();
        }
    }

    override vector CarimGetPosition() {
        if (carimPlayer && carimPlayer.IsAlive()) {
            return carimPlayer.GetPosition();
        } else {
            return super.CarimGetPosition();
        }
    }

    int CarimGetHealth() {
        if (carimPlayer) {
            return carimPlayer.GetHealthLevel();
        } else {
            return carimHealthLevel;
        }
    }

    override vector CarimGetMarkerOffset() {
        return "0 1.3 0";
    }

    override void CarimUpdate() {
        super.CarimUpdate();

        int currentHealth = CarimGetHealth();
        foreach(int level : CARIM_HEALTH_LEVELS) {
            carimHealths.Get(level).Show(level == currentHealth);
        }
    }
}

#endif
