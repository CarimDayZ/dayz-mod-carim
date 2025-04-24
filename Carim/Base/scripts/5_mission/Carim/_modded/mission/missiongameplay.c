#ifndef CARIM_MissionGameplay
#define CARIM_MissionGameplay

modded class MissionGameplay {
    CarimManagerAutorun carimManagerAutorun;
    CarimManagerChat carimManagerChat;
    CarimManagerCompass carimManagerCompass;
    CarimManagerPartyMarkerClient carimManagerPartyMarkerClient;
    CarimManagerPartyPositionClient carimManagerPartyPositionClient;
    CarimManagerPartyRegistrationClient carimManagerPartyRegistrationClient;

    ref CarimModelChatSettings carimModelChatSettings = new CarimModelChatSettings;
    ref CarimModelPartyMarkers carimModelPartyMarkers = new CarimModelPartyMarkers;
    ref CarimModelPartyRegistrations carimModelPartyRegistrations = new CarimModelPartyRegistrations;

    override void OnInit() {
        super.OnInit();

        if (CarimEnabled.Autorun()) {
            carimManagerAutorun = new CarimManagerAutorun;
        }
        if (CarimEnabled.Chat()) {
            carimModelChatSettings.Load();
            carimManagerChat = new CarimManagerChat;
        }
        if (CarimEnabled.Compass()) {
            carimManagerCompass = new CarimManagerCompass;
        }
        if (CarimEnabled.Party()) {
            carimModelPartyMarkers.Load();
            carimModelPartyRegistrations.Load();
            carimManagerPartyMarkerClient = new CarimManagerPartyMarkerClient(carimModelPartyMarkers, carimModelPartyRegistrations);
            carimManagerPartyPositionClient = new CarimManagerPartyPositionClient(carimModelPartyRegistrations);
            carimManagerPartyRegistrationClient = new CarimManagerPartyRegistrationClient(carimModelPartyRegistrations);
        }
    }

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        if (CarimEnabled.Autorun()) {
            carimManagerAutorun.OnUpdate();
        }
        if (CarimEnabled.Chat()) {
            carimManagerChat.OnUpdate();
        }
        if (CarimEnabled.Compass()) {
            carimManagerCompass.OnUpdate();
        }
        if (CarimEnabled.Party()) {
            carimManagerPartyRegistrationClient.OnUpdate();
            carimManagerPartyMarkerClient.OnUpdate();
        }
    }

    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (CarimEnabled.Party() && !menu) {
            switch (id) {
                case CarimMenuParty.REGISTER:
                    menu = new CarimMenuPartyRegister;
                    carimManagerPartyRegistrationClient.menu = CarimMenuPartyRegister.Cast(menu);
                    break;
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}

#endif
