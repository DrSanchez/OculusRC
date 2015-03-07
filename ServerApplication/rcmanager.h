#ifndef RCMANAGER_H
#define RCMANAGER_H

#include <QObject>

#include "motorcontroller.h"

class RCManager : public QObject
{
    Q_OBJECT
public:
    explicit RCManager(QObject *parent = 0);

signals:

public slots:
    void InitializeRCSystem();
    void DeactivateRCSystem();

private:
    //private members
    MotorController * _motor;

};

#endif // RCMANAGER_H
