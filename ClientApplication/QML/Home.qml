import QtQuick 2.0

Image
{
    id: userInterfaceContainer
    width: parent.width
    height: parent.height
    anchors.verticalCenter: parent.verticalCenter
    x: 0
    source: "qrc:/background/main_background.png"

    Behavior on x
    {
        SmoothedAnimation
        {
            duration: 800
            alwaysRunToEnd: true
        }
    }

    onHeightChanged:
    {
        button1.scaleButton();
        button2.scaleButton();
        button3.scaleButton();
        button4.scaleButton();
    }

    onWidthChanged:
    {
        button1.scaleButton();
        button2.scaleButton();
        button3.scaleButton();
        button4.scaleButton();
    }

    //screeen init/re-init method
    function setDefaultFocus()
    {
        button1.focus = true;
        button1.scaleButton();
        button2.scaleButton();
        button3.scaleButton();
        button4.scaleButton();
    }

    function buttonCallback(menuItem)
    {
        switch(menuItem)
        {
        case 1:
            clientMain.customState = "DRIVE";
            break;
        case 2:
            clientMain.customState = "CALIBRATE";
            break;
        case 3:
            clientMain.customState = "TEST";
            break;
        case 4:
            clientMain.customState = "SETTINGS";
            break;
        }
    }

    Rectangle
    {
        id: controlContainer
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.05
        anchors.right: parent.right
        anchors.rightMargin: -(parent.height * 0.4)
        height: parent.height * .85
        width: parent.height * 1.3
        rotation: 90
        radius: 500
        opacity: 0.9
        border.width: 2
        border.color: "black"
        gradient: Gradient
        {
            GradientStop { position: 0.00; color: "#0c343d"; }
            GradientStop { position: 0.25; color: "#155d6e"; }
            GradientStop { position: 0.75; color: "#155d6e"; }
            GradientStop { position: 1; color: "#0c343d"; }
        }

        z: parent.z + 1;
    }

    Column
    {
        id: buttons
        anchors.right: parent.right
        anchors.topMargin: button1.height * 0.8
        anchors.bottomMargin: button4.height * 0.8
        z: controlContainer.z + 1
        anchors.top: parent.top
        spacing: button1.height * 0.8

        SelectorButton
        {
            id: button1
            anchors.right: parent.right
            sourceText: "qrc:/text/drive_text.png"

            KeyNavigation.up: button4;
            KeyNavigation.down: button2;
            KeyNavigation.left: serverItem;
            KeyNavigation.right: serverItem;

            Keys.onReturnPressed: buttonCallback(1)
        }

        SelectorButton
        {
            id: button2
            anchors.right: parent.right
            sourceText: "qrc:/text/calibrate_text.png"

            KeyNavigation.up: button1;
            KeyNavigation.down: button3;
            KeyNavigation.left: oculusItem;
            KeyNavigation.right: oculusItem;

            Keys.onReturnPressed: buttonCallback(2)
        }

        SelectorButton
        {
            id: button3
            anchors.right: parent.right
            sourceText: "qrc:/text/test_text.png"

            KeyNavigation.up: button2;
            KeyNavigation.down: button4;
            KeyNavigation.left: controllerItem;
            KeyNavigation.right: controllerItem;

            Keys.onReturnPressed: buttonCallback(3)
        }

        SelectorButton
        {
            id: button4
            anchors.right: parent.right
            sourceText: "qrc:/text/settings_text.png"

            KeyNavigation.up: button3;
            KeyNavigation.down: button1;
            KeyNavigation.left: exitButton;
            KeyNavigation.right: exitButton;

            Keys.onReturnPressed: buttonCallback(4)
        }
    }

    Rectangle
    {
        id: bevelOuter
        width: parent.height * 0.6
        height: parent.width * 0.45
        x: parent.width * 0.205
        anchors.verticalCenter: parent.verticalCenter
        rotation: -90
        gradient: Gradient
        {
            GradientStop { position: 0.00; color: "#073e70"; }
            GradientStop { position: 0.15; color: "#073763"; }
            GradientStop { position: 0.75; color: "#073763"; }
            GradientStop { position: 0.98; color: "#052747"; }
        }

        z: parent.z + 1
        border.width: 2
        border.color: "black"


        Rectangle
        {
            id: bevelInner
            width: parent.height * 0.95
            height: parent.width * 0.95
            gradient: Gradient
            {
                GradientStop { position: 0.00; color: "#073e70"; }
                GradientStop { position: 0.15; color: "#073763"; }
                GradientStop { position: 0.75; color: "#073763"; }
                GradientStop { position: 0.98; color: "#052747"; }
            }
            z: parent.z + 1
            opacity: 0.75
            anchors.centerIn: parent
            border.width: 2
            border.color: "black"
            rotation: 90

            Column
            {
                id: connectionItemContainer
                height: parent.height
                width: parent.width
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.05
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.05
                spacing: parent.height * 0.08

                ItemConnectionIndicator
                {
                    id: serverItem
                    hardwareDescriptor: 1
                    connected: serverConnectionStatus

                    Keys.onReturnPressed:
                    {
                        if (ClientNetwork.connected)
                            ClientNetwork.disconnectFromJetson();
                        else if (!ClientNetwork.connected)
                            ClientNetwork.connectToJetson();
                    }

                    Connections
                    {
                        target: ClientNetwork
                        onNetworkError:
                        {
                            alertBox.showBox(priority, "Network Error", message, "HOME");
                        }
                    }

                    KeyNavigation.up: exitButton;
                    KeyNavigation.down: oculusItem;
                    KeyNavigation.left: button1;
                    KeyNavigation.right: button1;
                }
                ItemConnectionIndicator
                {
                    id: oculusItem
                    hardwareDescriptor: 2
                    connected: oculusConnectionStatus

                    KeyNavigation.up: serverItem;
                    KeyNavigation.down: controllerItem;
                    KeyNavigation.left: button2;
                    KeyNavigation.right: button2;
                }
                ItemConnectionIndicator
                {
                    id: controllerItem
                    hardwareDescriptor: 3
                    connected: controllerConnectionStatus

                    KeyNavigation.up: oculusItem;
                    KeyNavigation.down: exitButton;
                    KeyNavigation.left: button3;
                    KeyNavigation.right: button3;
                }
            }
        }
    }
    GeneralButton
    {
        id: exitButton
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.04
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.25
        z: parent.z + 1
        customSource: "qrc:/text/exit_text.png"
        KeyNavigation.up: controllerItem;
        KeyNavigation.down: serverItem;
        KeyNavigation.left: button4;
        KeyNavigation.right: button4;

        MouseArea
        {
            anchors.fill: parent
            onClicked: exitButton.exit();
        }

        Keys.onPressed:
        {
            if (event.key == Qt.Key_Return)
            {
                if (exitButton.activeFocus)
                {
                    exitButton.exit();
                }
            }
        }
    }
}
