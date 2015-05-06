#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QBuffer>
#include <QThreadPool>
#include "packetmanager.h"
#include "rcmanager.h"
//#include "cameracontroller.h"

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    //constructors and destructors
    explicit NetworkManager(QObject *parent = 0);
    ~NetworkManager();

    //public cleanup method
    Q_INVOKABLE void customDestroy();
    void writeToSocket(QString message);

    void sendCurrentPacket();

signals:
    void sendBytesToMessageLog(QString message);
    void startDriving();
    void stopDriving();
    void updateRC(double steeringAngle, double throttle);//add boost later

public slots:
    void newConnection();
    void readClientBytes();

private:
    //private members
    bool _driveMode;
    RCManager * _rc;
    QTcpServer * _server;
    QTcpSocket * _clientSocket;
    QThreadPool * _poolInstance;
    PacketManager * _packetManager;

    //private methods
    void driveModeSet(int state);
    bool checkBytesForExit(QByteArray bytes);
    bool checkMessageForExit(QString message);

};

#endif // NETWORKMANAGER_H
