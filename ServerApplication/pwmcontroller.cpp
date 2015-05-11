//#include "pwmcontroller.h"
//#include <QDebug>

////sysfs pwm strings -- for reference
////const QString PWM_PATH = "/sys/class/pwm/pwmchip0";
////const QString PWM_EXPORT = "/export";
////const QString PWM_UNEXPORT = "/unexport";
////const QString PWM_PIN = "/pwm"; //+ index
////const QString PWM_DUTY = "/duty";
////const QString PWM_ENABLE = "/enable";
////const QString PWM_PERIOD = "/period";
////const QString PWM_POLARITY = "/polarity";

//PWMController::PWMController(int index, QObject *parent)
//    : QObject(parent), _sys(nullptr), _pwmIndex(index)
//{
//    if (_pwmIndex != 0 || _pwmIndex != 2 || _pwmIndex != 3)
//        qDebug() << "Jetson TK1 only supports index values: 0, 2, 3 => please reset the index...";
//    _sys = new QFile(this);
//    _duty = new QFile(this);
//    _duty->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_DUTY);
//}

//bool PWMController::exportPwm()
//{
//    if (isExported())
//        return true;
//    if (_pwmIndex == 0 || _pwmIndex == 2 || _pwmIndex == 3)
//    {
//        _sys->setFileName(PWM_PATH + PWM_EXPORT);
//        if (_sys->open(QIODevice::WriteOnly))
//        {
//            _sys->write(QString::number(_pwmIndex).toLatin1());
//            _sys->close();
//            return true;
//        }
//        else
//            return false;
//    }
//    else
//    {
//        qDebug() << "Jetson TK1 only supports index of values: 0, 2, 3";
//        return false;
//    }
//}

//bool PWMController::unexportPwm()
//{
//    if (!isExported())
//        return true;
//    if (_pwmIndex == 0 || _pwmIndex == 2 || _pwmIndex == 3)
//    {
//        _sys->setFileName(PWM_PATH + PWM_UNEXPORT);
//        if (_sys->open(QIODevice::WriteOnly))
//        {
//            _sys->write(QString::number(_pwmIndex).toLatin1());
//            _sys->close();
//            return true;
//        }
//        else
//            return false;
//    }
//    else
//    {
//        qDebug() << "Jetson TK1 only supports index of values: 0, 2, 3";
//        return false;
//    }
//}

//bool PWMController::openDuty()
//{
//    if (!_duty->isOpen())
//        _duty->open(QIODevice::WriteOnly);
//    else
//        qDebug() << "Duty cycle already open...\n";
//}

//bool PWMController::closeDuty()
//{
//    if (_duty->isOpen())
//        _duty->close();
//    else
//        qDebug() << "Duty cycle already closed...\n";
//}

//bool PWMController::setDutyCycle(qint32 value)
//{
//    if (_duty->isOpen())
//        _duty->write(QString::number(value).toLatin1());
//    else
//        qDebug() << "Duty cycle is not open...\n";
//}

//bool PWMController::setPeriod(qint32 value)
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_PERIOD);
//        if (_sys->open(QIODevice::WriteOnly))
//        {
//            _sys->write(QString::number(value).toLatin1());
//            _sys->close();
//            return true;
//        }
//        else
//            return false;
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return false;
//    }
//}

//bool PWMController::setEnable(bool enabled)
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_ENABLE);
//        if (_sys->open(QIODevice::WriteOnly))
//        {
//            _sys->write(QString::number((enabled ? 1 : 0)).toLatin1());
//            _sys->close();
//            return true;
//        }
//        else
//            return false;
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return false;
//    }
//}

//bool PWMController::setPolarity(POLARITY_VALUE value)
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_POLARITY);
//        if (_sys->open(QIODevice::WriteOnly))
//        {
//            if (value == NORMAL)
//                _sys->write("normal");
//            else if (value == INVERSED)
//                _sys->write("inversed");
//            _sys->close();
//            return true;
//        }
//        else
//            return false;
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return false;
//    }
//}

