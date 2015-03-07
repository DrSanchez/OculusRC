#include "cameracontroller.h"
#include <QDebug>

CameraController::CameraController(QObject *parent)
    : QObject(parent), _gstreamVideo0(nullptr),
      _gstreamVideo1(nullptr)
{
    _gstreamVideo0 = new QProcess(this);
    _gstreamVideo1 = new QProcess(this);
}

void CameraController::start()
{
    qDebug() << (absolutePath + '/' + gstVideo0);
    _gstreamVideo0->start(absolutePath + '/' + gstVideo0);
    _gstreamVideo1->start(absolutePath + '/' + gstVideo1);
}

void CameraController::stop()
{
    _gstreamVideo0->kill();
    _gstreamVideo1->kill();
}
