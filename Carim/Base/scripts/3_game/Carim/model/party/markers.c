#ifndef CARIM_CarimModelPartyMarkers
#define CARIM_CarimModelPartyMarkers

class CarimModelPartyMarkers extends CarimModelAbcDiskJson {
    ref array<vector> markers = new array<vector>;

    void Add(vector mark) {
        markers.Insert(mark);
        // TODO: respect server's max markers setting
        if (markers.Count() > 3) {
            markers.RemoveOrdered(0);
        }
        Persist();
    }

    void Clear() {
        markers.Clear();
        Persist();
    }
}

#endif
