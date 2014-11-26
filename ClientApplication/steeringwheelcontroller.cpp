#include "steeringwheelcontroller.h"
#include <math.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

SteeringWheelController::SteeringWheelController(unsigned int controllerNumber, unsigned int leftStickDeadZone,
                                                 unsigned int rightStickDeadZone, unsigned int triggerThreshold,
                                                 QObject * parent)
    : QObject(parent),  _previousConnectState(false), _currentConnectState(false),_leftStickDeadZone(qMin(leftStickDeadZone, MAX_STICK_VALUE)),
      _rightStickDeadZone(qMin(rightStickDeadZone, MAX_STICK_VALUE)), _triggerThreshold(qMin(triggerThreshold, MAX_TRIGGER_VALUE)), _currentState(this),
      _previousState(this)
{
    this->_controllerDesignator = qMin(controllerNumber, 3u);
    _updateTimer = new QTimer();
    connect(_updateTimer, &QTimer::timeout, this, &SteeringWheelController::update);
}

void SteeringWheelController::startPolling(unsigned int timerInterval)
{
    this->_updateTimer->start(timerInterval);
}

void SteeringWheelController::stopPolling()
{
    this->_updateTimer->stop();
}

void SteeringWheelController::update()
{
    XINPUT_STATE xState;
    memset(&xState, 0, sizeof(XINPUT_STATE));
    _currentConnectState = (XInputGetState(_controllerDesignator, &xState) == ERROR_SUCCESS);

    //connection event
    if (_previousConnectState == false && _currentConnectState == true)
        emit controllerConnected(_controllerDesignator);

    //disconnection event
    if (_previousConnectState == true && _currentConnectState == false)
        emit controllerDisconnected(_controllerDesignator);

    _previousConnectState = _currentConnectState;

    if (_currentConnectState == true)
    {
        //get buttons
        _currentState._buttons = xState.Gamepad.wButtons;

        //get sticks
        processStickDeadZone(xState.Gamepad.sThumbLX, xState.Gamepad.sThumbLY, _currentState._leftThumbX, _currentState._leftThumbY, _leftStickDeadZone);
        processStickDeadZone(xState.Gamepad.sThumbRX, xState.Gamepad.sThumbRY, _currentState._rightThumbX, _currentState._rightThumbY, _rightStickDeadZone);

        //get triggers
        processTriggerThreshold(xState.Gamepad.bLeftTrigger, _currentState._leftTrigger, _triggerThreshold);
        processTriggerThreshold(xState.Gamepad.bRightTrigger, _currentState._rightTrigger, _triggerThreshold);

        XINPUT_BATTERY_INFORMATION xBattery;
        memset(&xBattery, 0, sizeof(XINPUT_BATTERY_INFORMATION));
        if (XInputGetBatteryInformation(_controllerDesignator, BATTERY_DEVTYPE_GAMEPAD, &xBattery) == ERROR_SUCCESS)
        {
            _currentState._batteryState = xBattery.BatteryType;
            _currentState._batteryLevel = xBattery.BatteryLevel;
        }
        else
        {
            _currentState._batteryState = BATTERY_TYPE_UNKNOWN;
            _currentState._batteryLevel = BATTERY_LEVEL_EMPTY;
        }

        if (_currentState != _previousState)
            emit newControllerState(_currentState);

        if (!XInputControlState::batteryEquals(_previousState, _currentState))
            emit newControllerBatteryState(_currentState._batteryState, _currentState._batteryLevel);
        _previousState = _currentState;
    }

}

void SteeringWheelController::setGamepadVibration(float leftVibration, float rightVibration)
{
    XINPUT_VIBRATION xInputVibration;
    xInputVibration.wLeftMotorSpeed=MAX_VIBRATION_VALUE*qBound(0.0f,1.0f,leftVibration);
    xInputVibration.wRightMotorSpeed=MAX_VIBRATION_VALUE*qBound(0.0f,1.0f,rightVibration);
    XInputSetState(_controllerDesignator, &xInputVibration);
}

bool SteeringWheelController::processStickDeadZone(qint16 rawXValue, qint16 rawYValue, float &xValue, float &yValue, unsigned int deadZoneRadius)
{
    xValue=0;
    yValue=0;
    //making values symetrical (otherwise negative value can be 1 unit larger than positive value)
    rawXValue=qMax(rawXValue,(qint16)-MAX_STICK_VALUE);
    rawYValue=qMax(rawYValue,(qint16)-MAX_STICK_VALUE);
    float magnitude = sqrt(rawXValue*rawXValue+rawYValue*rawYValue);
    if(magnitude<deadZoneRadius)return false;
    //remapping values to make deadzone transparent
    xValue=((float)rawXValue)/magnitude;
    yValue=((float)rawYValue)/magnitude;
    magnitude=qMin(magnitude, (float)MAX_STICK_VALUE);
    float normalizedMagnitude = (magnitude-deadZoneRadius)/((MAX_STICK_VALUE-deadZoneRadius));
    xValue*=normalizedMagnitude;
    yValue*=normalizedMagnitude;
    return true;
}

bool SteeringWheelController::processTriggerThreshold(quint8 rawValue, float &value, unsigned int triggerThreshold)
{
    value=0;
    if(rawValue < triggerThreshold)
        return false;

    value=((float)rawValue-triggerThreshold)/(MAX_TRIGGER_VALUE-triggerThreshold);
    return true;
}
