//#include "cameracontroller.h"
//#include <QDebug>
//#include <signal.h>

//CameraController::CameraController(QObject *parent)
//    : QObject(parent), _gstreamVideo0(nullptr)//,
//      //_gstreamVideo1(nullptr)
//{
//    _gstreamVideo0 = new QProcess(this);
//   // _gstreamVideo1 = new QProcess(this);
//}

//void CameraController::start()
//{/*
//    qDebug() << (absolutePath + '/' + gstVideo0);
//    _gstreamVideo0->start(absolutePath + '/' + gstVideo0);
//    _gstreamVideo1->start(absolutePath + '/' + gstVideo1);*/
//    QStringList args = QString("-e v4l2src device=/dev/video0 ! video/x-raw-yuv,width=1280,height=720,framerate=30/1 ! nv_omx_h264enc quality-level=2 ! h264parse ! mpegtsmux ! tcpserversink host=192.168.2.4 port=5000").split(" ");
//    qDebug() << args;
//    _gstreamVideo0->start("gst-launch", args);
//    qDebug() << _gstreamVideo0->processId();
//}

//void CameraController::stop()
//{
//    kill(_gstreamVideo0->processId(), SIGINT);
//    //_gstreamVideo0->write()
//    //_gstreamVideo0->terminate();
//    delete _gstreamVideo0;
//    _gstreamVideo0 = nullptr;
//    //_gstreamVideo1->close();
//   // _gstreamVideo0->terminate();
//    //_gstreamVideo1->terminate();
//  //  _gstreamVideo0->kill();
//    //_gstreamVideo1->kill();
//}
