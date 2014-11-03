#ifndef XINPUTCONTROLSTATE_H
#define XINPUTCONTROLSTATE_H

/*******************************************
*   Device button                   Bitmask
*   XINPUT_GAMEPAD_DPAD_UP          0x0001
*   XINPUT_GAMEPAD_DPAD_DOWN        0x0002
*   XINPUT_GAMEPAD_DPAD_LEFT        0x0004
*   XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
*   XINPUT_GAMEPAD_START            0x0010
*   XINPUT_GAMEPAD_BACK             0x0020
*   XINPUT_GAMEPAD_LEFT_THUMB       0x0040
*   XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
*   XINPUT_GAMEPAD_LEFT_SHOULDER	0x0100
*   XINPUT_GAMEPAD_RIGHT_SHOULDER	0x0200
*   XINPUT_GAMEPAD_A                0x1000
*   XINPUT_GAMEPAD_B                0x2000
*   XINPUT_GAMEPAD_X                0x4000
*   XINPUT_GAMEPAD_Y                0x8000
******************************************/

#include <QObject>
#include "XInput.h"

class XInputControlState : public QObject
{
    Q_OBJECT

public:
    explicit XInputControlState(QObject *parent = 0);
    XInputControlState(const XInputControlState& copy);
    XInputControlState& operator=(const XInputControlState& rhs);

    static bool equals(const XInputControlState& lhs, const XInputControlState& rhs);
    bool buttonPressed(quint16 xinput_gamepad_button);
    static bool batteryEquals(const XInputControlState& lhs, const XInputControlState& rhs);

    //public members
    quint16 _buttons;
    float _leftTrigger;
    float _rightTrigger;
    float _leftThumbX;
    float _leftThumbY;
    float _rightThumbX;
    float _rightThumbY;
    quint8 _batteryState;
    quint8 _batteryLevel;

signals:

public slots:

private:

};

bool operator ==(const XInputControlState& lhs, const XInputControlState& rhs);
bool operator !=(const XInputControlState& lhs, const XInputControlState& rhs);

#endif // XINPUTCONTROLSTATE_H
