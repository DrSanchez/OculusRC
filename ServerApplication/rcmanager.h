#ifndef RCMANAGER_H
#define RCMANAGER_H

#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include <QWaitCondition>
#include "motorcontroller.h"
#include "servocontroller.h"
#include "boostcontroller.h"

const static char SERVO_TAG = '%';
const static char MOTOR_TAG = '^';

class RCManager : public QObject, public QRunnable
{
    Q_OBJECT

public:
    explicit RCManager(QThreadPool * pool, QObject *parent = 0);
    ~RCManager();

    void enqueueControl(QByteArray * bytes);

    void updateRunning(bool value);

protected:
    void run();

signals:
    void finishModules();

public slots:
    void InitializeRCSystem();
    void DeactivateRCSystem();
    //void applyUpdate(double angle, double throttle/*, bool boost*/);
//    void updateSteering(double angle);
//    void updateThrottle(double throttle);
    //void updateBoost(bool value);

private:
    //private members
    MotorController * _motor;
    ServoController * _servo;

    SafeQueue<QByteArray> * _controlQueue;
    QThreadPool * _poolPtr;

    bool _running;

    /*
    Added boost controller logic. Test in console
    before adding to the network call procedures.
    */

    //read usage warnings in header
    //BoostController * _boost;

};

#endif // RCMANAGER_H
