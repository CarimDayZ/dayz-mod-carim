#ifndef CARIM_CarimModelAbcDiskJson
#define CARIM_CarimModelAbcDiskJson

class CarimModelAbcDiskJson extends CarimModelAbcBase {
    string Path() {
        return "$profile:" + this.ClassName() + ".json";
    }

    override void Load() {
        if (FileExist(Path())) {
            string error;
            if (!JsonFileLoader<CarimModelAbcDiskJson>.LoadFile(Path(), this, error)) {
                CarimLogging.Warn(this, "Error loading " + Path() + ", " + error);
            } else {
                CarimLogging.Info(this, "Loaded " + Path());
            }
        }
    }

    override void Persist() {
        string error;
        if (!JsonFileLoader<CarimModelAbcDiskJson>.SaveFile(Path(), this, error)) {
            CarimLogging.Warn(this, "Error persisting at " + Path() + ", " + error);
        } else {
            CarimLogging.Info(this, "Persisted at " + Path());
        }
    }
}

#endif
