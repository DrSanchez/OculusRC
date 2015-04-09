#include "oculusmanager.h"
#include <QDebug>

/*********************************************************
 * Note: This is the initial include and
 * test use of the OculusSDK framework rebuilt
 * using the MinGW compiler.
 *
 * Future:
 * This will be extended into the overall
 * virtual reality manager in the future.
 *
 * Copyright Notice: @OculusSDK Source
 * I hereby state, that by including the OculusSDK,
 * I am in no way claiming ownership over any
 * intellectual proprety contained within the
 * OVRInclude directory.
 *
 ********************************************************/

OculusManager::OculusManager(QObject *parent)
    : QObject(parent)
{
    ovr_Initialize();
}

OculusManager::~OculusManager()
{
    ovr_Shutdown();
}
