#include "motorcontroller.h"
#include <math.h>

MotorController::MotorController(QObject *parent) :
    QObject(parent), _pwm(nullptr), _previousValue(0)
{
    _pwm = new PWMController(0,this);
    _pwm->exportPwm();
    _pwm->setPeriod(MOTOR_PERIOD_NS);
    _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS);
    _pwm->setPolarity(NORMAL);
    _pwm->setEnable(true);
}

void MotorController::setThrottle(double value)
{
    long previousDuty = MAX_DUTY_VALUE_NS * _previousValue;
    long nextDuty = MAX_DUTY_VALUE_NS * value;
    _previousValue = value;
    if (previousDuty == 0)
    {
        if (nextDuty == 0)
        {
            _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS);
        }
        else if (nextDuty > 0)
        {
            for (int i = MOTOR_NEUTRAL_DUTY_NS; i < (MOTOR_NEUTRAL_DUTY_NS + nextDuty); i += 10)
                _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS + i);
        }
        else if (nextDuty < 0)
        {

        }
    }
    else if (previousDuty > 0)
    {
        if (nextDuty == 0)
        {
            while (previousDuty != 0)
            {
                previousDuty -= 10;
                _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS + previousDuty);
            }
        }
        else if (nextDuty > 0)
        {

        }
        else if (nextDuty < 0)
        {

        }
    }
    else if (previousDuty < 0)
    {
        if (nextDuty == 0)
        {
            while (previousDuty != 0)
            {
                previousDuty += 10;
                _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS + previousDuty);
            }
        }
        else if (nextDuty > 0)
        {

        }
        else if (nextDuty < 0)
        {

        }
    }
    //for (int i = MOTOR_NEUTRAL_DUTY_NS; i )

    //_pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS + (MAX_DUTY_VALUE_NS * value));
}
