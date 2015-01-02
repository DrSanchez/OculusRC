#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    //constructors and destructors
    explicit NetworkManager(QObject *parent = 0);
    ~NetworkManager();

    //public cleanup method
    void Destroy();

signals:
    void sendBytesToMessageLog(QString message);

public slots:
    void newConnection();
    void readClientBytes();

private:
    //private members
    QTcpServer * _server;
    QTcpSocket * _clientSocket;

    //private methods
    bool checkBytesForExit(QByteArray bytes);

};

#endif // NETWORKMANAGER_H
