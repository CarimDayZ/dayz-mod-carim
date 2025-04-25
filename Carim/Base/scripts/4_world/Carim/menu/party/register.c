#ifndef CARIM_CarimMenuPartyRegister
#define CARIM_CarimMenuPartyRegister

class CarimMenuPartyRegister extends UIScriptedMenu {
    CarimManagerPartyRegistrationClient registrationClient;
    bool carimInitialized;
    TextListboxWidget carimPlayers;
    TextListboxWidget carimRegistered;
    ButtonWidget carimAdd;
    ButtonWidget carimRemove;

    void CarimMenuPartyRegister(CarimManagerPartyRegistrationClient client) {
        registrationClient = client;
    }

    void ~CarimMenuPartyRegister() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdateLists);
    }

    override Widget Init() {
        if (!carimInitialized) {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets("Carim/Base/gui/layouts/party/register.layout");
            carimPlayers = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("players"));
            carimRegistered = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("registered"));
            carimAdd = ButtonWidget.Cast(layoutRoot.FindAnyWidget("add"));
            carimRemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("remove"));

            carimInitialized = true;
        }

        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        GetGame().GetMission().AddActiveInputExcludes({"menu"});
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CarimUpdateLists, 500, true);

        CarimUpdateLists();
    }

    override void OnHide() {
        super.OnHide();
        GetGame().GetMission().RemoveActiveInputExcludes({"menu"}, true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdateLists);
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        int selectedRow;
        Param1<string> id;
        switch (w) {
            case carimAdd:
                selectedRow = carimPlayers.GetSelectedRow();
                if (selectedRow == -1) {
                    break;
                }
                carimPlayers.GetItemData(selectedRow, 0, id);
                registrationClient.AddPlayerToParty(id.param1);
                CarimUpdateLists();
                return true;
                break;
            case carimRemove:
                selectedRow = carimRegistered.GetSelectedRow();
                if (selectedRow == -1) {
                    break;
                }
                carimRegistered.GetItemData(selectedRow, 0, id);
                registrationClient.RemovePlayerFromParty(id.param1);
                carimRegistered.SelectRow(selectedRow - 1);
                CarimUpdateLists();
                return true;
                break;
        }
        return super.OnClick(w, x, y, button);
    }

    void CarimUpdateLists() {
        CarimUpdateList(carimPlayers, CarimUtil.GetClientPlayerIdentities());
        CarimUpdateList(carimRegistered, registrationClient.registrations.registrations);
        CarimUpdateColors();
    }

    void CarimUpdateList(TextListboxWidget targetList, map<string, string> values) {
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(values);
        int row = 0;
        foreach(string id : sortedIds) {
            if (row < targetList.GetNumItems()) {
                targetList.SetItem(row, values.Get(id), new Param1<string>(id), 0);
            } else {
                targetList.AddItem(values.Get(id), new Param1<string>(id), 0);
            }
            row++;
        }
        while (row < targetList.GetNumItems()) {
            targetList.RemoveRow(row);
        }
        if (targetList.GetSelectedRow() >= row) {
            targetList.SelectRow(row - 1);
        }
    }

    void CarimUpdateColors() {
        auto onlinePlayers = CarimUtil.GetClientPlayerIdentities();
        int selectedRow;
        int i;
        Param1<string> id;
        for (i = 0; i < carimRegistered.GetNumItems(); ++i) {
            carimRegistered.GetItemData(i, 0, id);
            if (onlinePlayers.Contains(id.param1) && registrationClient.mutual.Find(id.param1) >= 0) {
                // Green 400
                carimRegistered.SetItemColor(i, 0, 0xFF66BB6A);
            } else {
                // Gray 400
                carimRegistered.SetItemColor(i, 0, 0xFFBDBDBD);
            }
        }
        for (i = 0; i < carimPlayers.GetNumItems(); ++i) {
            // Gray 400
            carimPlayers.SetItemColor(i, 0, 0xFFBDBDBD);
        }
    }
}

#endif
