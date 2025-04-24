#ifndef CARIM_CarimManagerPartyRegistrationServer
#define CARIM_CarimManagerPartyRegistrationServer

class CarimManagerPartyRegistrationServer extends Managed {
    CarimModelPartyParties parties;
    ref CarimRPCPartyRegister rpc = new CarimRPCPartyRegister;

    void CarimManagerPartyRegistrationServer(CarimModelPartyParties inputParties) {
        parties = inputParties;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Send, 10000, true);
    }

    void ~CarimManagerPartyRegistrationServer() {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Send);
    }

    void Register(string id, array<string> players) {
        string jsonPlayers;
        if (CarimLogging.TraceEnabled()) {
            JsonSerializer().WriteToString(players, false, jsonPlayers);
        }
        CarimLogging.Trace(this, "Register " + id + ", " + jsonPlayers);
        CarimLogging.Trace(this, "Before: " + parties.Repr());
        bool changed = parties.Register(id, players);
        CarimLogging.Trace(this, "After: " + parties.Repr());
        if (changed) {
            Send();
        }
    }

    void Send() {
        map<string, PlayerBase> idMap = CarimManagerPartyUtil.GetServerIdPlayerMap();
        foreach(string id, PlayerBase player : idMap) {
            array<string> mutuals = new array<string>;
            if (parties.mutuals.Contains(id)) {
                foreach(string mutual : parties.mutuals.Get(id).ToArray()) {
                    mutuals.Insert(mutual);
                }
            }
            Param1<array<string>> params = new Param1<array<string>>(mutuals);
            rpc.Send(player, params, player.GetIdentity());
        }
    }
}

#endif
