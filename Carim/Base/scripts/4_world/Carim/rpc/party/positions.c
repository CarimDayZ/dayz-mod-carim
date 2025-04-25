#ifndef CARIM_CarimRPCPartyPositions
#define CARIM_CarimRPCPartyPositions

class CarimRPCPartyPositions extends CarimRPCBase<Param1<array<CarimModelPartyPlayer>>> {
    override int GetType() {
        return CarimRPCTypesParty.POSITIONS;
    }

    override void HandleClient(PlayerIdentity sender, Param1<array<CarimModelPartyPlayer>> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyPositionClientSetPositions(params.param1);
    }
}

#endif
