#ifndef CARIM_CarimMenuPartyList
#define CARIM_CarimMenuPartyList

class CarimMenuPartyList extends CarimMenuPartyNametag {
    int carimListIndex = 0;

    override string CarimGetLayout() {
        return "Carim/Base/gui/layouts/party/list.layout";
    }

    override void CarimSetRootPosition() {
        float width, height, x, y;
        layoutRoot.GetSize(width, height);
        layoutRoot.GetPos(x, y);
        y = (2 + height) * carimListIndex;
        layoutRoot.SetPos(x, y);
    }
}

#endif
