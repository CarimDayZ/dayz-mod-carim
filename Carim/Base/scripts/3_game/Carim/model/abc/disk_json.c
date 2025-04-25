#ifndef CARIM_CarimModelAbcDiskJson
#define CARIM_CarimModelAbcDiskJson

class CarimModelAbcDiskJson extends CarimModelAbcBase {
    string Path() {
        return "$profile:" + this.ClassName() + ".json";
    }

    override void Load() {
        if (FileExist(Path())) {
            FileHandle handle = OpenFile(Path(), FileMode.READ);
            if (handle == 0) {
                CarimLogging.Error(this, "Cannot open file for reading " + Path());
                return;
            }

            string fileContent;
            ReadFile(handle, fileContent, 100000000);

            CloseFile(handle);

            if (!LoadData(fileContent)) {
                CarimLogging.Warn(this, "Error loading " + Path());
            } else {
                CarimLogging.Info(this, "Loaded " + Path());
            }
        }
        Persist();
    }

    override void Persist() {
        string data = MakeData();

        FileHandle handle = OpenFile(Path(), FileMode.WRITE);
        if (handle == 0) {
            CarimLogging.Error(this, "Cannot open file for writing " + Path());
            return;
        }

        FPrint(handle, data);
        CloseFile(handle);

        CarimLogging.Info(this, "Persisted at " + Path());
    }

    bool LoadData(string data) {
        auto serializer = new JsonSerializer();

        CarimLogging.Debug(this, "Deserializing from " + data);

        string error;
        if (!serializer.ReadFromString(this, data, error)) {
            CarimLogging.Error(this, "LoadData " + error);
            return false;
        }
        return true;
    }

    string MakeData() {
        auto serializer = new JsonSerializer();

        string output;
        if (!serializer.WriteToString(this, true, output)) {
            CarimLogging.Error(this, "MakeData failed");
            return "";
        }

        CarimLogging.Debug(this, "Serialized to " + output);
        return output;
    }
}

#endif
