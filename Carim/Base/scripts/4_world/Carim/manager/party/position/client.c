#ifndef CARIM_CarimManagerPartyPositionClient
#define CARIM_CarimManagerPartyPositionClient

class CarimManagerPartyPositionClient extends Managed {
    CarimModelPartyRegistrations registrations;
    ref map<string, ref CarimModelPartyPlayer> serverPositions = new map<string, ref CarimModelPartyPlayer>;
    ref map<string, ref CarimMenuPartyNametag> nametagMenus = new map<string, ref CarimMenuPartyNametag>;
    ref map<string, ref CarimMenuPartyList> listMenus = new map<string, ref CarimMenuPartyList>;

    void CarimManagerPartyPositionClient(CarimModelPartyRegistrations inputRegistrations) {
        registrations = inputRegistrations;
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SyncMenus, 2000, true);
    }

    void ~CarimManagerPartyPositionClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SyncMenus);
    }

    void SetPositions(array<CarimModelPartyPlayer> positions) {
        serverPositions.Clear();
        foreach(CarimModelPartyPlayer position : positions) {
            serverPositions.Insert(position.id, position);
        }
    }

    void SyncMenus() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity() && player.IsAlive()) {
            AddAndUpdateNametags();
            RemoveInvalidNametags();
            UpdateNametagsWithLocalPlayers();
            UpdateMenuListSorting();
        }
    }

    void AddAndUpdateMenus() {
    }

    void AddAndUpdateNametags() {
        foreach(string id, CarimModelPartyPlayer position : serverPositions) {
            string name = id.Substring(0, 4);
            if (registrations.registrations.Contains(id)) {
                name = registrations.registrations.Get(id);
            }
            if (!nametagMenus.Contains(id)) {
                nametagMenus.Insert(id, new CarimMenuPartyNametag(name, position.position));
            }
            nametagMenus.Get(id).carimName = name;
            nametagMenus.Get(id).carimPosition = position.position;
            nametagMenus.Get(id).carimHealthLevel = position.healthLevel;
        }
    }

    void RemoveInvalidNametags() {
        auto ids = nametagMenus.GetKeyArray();
        foreach(string id : ids) {
            if (!serverPositions.Contains(id) && nametagMenus.Contains(id)) {
                nametagMenus.Get(id).Close();
                nametagMenus.Remove(id);
            }
        }
    }

    void UpdateNametagsWithLocalPlayers() {
        string activePlayerId;
        PlayerBase activePlayer = PlayerBase.Cast(GetGame().GetPlayer());
        if (activePlayer && activePlayer.GetIdentity()) {
            activePlayerId = activePlayer.GetIdentity().GetId();
        }
        foreach(PlayerBase player : GetClientPlayerBases()) {
            if (player && player.GetIdentity() && player.IsAlive()) {
                string id = player.GetIdentity().GetId();
                if (nametagMenus.Contains(id) && serverPositions.Contains(id)) {
                    nametagMenus.Get(id).carimPlayer = player;
                }
            }
        }
    }

    void UpdateMenuListSorting() {
        // menu ids should always be in registrations
        // if there's duplicate indicies (i.e. overlapping list items), then
        // that assumption is false for some reason and needs fixed here
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(registrations.registrations);
        int index = 0;
        foreach(auto id : sortedIds) {
            if (nametagMenus.Contains(id)) {
                nametagMenus.Get(id).carimListIndex = index;
                ++index;
            }
        }
    }

    static array<PlayerBase> GetClientPlayerBases() {
        array<PlayerBase> players = new array<PlayerBase>;
        foreach(Man m : ClientData.m_PlayerBaseList) {
            players.Insert(PlayerBase.Cast(m));
        }
        return players;
    }
}

#endif
