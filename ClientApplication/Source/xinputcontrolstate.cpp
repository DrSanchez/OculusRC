#include "xinputcontrolstate.h"
#include <QDebug>

XInputControlState::XInputControlState(QObject *parent)
    : QObject(parent), _buttons(0), _leftTrigger(0), _rightTrigger(0),
    _leftThumbX(0), _leftThumbY(0), _rightThumbX(0), _rightThumbY(0)
{
}

XInputControlState::XInputControlState(const XInputControlState& copy)
    : QObject(copy.parent()), _buttons(0), _leftTrigger(0), _rightTrigger(0),
      _leftThumbX(0), _leftThumbY(0), _rightThumbX(0), _rightThumbY(0)
{
    if (this != &copy)
    {
        this->_batteryLevel = copy._batteryLevel;
        this->_batteryState = copy._batteryState;
        this->_buttons = copy._buttons;
        this->_leftThumbX = copy._leftThumbX;
        this->_leftThumbY = copy._leftThumbY;
        this->_leftTrigger = copy._leftTrigger;
        this->_rightThumbX = copy._rightThumbX;
        this->_rightThumbY = copy._rightThumbY;
        this->_rightTrigger = copy._rightTrigger;
    }
}

XInputControlState& XInputControlState::operator=(const XInputControlState& rhs)
{
    if (this != &rhs)
    {
        this->_batteryLevel = rhs._batteryLevel;
        this->_batteryState = rhs._batteryState;
        this->_buttons = rhs._buttons;
        this->_leftThumbX = rhs._leftThumbX;
        this->_leftThumbY = rhs._leftThumbY;
        this->_leftTrigger = rhs._leftTrigger;
        this->_rightThumbX = rhs._rightThumbX;
        this->_rightThumbY = rhs._rightThumbY;
        this->_rightTrigger = rhs._rightTrigger;
    }
    return *this;
}

bool XInputControlState::equals(const XInputControlState& lhs, const XInputControlState& rhs)
{
    return (lhs._buttons == rhs._buttons &&
        lhs._leftTrigger == rhs._leftTrigger &&
        lhs._rightTrigger == rhs._rightTrigger &&
        lhs._leftThumbX == rhs._leftThumbX &&
        lhs._leftThumbY == rhs._leftThumbY &&
        lhs._rightThumbX == rhs._rightThumbX &&
        lhs._rightThumbY == rhs._rightThumbY &&
        lhs._batteryState == rhs._batteryState &&
        lhs._batteryLevel == rhs._batteryLevel);
}

/********************************************************************************
 * This method should be called by a previous state object
 *******************************************************************************/
void XInputControlState::emitControllerSignals(const XInputControlState *current)
{
    static bool pressed = false;

    pressed = this->buttonPressed(XINPUT_GAMEPAD_A);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_A))
        emit buttonAChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_B);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_B))
        emit buttonBChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_X);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_X))
        emit buttonXChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_Y);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_Y))
        emit buttonYChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER))
        emit leftBumperChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER))
        emit rightBumperChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_START);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_START))
        emit buttonStartChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_BACK);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_BACK))
        emit buttonSelectChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_DPAD_UP);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_DPAD_UP))
        emit dPadUpChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_DPAD_DOWN);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_DPAD_DOWN))
        emit dPadDownChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_DPAD_LEFT);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_DPAD_LEFT))
        emit dPadLeftChanged((int)pressed);
    pressed = this->buttonPressed(XINPUT_GAMEPAD_DPAD_RIGHT);
    if (pressed != current->buttonPressed(XINPUT_GAMEPAD_DPAD_RIGHT))
        emit dPadRightChanged((int)pressed);

    if (this->_leftThumbX != current->_leftThumbX)
        emit leftJoystickXChanged(current->_leftThumbX);
    if (this->_leftThumbY != current->_leftThumbY)
        emit leftJoystickYChanged(current->_leftThumbY);
    if (this->_rightThumbX != current->_rightThumbX)
        emit rightJoystickXChanged(current->_rightThumbX);
    if (this->_rightThumbY != current->_rightThumbY)
        emit rightJoystickYChanged(current->_rightThumbY);
    if (this->_leftTrigger != current->_leftTrigger)
        emit leftTriggerChanged(current->_leftTrigger);
    if (this->_rightTrigger != current->_rightTrigger)
        emit rightTriggerChanged(current->_rightTrigger);
}

