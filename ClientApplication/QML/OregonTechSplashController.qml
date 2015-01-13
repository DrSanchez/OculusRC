import QtQuick 2.0

Rectangle
{
    id: oregonTechSplashController
    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    color: "transparent"

    state: "STOPPED"
    property bool finished: false

    Image
    {
        id: oregonTechSplashImage
        height: parent.height
        source: "qrc:/background/oregon_tech_splash.png"
        fillMode: Image.PreserveAspectFit
        opacity: 0
    }
    Timer
    {
        id: timer
        interval: 2000
        running: false
        repeat: false
        onTriggered: oregonTechSplashController.state = "STOPPED"
    }
    states:
    [
        State
        {
            name: "STOPPED"
            PropertyChanges { target: oregonTechSplashImage; opacity: 0 }
        },
        State
        {
            name: "STARTED"
            PropertyChanges { target: oregonTechSplashImage; opacity: 1 }
        }
    ]
    transitions:
    [
        Transition
        {
            from: "STOPPED"
            to: "STARTED"
            onRunningChanged: if(running)timer.start();
            PropertyAnimation { target: oregonTechSplashImage; property: "opacity"; from: 0; to: 1; duration: 600 }
        },
        Transition
        {
            from: "STARTED"
            to: "STOPPED"
            onRunningChanged: if(!running)finished=true;
            PropertyAnimation { target: oregonTechSplashImage; property: "opacity"; from: 1; to: 0; duration: 700; alwaysRunToEnd: true }
        }
    ]
}
