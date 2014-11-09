import QtQuick 2.0

Rectangle
{
    id: connectionContainer
    width: clientMain.width * 0.33
    height: clientMain.height * 0.16
    color: "transparent"

    property int hardwareDescriptor: 1

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
            GradientStop { position: 0.00; color: clientTheme.indicatorBackground }
            GradientStop { position: 0.65; color: "dark red" }
        }
    }

    Rectangle
    {
        id: imageContainer
        anchors.left: statusContainer.right

        Image
        {
            id: itemImage
            height: connectionContainer.height
            width: connectionContainer.width * 0.3
            anchors.fill: parent
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
                    itemImage.source = "qrc:/images/wheel1.png"
                    break;
                default:
                    console.log("Usage: Server = 1\n\tOculus = 2\n\tController = 3")
                    break;
                }
            }
        }
    }
}
