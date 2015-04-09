#ifndef RCMANAGER_H
#define RCMANAGER_H

#include <QObject>
#include "motorcontroller.h"
#include "servocontroller.h"
#include "boostcontroller.h"

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
    void applyUpdate(double angle, double throttle/*, bool boost*/);

private:
    //private members
    MotorController * _motor;
    ServoController * _servo;

    /*
    Added boost controller logic. Test in console
    before adding to the network call procedures.
    */

    //read usage warnings in header
    BoostController * _boost;

};

#endif // RCMANAGER_H