//bool PWMController::isEnabled()
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_ENABLE);
//        if (_sys->open(QIODevice::ReadOnly))
//        {
//            char enabled;
//            _sys->read(&enabled, 1);
//            _sys->close();
//            if (enabled == '1')
//            {
//                qDebug() << "PWM index (" << _pwmIndex << ") is enabled...";
//                return true;
//            }
//            else if (enabled == '0')
//            {
//                qDebug() << "PWM index (" << _pwmIndex << ") is not enabled...";
//                return false;
//            }
//        }
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return false;
//    }
//    return false;
//}

//qint32 PWMController::getDutyCycle()
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_DUTY);
//        if (_sys->open(QIODevice::ReadOnly))
//        {
//            QByteArray duty(_sys->readAll());
//            _sys->close();
//            qDebug() << "PWM index (" << _pwmIndex << ") duty cycle: " << duty;
//            return duty.toLong();
//        }
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return false;
//    }
//    return false;
//}

//qint32 PWMController::getPeriod()
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_PERIOD);
//        if (_sys->open(QIODevice::ReadOnly))
//        {
//            QByteArray period(_sys->readAll());
//            _sys->close();
//            qDebug() << "PWM index (" << _pwmIndex << ") duty cycle: " << period;
//            return period.toLong();
//        }
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return false;
//    }
//    return false;
//}

//POLARITY_VALUE PWMController::getPolarity()
//{
//    if (isExported())
//    {
//        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_POLARITY);
//        if (_sys->open(QIODevice::ReadOnly))
//        {
//            QByteArray polarity(_sys->readAll());
//            _sys->close();
//            qDebug() << "PWM index (" << _pwmIndex << ") duty cycle: " << polarity;
//            if (polarity == "normal")
//                return NORMAL;
//            else if (polarity == "inversed")
//                return INVERSED;
//        }
//        else
//            return NORMAL;
//    }
//    else
//    {
//        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
//        return NORMAL;
//    }
//    return NORMAL;
//}

//bool PWMController::isExported()
//{
//    if (_pwmIndex == 0 || _pwmIndex == 2 || _pwmIndex == 3)
//    {
//        QDir pwm(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1());
//        return pwm.exists();
//    }
//    else
//    {
//        qDebug() << "Jetson TK1 only supports index of values: 0, 2, 3";
//        return false;
//    }
//}

#include "pwmcontroller.h"
#include <QDebug>

//sysfs pwm strings -- for reference
//const QString PWM_PATH = "/sys/class/pwm/pwmchip0";
//const QString PWM_EXPORT = "/export";
//const QString PWM_UNEXPORT = "/unexport";
//const QString PWM_PIN = "/pwm"; //+ index
//const QString PWM_DUTY = "/duty";
//const QString PWM_ENABLE = "/enable";
//const QString PWM_PERIOD = "/period";
//const QString PWM_POLARITY = "/polarity";

PWMController::PWMController(int index, QObject *parent)
    : QObject(parent), _sys(nullptr), _pwmIndex(index)
{
    if (_pwmIndex != 0 || _pwmIndex != 2 || _pwmIndex != 3)
        qDebug() << "Jetson TK1 only supports index values: 0, 2, 3 => please reset the index...";
    _sys = new QFile(this);
}

bool PWMController::exportPwm()
{
    if (isExported())
        return true;
    if (_pwmIndex == 0 || _pwmIndex == 2 || _pwmIndex == 3)
    {
        _sys->setFileName(PWM_PATH + PWM_EXPORT);
        if (_sys->open(QIODevice::WriteOnly))
        {
            _sys->write(QString::number(_pwmIndex).toLatin1());
            _sys->close();
            return true;
        }
        else
            return false;
    }
    else
    {
        qDebug() << "Jetson TK1 only supports index of values: 0, 2, 3";
        return false;
    }
}

