#ifndef CARIM_CarimModelPartyRegistrations
#define CARIM_CarimModelPartyRegistrations

class CarimModelPartyRegistrations extends CarimModelAbcDiskJson {
    ref map<string, string> registrations = new map<string, string>;

    void Add(string id, string name) {
        registrations.Set(id, name);
        Persist();
    }

    void Remove(string id) {
        registrations.Remove(id);
        Persist();
    }
}

#endif
