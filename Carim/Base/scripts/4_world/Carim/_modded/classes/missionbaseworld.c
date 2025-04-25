#ifndef CARIM_MissionBaseWorld
#define CARIM_MissionBaseWorld

modded class MissionBaseWorld {
    void CarimManagerPartyMarkerServerRegister(string id, CarimModelPartyMarkers markers);
    void CarimManagerPartyMarkerClientAddServer(string id, CarimModelPartyMarkers markers);

    void CarimManagerPartyPositionClientSetPositions(array<CarimModelPartyPlayer> players);

    void CarimManagerPartyRegistrationClientSetMutual(array<string> ids);
    void CarimManagerPartyRegistrationServerRegister(string id, array<string> ids);
}
#endif
