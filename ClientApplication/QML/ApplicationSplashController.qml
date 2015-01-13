import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id: applicationSplashController
    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    color: "transparent"

    state: "STOPPED"
    property bool finished: false

    Image
    {
        id: applicationSplashImage
        height: parent.height
        source: "qrc:/background/oculus_rc_splash_screen.png"
        fillMode: Image.PreserveAspectFit
        opacity: 0
    }

    Rectangle
    {
        id: anyKeyContainer
        color: "transparent"
        height: parent.height * 0.2
        width: anyKeyTextImage.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.25
        anchors.horizontalCenter: parent.horizontalCenter
        x: ((parent.width / 2) - (width / 2))

        Image
        {
            id: anyKeyTextImage
            height: parent.height
            fillMode: Image.PreserveAspectFit
            source: "qrc:/text/press_any_key_text.png"
            opacity: 0

            PropertyAnimation
            {
                id: anyKeyTextAnimationIn
                property: "opacity"
                target: anyKeyTextImage
                from: 0
                to: 1
                duration: 1000
                alwaysRunToEnd: true
                onRunningChanged:if (!running && !finished)anyKeyTextAnimationOut.start();
            }
            PropertyAnimation
            {
                id: anyKeyTextAnimationOut
                property: "opacity"
                target: anyKeyTextImage
                from: 1
                to: 0
                duration: 1000
                alwaysRunToEnd: true
                onRunningChanged:if (!running && !finished)anyKeyTextAnimationIn.start();
            }
        }
    }
    Keys.onPressed:
    {
        applicationSplashController.state = "STOPPED";
        event.accepted = true;
    }
    states:
    [
        State
        {
            name: "STOPPED"
            PropertyChanges { target: applicationSplashImage; opacity: 0 }
            PropertyChanges { target: anyKeyContainer; opacity: 0 }
        },
        State
        {
            name: "STARTED"
            PropertyChanges { target: applicationSplashImage; opacity: 1 }
        }
    ]

    transitions:
    [
        Transition
        {
            from: "STOPPED"
            to: "STARTED"
            onRunningChanged:
            {
                if (running)
                {
                    anyKeyTextAnimationIn.start();
                    applicationSplashController.focus = true;
                }
            }

            PropertyAnimation { target: applicationSplashImage; property: "opacity"; from: 0; to: 1; duration: 600 }
        },
        Transition
        {
            from: "STARTED"
            to: "STOPPED"
            onRunningChanged:if(!running)finished=true;
            PropertyAnimation { target: applicationSplashImage; property: "opacity"; from: 1; to: 0; duration: 700; alwaysRunToEnd: true }
            PropertyAnimation { target: anyKeyContainer; property: "opacity"; from: 1; to: 0; duration: 700; alwaysRunToEnd: true }
        }
    ]
}
