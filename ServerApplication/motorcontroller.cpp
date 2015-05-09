#include "motorcontroller.h"
#include <QDebug>

MotorController::MotorController(QObject *parent)
    : QObject(parent), _pwm(nullptr), _motorCommands(nullptr)
{
    _pwm = new PWMController(0,this);
    _pwm->exportPwm();
    _pwm->setPeriod(MOTOR_PERIOD_NS);
    _pwm->setDutyCycle(MOTOR_NEUTRAL_DUTY_NS);
    _pwm->setPolarity(NORMAL);
    _motorCommands = new SafeQueue<double>();
    _running = false;
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
    _pwm->openDuty();
}

void MotorController::deactivate()
{
    _pwm->closeDuty();
    _pwm->setEnable(false);
}

void MotorController::enqueueValue(double value)
{
    double temp = value;
    _motorCommands->safeEnqueue(&temp);
}

void MotorController::updateRunning(bool val)
{
    if (val)
        this->activate();
    else
        this->deactivate();
    _running = val;
}

void MotorController::run()
{
    while (_running)
    {
        qDebug() << "Motor::run...\n";
        this->setThrottle(_motorCommands->safeDequeue());
    }
}
