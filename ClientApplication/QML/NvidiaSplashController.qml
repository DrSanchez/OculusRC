import QtQuick 2.0

Rectangle
{
    id: nvidiaSplashController
    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    color: "transparent"

    state: "STOPPED"
    property bool finished: false

    Image
    {
        id: nvidiaSplashImage
        height: parent.height
        source: "qrc:/background/nvidia_splash_screen.png"
        fillMode: Image.PreserveAspectFit
        opacity: 0
    }

    Image
    {
        id: nvidiaSheen
        height: parent.height
        source: "qrc:/images/nvidia_sheen.png"
        fillMode: Image.PreserveAspectFit
        opacity: 0.4
        anchors.verticalCenter: parent.verticalCenter
        x: -500

        Behavior on x
        {
            SmoothedAnimation
            {
                id: sheenAnimation
                alwaysRunToEnd: true
                duration: 1250
                velocity: 5
                onRunningChanged:if (!running)nvidiaSplashController.state = "STOPPED";
            }
        }
    }

    states:
    [
        State
        {
            name: "STOPPED"
            PropertyChanges { target: nvidiaSheen; x: -500 }
            PropertyChanges { target: nvidiaSheen; opacity: 0 }
            PropertyChanges { target: nvidiaSplashImage; opacity: 0 }
        },
        State
        {
            name: "STARTED"
            PropertyChanges { target: nvidiaSheen; x: nvidiaSplashController.width + nvidiaSheen.width }
            PropertyChanges { target: nvidiaSheen; opacity: 0.4 }
            PropertyChanges { target: nvidiaSplashImage; opacity: 1 }
        }
    ]

    transitions:
    [
        Transition
        {
            from: "STOPPED"
            to: "STARTED"
            PropertyAnimation { target: nvidiaSplashImage; property: "opacity"; from: 0; to: 1; duration: 500 }
            PropertyAnimation { target: nvidiaSheen; property: "opacity"; from: 0; to: 0.4; duration: 100 }
        },
        Transition
        {
            from: "STARTED"
            to: "STOPPED"
            onRunningChanged: if (!running)finished=true;
            PropertyAnimation { target: nvidiaSplashImage; property: "opacity"; from: 1; to: 0; duration: 350; alwaysRunToEnd: true }
            PropertyAnimation { target: nvidiaSheen; property: "opacity"; from: 0.4; to: 0; duration: 50 }
        }
    ]
}
