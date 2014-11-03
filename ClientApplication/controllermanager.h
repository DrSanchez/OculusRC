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

public:
    explicit ControllerManager(QObject *parent = 0);
    ControllerManager(ControllerType controlType, QObject *parent = 0);

    void setControllerLayout(QList<QPair<Control, QVariant> > controllerMapping);
    QList<QPair<Control, QVariant> > getControllerLayout() const;
    bool Connect();
    bool Disconnect();

signals:

public slots:
    void processControllerState(XInputControlState controllerState);

private:
    bool _connected;
    QList<QPair<Control, QVariant> > _controllerLayout;
    SteeringWheelController * _controller;

};

#endif // CONTROLLERMANAGER_H
