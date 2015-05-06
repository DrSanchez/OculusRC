#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>
#include <QRunnable>
#include "safequeue.h"
#include "pwmcontroller.h"

//inherit qrunnable, not qobject
class MotorController : public QObject, public QRunnable
{
    Q_OBJECT
    const long MOTOR_PERIOD_NS = 2000000;
    const long MOTOR_NEUTRAL_DUTY_NS = 1500000;

    /* The current motor power to vehicle scale ratio   */
    /* is far too powerful, cutting back maximum power  */
    /* Actual MAX = 50000; use when mechanically stable */
    /* Then we can use the booster module               */
    const long MAX_DUTY_VALUE_NS = 30000;

public:
    explicit MotorController(QQueue<QByteArray> * motorCommandQueue, QObject *parent = 0);
    ~MotorController();
    void setThrottle(double value);
    void activate();
    void deactivate();

protected:
//    void run();

signals:

public slots:

private:
    //private members
    PWMController * _pwm;
    QQueue<QByteArray> * _motorCommandQueue;

};

#endif // MOTORCONTROLLER_H
