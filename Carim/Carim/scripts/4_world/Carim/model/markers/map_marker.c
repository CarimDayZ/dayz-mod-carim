enum CarimMapMarkerTypes {
    ARROW_1 = 200,
    ARROW_2,
    ARROW_3,
    HEALTH_0,
    HEALTH_1,
    HEALTH_2,
    HEALTH_3,
    HEALTH_4
}

class CarimMapMarker extends MapMarker {
    string carimPlayerId;
    int carimHealthLevel = -1;
    bool carimVisible3d = true;
    int carimHideGreaterThan = -1;

    [NonSerialized()] PlayerBase carimPlayer;

    static CarimMapMarker CarimNew(vector pos, string text, int color, int idx, string playerId, int healthLevel = -1) {
        auto marker = new CarimMapMarker(pos, text, color, idx);
        marker.carimPlayerId = playerId;
        marker.carimHealthLevel = healthLevel;
        return marker;
    }

    override vector GetMarkerPos() {
        if (carimPlayer && carimPlayer.IsAlive()) {
            return carimPlayer.GetPosition();
        } else {
            return super.GetMarkerPos();
        }
    }

    override int GetMarkerIcon() {
        switch (CarimGetHealthLevel()) {
            case 0:
                return CarimMapMarkerTypes.HEALTH_0;
                break;
            case 1:
                return CarimMapMarkerTypes.HEALTH_1;
                break;
            case 2:
                return CarimMapMarkerTypes.HEALTH_2;
                break;
            case 3:
                return CarimMapMarkerTypes.HEALTH_3;
                break;
            case 4:
                return CarimMapMarkerTypes.HEALTH_4;
                break;
        }
        return super.GetMarkerIcon();
    }

    override int GetMarkerColor() {
        switch (CarimGetHealthLevel()) {
            case 0:
                return CarimColor.HEALTH_WHITE;
                break;
            case 1:
                return CarimColor.HEALTH_WHITE;
                break;
            case 2:
                return CarimColor.HEALTH_YELLOW;
                break;
            case 3:
                return CarimColor.HEALTH_RED;
                break;
            case 4:
                return CarimColor.HEALTH_RED;
                break;
        }
        return super.GetMarkerColor();
    }

    int CarimGetHealthLevel() {
        if (carimPlayer && carimPlayer.IsAlive()) {
            return carimPlayer.GetHealthLevel();
        } else {
            return carimHealthLevel;
        }
    }

    void CarimCopyValues(CarimMapMarker other) {
        m_Position = other.m_Position;
        m_Color = other.m_Color;
        m_IconIdx = other.m_IconIdx;
        m_Text = other.m_Text;
        carimPlayerId = other.carimPlayerId;
        carimHealthLevel = other.carimHealthLevel;
        carimVisible3d = other.carimVisible3d;
        carimHideGreaterThan = other.carimHideGreaterThan;
    }

    void CarimSetMarkerText(string text) {
        m_Text = text;
    }

    void CarimSetMarkerIcon(int icon) {
        m_IconIdx = icon;
    }

    void CarimSetMarkerColor(int color) {
        m_Color = color;
    }

    void CarimSetMarkerVisible3d(bool visible) {
        carimVisible3d = visible;
    }

    void CarimSetMarkerHideGreaterThan(int hideGreaterThan) {
        carimHideGreaterThan = hideGreaterThan;
    }

    string CarimRepr() {
        return string.Format("%1<%2, %3>", ClassName(), carimPlayerId, GetMarkerPos(), CarimGetHealthLevel());
    }
}
