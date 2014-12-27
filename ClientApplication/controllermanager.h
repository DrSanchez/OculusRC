#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

/********************************
*
*   Note: Currently Deprecated
*   Note: Will handle the layer of
*   controller mapping settings. All
*   control signals are handled by
*   the lower level controller object
*
*********************************/

#include <QObject>
#include <Qlist>
#include <QPair>
#include <QVariant>

class ControllerManager : public QObject
{
    Q_OBJECT

public:
    explicit ControllerManager(QObject *parent = 0);
 /*   ControllerManager(ControllerType controlType, QObject *parent = 0);

    void setControllerLayout(QList<QPair<Control, QVariant> > controllerMapping);
    QList<QPair<Control, QVariant> > getControllerLayout() const;*/

signals:


public slots:

private:

};

#endif // CONTROLLERMANAGER_H
