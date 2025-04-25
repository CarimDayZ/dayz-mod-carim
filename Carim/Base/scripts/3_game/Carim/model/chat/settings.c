#ifndef CARIM_CarimModelChatSettings
#define CARIM_CarimModelChatSettings

class CarimModelChatSettings extends CarimModelAbcDiskJson {
    int size = 20;
    int color_direct = 0xfffafafa; /* grey 50 */
    int color_global = 0xffffd54f; /* amber 300 */
    int color_server = 0xff4fc3f7; /* light blue 300 */
    int color_alert = 0xffff8a65;  /* deep orange 300 */
}

#endif
