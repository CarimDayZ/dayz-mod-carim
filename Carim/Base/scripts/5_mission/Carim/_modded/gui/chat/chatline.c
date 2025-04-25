#ifndef CARIM_ChatLine
#define CARIM_ChatLine

modded class ChatLine {
    void ChatLine(Widget root_widget) {
        if (CarimEnabled.Chat()) {
            m_RootWidget = GetGame().GetWorkspace().CreateWidgets("Carim/Base/gui/layouts/chatline.layout", root_widget);
            m_NameWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemSenderWidget"));
            m_TextWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemTextWidget"));
            m_NameWidget.SetTextExactSize(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.size);
            m_TextWidget.SetTextExactSize(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.size);
        }
    }

    override void Set(ChatMessageEventParams params) {
        super.Set(params);
        if (CarimEnabled.Chat()) {
            int channel = params.param1;
            if (channel & CCSystem) {
                if (params.param2 == "" && params.param3.IndexOf(" : ") > 0) {
                    CarimSetColour(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.color_global);
                } else {
                    SetColour(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.color_alert);
                }
            } else if (channel & CCAdmin) {
                SetColour(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.color_server);
            } else if (channel == 0 || channel & CCDirect) {
                CarimSetColour(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.color_direct);
            } else {
                SetColour(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.color_server);
            }
        }
    }

    void CarimUpdateSize() {
        m_NameWidget.SetTextExactSize(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.size);
        m_TextWidget.SetTextExactSize(MissionGameplay.Cast(GetGame().GetMission()).carimModelChatSettings.size);
    }

    void CarimSetColour(int colour) {
        m_NameWidget.SetColor(colour);
        m_TextWidget.SetColor(colour);
    }
}

#endif
