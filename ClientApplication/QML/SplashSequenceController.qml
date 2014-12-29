import QtQuick 2.0

Rectangle
{
    id: splashScreenController
    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    z: parent.z + 100
    color: "black"

    property bool running: false

    onRunningChanged:if(running)oregonTechSplash.state="STARTED";

    OregonTechSplashController
    {
        id: oregonTechSplash
        onFinishedChanged: if(finished)nvidiaSplash.state = "STARTED"
    }
    NvidiaSplashController
    {
        id: nvidiaSplash
        onFinishedChanged: if(finished)oculusSplash.state = "STARTED";
    }
    OculusSplashController
    {
        id: oculusSplash
        onFinishedChanged: if(finished)applicationSplash.state = "STARTED";
    }
    ApplicationSplashController
    {
        id: applicationSplash
        onFinishedChanged: if(finished)splashScreenController.running = false;
    }
}
