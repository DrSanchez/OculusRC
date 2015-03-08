#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

/*********************************************
 * Note to self: Hardcode IP for in-house
 * testing, eventually setup multicast address
 * and dynamically ping the Jetson for it's
 * IP address
 *********************************************/

#include <QTcpSocket>
#include "packetmanager.h"
#include "steeringwheelcontroller.h"

//Default Jetson Home IP: 192.168.2.4
const QString _jetsonIP = "192.168.2.4";
//Default Jetson Server Port: 9999
const int _jetsonPort = 9999;

class ClientNetworkManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(QString JetsonIP READ jetsonIP NOTIFY jetsonIPChanged)
    Q_PROPERTY(int JetsonPort READ jetsonPort NOTIFY jetsonPortChanged)
    Q_PROPERTY(int state READ appState WRITE setAppState NOTIFY appStateChanged)

public:
    //constructors and destructors
    explicit ClientNetworkManager(SteeringWheelController * controller, QObject *parent = 0);

    //QML property read methods
    bool connected();
    QString jetsonIP();
    int jetsonPort();
    int appState();
    void setAppState(int stateValue);

    //public methods exposed to QML
    Q_INVOKABLE void connectToJetson();
    Q_INVOKABLE void disconnectFromJetson();
    Q_INVOKABLE void setMessage(QString message);

    //public send packet method
    void sendCurrentPacket();

signals:
    //QML property signals
    void connectedChanged();
    void networkError(int priority, QString message);
    void jetsonIPChanged();
    void jetsonPortChanged();
    void appStateChanged();

public slots:
    //tcp socket signal handlers
    void socketConnected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void handleNewControlData();

private:
    //private methods
    void jetsonConnected(bool connect);
    void writeToSocket(QString message);

    //private data members
    QTcpSocket * _socket;
    bool _connected;
    PacketManager * _packetizer;
    SteeringWheelController * _controller;
    int _state;

};

#endif // CLIENTNETWORKMANAGER_H
