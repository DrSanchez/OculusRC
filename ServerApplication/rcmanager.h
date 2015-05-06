#ifndef RCMANAGER_H
#define RCMANAGER_H

#include <QObject>
#include <QRunnable>
#include <QThreadPool>
#include "motorcontroller.h"
#include "servocontroller.h"
#include "boostcontroller.h"

class RCManager : public QObject, public QRunnable
{
    Q_OBJECT

public:
    explicit RCManager(QQueue<QByteArray> * mainControlQueue, QThreadPool * pool, QObject *parent = 0);
    ~RCManager();

protected:
//    void run();

signals:
    void finishModules();

public slots:
    void InitializeRCSystem();
    void DeactivateRCSystem();
    void applyUpdate(double angle, double throttle/*, bool boost*/);
    void updateSteering(double angle);
    void updateThrottle(double throttle);

private:
    //private members
    MotorController * _motor;
    ServoController * _servo;

    QQueue<QByteArray> * _controlQueuePtr;
    QThreadPool * _poolPtr;

    /*
    Added boost controller logic. Test in console
    before adding to the network call procedures.
    */

    //read usage warnings in header
    BoostController * _boost;

};

#endif // RCMANAGER_H
