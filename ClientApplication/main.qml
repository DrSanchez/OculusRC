import QtQuick 2.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

FocusScope
{
    id: applicationFocus
    property alias color: clientMain.color
    x: clientMain.x; y: clientMain.y
    width: clientMain.width; height: clientMain.height

    property bool oculusConnectionStatus: false
    property bool controllerConnectionStatus: SteeringWheel.connected
    property bool serverConnectionStatus: false

    Component.onCompleted:
    {//application initialization code
        button1.focus = true;
    }

    Window
    {
        id: clientMain
        visible: true
        minimumHeight: 480
        minimumWidth: minimumHeight * 1.4
        width: ScreenWidth * 0.66
        height: ScreenHeight * 0.66
        visibility: "Windowed"
        color: clientTheme.mainBackground

        //instantiate and name the app theme object
        ColorTheme{id:clientTheme}

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

        Rectangle
        {
            id: userInterfaceContainer
            width: parent.width
            height: parent.height
            anchors.fill: parent
            anchors.centerIn: parent
            gradient: Gradient
            {
                GradientStop { position: 0.0; color: "#0d353d" }
                GradientStop { position: 0.3; color: "#0c343d" }
                GradientStop { position: 0.6; color: "#0b2e35" }
            }

            Rectangle
            {
                id: backgroundUnderlay
                height: parent.height
                width: parent.width * 0.9
                radius: 300
                gradient: Gradient
                {
                    GradientStop { position: 0.2; color: "dark gray" }
                    GradientStop { position: 0.8; color: "gray" }
                }
                opacity: 0.8
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.05

                Text
                {
                    id: applicationTitleText
                    font.pixelSize: parent.height * 0.15
                    text: "OculusRC"
                    font.underline: true
                    font.italic: true
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.topMargin: parent.height * 0.008
                    anchors.leftMargin: parent.width * 0.075
                }

                Rectangle
                {
                    height: parent.height
                    width: parent.width / 2
                    anchors.left: parent.right
                    anchors.leftMargin: -(parent.width * 0.25)
                    opacity: 0.95
                    gradient: Gradient
                    {
                        GradientStop { position: 0.2; color: "dark gray" }
                        GradientStop { position: 0.8; color: "gray" }
                    }
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

            Component.onCompleted:
            {
                applicationFocus.focus =  button1;
                button1.focus = true;
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
                    buttonText: "Drive"

                    KeyNavigation.up: button4;
                    KeyNavigation.down: button2;
                    KeyNavigation.left: serverItem;
                    KeyNavigation.right: serverItem;
                }

                SelectorButton
                {
                    id: button2
                    anchors.right: parent.right
                    buttonText: "Calibrate"

                    KeyNavigation.up: button1;
                    KeyNavigation.down: button3;
                    KeyNavigation.left: oculusItem;
                    KeyNavigation.right: oculusItem;
                }

                SelectorButton
                {
                    id: button3
                    anchors.right: parent.right
                    buttonText: "Test"

                    KeyNavigation.up: button2;
                    KeyNavigation.down: button4;
                    KeyNavigation.left: controllerItem;
                    KeyNavigation.right: controllerItem;
                }

                SelectorButton
                {
                    id: button4
                    anchors.right: parent.right
                    buttonText: "Settings"

                    KeyNavigation.up: button3;
                    KeyNavigation.down: button1;
                    KeyNavigation.left: exitButton;
                    KeyNavigation.right: exitButton;
                }
            }

            Rectangle
            {
                id: bevelOuter
                width: parent.height * 0.65
                height: parent.width * 0.5
                x: parent.width * 0.15
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
                        spacing: parent.height * 0.05

                        ItemConnectionIndicator
                        {
                            id: serverItem
                            hardwareDescriptor: 1
                            connected: serverConnectionStatus

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
        }
        ExitButton
        {
            id: exitButton
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.03
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.25
            z: parent.z + 1

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
}
