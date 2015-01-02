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
    property bool skipped: false

    onRunningChanged:if(running)oregonTechSplash.state="STARTED";

    Keys.onPressed:
    {
        if (oregonTechSplash.state == "STARTED")
        {
            oregonTechSplash.state = "STOPPED";
            skipped = true;
        }
        else if (nvidiaSplash.state == "STARTED")
        {
            nvidiaSplash.state = "STOPPED";
            skipped = true;
        }
        else if (oculusSplash.state == "STARTED")
        {
            oculusSplash.state = "STOPPED";
            skipped = true;
        }
        if (skipped)
            applicationSplash.state = "STARTED";
    }

    OregonTechSplashController
    {
        id: oregonTechSplash
        onFinishedChanged: if(finished && !skipped)nvidiaSplash.state = "STARTED"
    }
    NvidiaSplashController
    {
        id: nvidiaSplash
        onFinishedChanged: if(finished && !skipped)oculusSplash.state = "STARTED";
    }
    OculusSplashController
    {
        id: oculusSplash
        onFinishedChanged: if(finished && !skipped)applicationSplash.state = "STARTED";
    }
    ApplicationSplashController
    {
        id: applicationSplash
        onFinishedChanged: if(finished)splashScreenController.running = false;
    }
}
