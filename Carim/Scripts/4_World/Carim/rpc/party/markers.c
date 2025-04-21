#ifndef CarimRPCPartyMarkers
#define CarimRPCPartyMarkers

class CarimRPCPartyMarkers extends CarimRPCBase<Param2<string, CarimModelPartyMarkers>> {
    override int GetType() {
        return CarimRPCTypesParty.MARKERS;
    }

    override void HandleServer(PlayerIdentity sender, Param2<string, CarimModelPartyMarkers> params) {
        // Register markers from client player
        CarimManagerPartyMarkerServerSingleton.Get().Register(sender.GetId(), params.param2);
    }

    override void HandleClient(PlayerIdentity sender, Param2<string, CarimModelPartyMarkers> params) {
        // Receive markers from server and show them
        CarimManagerPartyMarkerClientSingleton.Get().AddServer(params.param1, params.param2);
    }
}

#endif
