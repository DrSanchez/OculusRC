import QtQuick 2.3
import QtGraphicalEffects 1.0

Rectangle
{
    id: selectorButtonParent
    width: clientMain.width * 0.538
    height: clientMain.height * 0.12
    gradient: Gradient
    {
        GradientStop { position: 0.05; color: "white" }
        GradientStop { position: 0.15; color: "gray" }
        GradientStop { position: 0.25; color: clientTheme.selectorButtonBackground }
        GradientStop { position: 0.6; color: clientTheme.selectorButtonBackground }
        GradientStop { position: 0.99; color: "black" }
    }

    radius: (parent.height + parent.width) / 2
    border.width: 4
    border.color: "black"

    property string sourceText: ""

    onFocusChanged:
    {
        if (focus)
        {
            anchors.rightMargin =  -(selectorButtonParent.width * 0.35);
        }
        else if (!focus)
        {
            anchors.rightMargin = -(selectorButtonParent.width * 0.45);
        }
    }

    function scaleButton()
    {
        if (focus)
        {
            anchors.rightMargin =  -(selectorButtonParent.width * 0.35);
        }
        else if (!focus)
        {
            anchors.rightMargin = -(selectorButtonParent.width * 0.45);
        }
    }

    Behavior on anchors.rightMargin
    {
        SpringAnimation
        {
            alwaysRunToEnd:  true
            duration: 300
            spring: 1;
            damping: .18
        }
    }

    Rectangle
    {
        id: toggleCircle
        anchors.left: selectorButtonParent.left
        anchors.verticalCenter: selectorButtonParent.verticalCenter
        border.width: 4
        border.color: "black"
        gradient: Gradient
        {
            GradientStop { position: 0; color: selectorButtonParent.focus ? "dark green" : "dark red" }
            GradientStop { position: 0.5; color: selectorButtonParent.focus ? "light green" : "light red" }
            GradientStop { position: 1; color: selectorButtonParent.focus ? "dark green" : "dark red" }
        }

        function setSizeOfCircle(height, width, radius)
        {
            toggleCircle.height = height;
            toggleCircle.width = width;
            toggleCircle.radius = radius;
        }

        RectangularGlow
        {
            id: toggleButtonGlow
            height: toggleCircle.height
            width: toggleCircle.width
            color: selectorButtonParent.focus ? clientTheme.selectorButtonLightOnGlow : clientTheme.selectorButtonLightOffGlow
            glowRadius: toggleCircle.radius
        }

    }

    Image
    {
        id: textImage
        source: parent.sourceText
        height: parent.height * 0.85
        fillMode: Image.PreserveAspectFit
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.15
    }

    onHeightChanged:
    {
        toggleCircle.setSizeOfCircle(height, height, height / 2);
    }

    onWidthChanged:
    {
        toggleCircle.setSizeOfCircle(height, height, height / 2);
    }

    Component.onCompleted:
    {
        toggleCircle.setSizeOfCircle(height, height, height / 2);
    }
}
