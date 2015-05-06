#include "rcmanager.h"
#include <QDebug>

RCManager::RCManager(QQueue<QByteArray> * mainControlQueue, QThreadPool * pool, QObject *parent)
    : QObject(parent), _motor(nullptr), _servo(nullptr),
      _boost(nullptr), _controlQueuePtr(nullptr),
      _poolPtr(nullptr)
{
    _controlQueuePtr = mainControlQueue;
    _poolPtr = pool;
    //_motor = new MotorController(this);
    //_servo = new ServoController(this);
    //_boost = new BoostController(this);
}

RCManager::~RCManager()
{
    delete _motor;
    delete _servo;
    _motor = nullptr;
    _servo = nullptr;
}

void RCManager::InitializeRCSystem()
{
    _motor->activate();
    _servo->activate();
}

void RCManager::DeactivateRCSystem()
{
    _motor->deactivate();
    _servo->deactivate();
}

void RCManager::applyUpdate(double angle, double throttle)
{
    _motor->setThrottle(throttle);
    _servo->setSteering(angle);
}

void RCManager::updateSteering(double angle)
{
//safequeue.safeenqueue(angle)
}

void RCManager::updateThrottle(double throttle)
{

}
