#ifndef CARIM_CarimModelAbcBase
#define CARIM_CarimModelAbcBase

class CarimModelAbcBase extends Managed {
    protected static int instanceCount;

    void CarimModelAbcBase() {
        instanceCount++;
        if (instanceCount > 1) {
            CarimLogging.Error(this, "More than one instance spawned");
        }
    }

    void ~CarimModelAbcBase() {
        instanceCount--;
    }

    void Load();
    void Persist();
}

#endif
