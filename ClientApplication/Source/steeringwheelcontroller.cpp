#include "steeringwheelcontroller.h"
#include <math.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <QDebug>

SteeringWheelController::SteeringWheelController(unsigned int controllerNumber, unsigned int leftStickDeadZone,
                                                 unsigned int rightStickDeadZone, unsigned int triggerThreshold,
                                                 QObject * parent)
    : QObject(parent),  _previousConnectState(false), _currentConnectState(false),_leftStickDeadZone(qMin(leftStickDeadZone, MAX_STICK_VALUE)),
      _rightStickDeadZone(qMin(rightStickDeadZone, MAX_STICK_VALUE)), _triggerThreshold(qMin(triggerThreshold, MAX_TRIGGER_VALUE))
{
    _connected = false;
    _driveMode = false;
    _currentState = new XInputControlState(this);
    _previousState = new XInputControlState(this);
    _controllerDesignator = qMin(controllerNumber, 3u);
    _updateTimer = new QTimer();
    connect(_updateTimer, &QTimer::timeout, this, &SteeringWheelController::update);
    connectDefaultSignals();
}

void SteeringWheelController::connectDefaultSignals()
{
    connect(_previousState, &XInputControlState::buttonAChanged, this, &SteeringWheelController::sendEnterKeySignal);
    connect(_previousState, &XInputControlState::dPadUpChanged, this, &SteeringWheelController::sendUpArrowKeySignal);
    connect(_previousState, &XInputControlState::dPadDownChanged, this, &SteeringWheelController::sendDownArrowKeySignal);
    connect(_previousState, &XInputControlState::dPadLeftChanged, this, &SteeringWheelController::sendLeftArrowKeySignal);
    connect(_previousState, &XInputControlState::dPadRightChanged, this, &SteeringWheelController::sendRightArrowKeySignal);
    connect(_previousState, &XInputControlState::buttonSelectChanged, this, &SteeringWheelController::sendEscapeKeySignal);
}

void SteeringWheelController::sendEnterKeySignal(int value)
{
    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    QKeyEvent event2(QEvent::KeyRelease, Qt::Key_Return, Qt::NoModifier);
    QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());
    if (value == 0)
        receiver->window()->sendEvent(receiver, &event1);
    else if (value == 1)
        receiver->window()->sendEvent(receiver, &event2);
}

void SteeringWheelController::sendLeftArrowKeySignal(int value)
{
    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    QKeyEvent event2(QEvent::KeyRelease, Qt::Key_Left, Qt::NoModifier);
    QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());
    if (value == 0)
        receiver->window()->sendEvent(receiver, &event1);
    else if (value == 1)
        receiver->window()->sendEvent(receiver, &event2);
}

void SteeringWheelController::sendRightArrowKeySignal(int value)
{
    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    QKeyEvent event2(QEvent::KeyRelease, Qt::Key_Right, Qt::NoModifier);
    QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());
    if (value == 0)
        receiver->window()->sendEvent(receiver, &event1);
    else if (value == 1)
        receiver->window()->sendEvent(receiver, &event2);
}

void SteeringWheelController::sendUpArrowKeySignal(int value)
{
    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QKeyEvent event2(QEvent::KeyRelease, Qt::Key_Up, Qt::NoModifier);
    QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());
    if (value == 0)
        receiver->window()->sendEvent(receiver, &event1);
    else if (value == 1)
        receiver->window()->sendEvent(receiver, &event2);
}

void SteeringWheelController::sendEscapeKeySignal(int value)
{
    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
    QKeyEvent event2(QEvent::KeyRelease, Qt::Key_Escape, Qt::NoModifier);
    QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());
    if (value == 0)
        receiver->window()->sendEvent(receiver, &event1);
    else if (value == 1)
        receiver->window()->sendEvent(receiver, &event2);
}

