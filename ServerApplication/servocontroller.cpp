#include "servocontroller.h"

ServoController::ServoController(QObject *parent)
    : QObject(parent), _pwm(nullptr)
{
    _pwm = new PWMController(2, this);
    _pwm->exportPwm();
    _pwm->setPeriod(SERVO_PERIOD_NS);
    _pwm->setDutyCycle(SERVO_NEUTRAL_DUTY_NS);
    _pwm->setPolarity(NORMAL);
}

ServoController::~ServoController()
{
    _pwm->unexportPwm();
    if (_pwm->isEnabled())
        _pwm->setEnable(false);
    delete _pwm;
    _pwm = nullptr;
}

void ServoController::setSteering(double angle)
{
    long nextDuty = MAX_DUTY_VALUE_NS * angle;
    _pwm->setDutyCycle(SERVO_NEUTRAL_DUTY_NS + nextDuty);
}

void ServoController::activate()
{
    _pwm->setEnable(true);
}

void ServoController::deactivate()
{
    _pwm->setEnable(false);
}
