import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle
{
    id: exitButtonContainer
    height: parent.height * 0.12
    width: parent.width * 0.2
    radius: 50
    border.width: 4
    border.color: "black"
    color: clientTheme.selectorButtonBackground

    state: "UNFOCUSED"

    Text
    {
        id: exitText
        text: "Exit"
        font.pixelSize: parent.height * 0.65
        anchors.centerIn: parent
    }

    onFocusChanged:
    {
        if (focus == true)
        {
            exitButtonContainer.state = "FOCUSED";
            exitButtonContainer.scale = 1.05;
        }
        else if (focus == false)
        {
            exitButtonContainer.state = "UNFOCUSED";
            exitButtonContainer.scale = 1.00;
        }
    }

    RectangularGlow
    {
       id: exitGlow
       color: exitButtonContainer.focus ? "dark red" : "transparent"
       height: parent.height
       width: parent.width
       z: exitText.z - 1
       anchors.centerIn: parent
       glowRadius: parent.radius
       visible: exitButtonContainer.focus

    }

    Behavior on scale
    {
        SpringAnimation
        {
            alwaysRunToEnd:  true
            duration: 300
            spring: 1;
            damping: .18
        }
    }

    function exit()
    {
        Qt.quit();
    }

    states:
    [
        State
        {
            name: "FOCUSED"
            PropertyChanges { target: exitGlow; color: "dark red" }
        },
        State
        {
            name: "UNFOCUSED"
            PropertyChanges { target: exitGlow; color: "transparent" }
        }
    ]

    transitions:
    [
        Transition
        {
            from: "UNFOCUSED"
            to: "FOCUSED"
            ColorAnimation { target: exitGlow; duration: 250 }
        },
        Transition
        {
            from: "FOCUSED"
            to: "UNFOCUSED"
            ColorAnimation { target: exitGlow; duration: 250 }
        }
    ]
}





