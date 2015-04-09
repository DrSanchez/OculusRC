#ifndef OCULUSMANAGER_H
#define OCULUSMANAGER_H

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

#include <QObject>
#include "OVR.h"

class OculusManager : public QObject
{
    Q_OBJECT
public:
    explicit OculusManager(QObject *parent = 0);
    ~OculusManager();

signals:

public slots:

};

#endif // OCULUSMANAGER_H
