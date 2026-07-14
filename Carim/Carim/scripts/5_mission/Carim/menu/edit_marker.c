class CarimMenuEditMarker extends Managed {
    // This value should correspond to what's in the edit_marker.layout
    static const int MAX_DISTANCE = 6000;

    ref CarimModelAbcMarkers markerGroup;
    ref CarimMapMarker marker;
    int x;
    int y;
    bool visible;
    int currentIcon;
    float panelWidth;
    float panelHeight;
    int screenWidth;
    int screenHeight;

    Widget root;
    Widget panel;
    EditBoxWidget text;
    ImageWidget icon;

    ButtonWidget previous;
    ButtonWidget next;
    ButtonWidget save;
    ButtonWidget deleteButton;
    ButtonWidget cancel;

    CheckBoxWidget visible3d;
    SliderWidget distance;
    TextWidget distanceLabel;

    ref array<ref ButtonWidget> colorButtons;

    void CarimMenuEditMarker(CarimModelAbcMarkers iMarkerGroup, CarimMapMarker iMarker, int iX, int iY) {
        markerGroup = iMarkerGroup;
        marker = iMarker;
        x = iX;
        y = iY;
        currentIcon = marker.GetMarkerIcon();

        root = GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/edit_marker.layout");
        text = EditBoxWidget.Cast(root.FindAnyWidget("text"));
        icon = ImageWidget.Cast(root.FindAnyWidget("icon"));

        previous = ButtonWidget.Cast(root.FindAnyWidget("previous"));
        next = ButtonWidget.Cast(root.FindAnyWidget("next"));
        save = ButtonWidget.Cast(root.FindAnyWidget("save"));
        deleteButton = ButtonWidget.Cast(root.FindAnyWidget("deleteButton"));
        cancel = ButtonWidget.Cast(root.FindAnyWidget("cancel"));

        visible3d = CheckBoxWidget.Cast(root.FindAnyWidget("visible3d"));
        distance = SliderWidget.Cast(root.FindAnyWidget("distance"));
        distanceLabel = TextWidget.Cast(root.FindAnyWidget("distanceLabel"));

        panel = root.FindAnyWidget("panel");
        panel.GetSize(panelWidth, panelHeight);
        GetScreenSize(screenWidth, screenHeight);

        colorButtons = GetColorButtons();
    }

    void Show() {
        visible = true;
        Refresh();
    }

    void Hide() {
        visible = false;
        Refresh();
    }

    void Refresh() {
        if (root) {
            CarimLogging.Trace(this, "Refresh");

            text.SetText(marker.GetMarkerText());
            string imageFile = MapMarkerTypes.GetMarkerTypeFromID(marker.GetMarkerIcon());
            imageFile.Replace("\\DZ", "DZ");
            icon.LoadImageFile(0, imageFile);
            icon.SetColor(marker.GetMarkerColor());
            currentIcon = marker.GetMarkerIcon();

            visible3d.SetChecked(marker.carimVisible3d);
            if (marker.carimHideGreaterThan >= 0) {
                distance.SetCurrent(marker.carimHideGreaterThan);
            } else {
                distance.SetCurrent(MAX_DISTANCE);
            }
            UpdateDistanceLabel();

            float adjustedX = x;
            float adjustedY = y;

            if (x + panelWidth > screenWidth) {
                adjustedX = x - panelWidth;
            }
            if (y + panelHeight > screenHeight) {
                adjustedY = y - panelHeight;
            }

            root.SetPos(adjustedX, adjustedY);
            root.Show(visible);
        }
    }

    void UpdateDistanceLabel() {
        if (distance.GetCurrent() >= MAX_DISTANCE) {
            distanceLabel.SetText("unlimited");
        } else {
            distanceLabel.SetText(distance.GetCurrent().ToString() + "m");
        }
    }

    bool OnChange(Widget w) {
        if (w == distance) {
            UpdateDistanceLabel();
            return true;
        }

        return false;
    }

    bool OnClick(Widget w) {
        CarimLogging.Trace(this, "OnClick");

        string imageFile;

        int maxIconIndex = eMapMarkerTypes.MARKERTYPE_MAX + MapMarkerTypes.carimAdditionalIndex;

        switch (w) {
            case cancel:
                CarimLogging.Trace(this, "Cancel");
                Hide();
                break;
            case save:
                CarimLogging.Trace(this, "Save");
                marker.CarimSetMarkerText(text.GetText());
                marker.CarimSetMarkerIcon(currentIcon);
                marker.CarimSetMarkerColor(icon.GetColor());
                marker.CarimSetMarkerVisible3d(visible3d.IsChecked());
                if (distance.GetCurrent() >= MAX_DISTANCE) {
                    marker.CarimSetMarkerHideGreaterThan(-1);
                } else {
                    marker.CarimSetMarkerHideGreaterThan(distance.GetCurrent());
                }

                // Check if marker needs added
                auto existingMarker = markerGroup.GetClosest(marker);
                if (!existingMarker || existingMarker.GetMarkerPos() != marker.GetMarkerPos()) {
                    markerGroup.Add(marker);
                } else {
                    markerGroup.Persist();
                }
                Hide();
                break;
            case deleteButton:
                CarimLogging.Trace(this, "Delete");
                markerGroup.Remove(marker);
                Hide();
                break;
            case previous:
                CarimLogging.Trace(this, "Previous " + currentIcon.ToString());
                currentIcon = (currentIcon - 1 + maxIconIndex) % maxIconIndex;
                imageFile = MapMarkerTypes.GetMarkerTypeFromID(currentIcon);
                imageFile.Replace("\\DZ", "DZ");
                icon.LoadImageFile(0, imageFile);
                break;
            case next:
                CarimLogging.Trace(this, "Next " + currentIcon.ToString());
                currentIcon = (currentIcon + 1) % maxIconIndex;
                imageFile = MapMarkerTypes.GetMarkerTypeFromID(currentIcon);
                imageFile.Replace("\\DZ", "DZ");
                icon.LoadImageFile(0, imageFile);
                break;
            default:
                foreach(auto button : colorButtons) {
                    if (w == button) {
                        icon.SetColor(button.GetColor());
                        return true;
                    }
                }
                return false;
        }
        return true;
    }

    array<ref ButtonWidget> GetColorButtons() {
        // Needs to be 21 for layout to work
        int colors[] = {CarimColor.RED_500,
                        CarimColor.PINK_500,
                        CarimColor.PURPLE_500,
                        CarimColor.DEEP_PURPLE_500,
                        CarimColor.INDIGO_500,
                        CarimColor.BLUE_500,
                        CarimColor.LIGHT_BLUE_500,
                        CarimColor.CYAN_500,
                        CarimColor.TEAL_500,
                        CarimColor.GREEN_500,
                        CarimColor.LIGHT_GREEN_500,
                        CarimColor.LIME_500,
                        CarimColor.YELLOW_500,
                        CarimColor.AMBER_500,
                        CarimColor.ORANGE_500,
                        CarimColor.DEEP_ORANGE_500,
                        CarimColor.BROWN_500,
                        CarimColor.GRAY_500,
                        CarimColor.BLUE_GRAY_500,
                        CarimColor.BLACK,
                        CarimColor.WHITE};

        float currentX = 8;
        float currentY = 48;

        // Figure out the scaling based on the size defined in the layout
        float scaleX = panelWidth / 376;
        float scaleY = panelHeight / 212;

        ButtonWidget button;
        array<ref ButtonWidget> buttons = new array<ref ButtonWidget>;

        foreach(int color : colors) {
            CarimLogging.Trace(null, string.Format("%1 (%2, %3)", color, currentX, currentY));
            button = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/edit_color_button.layout"));
            button.SetPos(currentX * scaleX, currentY * scaleY);
            button.SetColor(color);
            panel.AddChild(button);
            if (currentX == 248) {
                currentX = 8;
                currentY += 40;
            } else {
                currentX += 40;
            }
            buttons.Insert(button);
        }

        return buttons;
    }
}
