class CarimModelPartyPings extends CarimModelAbcMarkers {
    int counter = 0;

    override void Clear(string id) {
        counter = 0;
        super.Clear(id);
    }

    override void Add(CarimMapMarker mark) {
        int maxPings = CfgGameplayHandler.GetCarimPartyMaxPings();
        bool markersLimited = maxPings >= 0;
        int countMarkers = 0;
        if (markers.Contains(mark.carimPlayerId)) {
            countMarkers = markers.Get(mark.carimPlayerId).Count();
        }
        // Remove greater than max markers
        if (markersLimited && countMarkers >= maxPings && maxPings != 0) {
            markers.Get(mark.carimPlayerId).RemoveOrdered(0);
            --countMarkers;
        }
        // Add marker if it would be less than max
        if (!markersLimited || countMarkers < maxPings) {
            mark.CarimSetMarkerText(mark.GetMarkerText() + " " + counter.ToString());
            ++counter;
            super.Add(mark);
        }
    }
}
