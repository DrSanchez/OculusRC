#include "packetmanager.h"
#include <QDebug>

PacketManager::PacketManager(QObject *parent)
    : QObject(parent), _clientPack(nullptr), _serverPack(nullptr)
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

QByteArray PacketManager::pack()
{
    QByteArray bytes;
    bytes.append(SERVER_TAG);
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_serverPack->_yaw));
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_serverPack->_pitch));
    bytes.append(BYTE_SPLIT);
    bytes.append(QString::number(_serverPack->_roll));
    bytes.append(BYTE_SPLIT);
    bytes.append(_serverPack->_message);
    qDebug() << "Server Pack: " << bytes;
    return bytes;
}

ClientPacket * PacketManager::unpack(QByteArray bytes)
{
    QList<QByteArray> unpackedBytes(bytes.split(BYTE_SPLIT));
    if (!unpackedBytes.isEmpty() && unpackedBytes.size() == 7)
    {
        QByteArray temp = unpackedBytes.takeFirst();
        if (*(temp.data()) != CLIENT_TAG)
            return nullptr;
        temp = unpackedBytes.takeFirst();
        _clientPack->_state = temp.toInt();
        temp = unpackedBytes.takeFirst();
        _clientPack->_steeringAngle = temp.toDouble();
        temp = unpackedBytes.takeFirst();
        _clientPack->_throttle = temp.toDouble();
        temp = unpackedBytes.takeFirst();
        _clientPack->_forward = (temp.toInt() == 1 ? true : false);
        temp = unpackedBytes.takeFirst();
        _clientPack->_boost = (temp.toInt() == 1 ? true : false);
        temp = unpackedBytes.takeFirst();
        _clientPack->_message = temp.data();
        unpackDebugOut();
    }
    else
    {
        qDebug() << unpackedBytes.size();
        qDebug() << bytes;
        qDebug() << "Invalid byte data passed...";
        return nullptr;
    }
    return _clientPack;
}

void PacketManager::setMessage(QString message)
{
    _serverPack->_message = message;
}

void PacketManager::prependMessage(QString message)
{
    _serverPack->_message.prepend(message);
}

void PacketManager::appendMessage(QString message)
{
    _serverPack->_message.append(message);
}

void PacketManager::setSensorData(double yaw, double roll, double pitch)
{
    _serverPack->_pitch = pitch;
    _serverPack->_roll = roll;
    _serverPack->_yaw = yaw;
    emit packetChanged();
}

int PacketManager::getState()
{
    return _clientPack->_state;
}

double PacketManager::getSteeringAngle()
{
    return _clientPack->_steeringAngle;
}

double PacketManager::getThrottle()
{
    return _clientPack->_throttle;
}

bool PacketManager::getDirection()
{
    return _clientPack->_forward;
}

bool PacketManager::getBoost()
{
    return _clientPack->_boost;
}

QString PacketManager::getMessage()
{
    return _clientPack->_message;
}

void PacketManager::unpackDebugOut()
{
    qDebug() << "Client Packet:";
    qDebug() << "State: " << _clientPack->_state;
    qDebug() << "Steering Angle: " << _clientPack->_steeringAngle;
    qDebug() << "Throttle: " << _clientPack->_throttle;
    qDebug() << "Direction: " << (_clientPack->_forward ? "Forward" : "Reverse");
    qDebug() << "Boost: " << (_clientPack->_boost ? "On" : "Off");
    qDebug() << "Message: " << _clientPack->_message;
}

void PacketManager::clearMessage()
{
    _clientPack->_message = "";
    _serverPack->_message = "";
}

