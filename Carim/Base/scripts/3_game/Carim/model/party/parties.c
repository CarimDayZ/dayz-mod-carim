#ifndef CARIM_CarimModelPartyParties
#define CARIM_CarimModelPartyParties

class CarimModelPartyParties extends CarimModelAbcBase {
    ref map<string, ref CarimSet> registered = new map<string, ref CarimSet>;
    ref map<string, ref CarimSet> mutuals = new map<string, ref CarimSet>;

    array<string> admins;

    void CarimModelPartyParties(array<string> adminIds) {
        admins = adminIds;
    }

    bool Register(string id, array<string> players) {
        if (!registered.Contains(id)) {
            registered.Insert(id, new CarimSet);
        }

        bool added;
        CarimSet removed = registered.Get(id).Copy();

        foreach(string newPlayer : players) {
            removed.Remove(newPlayer);
            if (!registered.Get(id).Contains(newPlayer)) {
                CarimLogging.Info(this, "Register " + id + " added " + newPlayer);
                added = true;
                registered.Get(id).Insert(newPlayer);
            }
        }

        foreach(string removedPlayer : removed.ToArray()) {
            CarimLogging.Info(this, "Register " + id + " removed " + removedPlayer);
            registered.Get(id).Remove(removedPlayer);
            UpdateMutual(removedPlayer);
        }

        bool changed = (added || removed.Count() > 0);
        if (changed) {
            UpdateMutual(id);
            foreach(string player : registered.Get(id).ToArray()) {
                UpdateMutual(player);
            }
        }

        return changed;
    }

    void UpdateMutual(string id) {
        CarimLogging.Trace(this, "UpdateMutual " + id);
        if (!registered.Contains(id)) {
            CarimLogging.Trace(this, "No registration found");
            return;
        }
        if (!mutuals.Contains(id)) {
            mutuals.Insert(id, new CarimSet);
        } else {
            mutuals.Get(id).Clear();
        }
        foreach(string player : registered.Get(id).ToArray()) {
            CarimLogging.Trace(this, "Checking if mutual: " + player);
            if (registered.Contains(player) && registered.Get(player).Contains(id)) {
                CarimLogging.Trace(this, "Mutual found: " + player);
                mutuals.Get(id).Insert(player);
            } else if (admins.Find(id) != -1) {
                CarimLogging.Info(this, "Mutual admin override: " + player);
                mutuals.Get(id).Insert(player);
            }
        }
    }

    string Repr() {
        string jsonRegistered;
        if (CarimLogging.TraceEnabled()) {
            JsonSerializer().WriteToString(registered, false, jsonRegistered);
        }
        string jsonMutuals;
        if (CarimLogging.TraceEnabled()) {
            JsonSerializer().WriteToString(mutuals, false, jsonMutuals);
        }
        return "PartyParties<" + jsonRegistered + ", " + jsonMutuals + ">";
    }
}

#endif
