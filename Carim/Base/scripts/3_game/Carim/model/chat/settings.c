#ifndef CARIM_CarimModelChatSettings
#define CARIM_CarimModelChatSettings

class CarimModelChatSettings extends CarimModelAbcDiskJson {
    static const int DEFAULT_SIZE = 20;
    static const int DEFAULT_COLOR_DIRECT = 0xfffafafa; /* grey 50 */
    static const int DEFAULT_COLOR_GLOBAL = 0xffffd54f; /* amber 300 */
    static const int DEFAULT_COLOR_SERVER = 0xff4fc3f7; /* light blue 300 */
    static const int DEFAULT_COLOR_ALERT = 0xffff8a65;  /* deep orange 300 */

    int size = DEFAULT_SIZE;
    int color_direct = DEFAULT_COLOR_DIRECT;
    int color_global = DEFAULT_COLOR_GLOBAL;
    int color_server = DEFAULT_COLOR_SERVER;
    int color_alert = DEFAULT_COLOR_ALERT;

    override void Load() {
        super.Load();
        if (size == 0) {
            size = DEFAULT_SIZE;
        }
        if (color_direct == 0) {
            color_direct = DEFAULT_COLOR_DIRECT;
        }
        if (color_global == 0) {
            color_global = DEFAULT_COLOR_GLOBAL;
        }
        if (color_server == 0) {
            color_server = DEFAULT_COLOR_SERVER;
        }
        if (color_alert == 0) {
            color_alert = DEFAULT_COLOR_ALERT;
        }
        Persist();
    }
}

#endif
