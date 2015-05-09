#include "rcmanager.h"
#include <QDebug>

const static char BYTE_SPLIT = '|';

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
    qDebug() << "Starting motor...\n";
    _poolPtr->start(_motor);
    qDebug() << "Starting servo...\n";
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
    QList<QByteArray> splitter;
    char flag;
    qDebug() << "RC::run init...\n" << "Running: " << _running << '\n';
    while (_running)
    {
        qDebug() << "RC::run...\n";
        if (!_controlQueue->safeIsEmpty())
        {
            temp = _controlQueue->safeDequeue();
            splitter = temp.split(BYTE_SPLIT);
            flag = splitter.takeFirst().toInt();
            if (flag == SERVO_TAG)
            {
                temp = splitter.takeFirst();
                _servo->enqueueValue(temp.toDouble());
            }
            else if (flag == MOTOR_TAG)
            {
                temp = splitter.takeFirst();
                _motor->enqueueValue(temp.toDouble());
            }
            else
            {
                qDebug() << "Error, should not reach this point...\n";
            }
        }
    }
}

void RCManager::ensureShutdown()
{
    _running = false;
    _motor->updateRunning(false);
    _servo->updateRunning(false);
    DeactivateRCSystem();
}
