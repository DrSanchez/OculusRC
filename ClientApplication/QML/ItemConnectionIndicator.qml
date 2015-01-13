import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id: connectionContainer
    width: clientMain.width * 0.37
    height: clientMain.height * 0.13
    color: "transparent"

    state: "UNFOCUSED"

    property int hardwareDescriptor: 1
    property bool connected: false

    Rectangle
    {
        id: statusContainer
        width: parent.width * 0.7
        height: parent.height
        z: parent.z + 1
        border.width: 3
        border.color: "black"
        gradient: Gradient
        {
            GradientStop { position: 0.00; color: connected ? "green" : clientTheme.indicatorBackground }
            GradientStop { position: 0.65; color: connected ? "dark green" : "dark red" }
        }

        Image
        {
            id: connectionImage
            height: parent.height
            width: parent.width * 0.3
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: parent.width * 0.03

            function toggleSource()
            {
                if (connected)
                {
                    connectionImage.source = "qrc:/images/ItemConnected.png"
                }
                else if (!connected)
                {
                    connectionImage.source = "qrc:/images/ItemDisconnected.png"
                }
            }

            source:
            {
                if (connected)
                {
                    connectionImage.source = "qrc:/images/ItemConnected.png"
                }
                else if (!connected)
                {
                    connectionImage.source = "qrc:/images/ItemDisconnected.png"
                }
            }
        }

        Image
        {
            id: hardwareText
            width: parent.width * 0.5
            fillMode: Image.PreserveAspectFit
            anchors.top: parent.top
            anchors.topMargin: parent.height * 0.1
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.1
            source:
            {
                switch(connectionContainer.hardwareDescriptor)
                {
                case 1:
                    hardwareText.source = "qrc:/text/jetson_tk1_text.png";
                    break;
                case 2:
                    hardwareText.source = "qrc:/text/oculus_text.png"
                    break;
                case 3:
                    hardwareText.source = "qrc:/text/controller_text.png"
                    break;
                }
            }
        }

        Image
        {
            id: hardwareConnectedText
            width: parent.width * 0.5
            fillMode: Image.PreserveAspectFit
            anchors.top: hardwareText.bottom
            anchors.topMargin: hardwareText.height * 0.05
            anchors.horizontalCenter: hardwareText.horizontalCenter

            function toggleText()
            {
                if (connected)
                {
                    hardwareConnectedText.source = "qrc:/text/connected_text.png";
                }
                else if (!connected)
                {
                    hardwareConnectedText.source = "qrc:/text/disconnected_text.png";
                }
            }

            source:
            {
                if (connected)
                {
                    hardwareConnectedText.source = "qrc:/text/connected_text.png";
                }
                else if (!connected)
                {
                    hardwareConnectedText.source = "qrc:/text/disconnected_text.png";
                }
            }
        }
    }

    Rectangle
    {
        id: imageContainer
        anchors.left: statusContainer.right
        anchors.leftMargin: parent.width * 0.05
        color: "transparent"
        height: parent.height
        width: parent.width * 0.3

        Image
        {
            id: itemImage
            height: connectionContainer.height
            width: connectionContainer.width * 0.3
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit

            source:
            {
                switch(connectionContainer.hardwareDescriptor)
                {
                case 1:
                    itemImage.source = "qrc:/images/tk1.png"
                    break;
                case 2:
                    itemImage.source = "qrc:/images/dk2.png"
                    break;
                case 3:
                    itemImage.source = "qrc:/images/steeringwheel.png"
                    break;
                default:
                    console.log("Usage: Server = 1\n\tOculus = 2\n\tController = 3")
                    break;
                }
            }
        }
    }

    onFocusChanged:
    {
        if (focus == true)
        {
            connectionContainer.state = "FOCUSED";
        }
        else if (focus == false)
        {
            connectionContainer.state = "UNFOCUSED"
        }
    }

    onConnectedChanged:
    {
        connectionImage.toggleSource();
        hardwareConnectedText.toggleText();
    }

    RectangularGlow
    {
        id: highlightedGlow
        color: connectionContainer.focus ? "dark red" : "transparent"
        height: connectionContainer.height
        width: connectionContainer.width
        z: connectionContainer.z - 1
        anchors.centerIn: connectionContainer
        glowRadius: parent.width / 8
        visible: connectionContainer.focus
    }

    states:
    [
        State
        {
            name: "FOCUSED"
            PropertyChanges { target: highlightedGlow; color: connected ? "dark green" : "dark red" }
        },
        State
        {
            name: "UNFOCUSED"
            PropertyChanges { target: highlightedGlow; color: "transparent" }
        }

    ]

    transitions:
    [
        Transition
        {
            from: "UNFOCUSED"
            to: "FOCUSED"
            ColorAnimation { target: highlightedGlow; duration: 250 }
        },
        Transition
        {
            from: "FOCUSED"
            to: "UNFOCUSED"
            ColorAnimation { target: highlightedGlow; duration: 250 }
        }
    ]
}
