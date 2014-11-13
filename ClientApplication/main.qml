import QtQuick 2.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

FocusScope
{
    id: applicationFocus
    property alias color: clientMain.color
    x: clientMain.x; y: clientMain.y
    width: clientMain.width; height: clientMain.height

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
        visibility: "FullScreen"
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
                buttons.buttonFocus = 1;
                buttons.index = 1;
                applicationFocus.focus =  button1;
            }

            Keys.onPressed:
            {
                if (event.key == Qt.Key_Up)
                {
                    if (buttons.buttonFocus == 1)
                    {
                        buttons.processMove(true);
                    }
                    else if (buttons.buttonFocus == 0)
                    {
                        //do other movement
                    }
                }
                else if (event.key == Qt.Key_Down)
                {
                    if (buttons.buttonFocus == 1)
                    {
                        buttons.processMove(false);
                    }
                    else if (buttons.buttonFocus == 0)
                    {
                        //do other movement
                    }
                }
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

                property int index: 1
                property int buttonFocus: 1

                function processMove(up)
                {
                    if (up)
                    {//up arrow
                        switch(buttons.index)
                        {
                        case 1:
                            buttons.index = 4;
                            button4.focus = true;
                            break;
                        case 2:
                            buttons.index = 1;
                            button1.focus = true;
                            break;
                        case 3:
                            buttons.index = 2;
                            button2.focus = true;
                            break;
                        case 4:
                            buttons.index = 3;
                            button3.focus = true;
                            break;
                        default:
                            break;
                        }
                    }
                    else if (!up)
                    {//down arrow
                        switch(buttons.index)
                        {
                        case 1:
                            buttons.index = 2;
                            button2.focus = true;
                            break;
                        case 2:
                            buttons.index = 3;
                            button3.focus = true;
                            break;
                        case 3:
                            buttons.index = 4;
                            button4.focus = true;
                            break;
                        case 4:
                            buttons.index = 1;
                            button1.focus = true;
                            break;
                        default:
                            break;
                        }
                    }
                }

                SelectorButton
                {
                    id: button1
                    anchors.right: parent.right
                    buttonText: "Drive"
                }

                SelectorButton
                {
                    id: button2
                    anchors.right: parent.right
                    buttonText: "Calibrate"
                }

                SelectorButton
                {
                    id: button3
                    anchors.right: parent.right
                    buttonText: "Test"
                }

                SelectorButton
                {
                    id: button4
                    anchors.right: parent.right
                    buttonText: "Settings"
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
                            id: testItem1
                            hardwareDescriptor: 1
                            connected: true
                        }
                        ItemConnectionIndicator
                        {
                            id: testItem2
                            hardwareDescriptor: 2
                            connected: true
                        }
                        ItemConnectionIndicator
                        {
                            id: testItem3
                            hardwareDescriptor: 3
                            connected: false
                        }
                    }
                }
            }

        }
    }
}
