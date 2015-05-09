#include "rcmanager.h"
#include <QDebug>

RCManager::RCManager(QThreadPool * pool, QObject *parent)
    : QObject(parent), _motor(nullptr), _servo(nullptr),
      /*_boost(nullptr),*/_poolPtr(nullptr), _controlQueue(nullptr)
{
    _controlQueue = new SafeQueue<QByteArray>();
    _poolPtr = pool;
    _motor = new MotorController(this);
    _servo = new ServoController(this);
    //_boost = new BoostController(this);
    _running = false;
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
    _motor->updateRunning(true);
    _servo->updateRunning(true);
    _poolPtr->start(_motor);
    _poolPtr->start(_servo);
}

void RCManager::DeactivateRCSystem()
{
    this->_running = false;
    _motor->updateRunning(false);
    _servo->updateRunning(false);
    _motor->deactivate();
    _servo->deactivate();
}

//void RCManager::applyUpdate(double angle, double throttle)
//{
//    _motor->setThrottle(throttle);
//    _servo->setSteering(angle);
//}

//void RCManager::updateSteering(double angle)
//{

//}

//void RCManager::updateThrottle(double throttle)
//{

//}

void RCManager::enqueueControl(QByteArray *bytes)
{
    _controlQueue->safeEnqueue(bytes);
}

void RCManager::updateRunning(bool value)
{
    _running = value;
}

void RCManager::run()
{
    QByteArray temp;
    QString intermediate;
    double tempVal;
    while (_running)
    {
        //temp is guaranteed to be of size 2
        if (!_controlQueue->isEmpty())
        {
            temp = _controlQueue->safeDequeue();
            if (temp[0] == SERVO_TAG)
            {
                intermediate = temp[1];
                tempVal = intermediate.toDouble();
                _servo->enqueueValue(tempVal);
            }
            else if (temp[1] == MOTOR_TAG)
            {
                intermediate = temp[1];
                tempVal = intermediate.toDouble();
                _motor->enqueueValue(tempVal);
            }
            else
            {
                qDebug() << "Error, should not reach this point...\n";
            }
        }
    }
}
