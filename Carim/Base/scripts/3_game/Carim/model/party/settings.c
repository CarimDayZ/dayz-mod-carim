#ifndef CARIM_CarimModelPartySettings
#define CARIM_CarimModelPartySettings

class CarimModelPartySettings extends CarimModelAbcDiskJson {
    static const int DEFAULT_LOG_FREQUENCY = -1;
    static const int DEFAULT_MAX_PARTY_SIZE = -1;
    static const int DEFAULT_SEND_INFO_FREQUENCY = 5000;
    static const int DEFAULT_SEND_MARKER_FREQUENCY = 5000;
    static const int DEFAULT_MAX_PARTY_REFRESH_RATE = 1000;

    int logPartiesFrequency = DEFAULT_LOG_FREQUENCY;
    int maxPartySize = DEFAULT_MAX_PARTY_SIZE;
    int sendInfoFrequency = DEFAULT_SEND_INFO_FREQUENCY;
    int sendMarkerFrequency = DEFAULT_SEND_MARKER_FREQUENCY;
    int maxPartyRefreshRate = DEFAULT_MAX_PARTY_REFRESH_RATE;

    override void Load() {
        super.Load();
        if (logPartiesFrequency == 0) {
            logPartiesFrequency = DEFAULT_LOG_FREQUENCY;
        }
        if (maxPartySize == 0) {
            maxPartySize = DEFAULT_MAX_PARTY_SIZE;
        }
        if (sendInfoFrequency == 0) {
            sendInfoFrequency = DEFAULT_SEND_INFO_FREQUENCY;
        }
        if (sendMarkerFrequency == 0) {
            sendMarkerFrequency = DEFAULT_SEND_MARKER_FREQUENCY;
        }
        if (maxPartyRefreshRate == 0) {
            maxPartyRefreshRate = DEFAULT_MAX_PARTY_REFRESH_RATE;
        }
        Persist();
    }
}

#endif
