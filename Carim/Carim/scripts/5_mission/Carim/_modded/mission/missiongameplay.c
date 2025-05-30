modded class MissionGameplay {
    ref CarimManagerMarker carimManagerMarker;

    ref CarimManagerAutorun carimManagerAutorun;
    ref CarimManagerChat carimManagerChat;
    ref CarimManagerCompass carimManagerCompass;
    ref CarimManagerEarPlugs carimManagerEarPlugs;
    ref CarimManagerPartyClient carimManagerPartyClient;

    ref CarimModelChatSettings carimModelChatSettings;

    ref CarimModelMapMarkers carimModelMapMarkers;
    ref CarimModelPartyPings carimModelPartyPings;
    ref CarimModelPartyMarkers carimModelPartyMarkers;
    ref CarimModelPartyPositions carimModelPartyPositions;

    ref CarimModelStaticMarkers carimModelStaticMarkers;
    ref CarimModelStaticOverrideMarkers carimModelStaticOverrideMarkers;

    ref CarimModelPartyRegistrations carimModelPartyRegistrations;

    override void OnInit() {
        super.OnInit();

        CarimInit();
        MapMarkerTypes.CarimInit();
    }

    void CarimInit() {
        CarimEnabled.Initialize();

        if (CarimEnabled.Autorun() && !carimManagerAutorun) {
            // Manager
            carimManagerAutorun = new CarimManagerAutorun;
        }
        if (CarimEnabled.Chat() && !carimManagerChat) {
            // Local
            carimModelChatSettings = new CarimModelChatSettings;
            carimModelChatSettings.Load();

            // Manager
            carimManagerChat = new CarimManagerChat;
        }
        if (CarimEnabled.Compass() && !carimManagerCompass) {
            // Manager
            carimManagerCompass = new CarimManagerCompass;
        }
        if (CarimEnabled.Map()) {
            // Local
            carimModelMapMarkers = new CarimModelMapMarkers;
            carimModelMapMarkers.Load();
        }
        if (CarimEnabled.Party() && !carimManagerPartyClient) {
            // Local
            carimModelPartyPings = new CarimModelPartyPings;
            carimModelPartyPings.Load();
            carimModelPartyRegistrations = new CarimModelPartyRegistrations;
            carimModelPartyRegistrations.Load();

            // From Server
            carimModelPartyMarkers = new CarimModelPartyMarkers;
            carimModelPartyPositions = new CarimModelPartyPositions;

            // Manager
            carimManagerPartyClient = new CarimManagerPartyClient(carimModelPartyMarkers, carimModelPartyPings, carimModelPartyPositions, carimModelPartyRegistrations);
        }
        if (CarimEnabled.EarPlugs() && !carimManagerEarPlugs) {
            carimManagerEarPlugs = new CarimManagerEarPlugs;
        }

        if (!carimManagerMarker) {
            // Manager
            carimModelStaticOverrideMarkers = new CarimModelStaticOverrideMarkers;
            carimModelStaticOverrideMarkers.Load();
            carimModelStaticMarkers = CarimModelStaticMarkers.GetFromConfig(carimModelStaticOverrideMarkers);

            carimManagerMarker = new CarimManagerMarker(carimModelPartyPings, carimModelMapMarkers, carimModelPartyMarkers, carimModelPartyPositions, carimModelStaticMarkers, carimModelPartyRegistrations);
        }
    }

    // ---------- RPC callbacks

    override void CarimPartyClientAddMarkers(string id, CarimModelPartyMarkers markers) {
        if (carimModelPartyMarkers) {
            carimModelPartyMarkers.Replace(id, markers.markers.Get(id));
        }
    }

    override void CarimPartyClientSetPositions(CarimModelPartyPositions positions) {
        if (carimModelPartyPositions) {
            foreach(string id, auto position : positions.markers) {
                if (carimModelPartyPositions.markers.Contains(id) && carimModelPartyPositions.markers.Get(id).Count() > 0) {
                    carimModelPartyPositions.markers.Get(id).Get(0).CarimCopyValues(position.Get(0));
                } else {
                    carimModelPartyPositions.Replace(id, position);
                }
            }
            // Clear no longer present positions
            foreach(string existingId, auto existingPosition : carimModelPartyPositions.markers) {
                if (!positions.markers.Contains(existingId)) {
                    carimModelPartyPositions.Clear(existingId);
                }
            }
        }
    }

    override void CarimPartyClientSetMutual(array<string> ids) {
        if (carimManagerPartyClient) {
            carimManagerPartyClient.SetMutual(ids);

            foreach(string posId, auto posPosition : carimModelPartyPositions.markers) {
                if (ids.Find(posId) < 0) {
                    carimModelPartyPositions.Clear(posId);
                }
            }

            foreach(string markId, auto markPosition : carimModelPartyMarkers.markers) {
                if (ids.Find(markId) < 0) {
                    carimModelPartyMarkers.Clear(markId);
                }
            }
        }
    }

    // ---------- RPC callbacks end

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);

        if (CarimEnabled.Autorun() && carimManagerAutorun) {
            carimManagerAutorun.OnUpdate();
        }
        if (CarimEnabled.Chat() && carimManagerChat) {
            carimManagerChat.OnUpdate(carimModelChatSettings);
        }
        if (CarimEnabled.Compass() && carimManagerCompass) {
            carimManagerCompass.OnUpdate(timeslice);
        }
        if (CarimEnabled.Party() && carimManagerPartyClient) {
            carimManagerPartyClient.OnUpdate(timeslice);
        }

        if (CarimEnabled.EarPlugs() && carimManagerEarPlugs) {
            carimManagerEarPlugs.OnUpdate(timeslice);
        }

        if (carimManagerMarker) {
            carimManagerMarker.OnUpdate(timeslice);
        }
    }

    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu;
        if (!CarimEnabled.Map() || id != MENU_MAP) {
            menu = super.CreateScriptedMenu(id);
        }
        if (!menu) {
            if (CarimEnabled.Party()) {
                switch (id) {
                    case CarimMenuParty.REGISTER:
                        menu = new CarimMenuPartyRegister(carimManagerPartyClient);
                        break;
                }
            }
            if (CarimEnabled.Map()) {
                switch (id) {
                    case MENU_MAP:
                        menu = new CarimMenuMap;
                        break;
                }
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}
