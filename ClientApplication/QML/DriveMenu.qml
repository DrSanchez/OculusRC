import QtQuick 2.0

Image
{
    id: driveMenuContainer
    width: parent.width
    height: parent.height
    anchors.verticalCenter: parent.verticalCenter
    x: parent.width
    source: "qrc:/background/drive_menu_background.png"

    function setDefaultFocus()
    {
        goButton.focus = true;
    }

    Behavior on x
    {
        SmoothedAnimation
        {
            duration: 800
            alwaysRunToEnd: true
        }
    }

    Rectangle
    {
        id: indicator1
        width: parent.width * 0.22
        height: parent.height * 0.08
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.29
        anchors.right: indicator2.left
        anchors.rightMargin: parent.width * 0.05
        border.width: 3
        border.color: "black"
        radius: 25
        gradient: Gradient
        {
            GradientStop { position: 0; color: serverConnectionStatus ? "dark green" : "dark red" }
            GradientStop { position: 0.5; color: serverConnectionStatus ? "light green" : "light red" }
            GradientStop { position: 1; color: serverConnectionStatus ? "dark green" : "dark red" }
        }

        Image
        {
            id: indicator1Text
            height: parent.height * 0.45
            fillMode: Image.PreserveAspectFit
            anchors.bottom: parent.top
            anchors.bottomMargin: parent.height * 0.075
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/text/jetson_tk1_text.png"
        }
    }

    Rectangle
    {
        id: indicator2
        width: parent.width * 0.22
        height: parent.height * 0.08
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.29
        anchors.horizontalCenter: parent.horizontalCenter
        border.width: 3
        border.color: "black"
        radius: 25
        gradient: Gradient
        {
            GradientStop { position: 0; color: controllerConnectionStatus ? "dark green" : "dark red" }
            GradientStop { position: 0.5; color: controllerConnectionStatus ? "light green" : "light red" }
            GradientStop { position: 1; color: controllerConnectionStatus ? "dark green" : "dark red" }
        }

        Image
        {
            id: indicator2Text
            height: parent.height * 0.45
            fillMode: Image.PreserveAspectFit
            anchors.bottom: parent.top
            anchors.bottomMargin: parent.height * 0.075
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/text/controller_text.png"
        }
    }

    Rectangle
    {
        id: indicator3
        width: parent.width * 0.22
        height: parent.height * 0.08
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.29
        anchors.left: indicator2.right
        anchors.leftMargin: parent.width * 0.05
        border.width: 3
        border.color: "black"
        radius: 25
        gradient: Gradient
        {
            GradientStop { position: 0; color: oculusConnectionStatus ? "dark green" : "dark red" }
            GradientStop { position: 0.5; color: oculusConnectionStatus ? "light green" : "light red" }
            GradientStop { position: 1; color: oculusConnectionStatus ? "dark green" : "dark red" }
        }

        Image
        {
            id: indicator3Text
            height: parent.height * 0.45
            fillMode: Image.PreserveAspectFit
            anchors.bottom: parent.top
            anchors.bottomMargin: parent.height * 0.075
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/text/oculus_text.png"
        }
    }

    GeneralButton
    {
        id: goButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.075
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.075
        customSource: "qrc:/text/go_text.png"

        KeyNavigation.left: backButton
        KeyNavigation.right: backButton

        Keys.onReturnPressed:
        {
            //oculusConnectionStatus needs to be added when video is started
            //drive menu in drive mode will display standard views of camera feeds
            //
            if (serverConnectionStatus && controllerConnectionStatus)
            {
                SteeringWheel.driveMode = true;
            }
            else
            {
                SteeringWheel.driveMode = true;
                clientMain.customState = "ALERT";
                alertBox.showBox(3, "Drive Check Failure",
                                 "Not all systems are ready to drive the RC. Please ensure all connections are properly established.",
                                 "DRIVE");
            }
        }
    }
    GeneralButton
    {
        id: backButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.075
        anchors.right: goButton.left
        anchors.rightMargin: parent.width * 0.075
        customSource: "qrc:/text/back_text.png"

        KeyNavigation.left: goButton
        KeyNavigation.right: goButton

        Keys.onReturnPressed: clientMain.customState = "HOME"
    }
}
