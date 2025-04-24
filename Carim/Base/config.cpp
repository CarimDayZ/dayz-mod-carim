class CfgPatches {
    class CarimBase {
        requiredAddons[] = {"DZ_Scripts"};
    };
};

class CfgMods {
    class CarimBase {
        name = "CarimBase";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "Carim/Base/scripts/3_game",
                };
            };

            class worldScriptModule {
                files[] = {
                    "Carim/Base/scripts/4_world",
                };
            };

            class missionScriptModule {
                files[] = {
                    "Carim/Base/scripts/5_mission",
                };
            };
        };
    };
};
