#ifndef CarimChatInputMenu
#define CarimChatInputMenu

#ifdef CARIM_ENABLE_CHAT
modded class ChatInputMenu {
    ref CarimRPCChat carimRPCChat = new CarimRPCChat;

    override bool OnChange(Widget w, int x, int y, bool finished) {
        /* super call manually because inheritance is weird */
        if (UIScriptedWindow.GetActiveWindows()) {
            for (int i = 0; i < UIScriptedWindow.GetActiveWindows().Count(); i++) {
                if (UIScriptedWindow.GetActiveWindows().GetElement(i).OnChange(w, x, y, finished)) {
                }
            }
        }
        if (!finished) {
            return false;
        }
        string text = m_edit_box.GetText();
        if (text != "") {
            MissionGameplay mission = MissionGameplay.Cast(GetGame().GetMission());
            if (text.IndexOf("#") != 0 && text.IndexOf("!") != 0 && CarimManagerChatSingleton.Get().isChannelGlobal) {
                PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
                auto params = new Param1<string>(text);
                carimRPCChat.Send(player, params);
                GetGame().ChatPlayer(CARIM_CHAT_PREFIX + " " + text);
            } else {
                GetGame().ChatPlayer(text);
            }
            if (!GetGame().IsMultiplayer()) {
                string name;
                GetGame().GetPlayerName(name);
                ChatMessageEventParams chat_params = new ChatMessageEventParams(CCDirect, name, text, "");
                MissionGameplay.Cast(GetGame().GetMission()).m_Chat.Add(chat_params);
            }
        }
        m_close_timer.Run(0.1, this, "Close");
        GetUApi().GetInputByName("UAPersonView").Supress();
        return true;
    }
}
#endif

#endif
