modded class MapHandler {
    ref CarimMenuEditMarker carimMenuEditMarker;

    override bool OnMouseButtonDown(Widget w, int x, int y, int button) {
        if (carimMenuEditMarker && carimMenuEditMarker.visible) {
            if (w == m_Root) {
                carimMenuEditMarker.Hide();
            } else {
                return true;
            }
        }

        if (button == MouseState.MIDDLE) {
            return true;
        }

        return super.OnMouseButtonDown(w, x, y, button);
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnDoubleClick(w, x, y, button);
        }
        if (carimMenuEditMarker && carimMenuEditMarker.visible) {
            return true;
        }
        super.OnDoubleClick(w, x, y, button);

        vector mousePos, worldPos;
        mousePos[0] = x;
        mousePos[1] = y;
        worldPos = MapWidget.Cast(w).ScreenToMap(mousePos);
        worldPos[1] = GetGame().SurfaceY(worldPos[0], worldPos[2]);

        CarimLogging.Trace(this, string.Format("OnDoubleClick %1, mouse(%2) world(%3)", button.ToString(), mousePos, worldPos));

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        auto marker = CarimMapMarker.CarimNew(worldPos, "", CfgGameplayHandler.GetCarimMapColorIconDefault(), eMapMarkerTypes.MARKERTYPE_MAP_BORDER_CROSS, CarimUtil.GetIdentifier(GetGame().GetPlayer().GetIdentity()));

        switch (button) {
            case MouseState.LEFT:
                // Add marker
                mission.carimModelMapMarkers.Add(marker);
                break;
            case MouseState.RIGHT:
                // Edit marker
                CarimLogging.Trace(this, "Searching for marker to edit");
                CarimModelAbcMarkers markerGroup = mission.carimModelMapMarkers;
                auto existingMarker = mission.carimModelMapMarkers.GetClosest(marker);
                if (!existingMarker) {
                    CarimLogging.Trace(this, "Map marker not found, searching static markers");
                    marker.carimPlayerId = CarimUtil.GetServerIdentifier();
                    existingMarker = mission.carimModelStaticMarkers.GetClosest(marker);
                    if (existingMarker) {
                        CarimLogging.Trace(this, "Static marker found, checking if override is present");
                        // Check if override is present
                        auto potentialOverride = mission.carimModelStaticMarkers.overrides.GetClosest(marker);
                        if (potentialOverride && potentialOverride.GetMarkerPos() == existingMarker.GetMarkerPos()) {
                            CarimLogging.Trace(this, "Override present");
                            existingMarker = potentialOverride;
                        } else {
                            CarimLogging.Trace(this, "Override not found; creating new");
                            auto copyValuesFrom = existingMarker;
                            existingMarker = new CarimMapMarker("0 0 0", "", 0, 0);
                            existingMarker.CarimCopyValues(copyValuesFrom);
                        }
                        markerGroup = mission.carimModelStaticMarkers.overrides;
                    }
                } else {
                    CarimLogging.Trace(this, "Found map marker");
                }
                if (existingMarker) {
                    CarimLogging.Debug(this, "Open MenuEditMarker");
                    if (!carimMenuEditMarker) {
                        carimMenuEditMarker = new CarimMenuEditMarker(markerGroup, existingMarker, x, y);
                        m_Root.AddChild(carimMenuEditMarker.root);
                    }
                    carimMenuEditMarker.markerGroup = markerGroup;
                    carimMenuEditMarker.marker = existingMarker;
                    carimMenuEditMarker.x = x;
                    carimMenuEditMarker.y = y;
                    carimMenuEditMarker.Show();
                }
                break;
        }

        return true;
    }

    override bool OnMouseButtonUp(Widget w, int x, int y, int button) {
        switch (button) {
            case MouseState.MIDDLE:
                // Quick marker removal
                vector mousePos, worldPos;
                mousePos[0] = x;
                mousePos[1] = y;
                worldPos = MapWidget.Cast(w).ScreenToMap(mousePos);
                worldPos[1] = GetGame().SurfaceY(worldPos[0], worldPos[2]);

                CarimLogging.Trace(this, string.Format("OnWheelClickUp %1, mouse(%2) world(%3)", button.ToString(), mousePos, worldPos));

                auto mission = MissionGameplay.Cast(GetGame().GetMission());
                auto marker = CarimMapMarker.CarimNew(worldPos, "", CfgGameplayHandler.GetCarimMapColorIconDefault(), eMapMarkerTypes.MARKERTYPE_MAP_BORDER_CROSS, CarimUtil.GetIdentifier(GetGame().GetPlayer().GetIdentity()));

                auto existingMarker = mission.carimModelMapMarkers.GetClosest(marker);
                if (existingMarker) {
                    CarimLogging.Trace(this, "Delete");
                    mission.carimModelMapMarkers.Remove(existingMarker);
                }
                return true;
        }
        return super.OnMouseButtonUp(w, x, y, button);
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnClick(w, x, y, button);
        }
        super.OnClick(w, x, y, button);

        CarimLogging.Trace(this, "OnClick " + w);

        if (button == MouseState.LEFT && carimMenuEditMarker && carimMenuEditMarker.visible) {
            carimMenuEditMarker.OnClick(w);
        }

        return true;
    }

    override bool OnChange(Widget w, int x, int y, bool finished) {
        if (!CarimEnabled.Map()) {
            return super.OnChange(w, x, y, finished);
        }
        super.OnChange(w, x, y, finished);

        if (carimMenuEditMarker && carimMenuEditMarker.visible) {
            carimMenuEditMarker.OnChange(w);
        }

        return true;
    }
}
