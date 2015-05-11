#include "servocontroller.h"
#include <QDebug>
#include <QThread>

ServoController::ServoController(QObject *parent)
    : QObject(parent), _pwm(nullptr), _steeringQueue(nullptr)
{
    _pwm = new PWMController(2, this);
    _pwm->exportPwm();
    _pwm->setPeriod(SERVO_PERIOD_NS);

    //set neutral duty
    _pwm->openDuty();
    _pwm->setDutyCycle(SERVO_NEUTRAL_DUTY_NS);
    _pwm->closeDuty();

    _pwm->setPolarity(NORMAL);
    _steeringQueue = new SafeQueue<double>();
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
    this->_running = true;
    _pwm->setEnable(true);
    _pwm->openDuty();
}

void ServoController::deactivate()
{
    this->_running = false;
    _pwm->closeDuty();
    _pwm->setEnable(false);
}

void ServoController::enqueueValue(double value)
{
    double temp = value;
    _steeringQueue->safeEnqueue(&temp);
}

void ServoController::updateRunning(bool val)
{
    _running = val;
}

void ServoController::run()
{
    double value = 0;
    while (_running)
    {
        value = _steeringQueue->safeDequeue();
        this->setSteering(value);
    }
}
