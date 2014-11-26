#include "controllermanager.h"

ControllerManager::ControllerManager(QObject *parent)
    : QObject(parent), _controller(nullptr), _connected(false)
{
    _controller = new SteeringWheelController(0);

    connect(_controller, &SteeringWheelController::controllerConnected,
            this, &ControllerManager::Connect);
    connect(_controller, &SteeringWheelController::controllerDisconnected,
            this, &ControllerManager::Disconnect);

    _controller->startPolling(10);
}

ControllerManager::ControllerManager(ControllerType controlType, QObject *parent)
    : QObject(parent), _controller(nullptr)
{

}

void ControllerManager::setConnected(bool connected)
{
    if (connected != _connected)
    {
        _connected = connected;
        emit connectedChanged();
    }
}

bool ControllerManager::connected()
{
    return _connected;
}

void ControllerManager::Connect()
{
    this->setConnected(true);
}

void ControllerManager::Disconnect()
{
    this->setConnected(false);
}

void ControllerManager::toggleConnected()
{
    this->connected() ? this->Disconnect() : this->Connect();
}

void ControllerManager::processControllerState(XInputControlState controllerState)
{
    //check button presed

    //dpad menu navigation

    //a is accept

    //b is cancel/back

    //y could toggle oculus/standard mode
}