bool XInputControlState::buttonPressed(quint16 xinput_gamepad_button) const
{
    return ((_buttons & xinput_gamepad_button) == xinput_gamepad_button);
}

bool XInputControlState::batteryEquals(const XInputControlState &lhs, const XInputControlState &rhs)
{
    return ((lhs._batteryState == rhs._batteryState) && (lhs._batteryLevel == rhs._batteryLevel));
}

bool operator ==(const XInputControlState& lhs, const XInputControlState& rhs)
{
    return XInputControlState::equals(lhs, rhs);
}

bool operator !=(const XInputControlState& lhs, const XInputControlState& rhs)
{
    return !XInputControlState::equals(lhs, rhs);
}

int XInputControlState::buttonA()
{
    return ((this->_buttons & XINPUT_GAMEPAD_A) == XINPUT_GAMEPAD_A) ? 0 : 1;
}

int XInputControlState::buttonB()
{
    return ((this->_buttons & XINPUT_GAMEPAD_B) == XINPUT_GAMEPAD_B) ? 0 : 1;
}

int XInputControlState::buttonX()
{
    return ((this->_buttons & XINPUT_GAMEPAD_X) == XINPUT_GAMEPAD_X) ? 0 : 1;
}

int XInputControlState::buttonY()
{
    return ((this->_buttons & XINPUT_GAMEPAD_Y) == XINPUT_GAMEPAD_Y) ? 0 : 1;
}

int XInputControlState::leftBumper()
{
    return ((this->_buttons & XINPUT_GAMEPAD_LEFT_SHOULDER) == XINPUT_GAMEPAD_LEFT_SHOULDER) ? 0 : 1;
}

int XInputControlState::rightBumper()
{
    return ((this->_buttons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 0 : 1;
}

int XInputControlState::dPadUp()
{
    return ((this->_buttons & XINPUT_GAMEPAD_DPAD_UP) == XINPUT_GAMEPAD_DPAD_UP) ? 0 : 1;
}

int XInputControlState::dPadDown()
{
    return ((this->_buttons & XINPUT_GAMEPAD_DPAD_DOWN) == XINPUT_GAMEPAD_DPAD_DOWN) ? 0 : 1;
}

int XInputControlState::dPadLeft()
{
    return ((this->_buttons & XINPUT_GAMEPAD_DPAD_LEFT) == XINPUT_GAMEPAD_DPAD_LEFT) ? 0 : 1;
}

int XInputControlState::dPadRight()
{
    return ((this->_buttons & XINPUT_GAMEPAD_DPAD_RIGHT) == XINPUT_GAMEPAD_DPAD_RIGHT) ? 0 : 1;
}

int XInputControlState::buttonStart()
{
    return ((this->_buttons & XINPUT_GAMEPAD_START) == XINPUT_GAMEPAD_START) ? 0 : 1;
}

int XInputControlState::buttonSelect()
{
    return ((this->_buttons & XINPUT_GAMEPAD_BACK) == XINPUT_GAMEPAD_BACK) ? 0 : 1;
}

int XInputControlState::buttonLeftStick()
{
    return ((this->_buttons & XINPUT_GAMEPAD_LEFT_THUMB) == XINPUT_GAMEPAD_LEFT_THUMB) ? 0 : 1;
}

int XInputControlState::buttonRightStick()
{
    return ((this->_buttons & XINPUT_GAMEPAD_RIGHT_THUMB) == XINPUT_GAMEPAD_RIGHT_THUMB) ? 0 : 1;
}

float XInputControlState::leftJoystickX()
{
    return this->_rightTrigger;
}

float XInputControlState::leftJoystickY()
{
    return this->_rightTrigger;
}

float XInputControlState::rightJoystickX()
{
    return this->_rightTrigger;
}

float XInputControlState::rightJoystickY()
{
    return this->_rightTrigger;
}

float XInputControlState::leftTrigger()
{
    return this->_rightTrigger;
}

float XInputControlState::rightTrigger()
{
    return this->_rightTrigger;
}
