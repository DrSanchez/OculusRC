#include "clientnetworkmanager.h"
#include <QDebug>

ClientNetworkManager::ClientNetworkManager(SteeringWheelController * controller, QObject *parent)
    : QObject(parent), _socket(nullptr), _connected(false),
      _packetizer(nullptr), _controller(controller)
{
    _packetizer = new PacketManager(this);
    connect(_controller, &SteeringWheelController::remoteControlData,
            _packetizer, &PacketManager::updateControlData);
    connect(_packetizer, &PacketManager::packetChanged,
            this, &ClientNetworkManager::handleNewControlData);
}

void ClientNetworkManager::connectToJetson()
{
    _socket = new QTcpSocket(this);

    connect(_socket, &QTcpSocket::connected,
            this, &ClientNetworkManager::socketConnected);
    connect(_socket, &QTcpSocket::disconnected,
            this, &ClientNetworkManager::disconnected);
    connect(_socket, &QTcpSocket::bytesWritten,
            this, &ClientNetworkManager::bytesWritten);
    connect(_socket, &QTcpSocket::readyRead,
            this, &ClientNetworkManager::readyRead);

    qDebug() << "Connecting to Jetson...";

    _socket->connectToHost(jetsonIP, jetsonPort);

    if (!_socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << _socket->errorString();
        emit networkError(3, "Failure on connection to Jetson. Check the IP Address.");
    }
    else
    {
        _packetizer->setState(MENU);
        _packetizer->setSteeringAngle(0.0);
        _packetizer->setThrottleDirection(0.0, true);
        _packetizer->setBoost(false);
        _packetizer->setMessage("Connection Packet");
        jetsonConnected(true);
    }
}

void ClientNetworkManager::disconnectFromJetson()
{
    if (_socket->isOpen())
    {
        writeToSocket("Goodbyte server...exit now");
        if (!_socket->waitForBytesWritten(5000))
        {
            qDebug() << "Something bad happened on disconnect...";
            emit networkError(3, "Failure on disconnection from Jetson.");
        }
        else
        {
            _socket->close();
            delete _socket;
            _socket = nullptr;
            jetsonConnected(false);
        }
    }
}

void ClientNetworkManager::socketConnected()
{
    qDebug() << "Successfully connected to Jetson!";
    _packetizer->setMessage("Client-side socket connected slot");
    sendCurrentPacket();
}

void ClientNetworkManager::disconnected()
{
    qDebug() << "Disconnected...";
    jetsonConnected(false);
}

void ClientNetworkManager::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void ClientNetworkManager::readyRead()
{
    QByteArray bytes(_socket->readAll());
    ServerPacket * pack = _packetizer->unpack(bytes);
    if (pack != nullptr)
        qDebug() << "unpacked message: " << pack->_message;
    else if (pack == nullptr)
        qDebug() << "something bad happened";
}

bool ClientNetworkManager::connected()
{
    return _connected;
}

void ClientNetworkManager::jetsonConnected(bool connect)
{
    if (connect != _connected)
    {
        _connected = connect;
        emit connectedChanged();
    }
}

void ClientNetworkManager::writeToSocket(QString message)
{
    message.prepend("Client: ");
    message.append("\r\n");
    if (_socket->isOpen())
        _socket->write(message.toStdString().c_str());
}

void ClientNetworkManager::sendCurrentPacket()
{
    if (_socket->isOpen())
    {
        _packetizer->prependToMessage("Client: ");
        _packetizer->appendToMessage("\r\n");
        QByteArray bytes(_packetizer->pack());
        _socket->write(bytes.data(), bytes.size() + 1);
        _socket->waitForBytesWritten();
        _socket->flush();
    }
}

void ClientNetworkManager::handleNewControlData()
{
    sendCurrentPacket();
}
