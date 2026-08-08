modded class CfgGameplayJson {
    ref ITEM_CarimData CarimData = new ITEM_CarimData;
}

class ITEM_CarimData extends ITEM_DataBase {
    ref ITEM_CarimAutorunData CarimAutorunData = new ITEM_CarimAutorunData;
    ref ITEM_CarimChatData CarimChatData = new ITEM_CarimChatData;
    ref ITEM_CarimCompassData CarimCompassData = new ITEM_CarimCompassData;
    ref ITEM_CarimMapData CarimMapData = new ITEM_CarimMapData;
    ref ITEM_CarimNametagData CarimNametagData = new ITEM_CarimNametagData;
    ref ITEM_CarimPartyData CarimPartyData = new ITEM_CarimPartyData;

    bool initialized = false;
    ref array<string> adminIds;
    bool useSteamId = false; // TODO

    override bool ValidateServer() {
        // Use initialize to determine if the data has been loaded
        // in the client so we don't have to override the static
        // onRPC in the Handler. So before the client uses any
        // values, it checks if initialized is true, which means
        // the values have been sync'd from the server.
        // We use ValidateServer() since InitServer() is only
        // called when the cfgGameplay.json isn't used.
        initialized = true;
        return true;
    }
}

class ITEM_CarimAutorunData extends ITEM_DataBase {
    bool enabled = true;
}

class ITEM_CarimChatData extends ITEM_DataBase {
    bool enabled = true;
    int colorDirect = CarimColor.GREY_50;
    int colorGlobal = CarimColor.AMBER_500;
    int colorServer = CarimColor.LIGHT_BLUE_500;
    int colorAlert = CarimColor.DEEP_ORANGE_500;
    int colorAdmin = CarimColor.RED_500;   // TODO
    int colorParty = CarimColor.GREEN_500; // TODO
    bool enableKillfeed = false;           // TODO
}

class ITEM_CarimCompassData extends ITEM_DataBase {
    bool enabled = true;
    bool showOnSpawn = true;
    bool requireNavItem = false;
    int color = CarimColor.RED_500;
}

class ITEM_CarimMapData extends ITEM_DataBase {
    bool enabled = true;
    int colorText = CarimColor.WHITE;
    int colorIconDefault = CarimColor.RED_500;
    int distanceHideLessThan = -1;
    int distanceHideGreaterThan = -1;
    bool showDistance = true;
    bool requireLineOfSight = false;
    ref array<string> icons = {};
    ref array<ref CarimMapServerMarkerData> serverMarkers = {};
}

class CarimMapServerMarkerData {
    string text;
    vector position;
    int icon;
    int color;
    bool visible3d;
    int distanceHideGreaterThan;
}

class ITEM_CarimNametagData extends ITEM_DataBase {
    bool enabled = true;
    ref array<ref CarimNametagZoneData> zones = {};
}

class CarimNametagZoneData {
    vector center;
    int radius;
    int colorText;
    bool showDistance;
    bool requireLineOfSight;
    int distanceHideGreaterThan;
}

class ITEM_CarimPartyData extends ITEM_DataBase {
    bool enabled = true;
    int maxPartySize = -1;
    int maxPings = 3;
    int colorPingIconLocal = CarimColor.YELLOW_500;
    int colorPingIconServer = CarimColor.ORANGE_500;
    int colorPingTextLocal = CarimColor.WHITE;
    int colorPingTextServer = CarimColor.WHITE;
    int colorPlayerText = CarimColor.WHITE;
    int distancePingHideLessThan = -1;
    int distancePingHideGreaterThan = -1;
    int distancePlayerHideLessThan = -1;
    int distancePlayerHideGreaterThan = -1;
    bool showDistancePing = true;
    bool showDistancePlayer = true;
    bool requirePingLineOfSight = false;
    bool requirePlayerLineOfSight = false;
}
