#ifndef CARIM_CarimModelPartySettings
#define CARIM_CarimModelPartySettings

class CarimModelPartySettings extends CarimModelAbcDiskJson {
    int logPartiesFrequency = -1;
    int maxPartySize = -1;
    int sendInfoFrequency = 5000;
    int sendMarkerFrequency = 5000;
    int maxPartyRefreshRate = 1000;
}

#endif
