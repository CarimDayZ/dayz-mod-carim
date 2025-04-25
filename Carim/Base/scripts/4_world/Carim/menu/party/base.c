#ifndef CARIM_CarimMenuPartyBase
#define CARIM_CarimMenuPartyBase

class CarimMenuPartyBase extends UIScriptedMenu {
    bool carimInitialized;

    string carimName;
    vector carimPosition;
    PlayerBase carimPlayer;

    TextWidget carimNametag;
    TextWidget carimDistance;
    ImageWidget carimIcon;

    void CarimMenuPartyBase(string name, vector position, PlayerBase player = null) {
        carimName = name;
        carimPosition = position;
        carimPlayer = player;
    }

    void ~CarimMenuPartyBase() {
        if (layoutRoot) {
            layoutRoot.Unlink();
        }
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdate);
    }

    string CarimGetLayout() {
        CarimLogging.Error(this, "CarimGetLayout() not implemented");
        return "";
    }

    override Widget Init() {
        if (!layoutRoot) {
            layoutRoot = Widget.Cast(GetGame().GetWorkspace().CreateWidgets(CarimGetLayout()));
            carimNametag = TextWidget.Cast(layoutRoot.FindAnyWidget("nametag"));
            carimDistance = TextWidget.Cast(layoutRoot.FindAnyWidget("distance"));
            carimIcon = ImageWidget.Cast(layoutRoot.FindAnyWidget("icon"));

            GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CarimUpdate, CARIM_60_FPS_INTERVAL_MS, true);
        }

        return layoutRoot;
    }

    string CarimGetName() {
        return carimName;
    }

    vector CarimGetPosition() {
        return carimPosition;
    }

    void CarimUpdate() {
        float distance = Math.Round(vector.Distance(CarimGetPosition(), GetGame().GetPlayer().GetPosition()));
        string distanceString = distance.ToString() + "m";
        if (distance > 1000) {
            distanceString = (Math.Round(distance / 100) / 10).ToString() + "km";
        }
        carimNametag.SetText(CarimGetName());
        carimDistance.SetText(distanceString);
    }
}

#endif
