#ifndef CARIM_CarimManagerPartyMarkerClient
#define CARIM_CarimManagerPartyMarkerClient

class CarimManagerPartyMarkerClient extends Managed {
    CarimModelPartyMarkers markers;
    CarimModelPartyRegistrations registrations;
    ref map<string, ref CarimModelPartyMarkers> serverMarkers = new map<string, ref CarimModelPartyMarkers>;
    ref array<ref CarimMenuPartyMarker> menus = new array<ref CarimMenuPartyMarker>;
    ref CarimRPCPartyMarkers rpc = new CarimRPCPartyMarkers;

    void CarimManagerPartyMarkerClient(CarimModelPartyMarkers inputMarkers, CarimModelPartyRegistrations inputRegistrations) {
        markers = inputMarkers;
        registrations = inputRegistrations;
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.InitialRegistration, 2000, true);
    }

    void ~CarimManagerPartyMarkerClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialRegistration);
    }

    void InitialRegistration() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            Send();
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialRegistration);
        }
    }

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimPartyPing")) {
                vector position = GetRaycastPosition();
                if (position != vector.Zero) {
                    Add(position);
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyPingClear")) {
                Reset();
            }
        }
    }

    void SyncMenus() {
        string name = "null";
        if (GetGame().GetPlayer() && GetGame().GetPlayer().GetIdentity()) {
            name = GetGame().GetPlayer().GetIdentity().GetName();
        }

        int menuIndex = 0;
        foreach(int index, vector position : markers.markers) {
            string markerName = name + " " + (markers.markers.Count() - index).ToString();
            CarimLogging.Debug(this, "Adding local marker " + markerName + " " + position.ToString() + " at index " + menuIndex.ToString());
            if (menus.Count() <= menuIndex) {
                menus.Insert(new CarimMenuPartyMarker(markerName, position));
            } else {
                menus.Get(menuIndex).carimName = markerName;
                menus.Get(menuIndex).carimPosition = position;
            }
            menuIndex++;
        }
        foreach(string id, CarimModelPartyMarkers singleServerMarkers : serverMarkers) {
            int playerIndex = 0;
            foreach(vector mark : singleServerMarkers.markers) {
                if (registrations.registrations.Contains(id)) {
                    markerName = registrations.registrations.Get(id) + " " + (singleServerMarkers.markers.Count() - playerIndex).ToString();

                    CarimLogging.Debug(this, "Adding server marker " + markerName + " " + mark.ToString() + " at index " + menuIndex.ToString());
                    if (menus.Count() <= menuIndex) {
                        auto menu = new CarimMenuPartyMarker(markerName, mark);
                        menu.Init();
                        menus.Insert(menu);
                    } else {
                        menus.Get(menuIndex).carimName = markerName;
                        menus.Get(menuIndex).carimPosition = mark;
                    }
                    playerIndex++;
                    menuIndex++;
                }
            }
        }
        for (int i = menus.Count() - 1; i >= menuIndex; --i) {
            CarimLogging.Debug(this, "Closing marker menu at index " + i.ToString());
            menus.Get(i).Close();
            menus.Remove(i);
        }
    }

    void AddServer(string id, CarimModelPartyMarkers inputMarkers) {
        serverMarkers.Set(id, inputMarkers);
        SyncMenus();
    }

    void Add(vector position) {
        markers.Add(position);
        markers.Persist();
        SyncMenus();
        Send();
    }

    void Reset() {
        markers.Clear();
        markers.Persist();
        SyncMenus();
        Send();
    }

    void Send() {
        Param2<string, CarimModelPartyMarkers> params = new Param2<string, CarimModelPartyMarkers>("", markers);
        rpc.Send(GetGame().GetPlayer(), params);
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

#endif
