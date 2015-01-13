import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2

Rectangle
{
    id: transparencyContainer
    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    color: "transparent"
    z: parent.z + 1
    visible: false

    property int alertLevel: 0
    property string alertMessage: ""
    property string alertTitle: ""
    property string previousMenuState: ""

    function showBox(level, title, message, previous)
    {
        transparencyContainer.alertLevel = level;
        if (level == 1)
            alertLevelIconContainer.source = "qrc:/images/information_icon.png";
        else if (level == 2)
            alertLevelIconContainer.source = "qrc:/images/warning_icon.png";
        else if (level == 3)
            alertLevelIconContainer.source = "qrc:/images/error_icon.png";

        transparencyContainer.alertTitle = title;
        transparencyContainer.alertMessage = message;
        transparencyContainer.previousMenuState = previous;
        transparencyContainer.visible = true;
        okButton.focus = true;
        applicationShadingAnimationIn.start();
    }

    function hideBox()
    {
        transparencyContainer.alertLevel = 0;
        transparencyContainer.alertTitle = "";
        transparencyContainer.alertMessage = "";
        transparencyContainer.visible = false;
        applicationShadingAnimationOut.start();
        if (transparencyContainer.previousMenuState == "HOME")
        {
            clientMain.customState = "HOME";
            homeScreen.setDefaultFocus();
        }
        else if (transparencyContainer.previousMenuState == "DRIVE")
        {
            clientMain.customState = "DRIVE";
            driveMenu.setDefaultFocus();
        }
//        else if (transparencyContainer.previousMenuState == "CALIBRATE")
//        {

//        }
//        else if (transparencyContainer.previousMenuState == "TEST")
//        {

//        }
        else if (transparencyContainer.previousMenuState == "SETTINGS")
        {
            clientMain.customState = "SETTINGS";
            settingsMenu.setDefaultFocus();
        }
    }

    Rectangle
    {
        id: applicationShading
        height: parent.height
        width: parent.width
        anchors.centerIn: parent
        color: "black"
        opacity: 0.5
        z: parent.z + 1

        PropertyAnimation
        {
            id: applicationShadingAnimationIn
            property: "opacity"
            target: applicationShading
            from: 0
            to: 0.5
            duration: 500
            alwaysRunToEnd: true
        }
        PropertyAnimation
        {
            id: applicationShadingAnimationOut
            property: "opacity"
            target: applicationShading
            from: 0.5
            to: 0
            duration: 500
            alwaysRunToEnd: true
        }
    }

    Rectangle
    {
        id: alertBoxContainer
        width: parent.width * 0.4
        height: parent.height * 0.3
        anchors.centerIn: parent
        gradient: Gradient
        {
            GradientStop { position: 0.15; color: "light gray" }
            GradientStop { position: 0.4; color: "gray" }
            GradientStop { position: 0.85; color: "gray" }
            GradientStop { position: 0.95; color: "black" }
        }
        border.width: 3
        border.color: "black"
        radius: 10
        z: parent.z + 100//message box should always be on top

        Rectangle
        {
            id: alertBoxTitleBar
            height: parent.height * 0.125
            width: parent.width
            radius: 10
            color: "gray"
            border.width: 3
            border.color: "black"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            Text
            {
                id: alertTitleText
                font.pixelSize: parent.height * 0.7
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.05
                text: transparencyContainer.alertTitle
            }
        }

        Image
        {//just use colored rectangle until icons are created
            id: alertLevelIconContainer
            height: parent.height * 0.3
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/information_icon.png"
            anchors.top: alertMessageContainer.top
            anchors.right: alertMessageContainer.left
        }

        Rectangle
        {
            id: alertMessageContainer
            height: parent.height * 0.5
            width: parent.width * 0.6
            anchors.top: alertBoxTitleBar.bottom
            anchors.topMargin: parent.height * 0.075
            anchors.horizontalCenter: parent.horizontalCenter
            color: "transparent"

            Text
            {
                id: alertMessageText
                font.pixelSize: alertTitleText.font.pixelSize
                wrapMode: Text.Wrap
                anchors.fill: parent
                anchors.margins: parent.height * 0.05
                text: transparencyContainer.alertMessage
            }
        }

        GeneralButton
        {
            id: okButton
            height: parent.height * 0.18
            width: parent.width * 0.22
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.12
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.12
            customSource: "qrc:/text/ok_text.png"

            Keys.onReturnPressed: transparencyContainer.hideBox();
        }
    }
}
