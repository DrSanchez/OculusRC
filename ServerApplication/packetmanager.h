#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QList>

const static char SERVER_TAG = '@';
const static char CLIENT_TAG = '$';
const static char BYTE_SPLIT = '|';

//public packet structure
enum AppState { MENU, DRIVE };
struct ClientPacket
{
    AppState _state;
    double _steeringAngle;
    double _throttle;
    bool _forward;
    bool _boost;
    QString _message;
};

struct ServerPacket
{
    double _yaw;
    double _pitch;
    double _roll;
    QString _message;
};

class PacketManager : public QObject
{
    Q_OBJECT
public:
    explicit PacketManager(QObject *parent = 0);

    QByteArray pack();
    ClientPacket * unpack(QByteArray bytes);

    //packet data setters
    void setMessage(QString message);
    void prependMessage(QString message);
    void appendMessage(QString message);
    void setSensorData(double yaw, double roll, double pitch);

    //packet data getters
    AppState getState();
    double getSteeringAngle();
    double getThrottle();
    bool getDirection();
    bool getBoost();
    QString getMessage();

    void unpackDebugOut();

signals:
    void packetChanged();

public slots:

private:
    //private data members
    ClientPacket * _clientPack;
    ServerPacket * _serverPack;


};

#endif // PACKETMANAGER_H
