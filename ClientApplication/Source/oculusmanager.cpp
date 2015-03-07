#include "oculusmanager.h"
#include <QDebug>
OculusManager::OculusManager(QObject *parent)
    : QObject(parent)
{
    qDebug() << "before ovr init";
    //ovr_Initialize();

    qDebug() << "after ovr init";
}

//OculusManager::~OculusManager()
//{
//    ovr_Shutdown();
//}
