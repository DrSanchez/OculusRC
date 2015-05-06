#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <QObject>
#include <QRunnable>
#include "safequeue.h"
#include "pwmcontroller.h"


class ServoController : public QObject, public QRunnable
{
    Q_OBJECT
    const long SERVO_PERIOD_NS = 20000000;
    const long SERVO_NEUTRAL_DUTY_NS = 1500000;

    /* Prevent overdriving of the servo hardware         */
    /* Actual MAX = 50000; keep for future use, possibly */
    const long MAX_DUTY_VALUE_NS = 40000;

public:
    explicit ServoController(QObject *parent = 0);
    ~ServoController();
    void setSteering(double angle);
    void activate();
    void deactivate();

signals:

public slots:

private:
    //private members
    PWMController * _pwm;
    SafeQueue<double> * _steeringQueue;

};

#endif // SERVOCONTROLLER_H
