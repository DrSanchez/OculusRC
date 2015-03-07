#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QProcess>

static QString absolutePath = "/home/ubuntu/Documents/OculusRC/ServerApplication";

static QString gstVideo0 = "gstVideo0.sh";
static QString gstVideo1 = "gstVideo1.sh";

class CameraController : public QObject
{
    Q_OBJECT
public:
    explicit CameraController(QObject *parent = 0);

    void start();
    void stop();

signals:

public slots:

private:
    //private data members
    QProcess * _gstreamVideo0;
    QProcess * _gstreamVideo1;

    //private methods

};

#endif // CAMERACONTROLLER_H
