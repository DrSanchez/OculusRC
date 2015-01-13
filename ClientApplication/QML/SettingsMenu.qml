import QtQuick 2.0
import QtGraphicalEffects 1.0

Image
{
    id: settingsMenuContainer
    width: parent.width
    height: parent.height
    anchors.verticalCenter: parent.verticalCenter
    x: parent.width
    source: "qrc:/background/settings_menu_background.png"

    Behavior on x
    {
        SmoothedAnimation
        {
            duration: 800
            alwaysRunToEnd: true
        }
    }

    function setDefaultFocus()
    {
        applicationMenuItem.focus = true;
    }

    onHeightChanged:
    {
        settingsMenuTitle.scaleTitle();
    }

    onWidthChanged:
    {
        settingsMenuTitle.scaleTitle();
    }

    Image
    {
        id: settingsMenuTitle
        width: parent.width * 0.25
        fillMode: Image.PreserveAspectFit
        source: "qrc:/text/settings_text.png"
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.04
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.125

        function scaleTitle()
        {
            width = parent.width * 0.25;
        }
    }

    Rectangle
    {
        id: settingsItemsContainer
        width: parent.width * 0.3
        height: parent.height * 0.7
        color: "dark blue"
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.15
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.1
        radius: 20
        opacity: 0.4
        border.width: 2
        border.color: "black"

        RectangularGlow
        {
            id: settingsItemsShadow
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: width * 0.0125
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: height * 0.0125
            z: parent.z - 1
            glowRadius: 20
            color: "black"
        }
    }
    Column
    {
        anchors.top: settingsItemsContainer.top
        anchors.topMargin: settingsItemsContainer.height * 0.025
        spacing: settingsItemsContainer.height * 0.025
        anchors.fill: settingsItemsContainer
        z: parent.z + 1

        SettingsMenuItem
        {
            id: applicationMenuItem
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * 0.025
            settingsItemDescriptor: 1

            KeyNavigation.up: backMenuItem
            KeyNavigation.down: oculusMenuItem
        }
        SettingsMenuItem
        {
            id: oculusMenuItem
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * 0.025
            settingsItemDescriptor: 2

            KeyNavigation.up: applicationMenuItem
            KeyNavigation.down: controllerMenuItem
        }
        SettingsMenuItem
        {
            id: controllerMenuItem
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * 0.025
            settingsItemDescriptor: 3

            KeyNavigation.up: oculusMenuItem
            KeyNavigation.down: escMenuItem
        }
        SettingsMenuItem
        {
            id: escMenuItem
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * 0.025
            settingsItemDescriptor: 4

            KeyNavigation.up: controllerMenuItem
            KeyNavigation.down: backMenuItem
        }
        SettingsMenuItem
        {
            id: backMenuItem
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width * 0.025
            settingsItemDescriptor: 5

            KeyNavigation.up: escMenuItem
            KeyNavigation.down: applicationMenuItem

            Keys.onReturnPressed: clientMain.customState = "HOME";
        }
    }

    Rectangle
    {
        id: settingsContentContainer
        width: parent.width * 0.5
        height: parent.height * 0.85
        gradient: Gradient
        {
            GradientStop { position: 0.15; color: "blue" }
            GradientStop { position: 0.4; color: "dark blue" }
            GradientStop { position: 0.6; color: "dark blue" }
            GradientStop { position: 0.95; color: "gray" }
        }
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.1
        anchors.left: settingsItemsContainer.right
        anchors.leftMargin: -parent.width * 0.00125
        radius: 20
        opacity: 0.4
        border.width: 2
        border.color: "black"

        RectangularGlow
        {
            id: settingsContentShadow
            width: parent.width
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: width * 0.0125
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: height * 0.0125
            z: parent.z - 1
            glowRadius: 20
            color: "black"
        }
    }
}
