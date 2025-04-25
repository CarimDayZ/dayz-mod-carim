#ifndef CARIM_CarimManagerPartyPositionClient
#define CARIM_CarimManagerPartyPositionClient

class CarimManagerPartyPositionClientMenus extends Managed {
    ref CarimMenuPartyNametag nametag;
    ref CarimMenuPartyList list;

    void CarimManagerPartyPositionClientMenus(string name, vector position) {
        nametag = new CarimMenuPartyNametag(name, position);
        nametag.Init();
        list = new CarimMenuPartyList(name, position);
        list.Init();
    }

    void SetName(string name) {
        nametag.carimName = name;
        list.carimName = name;
    }

    void SetPosition(vector position) {
        nametag.carimPosition = position;
        list.carimPosition = position;
    }

    void SetHealthLevel(int healthLevel) {
        nametag.carimHealthLevel = healthLevel;
        list.carimHealthLevel = healthLevel;
    }

    void SetPlayer(PlayerBase player) {
        nametag.carimPlayer = player;
        list.carimPlayer = player;
    }

    void SetIndex(int index) {
        list.carimListIndex = index;
    }

    void Close() {
        nametag.Close();
        list.Close();
    }
}

class CarimManagerPartyPositionClient extends Managed {
    CarimModelPartyRegistrations registrations;
    ref map<string, ref CarimModelPartyPlayer> serverPositions = new map<string, ref CarimModelPartyPlayer>;
    ref map<string, ref CarimManagerPartyPositionClientMenus> menus = new map<string, ref CarimManagerPartyPositionClientMenus>;

    void CarimManagerPartyPositionClient(CarimModelPartyRegistrations inputRegistrations) {
        registrations = inputRegistrations;
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SyncMenus, 1000, true);
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
            AddAndUpdateMenus();
            RemoveInvalidMenus();
            UpdateMenusWithLocalPlayers();
            UpdateListSorting();
        }
    }

    void AddAndUpdateMenus() {
        foreach(string id, CarimModelPartyPlayer position : serverPositions) {
            string name = id.Substring(0, 4);
            if (registrations.registrations.Contains(id)) {
                name = registrations.registrations.Get(id);
            }
            if (!menus.Contains(id)) {
                menus.Insert(id, new CarimManagerPartyPositionClientMenus(name, position.position));
            }
            menus.Get(id).SetName(name);
            menus.Get(id).SetPosition(position.position);
            menus.Get(id).SetHealthLevel(position.healthLevel);
        }
    }

    void RemoveInvalidMenus() {
        auto ids = menus.GetKeyArray();
        foreach(string id : ids) {
            if (!serverPositions.Contains(id) && menus.Contains(id)) {
                menus.Get(id).Close();
                menus.Remove(id);
            }
        }
    }

    void UpdateMenusWithLocalPlayers() {
        string activePlayerId;
        PlayerBase activePlayer = PlayerBase.Cast(GetGame().GetPlayer());
        if (activePlayer && activePlayer.GetIdentity()) {
            activePlayerId = activePlayer.GetIdentity().GetId();
        }
        foreach(PlayerBase player : GetClientPlayerBases()) {
            if (player && player.GetIdentity() && player.IsAlive()) {
                string id = player.GetIdentity().GetId();
                if (menus.Contains(id) && serverPositions.Contains(id)) {
                    menus.Get(id).SetPlayer(player);
                }
            }
        }
    }

    void UpdateListSorting() {
        // menu ids should always be in registrations
        // if there's duplicate indicies (i.e. overlapping list items), then
        // that assumption is false for some reason and needs fixed here
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(registrations.registrations);
        int index = 0;
        foreach(auto id : sortedIds) {
            if (menus.Contains(id)) {
                menus.Get(id).SetIndex(index);
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
