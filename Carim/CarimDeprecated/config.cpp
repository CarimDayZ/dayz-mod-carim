class CfgPatches {
    class CarimDeprecated {
        requiredAddons[] = {"DZ_Scripts", "Carim"};
    };
};

class CfgMods {
    class CarimDeprecated {
        name = "CarimDeprecated";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"Mission"};

        class defs {
            class missionScriptModule {
                files[] = {
                    "Carim/CarimDeprecated/scripts/5_mission",
                };
            };
        };
    };
};
