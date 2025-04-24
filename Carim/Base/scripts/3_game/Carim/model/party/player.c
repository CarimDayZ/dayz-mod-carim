#ifndef CARIM_CarimModelPartyPlayer
#define CARIM_CarimModelPartyPlayer

class CarimModelPartyPlayer extends CarimModelAbcBase {
    string id;
    vector position;
    int healthLevel;

    void CarimModelPartyPlayer(string newId, vector newPosition, int newHealthLevel) {
        id = newId;
        position = newPosition;
        healthLevel = newHealthLevel;
    }

    string Repr() {
        return "PartyPlayer<" + id + ", " + position.ToString() + ", " + healthLevel.ToString() + ">";
    }
}

#endif
