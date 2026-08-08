modded class PlayerBase {
    ref CarimRPCAutorun carimRPCAutorun = new CarimRPCAutorun;
    ref CarimRPCChat carimRPCChat = new CarimRPCChat;
    ref CarimRPCPartyMarkers carimRPCPartyMarkers = new CarimRPCPartyMarkers;
    ref CarimRPCPartyPings carimRPCPartyPings = new CarimRPCPartyPings;
    ref CarimRPCPartyPositions carimRPCPartyPositions = new CarimRPCPartyPositions;
    ref CarimRPCPartyRegister carimRPCPartyRegister = new CarimRPCPartyRegister;

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
        super.OnRPC(sender, rpc_type, ctx);
        switch (rpc_type) {
            case carimRPCChat.GetType():
                if (CarimEnabled.Chat()) {
                    carimRPCChat.OnRPC(sender, ctx);
                }
                break;
            case carimRPCAutorun.GetType():
                if (CarimEnabled.Autorun()) {
                    carimRPCAutorun.OnRPC(sender, ctx);
                }
                break;
            case carimRPCPartyMarkers.GetType():
                if (CarimEnabled.Party()) {
                    carimRPCPartyMarkers.OnRPC(sender, ctx);
                }
                break;
            case carimRPCPartyPings.GetType():
                if (CarimEnabled.Party()) {
                    carimRPCPartyPings.OnRPC(sender, ctx);
                }
                break;
            case carimRPCPartyPositions.GetType():
                if (CarimEnabled.Party()) {
                    carimRPCPartyPositions.OnRPC(sender, ctx);
                }
                break;
            case carimRPCPartyRegister.GetType():
                if (CarimEnabled.Party()) {
                    carimRPCPartyRegister.OnRPC(sender, ctx);
                }
                break;
        }
    }

    override void CloseMapEx(bool cancelled)
    {
        super.CloseMapEx(cancelled)
        m_Hud.ShowHudUI(true);
		m_Hud.ShowQuickbarUI(true);
    }
}
