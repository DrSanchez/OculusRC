import QtQuick 2.0

Rectangle
{
    id: oculusSplashController
    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    color: "transparent"

    state: "STOPPED"
    property bool finished: false

    Image
    {
        id: oculusSplashImage
        height: parent.height
        source: "qrc:/images/Oculus_Splash.png"
        fillMode: Image.PreserveAspectFit
        opacity: 0
    }
    Timer
    {
        id: timer
        interval: 2000
        running: false
        repeat: false
        onTriggered: oculusSplashController.state = "STOPPED"
    }
    states:
    [
        State
        {
            name: "STOPPED"
            PropertyChanges { target: oculusSplashImage; opacity: 0 }
        },
        State
        {
            name: "STARTED"
            PropertyChanges { target: oculusSplashImage; opacity: 1 }
        }
    ]
    transitions:
    [
        Transition
        {
            from: "STOPPED"
            to: "STARTED"
            onRunningChanged: if(running)timer.start();
            PropertyAnimation { target: oculusSplashImage; property: "opacity"; from: 0; to: 1; duration: 600 }
        },
        Transition
        {
            from: "STARTED"
            to: "STOPPED"
            onRunningChanged: if(!running)finished=true;
            PropertyAnimation { target: oculusSplashImage; property: "opacity"; from: 1; to: 0; duration: 700; alwaysRunToEnd: true }
        }
    ]
}
