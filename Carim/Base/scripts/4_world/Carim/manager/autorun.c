#ifndef CARIM_CarimManagerAutorun
#define CARIM_CarimManagerAutorun

class CarimManagerAutorun extends Managed {
    static const string interruptInputs[] = {
        "UACarimAutorunToggle",
        "UAMoveForward",
        "UAMoveBack",
        "UAMoveLeft",
        "UAMoveRight",
        "UAFire",
        "UATempRaiseWeapon",
        "UALeanLeft",
        "UALeanRight"};

    bool isAutorunning = false;
    ref CarimRPCAutorun rpc = new CarimRPCAutorun;

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (ShouldInterrupt(player)) {
                Stop();
            } else if (ShouldStart(player)) {
                Start();
            } else if (isAutorunning) {
                int speed = GetUpdatedSpeed(player);
                if (speed != DayZPlayerConstants.MOVEMENTIDX_IDLE) {
                    Start(speed);
                }
            }
        }
    }

    bool ShouldInterrupt(PlayerBase player) {
        if (!isAutorunning) {
            return false;
        }
        /* Check player status */
        if (player.IsInVehicle() || player.IsUnconscious() || player.IsRestrained() || !player.IsAlive()) {
            return true;
        }
        /* Check inputs */
        foreach(string inputName : interruptInputs) {
            if (CarimUtil.CheckInput(inputName)) {
                return true;
            }
        }
        return false;
    }

    bool ShouldStart(PlayerBase player) {
        if (isAutorunning) {
            return false;
        }
        string autorunStartInput = interruptInputs[0];
        if (CarimUtil.CheckInput(autorunStartInput) && !isAutorunning && !GetGame().GetMission().IsControlDisabled()) {
            return true;
        }
        return false;
    }

    int GetUpdatedSpeed(PlayerBase player) {
        if (player && (!player.CanSprint() || player.GetStaminaHandler().GetStamina() <= 0)) {
            return DayZPlayerConstants.MOVEMENTIDX_RUN;
        }
        if (CarimUtil.CheckInput("UAWalkRunToggle")) {
            return DayZPlayerConstants.MOVEMENTIDX_WALK;
        } else if (CarimUtil.CheckInput("UAWalkRunTemp")) {
            return DayZPlayerConstants.MOVEMENTIDX_RUN;
        } else if (CarimUtil.CheckInput("UATurbo")) {
            return DayZPlayerConstants.MOVEMENTIDX_SPRINT;
        } else {
            /* Used to indicate that there is to be no update to the speed */
            return DayZPlayerConstants.MOVEMENTIDX_IDLE;
        }
    }

    void Start(int speed = DayZPlayerConstants.MOVEMENTIDX_SPRINT) {
        isAutorunning = true;
        Sync(speed, 1);
    }

    void Stop() {
        isAutorunning = false;
        Sync(DayZPlayerConstants.MOVEMENTIDX_IDLE, 0);
    }

    void Sync(int movementIdx, int angle) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        player.GetInputController().OverrideMovementSpeed(isAutorunning, movementIdx);
        player.GetInputController().OverrideMovementAngle(isAutorunning, angle);
        auto params = new Param3<bool, int, int>(isAutorunning, movementIdx, angle);
        rpc.Send(player, params);
    }
}

#endif
