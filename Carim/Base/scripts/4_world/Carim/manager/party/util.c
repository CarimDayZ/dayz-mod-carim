#ifndef CARIM_CarimManagerPartyUtil
#define CARIM_CarimManagerPartyUtil

class CarimManagerPartyUtil {
    static map<string, PlayerBase> GetServerIdPlayerMap() {
        map<string, PlayerBase> idMap = new map<string, PlayerBase>;
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach(Man man : players) {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity()) {
                idMap.Insert(player.GetIdentity().GetId(), player);
            }
        }

        return idMap;
    }
}

#endif
