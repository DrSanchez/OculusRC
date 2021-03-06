#ifndef STEERINGWHEELCONTROLLER_H
#define STEERINGWHEELCONTROLLER_H

#include "xinputcontrolstate.h"
#include <QObject>
#include <QTimer>
#include <QGuiApplication>
#include <QQuickWindow>
#include <QKeyEvent>
#include <QQuickItem>

/*
* Note to Self: Asynchronous packetizer object will tie in to
* the signals emitted by this controller class and the packetizer
* will hold a current state which will have the control of that state
* updated to the new value based on the signal/slot relationship which
* carries the value and control pair, allowing for easy controller mapping
* functionality to be added later
*/

//XInput analog control maximums
#define MAX_STICK_VALUE 32767u
#define MAX_TRIGGER_VALUE 255u
#define MAX_VIBRATION_VALUE 65535u

class SteeringWheelController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(bool driveMode READ driveMode WRITE setDriveMode NOTIFY driveModeChanged)

public:
    explicit SteeringWheelController(unsigned int controllerNumber, unsigned int leftStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, unsigned int rightStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, unsigned int triggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD, QObject *parent = 0);

    bool connected();

    void setDriveMode(bool set);
    bool driveMode();
    void sendRemoteControlData();
    bool controlsChanged();

signals:
    void newControllerBatteryState(quint8 newBatteryType, quint8 newBatteryLevel);
    void connectedChanged();
    void driveModeChanged();
    void remoteControlData(double steeringValue, double throttle, bool direction, bool boost);

    void new_remoteControlData(double steeringValue, double throttle);

public slots:
    //public controller methods
    void startPolling(unsigned int timerInterval);
    void stopPolling();
    void update();
    void setGamepadVibration(float leftVibration, float rightVibration);

    //deadzone/threshold setters
    void setLeftStickDeadZone(unsigned int newDeadZone){_leftStickDeadZone=qMin(newDeadZone,MAX_STICK_VALUE);}
    void setRightStickDeadZone(unsigned int newDeadZone){_rightStickDeadZone=qMin(newDeadZone,MAX_STICK_VALUE);}
    void setTriggerThreshold(unsigned int newThreshold){_triggerThreshold=qMin(newThreshold,MAX_TRIGGER_VALUE);}

    //key event senders
    void sendEnterKeySignal(int value);
    void sendLeftArrowKeySignal(int value);
    void sendRightArrowKeySignal(int value);
    void sendUpArrowKeySignal(int value);
    void sendDownArrowKeySignal(int value);
    void sendEscapeKeySignal(int value);

private:
    //private methods
    static bool processStickDeadZone(qint16 rawXValue, qint16 rawYValue, float& xValue, float& yValue, unsigned int deadZoneRadius);
    static bool processTriggerThreshold(quint8 rawValue, float& value,unsigned int triggerThreshold);

    //private signal/slot connection method
    void connectDefaultSignals();

    //controller connect methods
    void controllerConnected(bool connect);

    //private members
    unsigned int _controllerDesignator;
    bool _previousConnectState;
    bool _currentConnectState;
    QTimer * _updateTimer;
    unsigned int _leftStickDeadZone;
    unsigned int _rightStickDeadZone;
    unsigned int _triggerThreshold;
    XInputControlState * _currentState;
    XInputControlState * _previousState;

    //private members
    bool _connected;
    bool _driveMode;

};

#endif // STEERINGWHEELCONTROLLER_H
