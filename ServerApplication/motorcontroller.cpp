#include "motorcontroller.h"
#include <math.h>

MotorController::MotorController(QObject *parent) :
    QObject(parent), _pwm(nullptr)
{
    _pwm = new PWMController(0,this);
    _pwm->exportPwm();
    _pwm->setPeriod(MOTOR_PERIOD_NS);
    _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS);
    _pwm->setPolarity(NORMAL);
}

MotorController::~MotorController()
{
    _pwm->unexportPwm();
    if (_pwm->isEnabled())
        _pwm->setEnable(false);
    delete _pwm;
    _pwm = nullptr;
}

void MotorController::setThrottle(double value)
{
    long nextDuty = MAX_DUTY_VALUE_NS * value;
    _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS + nextDuty);
}

void MotorController::activate()
{
    _pwm->setEnable(true);
}

void MotorController::deactivate()
{
    _pwm->setEnable(false);
}
