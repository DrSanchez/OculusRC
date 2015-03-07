import QtQuick 2.0
import QtMultimedia 5.0

Rectangle
{
    id: mainApplicationContainer
    width: 1280
    height: 720
    color: "light gray"

    Connections
    {
        target: NetworkManager

        onSendBytesToMessageLog: messageLog.text += message;
    }

    Text
    {
        id: applicationLabel
        text: "Jetson Server"
        font.underline: true
        font.pixelSize: parent.height * 0.09
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height * 0.025
        anchors.leftMargin: parent.width * 0.025
    }

    Text
    {
        id: messageLogLabel
        text: "Message Log:"
        font.pixelSize: applicationLabel.font.pixelSize * 0.5
        anchors.top: applicationLabel.bottom
        anchors.topMargin: parent.height * 0.025
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.025
    }

    Rectangle
    {
        id: messageLogContainer
        height: parent.height * 0.51
        width: parent.width * 0.51
        color: "white"
        anchors.top: messageLogLabel.bottom
        anchors.topMargin: parent.height * 0.025
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.025
        border.width: 3
        border.color: "black"
        clip: true

        Flickable
        {
            id: editorView
            height: parent.height
            width: parent.width
            contentWidth: messageLog.paintedWidth
            contentHeight: messageLog.paintedHeight
            clip: true

            function ensureVisible(r)
            {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                    contentX = r.x+r.width-width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                    contentY = r.y+r.height-height;
            }

            TextEdit
            {
                id: messageLog
                width: editorView.width
                height: editorView.height
                wrapMode: TextEdit.Wrap
                onContentSizeChanged: editorView.ensureVisible(cursorRectangle)
                onCursorRectangleChanged: editorView.ensureVisible(cursorRectangle)
                textMargin: 5
            }
        }
    }

    Rectangle
    {
        id: exitButton
        height: parent.height * 0.1
        width: parent.width * 0.15
        color: "gray"
        border.color: "black"
        border.width: 3
        anchors.top: messageLogContainer.bottom
        anchors.topMargin: parent.height * 0.09
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.025
        Text
        {
            id: exitText
            text: "exit"
            font.pixelSize: parent.height * 0.66
            anchors.centerIn: parent
        }
        MouseArea
        {
            id: exitArea
            anchors.fill: parent
            onClicked:
            {
                NetworkManager.customDestroy();
                Qt.quit();
            }
        }
    }

    Rectangle
    {
        id: cameraFeedContainer1
        height: parent.height * 0.25
        width: parent.width * 0.4
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.025
        anchors.left: messageLogContainer.right
        anchors.leftMargin: parent.width * 0.03
        color: "transparent"
        border.color: "black"
        border.width: 2

        Text
        {
            id: camera1Text
            text: "Camera 1:"
            font.pixelSize: parent.height * 0.15
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.01
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Rectangle
    {
        id: cameraFeedContainer2
        height: parent.height * 0.25
        width: parent.width * 0.4
        anchors.top: cameraFeedContainer1.bottom
        anchors.topMargin: parent.height * 0.015
        anchors.left: messageLogContainer.right
        anchors.leftMargin: parent.width * 0.03
        color: "transparent"
        border.color: "black"
        border.width: 2

        Text
        {
            id: camera2Text
            text: "Camera 2:"
            font.pixelSize: parent.height * 0.15
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.01
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Text
    {
        id: rcDummyLabel
        text: "RC Dummy:                              "
        font.pixelSize: applicationLabel.font.pixelSize * 0.5
        font.underline: true
        anchors.top: cameraFeedContainer2.bottom
        anchors.topMargin: parent.height * 0.015
        anchors.left: messageLogContainer.right
        anchors.leftMargin: parent.width * 0.03
    }
    Rectangle
    {
        id: rcDummyContainer
        height: parent.height * 0.35
        width: parent.width * 0.4
        anchors.top: rcDummyLabel.bottom
        anchors.topMargin: parent.height * 0.0125
        anchors.left: messageLogContainer.right
        anchors.leftMargin: parent.width * 0.03
        color: "transparent"
        border.color: "black"
        border.width: 2
    }
}
