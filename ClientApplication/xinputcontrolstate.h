/**************************************************
* Author:               Jack Sanchez
* Date Last Modified:   12/20/2014
* File:                 xinputcontrolstate.h
*
* Purpose:  The XInputControlState class maintains
* a view of an XInput device and emits signals for
* triggers, joysticks, any changes in button
* state values, and changes in battery states.
*
**************************************************/

#ifndef XINPUTCONTROLSTATE_H
#define XINPUTCONTROLSTATE_H

//XInput Gamepad Bitmask Values
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

enum Control
{
    ButtonA,
    ButtonB,
    ButtonX,
    ButtonY,
    LeftBumper,
    RightBumper,
    LeftTrigger,
    RightTrigger,
    DPadUp,
    DPadDown,
    DPadLeft,
    DPadRight,
    LeftStickX,
    LeftStickY,
    RightStickX,
    RightStickY,
    ButtonStart,
    ButtonSelect,
    ButtonLeftStick,
    ButtonRightStick
};

#include <QObject>
#include "XInput.h"

class XInputControlState : public QObject
{
    Q_OBJECT

public:
    //constructors and destructors
    explicit XInputControlState(QObject *parent = 0);
    XInputControlState(const XInputControlState& copy);
    XInputControlState& operator=(const XInputControlState& rhs);

    //public methods
    static bool equals(const XInputControlState& lhs, const XInputControlState& rhs);
    bool buttonPressed(quint16 xinput_gamepad_button) const;
    static bool batteryEquals(const XInputControlState& lhs, const XInputControlState& rhs);
    void emitControllerSignals(const XInputControlState * current);

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

    //controller input read methods
    int buttonA();
    int buttonB();
    int buttonX();
    int buttonY();
    int leftBumper();
    int rightBumper();
    int dPadUp();
    int dPadDown();
    int dPadLeft();
    int dPadRight();
    int buttonStart();
    int buttonSelect();
    int buttonLeftStick();
    int buttonRightStick();
    float leftJoystickX();
    float leftJoystickY();
    float rightJoystickX();
    float rightJoystickY();
    float leftTrigger();
    float rightTrigger();

signals:
    //controller input signals
    void buttonAChanged(int value, Control c = ButtonA);
    void buttonBChanged(int value, Control c = ButtonB);
    void buttonXChanged(int value, Control c = ButtonX);
    void buttonYChanged(int value, Control c = ButtonY);
    void rightBumperChanged(int value, Control c = RightBumper);
    void leftBumperChanged(int value, Control c = LeftBumper);
    void dPadUpChanged(int value, Control c = DPadUp);
    void dPadDownChanged(int value, Control c = DPadDown);
    void dPadLeftChanged(int value, Control c = DPadLeft);
    void dPadRightChanged(int value, Control c = DPadRight);
    void buttonStartChanged(int value, Control c = ButtonStart);
    void buttonSelectChanged(int value, Control c = ButtonSelect);
    void buttonLeftStickChanged(int value, Control c = ButtonLeftStick);
    void buttonRightStickChanged(int value, Control c = ButtonRightStick);
    void leftJoystickXChanged(float value, Control c = LeftStickX);
    void leftJoystickYChanged(float value, Control c = LeftStickY);
    void rightJoystickXChanged(float value, Control c = RightStickX);
    void rightJoystickYChanged(float value, Control c = RightStickY);
    void leftTriggerChanged(float value, Control c = LeftTrigger);
    void rightTriggerChanged(float value, Control c = RightTrigger);

};

bool operator ==(const XInputControlState& lhs, const XInputControlState& rhs);
bool operator !=(const XInputControlState& lhs, const XInputControlState& rhs);

#endif // XINPUTCONTROLSTATE_H
