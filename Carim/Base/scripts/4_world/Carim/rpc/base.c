#ifndef CARIM_CarimRPCBase
#define CARIM_CarimRPCBase

class CarimRPCBase<Class T> extends Managed {
    int GetType();
    void Handle(PlayerIdentity sender, T params);

    void OnRPC(PlayerIdentity sender, ParamsReadContext ctx) {
        CarimLogging.Trace(this, "OnRPC " + ClassName());
        T params;
        if (!ctx.Read(params)) {
            CarimLogging.Warn(this, "Unable to read params from ctx");
            return;
        }
        if (GetGame().IsClient()) {
            CarimLogging.Trace(this, "HandleClient " + ClassName());
            HandleClient(sender, params);
        } else {
            CarimLogging.Trace(this, "HandleServer " + ClassName());
            HandleServer(sender, params);
        }
    }

    void HandleClient(PlayerIdentity sender, T params) {
        Handle(sender, params);
    }

    void HandleServer(PlayerIdentity sender, T params) {
        Handle(sender, params);
    }

    void Send(Man man, T params, PlayerIdentity recipient = null) {
        CarimLogging.Trace(this, "Send " + ClassName());
        PlayerBase player = PlayerBase.Cast(man);
        if (player) {
            GetGame().RPCSingleParam(player, GetType(), params, true, recipient);
        }
    }
}

#endif
