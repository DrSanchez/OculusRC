#ifndef BOOSTCONTROLLER_H
#define BOOSTCONTROLLER_H

// As of right now, the Motor is too fast to add
// a booster module...

/************************************************
 * Note: The boost module behavior is relatively
 * undefined. For saftey we leave the object
 * deactivated until user inputs the engage command.
 * The boost is then enabled, activated, and disabled,
 * followed by a timer which toggles the process again
 * to ensure the module has the off command just prior
 * to the end of the contained energy expenditure
 **********************************************/

#include <QObject>
#include <QTimer>
#include "pwmcontroller.h"

class BoostController : public QObject
{
    Q_OBJECT
    const long BOOST_PERIOD_NS = 20000000;
    const long BOOST_TOGGLE_DUTY_NS = 1400000;
public:
    explicit BoostController(QObject *parent = 0);
    ~BoostController();

    void engageBoost();
    void activate();
    void deactivate();

signals:

public slots:

private slots:
    void disengageBoost();

private:
    //private data members
    PWMController * _pwm;
    QTimer * _timer;

};

#endif // BOOSTCONTROLLER_H
