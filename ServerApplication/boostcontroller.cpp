#include "boostcontroller.h"

BoostController::BoostController(QObject *parent)
    : QObject(parent), _pwm(nullptr), _timer(nullptr)
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &BoostController::disengageBoost);

    _pwm = new PWMController(3, this);
    _pwm->exportPwm();
    _pwm->setPeriod(BOOST_PERIOD_NS);
    _pwm->setDutyCycle(BOOST_TOGGLE_DUTY_NS);
    _pwm->setPolarity(NORMAL);
}

BoostController::~BoostController()
{
    _pwm->unexportPwm();
    if (_pwm->isEnabled())
        _pwm->setEnable(false);
    delete _pwm;
    _pwm = nullptr;
}

void BoostController::engageBoost()
{
    //need to test this segment in console
    _pwm->setEnable(true);
    _pwm->setDutyCycle(BOOST_TOGGLE_DUTY_NS);
    _pwm->setEnable(false);

    //set timer to activate just before end of boost cycle
    _timer->start(2800);
}

void BoostController::activate()
{
    _pwm->setEnable(true);
}

void BoostController::deactivate()
{
    _pwm->setEnable(false);
}

void BoostController::disengageBoost()
{
    _pwm->setEnable(true);
    _pwm->setDutyCycle(BOOST_TOGGLE_DUTY_NS);
    _pwm->setEnable(false);
}
