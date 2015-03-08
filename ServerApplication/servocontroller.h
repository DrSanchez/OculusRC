#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <QObject>
#include "pwmcontroller.h"


class ServoController : public QObject
{
    Q_OBJECT
    const long SERVO_PERIOD_NS = 20000000;
    const long SERVO_NEUTRAL_DUTY_NS = 1500000;
    const long MAX_DUTY_VALUE_NS = 500000;
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

};

#endif // SERVOCONTROLLER_H
