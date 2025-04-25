#ifndef CARIM_CarimModelAbcDiskJson
#define CARIM_CarimModelAbcDiskJson

class CarimModelAbcDiskJson extends CarimModelAbcBase {
    string Path() {
        return "$profile:" + this.ClassName() + ".json";
    }

    override void Load() {
        if (FileExist(Path())) {
            string error;
            if (!CarimModelAbcSerializers.LoadFile(this, error)) {
                CarimLogging.Warn(this, "Error loading " + Path() + ", " + error);
            } else {
                CarimLogging.Info(this, "Loaded " + Path());
            }
        }
        Persist();
    }

    override void Persist() {
        string error;
        if (!CarimModelAbcSerializers.SaveFile(this, error)) {
            CarimLogging.Warn(this, "Error persisting at " + Path() + ", " + error);
        } else {
            CarimLogging.Info(this, "Persisted at " + Path());
        }
    }
}

#endif
