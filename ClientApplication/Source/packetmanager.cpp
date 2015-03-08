#include "packetmanager.h"
#include <QDebug>

PacketManager::PacketManager(QObject *parent) :
    QObject(parent), _clientPack(nullptr), _serverPack(nullptr)
{
    _clientPack = new ClientPacket();
    _clientPack->_state = 0;
    _clientPack->_steeringAngle = 0.0;
    _clientPack->_throttle = 0.0;
    _clientPack->_forward = true;
    _clientPack->_boost = false;
    _clientPack->_message = "";
    _serverPack = new ServerPacket();
    _serverPack->_yaw = 0.0;
    _serverPack->_pitch = 0.0;
    _serverPack->_roll = 0.0;
    _serverPack->_message = "";
}

void PacketManager::setState(int state)
{
    _clientPack->_state = state;
}

void PacketManager::setSteeringAngle(double angle)
{
    _clientPack->_steeringAngle = angle;
}

void PacketManager::setSteeringAngleFromController(double controllerValue)
{
    double angle = STEERING_ANGLE_MULTIPLER * controllerValue;
    setSteeringAngle(angle);
}

void PacketManager::setThrottleDirection(double throttle, bool forward)
{
    _clientPack->_throttle = throttle;
    _clientPack->_forward = forward;
}

void PacketManager::setBoost(bool boost)
{
    _clientPack->_boost = boost;
}

void PacketManager::setMessage(QString message)
{
    _clientPack->_message = message;
}

QByteArray PacketManager::pack()
{
    QByteArray bytes;
    bytes.append(CLIENT_TAG);//set client byte
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_clientPack->_state));
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_clientPack->_steeringAngle));
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_clientPack->_throttle));
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_clientPack->_forward));
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_clientPack->_boost));
    bytes.append(BYTE_SPLIT);
    bytes.append(_clientPack->_message);
    qDebug() << "Client Pack: " << bytes;
    return bytes;
}

ServerPacket * PacketManager::unpack(QByteArray bytes)
{
    QList<QByteArray> unpackedBytes(bytes.split(BYTE_SPLIT));
    if (!unpackedBytes.isEmpty() && unpackedBytes.size() == 5)
    {
        QByteArray temp = unpackedBytes.takeFirst();
        if (*(temp.data()) != SERVER_TAG)
            return nullptr;
        temp = unpackedBytes.takeFirst();
        _serverPack->_yaw = temp.toDouble();
        temp = unpackedBytes.takeFirst();
        _serverPack->_pitch = temp.toDouble();
        temp = unpackedBytes.takeFirst();
        _serverPack->_roll = temp.toDouble();
        temp = unpackedBytes.takeFirst();
        _serverPack->_message = temp.data();
        unpackDebugOut();
    }
    else
    {
        qDebug() << "Invalid byte data passed...";
        return nullptr;
    }
    return _serverPack;
}

void PacketManager::appendToMessage(QString more)
{
    _clientPack->_message.append(more);
}

void PacketManager::prependToMessage(QString more)
{
    _clientPack->_message.prepend(more);
}

void PacketManager::updateControlData(double steeringValue, double throttle, bool direction, bool boost)
{
    //setSteeringAngleFromController(steeringValue);
    setSteeringAngle(steeringValue);
    setThrottleDirection(throttle, direction);
    setBoost(boost);
    emit packetChanged();
}

void PacketManager::unpackDebugOut()
{
    qDebug() << "Server Packet:";
    qDebug() << "Yaw: " << _serverPack->_yaw;
    qDebug() << "Pitch: " << _serverPack->_pitch;
    qDebug() << "Roll: " << _serverPack->_roll;
    qDebug() << "Message: " << _serverPack->_message;
}

void PacketManager::clearMessage()
{
    _clientPack->_message = "";
    _serverPack->_message = "";
}
