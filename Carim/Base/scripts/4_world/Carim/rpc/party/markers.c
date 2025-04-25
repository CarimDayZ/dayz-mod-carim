#ifndef CARIM_CarimRPCPartyMarkers
#define CARIM_CarimRPCPartyMarkers

class CarimRPCPartyMarkers extends CarimRPCBase<Param2<string, CarimModelPartyMarkers>> {
    override int GetType() {
        return CarimRPCTypesParty.MARKERS;
    }

    override void HandleServer(PlayerIdentity sender, Param2<string, CarimModelPartyMarkers> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyMarkerServerRegister(sender.GetId(), params.param2);
    }

    override void HandleClient(PlayerIdentity sender, Param2<string, CarimModelPartyMarkers> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyMarkerClientAddServer(params.param1, params.param2);
    }
}

#endif
