#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>
#include "pwmcontroller.h"


class MotorController : public QObject
{
    Q_OBJECT
    const long MOTOR_PERIOD_NS = 2000000;
    const long MOTOR_NEUTRAL_DUTY_NS = 1500000;
    const long MAX_DUTY_VALUE_NS = 500000;
public:
    explicit MotorController(QObject *parent = 0);
    ~MotorController();
    void setThrottle(double value);
    void activate();
    void deactivate();

signals:

public slots:

private:
    //private members
    PWMController * _pwm;

};

#endif // MOTORCONTROLLER_H
