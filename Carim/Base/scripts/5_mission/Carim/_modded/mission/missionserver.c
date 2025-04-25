#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    ref CarimManagerPartyMarkerServer carimManagerPartyMarkerServer;
    ref CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    ref CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;

    ref CarimModelServerSettings carimModelServerSettings = new CarimModelServerSettings;

    ref CarimModelPartyParties carimModelPartyParties;

    override void OnInit() {
        super.OnInit();

        carimModelServerSettings.Load();

        if (CarimEnabled.Party()) {
            carimManagerPartyMarkerServer = new CarimManagerPartyMarkerServer(carimModelPartyParties);
            carimManagerPartyPositionServer = new CarimManagerPartyPositionServer(carimModelPartyParties);
            carimManagerPartyRegistrationServer = new CarimManagerPartyRegistrationServer(carimModelPartyParties);

            carimModelPartyParties = new CarimModelPartyParties(carimModelServerSettings.adminIds);
        }
    }

    override void CarimManagerPartyMarkerServerRegister(string id, CarimModelPartyMarkers markers) {
        carimManagerPartyMarkerServer.Register(id, markers);
    }

    override void CarimManagerPartyRegistrationServerRegister(string id, array<string> ids) {
        carimManagerPartyRegistrationServer.Register(id, ids);
    }
}

#endif
