import QtQuick 2.0

Rectangle
{
    height: parent.height * 0.12
    width: parent.width * 0.2
    radius: 50
    border.width: 4
    border.color: "black"
    color: clientTheme.selectorButtonBackground

    Text
    {
        text: "Exit"
        font.pixelSize: parent.height * 0.65
        anchors.centerIn: parent
    }

}
