#ifndef RCMANAGER_H
#define RCMANAGER_H

#include <QList>
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
    explicit RCManager(QObject *parent = 0);
    ~RCManager();

    void enqueueControl(QByteArray * bytes);
    void ensureShutdown();
    void updateRunning(bool value);
    void InitializeRCSystem();
    void DeactivateRCSystem();

protected:
    void run();

signals:
    void finishModules();

private:
    //private members
    MotorController * _motor;
    ServoController * _servo;
    SafeQueue<QByteArray> * _controlQueue;

    bool _running;

    
    /*
    Added boost controller logic. Test in console
    before adding to the network call procedures.
    */
    //read usage warnings in header
    //BoostController * _boost;

};

#endif // RCMANAGER_H
