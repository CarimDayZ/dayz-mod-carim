enum CarimMarkerToggles {
    NONE = 0,
    PINGS = 1,
    SERVER_MARKERS = 2,
    MARKS = 4,
    STATIC_MARKS = 8,
    POSITIONS = 16,
    NAMETAGS = 32,
    ALL = 63,
}

class CarimManagerMarker extends Managed {
    // Local
    ref CarimModelMapMarkers marks;
    ref CarimModelStaticMarkers staticMarks;
    ref CarimModelPartyPings pings;

    ref CarimModelPartyPositions nametags;

    // Server
    ref CarimModelPartyMarkers serverMarkers;
    ref CarimModelPartyPositions positions;

    ref CarimModelPartyRegistrations registrations;

    ref array<ref CarimMenuMarker> menus = new array<ref CarimMenuMarker>;
    ref array<ref CarimMenuPartyList> listMenus = new array<ref CarimMenuPartyList>;

    int toggleState = CarimMarkerToggles.ALL;

    void CarimManagerMarker(CarimModelPartyPings iPings, CarimModelMapMarkers iMarks, CarimModelPartyMarkers iServerMarkers, CarimModelPartyPositions iPositions, CarimModelStaticMarkers iStaticMarkers, CarimModelPartyRegistrations iRegistrations) {
        pings = iPings;
        marks = iMarks;
        serverMarkers = iServerMarkers;
        positions = iPositions;
        staticMarks = iStaticMarkers;
        registrations = iRegistrations;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SyncMenus, 10000, true);
    }

    void ~CarimManagerMarker() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SyncMenus);
    }

    void OnUpdate(float timeslice) {
        foreach(CarimMenuMarker menu : menus) {
            if (menu) {
                menu.Update(timeslice);
            }
        }
        foreach(CarimMenuPartyList listMenu : listMenus) {
            if (listMenu) {
                listMenu.Update(timeslice);
            }
        }

        bool needsSync = false;

        if (CarimUtil.CheckInput("UACarimToggleMarkers")) {
            // TODO: provide more granular toggling
            if (toggleState) {
                toggleState = CarimMarkerToggles.NONE;
            } else {
                toggleState = CarimMarkerToggles.ALL;
            }
            needsSync = true;
        }

        needsSync = needsSync || (pings && pings.changed);
        needsSync = needsSync || (serverMarkers && serverMarkers.changed);
        needsSync = needsSync || (positions && positions.changed);
        needsSync = needsSync || (marks && marks.changed);

        if (needsSync) {
            // Don't wait for the timed sync - do it immediately
            SyncMenus();
            if (pings) {
                pings.changed = false;
            }
            if (serverMarkers) {
                serverMarkers.changed = false;
            }
            if (positions) {
                positions.changed = false;
            }
            if (marks) {
                marks.changed = false;
            }
        }
    }

    void SyncMenus() {
        int index = 0;
        int textColor;
        int hideLessThan;
        int hideGreaterThan;
        bool showDistance;
        bool requireLineOfSight;
        if (CarimEnabled.Map()) {
            // Local markers
            textColor = CfgGameplayHandler.GetCarimMapColorText();
            hideLessThan = CfgGameplayHandler.GetCarimMapDistanceHideLessThan();
            hideGreaterThan = CfgGameplayHandler.GetCarimMapDistanceHideGreaterThan();
            showDistance = CfgGameplayHandler.GetCarimMapShowDistance();
            requireLineOfSight = CfgGameplayHandler.GetCarimMapRequireLineOfSight();
            if (toggleState & CarimMarkerToggles.MARKS) {
                index = Sync(marks, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
            }
            // Server configured markers
            if (toggleState & CarimMarkerToggles.STATIC_MARKS) {
                index = SyncWithOverrides(staticMarks, staticMarks.overrides, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
            }
        }
        if (CarimEnabled.Party()) {
            // Local pings
            textColor = CfgGameplayHandler.GetCarimPartyColorPingTextLocal();
            hideLessThan = CfgGameplayHandler.GetCarimPartyDistancePingHideLessThan();
            hideGreaterThan = CfgGameplayHandler.GetCarimPartyDistancePingHideGreaterThan();
            showDistance = CfgGameplayHandler.GetCarimPartyShowDistancePing();
            requireLineOfSight = CfgGameplayHandler.GetCarimPartyRequirePingLineOfSight();
            if (toggleState & CarimMarkerToggles.PINGS) {
                index = Sync(pings, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
            }

            // Server pings
            textColor = CfgGameplayHandler.GetCarimPartyColorPingTextServer();
            if (toggleState & CarimMarkerToggles.SERVER_MARKERS) {
                index = Sync(serverMarkers, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
            }

            // Positions
            textColor = CfgGameplayHandler.GetCarimPartyColorPlayerText();
            hideLessThan = CfgGameplayHandler.GetCarimPartyDistancePlayerHideLessThan();
            hideGreaterThan = CfgGameplayHandler.GetCarimPartyDistancePlayerHideGreaterThan();
            showDistance = CfgGameplayHandler.GetCarimPartyShowDistancePlayer();
            requireLineOfSight = CfgGameplayHandler.GetCarimPartyRequirePlayerLineOfSight();
            if (toggleState & CarimMarkerToggles.POSITIONS) {
                index = Sync(positions, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
            }

            SyncList(positions, textColor, hideLessThan, hideGreaterThan);
        }
        if (CarimEnabled.Nametag()) {
            nametags = new CarimModelPartyPositions;
            auto zones = CfgGameplayHandler.GetCarimNametagZones();
            auto players = CarimUtil.GetClientPlayerBases();
            foreach(auto player : players) {
                bool includeInNametags = false;
                foreach(auto checkZone : zones) {
                    if (vector.Distance(player.GetPosition(), checkZone.center) < checkZone.radius) {
                        includeInNametags = true;
                    }
                }
                if (includeInNametags && player.IsAlive()) {
                    CarimMapMarker newMarker = new CarimMapMarker("0 0 0", player.GetIdentity().GetName(), 0, 0);
                    newMarker.carimPlayerId = CarimUtil.GetIdentifier(player.GetIdentity());
                    newMarker.carimPlayer = player;
                    nametags.Add(newMarker);
                }
            }
            foreach(auto zone : zones) {
                textColor = zone.colorText;
                hideLessThan = -1;
                hideGreaterThan = zone.distanceHideGreaterThan;
                showDistance = zone.showDistance;
                requireLineOfSight = zone.requireLineOfSight;

                if (toggleState & CarimMarkerToggles.NAMETAGS) {
                    index = Sync(nametags, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
                }
            }
        }

        for (int i = menus.Count() - 1; i >= index; --i) {
            CarimLogging.Debug(this, "Closing marker menu at index " + i.ToString());
            menus.Get(i).Close();
        }
        menus.Resize(index);
    }

    int Sync(CarimModelAbcMarkers markers, int index, int textColor, int hideLessThan, int hideGreaterThan, bool showDistance, bool requireLineOfSight) {
        return SyncWithOverrides(markers, null, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
    }

    int SyncWithOverrides(CarimModelAbcMarkers markers, CarimModelAbcMarkers overrides, int index, int textColor, int hideLessThan, int hideGreaterThan, bool showDistance, bool requireLineOfSight) {
        foreach(array<ref CarimMapMarker> markerArray : markers.markers) {
            foreach(CarimMapMarker marker : markerArray) {
                auto markerToAdd = marker;
                // Check if override is present
                if (overrides) {
                    auto potentialOverride = overrides.GetClosest(marker);
                    if (potentialOverride && potentialOverride.GetMarkerPos() == marker.GetMarkerPos()) {
                        markerToAdd = potentialOverride;
                    }
                }
#ifdef DIAG_DEVELOPER
                CarimLogging.Debug(this, string.Format("Adding %1: <%2, %3, %4> at index %5", markers.ClassName(), markerToAdd.carimPlayerId, markerToAdd.GetMarkerText(), markerToAdd.GetMarkerPos(), index));
#else
                CarimLogging.Debug(this, string.Format("Adding marker at index %1", index));
#endif
                if (menus.Count() <= index) {
                    CarimLogging.Trace(this, "Creating new");
                    auto menu = new CarimMenuMarker(markerToAdd, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
                    menu.Init();
                    menus.Insert(menu);
                } else {
                    CarimLogging.Trace(this, "Using existing");
                    menus.Get(index).CarimSetAttributes(markerToAdd, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
                }
                ++index;
            }
        }
        return index;
    }

    void SyncList(CarimModelAbcMarkers markers, int textColor, int hideLessThan, int hideGreaterThan) {
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(registrations.registrations);
        int index = 0;
        foreach(auto id : sortedIds) {
            if (markers.markers.Contains(id)) {
                auto markerArray = markers.markers.Get(id);
                if (markerArray.Count() == 1) { // Should only have one position per id
                    auto marker = markerArray.Get(0);
                    CarimLogging.Debug(this, string.Format("Adding %1: <%2, %3, %4> at index %5", markers.ClassName(), marker.carimPlayerId, marker.GetMarkerText(), marker.GetMarkerPos(), index));
                    if (listMenus.Count() <= index) {
                        CarimLogging.Trace(this, "Creating new");
                        auto menu = new CarimMenuPartyList(marker, textColor, hideLessThan, hideGreaterThan, true, false);
                        menu.Init();
                        menu.carimListIndex = index;
                        listMenus.Insert(menu);
                    } else {
                        CarimLogging.Trace(this, "Using existing");
                        listMenus.Get(index).CarimSetAttributes(marker, textColor, hideLessThan, hideGreaterThan, true, false);
                        listMenus.Get(index).carimListIndex = index;
                    }
                    ++index;
                }
            }
        }
        for (int i = listMenus.Count() - 1; i >= index; --i) {
            CarimLogging.Debug(this, "Closing list menu at index " + i.ToString());
            listMenus.Get(i).Close();
        }
        listMenus.Resize(index);
    }
}