bool PWMController::unexportPwm()
{
    if (!isExported())
        return true;
    if (_pwmIndex == 0 || _pwmIndex == 2 || _pwmIndex == 3)
    {
        _sys->setFileName(PWM_PATH + PWM_UNEXPORT);
        if (_sys->open(QIODevice::WriteOnly))
        {
            _sys->write(QString::number(_pwmIndex).toLatin1());
            _sys->close();
            return true;
        }
        else
            return false;
    }
    else
    {
        qDebug() << "Jetson TK1 only supports index of values: 0, 2, 3";
        return false;
    }
}

bool PWMController::setDutyCycle(qint32 value)
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_DUTY);
        if (_sys->open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "PWM Duty: " << QString::number(value).toLatin1();
            _sys->write(QString::number(value).toLatin1());
            _sys->flush();
            _sys->close();
            return true;
        }
        else
            return false;
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
}

bool PWMController::setPeriod(qint32 value)
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_PERIOD);
        if (_sys->open(QIODevice::WriteOnly))
        {
            _sys->write(QString::number(value).toLatin1());
            _sys->close();
            return true;
        }
        else
            return false;
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
}

bool PWMController::setEnable(bool enabled)
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_ENABLE);
        if (_sys->open(QIODevice::WriteOnly))
        {
            _sys->write(QString::number((enabled ? 1 : 0)).toLatin1());
            _sys->close();
            return true;
        }
        else
            return false;
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
}

bool PWMController::setPolarity(POLARITY_VALUE value)
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_POLARITY);
        if (_sys->open(QIODevice::WriteOnly))
        {
            if (value == NORMAL)
                _sys->write("normal");
            else if (value == INVERSED)
                _sys->write("inversed");
            _sys->close();
            return true;
        }
        else
            return false;
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
}

bool PWMController::isEnabled()
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_ENABLE);
        if (_sys->open(QIODevice::ReadOnly))
        {
            char enabled;
            _sys->read(&enabled, 1);
            _sys->close();
            if (enabled == '1')
            {
                qDebug() << "PWM index (" << _pwmIndex << ") is enabled...";
                return true;
            }
            else if (enabled == '0')
            {
                qDebug() << "PWM index (" << _pwmIndex << ") is not enabled...";
                return false;
            }
        }
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
    return false;
}

qint32 PWMController::getDutyCycle()
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_DUTY);
        if (_sys->open(QIODevice::ReadOnly))
        {
            QByteArray duty(_sys->readAll());
            _sys->close();
            qDebug() << "PWM index (" << _pwmIndex << ") duty cycle: " << duty;
            return duty.toLong();
        }
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
    return false;
}

qint32 PWMController::getPeriod()
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_PERIOD);
        if (_sys->open(QIODevice::ReadOnly))
        {
            QByteArray period(_sys->readAll());
            _sys->close();
            qDebug() << "PWM index (" << _pwmIndex << ") duty cycle: " << period;
            return period.toLong();
        }
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return false;
    }
    return false;
}

POLARITY_VALUE PWMController::getPolarity()
{
    if (isExported())
    {
        _sys->setFileName(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1() + PWM_POLARITY);
        if (_sys->open(QIODevice::ReadOnly))
        {
            QByteArray polarity(_sys->readAll());
            _sys->close();
            qDebug() << "PWM index (" << _pwmIndex << ") duty cycle: " << polarity;
            if (polarity == "normal")
                return NORMAL;
            else if (polarity == "inversed")
                return INVERSED;
        }
        else
            return NORMAL;
    }
    else
    {
        qDebug() << "PWM index (" << _pwmIndex << ") not exported...";
        return NORMAL;
    }
    return NORMAL;
}

bool PWMController::isExported()
{
    if (_pwmIndex == 0 || _pwmIndex == 2 || _pwmIndex == 3)
    {
        QDir pwm(PWM_PATH + PWM_PIN + QString::number(_pwmIndex).toLatin1());
        return pwm.exists();
    }
    else
    {
        qDebug() << "Jetson TK1 only supports index of values: 0, 2, 3";
        return false;
    }
}
