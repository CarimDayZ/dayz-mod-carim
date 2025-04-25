#ifndef CARIM_CarimModelAbcBase
#define CARIM_CarimModelAbcBase

class CarimModelAbcBase extends Managed {
    void CarimModelAbcBase() {
        CarimLogging.Debug(this, "Spawned instance");
    }

    void Load();
    void Persist();
}

#endif
