#ifndef CARIM_CarimManagerChat
#define CARIM_CarimManagerChat

class CarimManagerChat extends Managed {
    bool isChannelGlobal = true;

    void OnUpdate(CarimModelChatSettings settings) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimChatChannel")) {
                isChannelGlobal = !isChannelGlobal;
                GetGame().Chat("Channel switched to " + getChannelName(), "colorAction");
            }
            if (CarimUtil.CheckInput("UACarimChatSizeDown")) {
                settings.size = Math.Max(12, settings.size - 1);
                settings.Persist();
                MissionGameplay.Cast(GetGame().GetMission()).m_Chat.CarimUpdateSize();
            }
            if (CarimUtil.CheckInput("UACarimChatSizeUp")) {
                settings.size = Math.Min(30, settings.size + 1);
                settings.Persist();
                MissionGameplay.Cast(GetGame().GetMission()).m_Chat.CarimUpdateSize();
            }
        }
    }

    string getChannelName() {
        if (isChannelGlobal) {
            return "Global";
        } else {
            return "Direct";
        }
    }
}

#endif
