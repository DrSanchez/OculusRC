#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <QObject>
#include "pwmcontroller.h"

const long MOTOR_PERIOD_NS = 2000000;
const long MOTOR_NEUTRAL_DUTY_NS = 1500000;
const long MAX_DUTY_VALUE_NS = 500000;

class MotorController : public QObject
{
    Q_OBJECT
public:
    explicit MotorController(QObject *parent = 0);

    void setThrottle(double value);

signals:

public slots:

private:
    //private members
    PWMController * _pwm;
    double _previousValue;

};

#endif // MOTORCONTROLLER_H
