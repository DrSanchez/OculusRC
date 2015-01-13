import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id: settingsItemContainer
    height: parent.height * 0.175
    width: parent.width * 0.95
    border.color: "black"
    border.width: focus ? 1 : 0
    radius: 30
    z: parent.z + 1
    color: "transparent"

    property int settingsItemDescriptor: 0

    Image
    {
        id: settingsText
        width: parent.width * 0.8
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
        z: parent.z + 2
        source:
        {
            if (settingsItemDescriptor == 1)
            {
                settingsText.source = "qrc:/text/application_settings_text.png";
            }
            else if (settingsItemDescriptor == 2)
            {
                settingsText.source = "qrc:/text/oculus_rift_settings_text.png";
            }
            else if (settingsItemDescriptor == 3)
            {
                settingsText.source = "qrc:/text/controller_text.png";
            }
            else if (settingsItemDescriptor == 4)
            {
                settingsText.source = "qrc:/text/esc_settings_text.png";
            }
            else if (settingsItemDescriptor == 5)
            {
                settingsText.source = "qrc:/text/back_text.png";
            }
        }
    }
    RectangularGlow
    {
        id: highlightGlow
        height: parent.height * 0.95
        width: parent.width * 0.95
        anchors.centerIn: parent
        glowRadius: 30
        opacity: parent.focus ? 0.65 : 0
        color: "black"
        z: settingsText.z - 1

        Behavior on opacity
        {
            SpringAnimation
            {
                alwaysRunToEnd:  true
                duration: 300
                spring: 1;
                damping: .18
            }
        }
    }
}
