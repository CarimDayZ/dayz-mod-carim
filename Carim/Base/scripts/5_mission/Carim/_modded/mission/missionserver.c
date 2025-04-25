#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    ref CarimManagerPartyMarkerServer carimManagerPartyMarkerServer;
    ref CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    ref CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;

    ref CarimModelServerSettings carimModelServerSettings = new CarimModelServerSettings;

    ref CarimModelPartyParties carimModelPartyParties;

    void MissionServer() {
        carimModelSettings.Load();
        CarimLogging.settings = carimModelSettings;

        carimModelServerSettings.Load();

        if (CarimEnabled.Party()) {
            carimModelPartyParties = new CarimModelPartyParties(carimModelServerSettings.adminIds);

            carimManagerPartyMarkerServer = new CarimManagerPartyMarkerServer(carimModelPartyParties);
            carimManagerPartyPositionServer = new CarimManagerPartyPositionServer(carimModelPartyParties);
            carimManagerPartyRegistrationServer = new CarimManagerPartyRegistrationServer(carimModelPartyParties);
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
