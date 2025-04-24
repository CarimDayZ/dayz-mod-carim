#ifndef CARIM_MissionBase
#define CARIM_MissionBase

modded class MissionBase {
    ref CarimModelSettings carimModelSettings = new CarimModelSettings;

    override void OnInit() {
        super.OnInit();

        carimModelSettings.Load();
    }
}

#endif
