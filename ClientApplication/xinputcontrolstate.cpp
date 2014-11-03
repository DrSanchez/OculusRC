#include "xinputcontrolstate.h"

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

bool XInputControlState::buttonPressed(quint16 xinput_gamepad_button)
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

