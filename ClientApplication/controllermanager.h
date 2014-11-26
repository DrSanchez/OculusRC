#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <Qlist>
#include <QPair>
#include <QVariant>
#include "steeringwheelcontroller.h"

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

enum ControllerType
{
    GamePad,
    SteeringWheel
};

class ControllerManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:
    explicit ControllerManager(QObject *parent = 0);
    ControllerManager(ControllerType controlType, QObject *parent = 0);

    void setControllerLayout(QList<QPair<Control, QVariant> > controllerMapping);
    QList<QPair<Control, QVariant> > getControllerLayout() const;
    void Connect();
    void Disconnect();

    void setConnected(bool connected);
    bool connected();

signals:
    void connectedChanged();

public slots:
    void processControllerState(XInputControlState controllerState);
    //void gamepadConnected();
    //void gamepadDisconnected();
    void toggleConnected();

private:
    SteeringWheelController * _controller;
    bool _connected;
    QList<QPair<Control, QVariant> > _controllerLayout;

};

#endif // CONTROLLERMANAGER_H
