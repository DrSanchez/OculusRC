#include "servocontroller.h"

ServoController::ServoController(QObject *parent)
    : QObject(parent), _pwm(nullptr)
{
    _pwm = new PWMController(2, this);
    _pwm->exportPwm();
    _pwm->setPeriod(SERVO_PERIOD_NS);
    _pwm->setDutyCycle(SERVO_NEUTRAL_DUTY_NS);
    _pwm->setPolarity(NORMAL);
    _running = false;
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
    _pwm->openDuty();
}

void ServoController::deactivate()
{
    _pwm->closeDuty();
    _pwm->setEnable(false);
}

void ServoController::enqueueValue(double value)
{
    _steeringQueue->safeEnqueue(&value);
}

void ServoController::updateRunning(bool val)
{
    if (val)
        this->activate();
    else
        this->deactivate();
    _running = val;
}

void ServoController::run()
{
    while (_running)
    {
        this->setSteering(_steeringQueue->safeDequeue());
    }
}
