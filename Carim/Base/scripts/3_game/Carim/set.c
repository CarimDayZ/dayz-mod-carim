#ifndef CARIM_CarimSet
#define CARIM_CarimSet

class CarimSet {
    private ref map<string, bool> data;

    void CarimSet() {
        data = new map<string, bool>;
    }

    void Insert(string item) {
        data.Set(item, true);
    }

    void Remove(string item) {
        data.Remove(item);
    }

    bool Contains(string item) {
        return data.Contains(item);
    }

    void Clear() {
        data.Clear();
    }

    int Count() {
        return data.Count();
    }

    array<string> ToArray() {
        return data.GetKeyArray();
    }

    CarimSet Copy() {
        return CarimSet.FromArray(ToArray());
    }

    static CarimSet FromArray(array<string> values) {
        auto result = new CarimSet;
        foreach(string value : values) {
            result.Insert(value);
        }
        return result;
    }
}

#endif
