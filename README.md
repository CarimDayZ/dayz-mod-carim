# Carim

*Open Source mods for DayZ*

This Open Source mod includes all the features Carim has to offer:

- Autorun
- Chat
- Compass
- Map
- Nametags
- Party

You are free to use this mod on your monetized servers. The works are licensed under the [Apache License](https://www.apache.org/licenses/LICENSE-2.0).

The mod is availble [in the Steam Workshop for DayZ](https://steamcommunity.com/sharedfiles/filedetails/?id=3468061029).

## Autorun

Provides autorunning functionality. Start and stop using the configurable key (default: `+`). Adjust the running speed using your normal keybinds.

## Chat

Provides global chat. Switch chat channels with the press of a configurable key (default: `Z`). Adjust size with configurable keys (up: `]`, down: `[`).

If you have an admin tool that disallows non-ascii characters, you need to allowlist the following: `ᐅ`.
For Battleye BEC, go to Config.cfg in the battleye/Bec folder and change IgnoreChatChars to `IgnoreChatChars = €,£,æ,Æ,ø,Ø,å,Å,ö,ä,ü,ß,ᐅ`.

## Compass

Provides a compass at the top of the display with the press of a configurable key (default: `H`).

## Earplugs

Provides sound reduction with the press of a configurable key (default: `N`).

## Map

Provides an in-game map for saving markers and viewing party members. Open with the vanilla configurable key (default: `M`). Double-click to add a marker, double-right-click to edit and remove.

To apply a nicer style than vanilla with additional locations, you can use [the CarimMapStyle mod](https://steamcommunity.com/sharedfiles/filedetails/?id=3483791557).

### Customization

Servers can configure custom icons and static markers by adding to the `icons` and `serverMarkers` properties within `CarimMapData`. Custom icons start at 40. The built-in icons are 0-39.

```json
"CarimMapData": {
    "icons": [
        "\\DZ\\animals\\Data\\mapicon_animals_ca.paa"
    ],
    "serverMarkers": [
        {
            "text": "server marker using custom icon",
            "position": [
                5345,
                110,
                3262
            ],
            "icon": 40,
            "color": -16537100,
            "visible3d": true,
            "distanceHideGreaterThan": -1
        }
    ]
}
```

## Nametags

Provides ability to configure zones to display player nametags by specifying a position and radius. Copy the template below and edit as desired. The nametags will only be shown if the players are within the network bubble (~1km).

```json
"CarimNametagData": {
    "enabled": true,
    "zones": [
        {
            "center": [
                5345,
                110,
                3262
            ],
            "radius": 300,
            "colorText": -1,
            "showDistance": true,
            "requireLineOfSight": true,
            "distanceHideGreaterThan": 40
        }
    ]
}
```

## Party

Allows creation of parties and displaying of nametags of party members. There is no party size limit.

Parties are managed by the player. Open the menu (default key: `P`), and Add players to your party. If they have also added you, then your nametags will automatically appear. Parties are saved, so you don't have to re-create it each time you login. They also work for whatever server runs the mod.

Tactical pings can be placed (default key: `T`, clear with `Y`) that will be shared with your party.

Optionally, servers can configure Admin Ids that allow adding party members without them needing to add back.

## Configuration

Configuration is managed in your `cfggameplay.json`. Different modules can be enabled/disabled independently. The defaults are below (copy these into your `cfggameplay.json` and change as you want). You only need to add the values if you want to change from the defaults.

Be sure to enable the use of this config file in your `serverDZ.cfg` with
`enableCfgGameplayFile=1;`

Put them in your cfggameplay.json at the top level, like
```json
{
    "version": 122,
    "GeneralData": {
        ...
    },
    "PlayerData": {
        ...
    },
    "CarimData": {
        ...
    },
    ...
}
```

### Defaults
The color values are signed integers based on the ARGB bytes, so `0xfffafafa` is `-328966`. You can [use a tool to figure out the values](https://argb-int-calculator.netlify.app/).

```json
"CarimData": {
    "adminIds": [],
    "CarimAutorunData": {
        "enabled": true
    },
    "CarimChatData": {
        "enabled": true,
        "colorDirect": -328966,
        "colorGlobal": -16121,
        "colorServer": -16537100,
        "colorAlert": -43230
    },
    "CarimCompassData": {
        "enabled": true,
        "requireNavItem": false,
        "color": -769226
    },
    "CarimEarPlugsData": {
        "enabled": true
    },
    "CarimMapData": {
        "enabled": true,
        "colorText": -1,
        "colorIconDefault": -769226,
        "distanceHideLessThan": -1,
        "distanceHideGreaterThan": -1,
        "showDistance": true,
        "requireLineOfSight": false,
        "icons": [],
        "serverMarkers": []
    },
    "CarimNametagData": {
        "enabled": true,
        "zones": []
    },
    "CarimPartyData": {
        "enabled": true,
        "maxPartySize": -1,
        "maxPings": 3,
        "colorPingIconLocal": -5317,
        "colorPingIconServer": -26624,
        "colorPingTextLocal": -1,
        "colorPingTextServer": -1,
        "colorPlayerText": -1,
        "distancePingHideLessThan": -1,
        "distancePingHideGreaterThan": -1,
        "distancePlayerHideLessThan": -1,
        "distancePlayerHideGreaterThan": -1,
        "showDistancePing": true,
        "showDistancePlayer": true,
        "requirePingLineOfSight": false,
        "requirePlayerLineOfSight": false
    }
},
```

### Map specific configuration
To enable the map without needing any items, you can edit those existing settings to
```json
"MapData": {
    "ignoreMapOwnership": true,
    "ignoreNavItemsOwnership": true,
    "displayPlayerPosition": true,
    "displayNavInfo": true
},
```

Also, make sure the map can opened by disabling the 3d map
```json
"UIData": {
    "use3DMap": false
}
```

## Information

- This mod originated from the Carim DayZ project
- The original source is at https://github.com/CarimDayZ/dayz-mod-carim
- To support this open source project, you can donate at https://paypal.me/cnofafva
- To learn more visit https://discord.gg/kdPnVu4

## Acknowledgements

- Thank you to Karma's Wasteland for testing and providing valuable feedback.
