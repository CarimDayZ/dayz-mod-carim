#ifndef CARIM_CarimRPCPartyRegister
#define CARIM_CarimRPCPartyRegister

class CarimRPCPartyRegister extends CarimRPCBase<Param1<array<string>>> {
    override int GetType() {
        return CarimRPCTypesParty.REGISTER;
    }

    override void HandleClient(PlayerIdentity sender, Param1<array<string>> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyRegistrationClientSetMutual(params.param1);
    }

    override void HandleServer(PlayerIdentity sender, Param1<array<string>> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyRegistrationServerRegister(sender.GetId(), params.param1);
    }
}

#endif
