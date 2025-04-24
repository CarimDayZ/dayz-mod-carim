#ifndef CARIM_CarimManagerPartyRegistrationClient
#define CARIM_CarimManagerPartyRegistrationClient

class CarimManagerPartyRegistrationClient extends Managed {
    CarimModelPartyRegistrations registrations;
    ref CarimMenuPartyRegister menu;
    ref array<string> mutual = new array<string>;
    ref CarimRPCPartyRegister rpc = new CarimRPCPartyRegister;

    void CarimManagerPartyRegistrationClient(CarimModelPartyRegistrations inputRegistrations) {
        registrations = inputRegistrations;
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.InitialRegistration, 2000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.RenewRegistration, 60000, true);
    }

    void ~CarimManagerPartyRegistrationClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialRegistration);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.RenewRegistration);
    }

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UAUIBack")) {
                if (menu && GetGame().GetUIManager().GetMenu() == menu) {
                    menu.UnlockControls();
                    menu.Close();
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyMenu")) {
                if (menu) {
                    menu.Close();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    GetGame().GetUIManager().EnterScriptedMenu(CarimMenuParty.REGISTER, NULL);
                }
            }
        }
    }

    void SetMutual(array<string> players) {
        mutual.Clear();
        mutual.Copy(players);
    }

    void InitialRegistration() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            RenewRegistration();
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialRegistration);
        }
    }

    void RenewRegistration() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            array<string> keys = registrations.registrations.GetKeyArray();
            auto params = new Param1<array<string>>(keys);
            rpc.Send(player, params);
        }
    }

    void AddPlayerToParty(string id) {
        registrations.Add(id, CarimUtil.GetClientPlayerIdentities().Get(id));
        registrations.Persist();
        RenewRegistration();
    }

    void RemovePlayerFromParty(string id) {
        registrations.Remove(id);
        registrations.Persist();
        mutual.RemoveItem(id);
        RenewRegistration();
    }
}

#endif
