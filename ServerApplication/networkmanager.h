#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QBuffer>
#include "packetmanager.h"

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    //constructors and destructors
    explicit NetworkManager(QObject *parent = 0);
    ~NetworkManager();

    //public cleanup method
    void Destroy();
    void writeToSocket(QString message);

    void sendCurrentPacket();

signals:
    void sendBytesToMessageLog(QString message);

public slots:
    void newConnection();
    void readClientBytes();

private:
    //private members
    QTcpServer * _server;
    QTcpSocket * _clientSocket;
    PacketManager * _packetManager;

    //private methods
    bool checkBytesForExit(QByteArray bytes);
    bool checkMessageForExit(QString message);

};

#endif // NETWORKMANAGER_H
