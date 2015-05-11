#include "rcmanager.h"
#include <QDebug>

const static char BYTE_SPLIT = '|';

RCManager::RCManager(QObject *parent)
    : QObject(parent), _motor(nullptr), _servo(nullptr),
      /*_boost(nullptr),*/_controlQueue(nullptr)
{
    _controlQueue = new SafeQueue<QByteArray>();
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
   QThreadPool::globalInstance()->start(_motor, QThread::HighPriority);
   QThreadPool::globalInstance()->start(_servo, QThread::HighPriority);
}

void RCManager::DeactivateRCSystem()
{
    this->_running = false;
    _motor->updateRunning(false);
    _servo->updateRunning(false);
    _motor->deactivate();
    _servo->deactivate();
}

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

    InitializeRCSystem();

    while (_running)
    {
        if (!_controlQueue->safeIsEmpty())
        {
            temp = _controlQueue->safeDequeue();
            splitter = temp.split(BYTE_SPLIT);
            flag = (splitter.takeFirst())[0];
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
                qDebug() << "Error, rc thread should not reach this point...\n";
            }
        }
    }

    DeactivateRCSystem();
}

void RCManager::ensureShutdown()
{
    _running = false;
    _motor->updateRunning(false);
    _servo->updateRunning(false);
}
