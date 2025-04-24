#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    CarimManagerPartyMarkerServer carimManagerPartyMarkerServer;
    CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;

    ref CarimModelServerSettings carimModelServerSettings = new CarimModelServerSettings;

    ref CarimModelPartyParties carimModelPartyParties = new CarimModelPartyParties;

    override void OnInit() {
        super.OnInit();

        carimModelServerSettings.Load();

        if (CarimEnabled.Party()) {
            carimManagerPartyMarkerServer = new CarimManagerPartyMarkerServer;
            carimManagerPartyPositionServer = new CarimManagerPartyPositionServer;
            carimManagerPartyRegistrationServer = new CarimManagerPartyRegistrationServer;
        }
    }
}

#endif
