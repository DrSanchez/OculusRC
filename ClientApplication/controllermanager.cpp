#include "controllermanager.h"

ControllerManager::ControllerManager(QObject *parent)
    : QObject(parent), _controller(nullptr)
{
}

void ControllerManager::processControllerState(XInputControlState controllerState)
{
    //check button presed

    //dpad menu navigation

    //a is accept

    //b is cancel/back

    //y could toggle oculus/standard mode
}
