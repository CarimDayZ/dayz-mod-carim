class CarimManagerPartyClient extends Managed {
    ref CarimModelPartyMarkers markers;
    ref CarimModelPartyPings pings;
    ref CarimModelPartyPositions positions;
    ref CarimModelPartyRegistrations registrations;

    ref array<string> mutual = new array<string>;

    ref CarimMenuPartyRegister menuRegister;

    ref CarimRPCPartyPings rpcPing = new CarimRPCPartyPings;
    ref CarimRPCPartyRegister rpcRegister = new CarimRPCPartyRegister;

    void CarimManagerPartyClient(CarimModelPartyMarkers iMarkers, CarimModelPartyPings iPings, CarimModelPartyPositions iPositions, CarimModelPartyRegistrations iRegistrations) {
        markers = iMarkers;
        pings = iPings;
        positions = iPositions;
        registrations = iRegistrations;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.InitialSend, 2000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.PeriodicSend, 60000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdatePositionsWithLocalPlayers, 2000, true);
    }

    void ~CarimManagerPartyClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialSend);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.PeriodicSend);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.UpdatePositionsWithLocalPlayers);
    }

    void InitialSend() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            PeriodicSend();
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialSend);
        }
    }

    void PeriodicSend() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            SendRegistration();
            SendPings();
        }
    }

    void UpdatePositionsWithLocalPlayers() {
        auto players = CarimUtil.GetClientPlayerBases();
        foreach(PlayerBase player : players) {
            if (player && player.GetIdentity() && player.IsAlive()) {
                string id = CarimUtil.GetIdentifier(player.GetIdentity());
                if (positions.markers.Contains(id) && positions.markers.Get(id).Count() > 0) {
                    if (!positions.markers.Get(id).Get(0).carimPlayer) {
                        CarimLogging.Debug(this, "Adding local player to positions " + id);
                        positions.markers.Get(id).Get(0).carimPlayer = player;
                    }
                }
            }
        }
    }

    void SendRegistration() {
        array<string> keys = registrations.registrations.GetKeyArray();
        auto params = new Param1<array<string>>(keys);
        rpcRegister.Send(GetGame().GetPlayer(), params);
    }

    void SendPings() {
        Param2<string, CarimModelPartyPings> params = new Param2<string, CarimModelPartyPings>("", pings);
        rpcPing.Send(GetGame().GetPlayer(), params);
    }

    void OnUpdate(float timeslice) {
        if (CarimUtil.CheckInput("UACarimPartyPing")) {
            vector position = GetRaycastPosition();
            if (position != vector.Zero) {
                CarimLogging.Debug(this, "Input ping");
                AddPing(position);
            }
        }
        if (CarimUtil.CheckInput("UACarimPartyPingClear")) {
            CarimLogging.Debug(this, "Input clear");
            ResetPings();
        }
        if (CarimUtil.CheckInput("UAUIBack")) {
            if (menuRegister && GetGame().GetUIManager().GetMenu() == menuRegister) {
                menuRegister.UnlockControls();
                menuRegister.Close();
            }
        }
        if (CarimUtil.CheckInput("UACarimPartyMenu")) {
            if (menuRegister) {
                menuRegister.Close();
            } else if (!GetGame().GetUIManager().GetMenu()) {
                menuRegister = CarimMenuPartyRegister.Cast(GetGame().GetUIManager().EnterScriptedMenu(CarimMenuParty.REGISTER, null));
            }
        }
        if (menuRegister) {
            menuRegister.Update(timeslice);
        }
    }

    void AddPing(vector position) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        auto mark = CarimMapMarker.CarimNew(position, player.GetIdentity().GetName(), CfgGameplayHandler.GetCarimPartyColorPingIconLocal(), CarimMapMarkerTypes.ARROW_1, CarimUtil.GetIdentifier(player.GetIdentity()));
        pings.Add(mark);
        SendPings();
    }

    void ResetPings() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        pings.Clear(CarimUtil.GetIdentifier(player.GetIdentity()));
        SendPings();
    }

    void SetMutual(array<string> players) {
        mutual.Clear();
        mutual.Copy(players);
    }

    void AddPlayerToParty(string id) {
        registrations.Add(id, CarimUtil.GetClientPlayerIdentities().Get(id));
        PeriodicSend();
    }

    void RemovePlayerFromParty(string id) {
        registrations.Remove(id);
        mutual.RemoveItem(id);
        PeriodicSend();
    }

    static vector GetRaycastPosition() {
        vector begin = GetGame().GetCurrentCameraPosition() + GetGame().GetCurrentCameraDirection();
        vector end = begin + GetGame().GetCurrentCameraDirection() * 8000;
        vector contactPos;
        vector contactDir;
        int contactComponent;
        if (DayZPhysics.RaycastRV(begin, end, contactPos, contactDir, contactComponent)) {
            return contactPos;
        }
        return vector.Zero;
    }
}
