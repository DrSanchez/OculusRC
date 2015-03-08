#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <Qlist>

const static double STEERING_ANGLE_MULTIPLER = 22.5;

const static char SERVER_TAG = '@';
const static char CLIENT_TAG = '$';
const static char BYTE_SPLIT = '|';

//public packet structure
struct ClientPacket
{
    int _state;//0 == menu, 1 == drive
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

    void setSteeringAngleFromController(double controllerValue);

    //Packet data setters
    void setState(int state);
    void setSteeringAngle(double angle);
    void setThrottleDirection(double throttle, bool forward);
    void setBoost(bool boost);
    void setMessage(QString message);
    void appendToMessage(QString more);
    void prependToMessage(QString more);

    //message reset method
    void clearMessage();

    //debug method
    void unpackDebugOut();

    //pack/unpack methods
    QByteArray pack();
    ServerPacket * unpack(QByteArray bytes);

signals:
    void packetChanged();

public slots:
    void updateControlData(double steeringValue, double throttle, bool direction, bool boost);

private:
    //private members
    ClientPacket * _clientPack;
    ServerPacket * _serverPack;

};

#endif // PACKETMANAGER_H
