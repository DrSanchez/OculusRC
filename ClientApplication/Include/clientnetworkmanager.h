#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

/*********************************************
 * Note to self: Hardcode IP for in-house
 * testing, eventually setup multicast address
 * and dynamically ping the Jetson for it's
 * IP address
 *********************************************/

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QString>

//Default Jetson Home IP: 192.168.2.3
static const QString jetsonIP = "192.168.2.3";
//Default Jetson Server Port: 9999
static const int jetsonPort = 9999;

class ClientNetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
public:
    //constructors and destructors
    explicit ClientNetworkManager(QObject *parent = 0);

    //QML property read methods
    bool connected();

    //public methods exposed to QML
    Q_INVOKABLE void connectToJetson();
    Q_INVOKABLE void disconnectFromJetson();

signals:
    //QML property signals
    void connectedChanged();
    void networkError(int priority, QString message);

public slots:
    //tcp socket signal handlers
    void socketConnected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    //private methods
    void jetsonConnected(bool connect);
    void writeToSocket(QString message);

    //private data members
    QTcpSocket * _socket;
    bool _connected;

};

#endif // CLIENTNETWORKMANAGER_H
