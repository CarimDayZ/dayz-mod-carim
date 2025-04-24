#ifndef CARIM_CarimEnabled
#define CARIM_CarimEnabled

class CarimEnabled {
    static const string autorunType = "CarimEnableAutorun";
    static const string chatType = "CarimEnableChat";
    static const string compassType = "CarimEnableCompass";
    static const string partyType = "CarimEnableParty";

    static bool autorun;
    static bool chat;
    static bool compass;
    static bool party;

    static bool initialized;

    static bool Autorun() {
        if (!initialized) {
            Initialize();
        }
        if (!autorun) {
            CarimLogging.Info(NULL, "Autorun not enabled");
        }
        return autorun;
    }

    static bool Chat() {
        if (!initialized) {
            Initialize();
        }
        if (!chat) {
            CarimLogging.Info(NULL, "Chat not enabled");
        }
        return chat;
    }

    static bool Compass() {
        if (!initialized) {
            Initialize();
        }
        if (!compass) {
            CarimLogging.Info(NULL, "Compass not enabled");
        }
        return compass;
    }

    static bool Party() {
        if (!initialized) {
            Initialize();
        }
        if (!party) {
            CarimLogging.Info(NULL, "Party not enabled");
        }
        return party;
    }

    static void Initialize() {
        autorun = (autorunType.ToType().ToString().Length() > 0);
        chat = (chatType.ToType().ToString().Length() > 0);
        compass = (compassType.ToType().ToString().Length() > 0);
        party = (partyType.ToType().ToString().Length() > 0);
        initialized = true;
    }
}

#endif
