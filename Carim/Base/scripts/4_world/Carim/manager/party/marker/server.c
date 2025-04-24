#ifndef CARIM_CarimManagerPartyMarkerServer
#define CARIM_CarimManagerPartyMarkerServer

class CarimManagerPartyMarkerServer extends Managed {
    ref map<string, ref CarimModelPartyMarkers> markers = new map<string, ref CarimModelPartyMarkers>;
    ref CarimRPCPartyMarkers rpc = new CarimRPCPartyMarkers;
    CarimModelPartyParties parties;

    void CarimManagerPartyMarkerServer(CarimModelPartyParties inputParties) {
        parties = inputParties;
    }

    void Register(string id, CarimModelPartyMarkers playerMarkers) {
        markers.Set(id, playerMarkers);

        // Send markers to mutual members
        if (parties.mutuals.Contains(id)) {
            auto idMap = CarimManagerPartyUtil.GetServerIdPlayerMap();
            foreach(string playerId : parties.mutuals.Get(id).ToArray()) {
                if (idMap.Contains(playerId)) {
                    PlayerBase player = idMap.Get(playerId);
                    if (player.GetIdentity() && player.IsAlive()) {
                        auto params = new Param2<string, CarimModelPartyMarkers>(id, playerMarkers);
                        rpc.Send(player, params, player.GetIdentity());
                    }
                }
            }
        }
    }
}

#endif
