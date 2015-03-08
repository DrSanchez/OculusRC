#ifndef RCMANAGER_H
#define RCMANAGER_H

#include <QObject>
#include "motorcontroller.h"
#include "servocontroller.h"

class RCManager : public QObject
{
    Q_OBJECT
public:
    explicit RCManager(QObject *parent = 0);
    ~RCManager();

signals:

public slots:
    void InitializeRCSystem();
    void DeactivateRCSystem();
    void applyUpdate(double angle, double throttle);

private:
    //private members
    MotorController * _motor;
    ServoController * _servo;

};

#endif // RCMANAGER_H