void SteeringWheelController::sendDownArrowKeySignal(int value)
{
    QKeyEvent event1(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    QKeyEvent event2(QEvent::KeyRelease, Qt::Key_Down, Qt::NoModifier);
    QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());
    if (value == 0)
        receiver->window()->sendEvent(receiver, &event1);
    else if (value == 1)
        receiver->window()->sendEvent(receiver, &event2);
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
        controllerConnected(true);

    //disconnection event
    if (_previousConnectState == true && _currentConnectState == false)
        controllerConnected(false);

    _previousConnectState = _currentConnectState;

    if (_currentConnectState == true)
    {
        //get buttons
        _currentState->_buttons = xState.Gamepad.wButtons;

        //get sticks
        processStickDeadZone(xState.Gamepad.sThumbLX, xState.Gamepad.sThumbLY, _currentState->_leftThumbX, _currentState->_leftThumbY, _leftStickDeadZone);
        processStickDeadZone(xState.Gamepad.sThumbRX, xState.Gamepad.sThumbRY, _currentState->_rightThumbX, _currentState->_rightThumbY, _rightStickDeadZone);

        //get triggers
        processTriggerThreshold(xState.Gamepad.bLeftTrigger, _currentState->_leftTrigger, _triggerThreshold);
        processTriggerThreshold(xState.Gamepad.bRightTrigger, _currentState->_rightTrigger, _triggerThreshold);

        //get battery info
        XINPUT_BATTERY_INFORMATION xBattery;
        memset(&xBattery, 0, sizeof(XINPUT_BATTERY_INFORMATION));
        if (XInputGetBatteryInformation(_controllerDesignator, BATTERY_DEVTYPE_GAMEPAD, &xBattery) == ERROR_SUCCESS)
        {
            _currentState->_batteryState = xBattery.BatteryType;
            _currentState->_batteryLevel = xBattery.BatteryLevel;
        }
        else
        {
            _currentState->_batteryState = BATTERY_TYPE_UNKNOWN;
            _currentState->_batteryLevel = BATTERY_LEVEL_EMPTY;
        }

        _previousState->emitControllerSignals(_currentState);

        if (!XInputControlState::batteryEquals(*_previousState, *_currentState))
            emit newControllerBatteryState(_currentState->_batteryState, _currentState->_batteryLevel);

        if (_driveMode)
            sendRemoteControlData();

        _previousState->operator =(*_currentState);//force overloaded operator usage
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

void SteeringWheelController::controllerConnected(bool connect)
{
    if (connect != _connected)
    {
        _connected = connect;
        emit connectedChanged();
    }
}

bool SteeringWheelController::connected()
{
    return _connected;
}

void SteeringWheelController::setDriveMode(bool set)
{
    if (_driveMode != set)
    {
        _driveMode = set;
        emit driveModeChanged();
    }
}

bool SteeringWheelController::driveMode()
{
    return _driveMode;
}

void SteeringWheelController::sendRemoteControlData()
{
    double steeringAngleValue = 0.0;
    double throttleValue = 0.0;
    bool forward = true;//default direction is forward
    if (_currentState->_leftTrigger > 0 && _currentState->_rightTrigger > 0)
    {//check if both pedals/triggers are pressed - use the higher value
        if (_currentState->_leftTrigger > _currentState->_rightTrigger)
        {
            forward = false;
            throttleValue = -(_currentState->_leftTrigger);
        }
        else if (_currentState->_rightTrigger > _currentState->_leftTrigger)
        {
            forward = true;
            throttleValue = _currentState->_rightTrigger;
        }
        else if (_currentState->_leftTrigger == _currentState->_rightTrigger)
        {//in very unlikely case of equal values, use forward (right trigger)
            forward = true;
            throttleValue = _currentState->_rightTrigger;
        }
    }
    else if (_currentState->_leftTrigger > 0 && _currentState->_rightTrigger == 0)
    {//reverse trigger/pedal
        throttleValue = -(_currentState->_leftTrigger);
        forward = false;
    }
    else if (_currentState->_rightTrigger > 0 && _currentState->_leftTrigger == 0)
    {//forward trigger/pedal
        throttleValue = _currentState->_rightTrigger;
        forward = true;
    }
    steeringAngleValue = _currentState->_leftThumbX;
    emit new_remoteControlData(steeringAngleValue, throttleValue);
    //emit remoteControlData(steeringAngleValue, throttleValue, forward, _currentState->buttonA() == 0 ? true : false);
}

bool SteeringWheelController::controlsChanged()
{
    return !(XInputControlState::equals(*_previousState, *_currentState));
}
