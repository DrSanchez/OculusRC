#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include <QObject>
#include <QFile>
#include <QDir>

//sysfs pwm strings
const QString PWM_PATH = "/sys/class/pwm/pwmchip0";
const QString PWM_EXPORT = "/export";
const QString PWM_UNEXPORT = "/unexport";
const QString PWM_PIN = "/pwm"; //+ index
const QString PWM_DUTY = "/duty";
const QString PWM_ENABLE = "/enable";
const QString PWM_PERIOD = "/period";
const QString PWM_POLARITY = "/polarity";

enum POLARITY_VALUE { NORMAL, INVERSED };

class PWMController : public QObject
{
    Q_OBJECT
public:
    explicit PWMController(int index, QObject *parent = 0);

    //pwm interface methods
    bool exportPwm();
    bool unexportPwm();
    bool setDutyCycle(qint32 value);
    bool setPeriod(qint32 value);
    bool setEnable(bool enabled);
    bool setPolarity(POLARITY_VALUE value);

    //pwm interface check/getter methods
    bool isEnabled();
    qint32 getDutyCycle();
    qint32 getPeriod();
    POLARITY_VALUE getPolarity();
    bool isExported();


signals:

public slots:

private:
    //private data members
    QFile * _sys;
    int _pwmIndex;
};

#endif // PWMCONTROLLER_H
