modded class CfgGameplayHandler {
    // Carim
    static bool GetCarimInitialized() {
        return m_Data.CarimData.initialized;
    }

    static array<string> GetCarimAdminIds() {
        return m_Data.CarimData.adminIds;
    }

    static bool GetCarimUseSteamId() {
        return m_Data.CarimData.useSteamId;
    }

    // Autorun
    static bool GetCarimAutorunEnabled() {
        return m_Data.CarimData.CarimAutorunData.enabled;
    }

    // Chat
    static bool GetCarimChatEnabled() {
        return m_Data.CarimData.CarimChatData.enabled;
    }

    static int GetCarimChatColorDirect() {
        return m_Data.CarimData.CarimChatData.colorDirect;
    }

    static int GetCarimChatColorGlobal() {
        return m_Data.CarimData.CarimChatData.colorGlobal;
    }

    static int GetCarimChatColorServer() {
        return m_Data.CarimData.CarimChatData.colorServer;
    }

    static int GetCarimChatColorAlert() {
        return m_Data.CarimData.CarimChatData.colorAlert;
    }

    static int GetCarimChatColorAdmin() {
        return m_Data.CarimData.CarimChatData.colorAdmin;
    }

    static int GetCarimChatColorParty() {
        return m_Data.CarimData.CarimChatData.colorParty;
    }

    static bool GetCarimChatEnableKillfeed() {
        return m_Data.CarimData.CarimChatData.enableKillfeed;
    }

    // Compass
    static bool GetCarimCompassEnabled() {
        return m_Data.CarimData.CarimCompassData.enabled;
    }

    static bool GetCarimCompassRequireNavItem() {
        return m_Data.CarimData.CarimCompassData.requireNavItem;
    }

    static int GetCarimCompassColor() {
        return m_Data.CarimData.CarimCompassData.color;
    }

    // EarPlugs
    static bool GetCarimEarPlugsEnabled() {
        return m_Data.CarimData.CarimEarPlugsData.enabled;
    }

    // Map
    static bool GetCarimMapEnabled() {
        return m_Data.CarimData.CarimMapData.enabled;
    }

    static int GetCarimMapColorText() {
        return m_Data.CarimData.CarimMapData.colorText;
    }

    static int GetCarimMapColorIconDefault() {
        return m_Data.CarimData.CarimMapData.colorIconDefault;
    }

    static int GetCarimMapDistanceHideLessThan() {
        return m_Data.CarimData.CarimMapData.distanceHideLessThan;
    }

    static int GetCarimMapDistanceHideGreaterThan() {
        return m_Data.CarimData.CarimMapData.distanceHideGreaterThan;
    }

    static bool GetCarimMapShowDistance() {
        return m_Data.CarimData.CarimMapData.showDistance;
    }

    static bool GetCarimMapRequireLineOfSight() {
        return m_Data.CarimData.CarimMapData.requireLineOfSight;
    }

    static array<string> GetCarimMapIcons() {
        return m_Data.CarimData.CarimMapData.icons;
    }

    static array<ref CarimMapServerMarkerData> GetCarimMapServerMarkers() {
        return m_Data.CarimData.CarimMapData.serverMarkers;
    }

    // Nametag
    static bool GetCarimNametagEnabled() {
        return m_Data.CarimData.CarimNametagData.enabled;
    }

    static array<ref CarimNametagZoneData> GetCarimNametagZones() {
        return m_Data.CarimData.CarimNametagData.zones;
    }

    // Party
    static bool GetCarimPartyEnabled() {
        return m_Data.CarimData.CarimPartyData.enabled;
    }

    static int GetCarimPartyMaxPartySize() {
        return m_Data.CarimData.CarimPartyData.maxPartySize;
    }

    static int GetCarimPartyMaxPings() {
        return m_Data.CarimData.CarimPartyData.maxPings;
    }

    static int GetCarimPartyColorPingIconLocal() {
        return m_Data.CarimData.CarimPartyData.colorPingIconLocal;
    }

    static int GetCarimPartyColorPingIconServer() {
        return m_Data.CarimData.CarimPartyData.colorPingIconServer;
    }

    static int GetCarimPartyColorPingTextLocal() {
        return m_Data.CarimData.CarimPartyData.colorPingTextLocal;
    }

    static int GetCarimPartyColorPingTextServer() {
        return m_Data.CarimData.CarimPartyData.colorPingTextServer;
    }

    static int GetCarimPartyColorPlayerText() {
        return m_Data.CarimData.CarimPartyData.colorPlayerText;
    }

    static int GetCarimPartyDistancePingHideLessThan() {
        return m_Data.CarimData.CarimPartyData.distancePingHideLessThan;
    }

    static int GetCarimPartyDistancePingHideGreaterThan() {
        return m_Data.CarimData.CarimPartyData.distancePingHideGreaterThan;
    }

    static int GetCarimPartyDistancePlayerHideLessThan() {
        return m_Data.CarimData.CarimPartyData.distancePlayerHideLessThan;
    }

    static int GetCarimPartyDistancePlayerHideGreaterThan() {
        return m_Data.CarimData.CarimPartyData.distancePlayerHideGreaterThan;
    }

    static bool GetCarimPartyShowDistancePing() {
        return m_Data.CarimData.CarimPartyData.showDistancePing;
    }

    static bool GetCarimPartyShowDistancePlayer() {
        return m_Data.CarimData.CarimPartyData.showDistancePlayer;
    }

    static bool GetCarimPartyRequirePingLineOfSight() {
        return m_Data.CarimData.CarimPartyData.requirePingLineOfSight;
    }

    static bool GetCarimPartyRequirePlayerLineOfSight() {
        return m_Data.CarimData.CarimPartyData.requirePlayerLineOfSight;
    }
}
