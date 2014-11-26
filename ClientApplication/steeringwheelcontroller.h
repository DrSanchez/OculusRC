#ifndef STEERINGWHEELCONTROLLER_H
#define STEERINGWHEELCONTROLLER_H

#include "xinputcontrolstate.h"
#include <QObject>
#include <QTimer>

#define MAX_STICK_VALUE 32767u
#define MAX_TRIGGER_VALUE 255u
#define MAX_VIBRATION_VALUE 65535u

class SteeringWheelController : public QObject
{
    Q_OBJECT

public:
    explicit SteeringWheelController(unsigned int controllerNumber, unsigned int leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, unsigned int rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, unsigned int triggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD, QObject *parent = 0);

signals:
    void newControllerState(XInputControlState);
    void newControllerBatteryState(quint8 newBatteryType, quint8 newBatteryLevel);
    void controllerConnected(unsigned int controllerNumber);
    void controllerDisconnected(unsigned int controllerNumber);

public slots:

    void startPolling(unsigned int timerInterval);
    void stopPolling();
    void update();
    void setGamepadVibration(float leftVibration, float rightVibration);

    //deadzone/threshold setters
    void setLeftStickDeadZone(unsigned int newDeadZone){_leftStickDeadZone=qMin(newDeadZone,MAX_STICK_VALUE);}
    void setRightStickDeadZone(unsigned int newDeadZone){_rightStickDeadZone=qMin(newDeadZone,MAX_STICK_VALUE);}
    void setTriggerThreshold(unsigned int newThreshold){_triggerThreshold=qMin(newThreshold,MAX_TRIGGER_VALUE);}

private:
    //private methods
    static bool processStickDeadZone(qint16 rawXValue, qint16 rawYValue, float& xValue, float& yValue, unsigned int deadZoneRadius);
    static bool processTriggerThreshold(quint8 rawValue, float& value,unsigned int triggerThreshold);

    //private members
    unsigned int _controllerDesignator;
    bool _previousConnectState;
    bool _currentConnectState;
    QTimer * _updateTimer;
    unsigned int _leftStickDeadZone;
    unsigned int _rightStickDeadZone;
    unsigned int _triggerThreshold;
    XInputControlState _currentState;
    XInputControlState _previousState;

};

#endif // STEERINGWHEELCONTROLLER_H
