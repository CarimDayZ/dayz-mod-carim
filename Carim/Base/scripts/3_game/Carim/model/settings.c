#ifndef CARIM_CarimModelSettings
#define CARIM_CarimModelSettings

class CarimModelSettings extends CarimModelAbcDiskJson {
    static const int DEFAULT_VERBOSITY = -1;

    int verbosity = DEFAULT_VERBOSITY;

    override void Load() {
        super.Load();
        if (verbosity == 0) {
            verbosity = DEFAULT_VERBOSITY;
        }
    }
}

#endif
