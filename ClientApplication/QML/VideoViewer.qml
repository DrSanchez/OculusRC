import QtQuick 2.0
import QmlVlc 0.1

Rectangle
{
    id: viewerContainer
    color: "transparent"
    height: parent.height * 0.3
    width: parent.width * 0.5
    z: parent.z + 50
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenterOffset: parent.height * 0.05
    anchors.verticalCenter: parent.verticalCenter

    property int previewHeight: parent.height * 0.3
    property int previewWidth: parent.width * 0.5
    property int fullViewHeight: parent.height * 0.75
    property int fullViewWidth: parent.width * 0.85
    property int parentHeight: parent.height
    property int parentWidth: parent.width

    function setDefaultFocus()
    {
        toExpanded.start();
        viewerContainer.focus = true;
        ClientNetwork.state = 1;
        SteeringWheel.driveMode = true;
    }

    Keys.onEscapePressed:
    {
        toPreview.start();
        ClientNetwork.state = 0;
        SteeringWheel.driveMode = false;
        //we guarantee the driveMenu was the previous menu
        driveMenu.setDefaultFocus();
    }

    ParallelAnimation
    {
        id: toPreview
        alwaysRunToEnd: false

        SpringAnimation
        {
            target: viewerContainer
            property: "height"
            to: previewHeight
            alwaysRunToEnd: true
            duration: 50
            spring: 1
            damping: .18
        }
        SpringAnimation
        {
            target: viewerContainer
            property: "width"
            to: previewWidth
            alwaysRunToEnd: true
            duration: 50
            spring: 1
            damping: .18
        }
        SpringAnimation
        {
            target: fullShadow
            property: "opacity"
            to: 0.0
            alwaysRunToEnd: true
            duration: 50
            spring: 1
            damping: .18
        }
    }
    ParallelAnimation
    {
        id: toExpanded
        alwaysRunToEnd: false

        SpringAnimation
        {
            target: viewerContainer
            property: "height"
            to: fullViewHeight
            alwaysRunToEnd: true
            duration: 50
            spring: 1
            damping: .18
        }
        SpringAnimation
        {
            target: viewerContainer
            property: "width"
            to: fullViewWidth
            alwaysRunToEnd: true
            duration: 50
            spring: 1
            damping: .18
        }
        SpringAnimation
        {
            target: fullShadow
            property: "opacity"
            to: 0.75
            alwaysRunToEnd: true
            duration: 50
            spring: 1
            damping: .18
        }
    }

    Rectangle
    {
        id: fullShadow
        height: parentHeight * 1.15
        width: parentWidth * 1.15
        anchors.centerIn: parent
        color: "black"
        opacity: 0.0
    }

    Rectangle
    {
        id: cam1Container
        height: parent.height * 0.975
        width: parent.width * 0.495
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: width * 0.025
        border.width: 2
        border.color: "black"
        color: "transparent"

        VlcPlayer
        {
            id: cam1Source
            mrl: ("tcp://" + ClientNetwork.JetsonIP + ":5000")
        }
        VlcVideoSurface
        {
            id: cam1View
            source: cam1Source
            anchors.fill: parent
            fillMode: VlcVideoSurface.PreserveAspectFit
        }
    }
    Rectangle
    {
        id: cam2Container
        height: parent.height * 0.975
        width: parent.width * 0.495
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: width * 0.025
        border.width: 2
        border.color: "black"
        color: "transparent"

        VlcPlayer
        {
            id: cam2Source
            mrl: ("tcp://" + ClientNetwork.JetsonIP + ":5005")
        }
        VlcVideoSurface
        {
            id: cam2View
            source: cam2Source
            anchors.fill: parent
            fillMode: VlcVideoSurface.PreserveAspectFit
        }
    }
}
