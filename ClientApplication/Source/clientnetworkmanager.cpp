#include "clientnetworkmanager.h"
#include <QDebug>

ClientNetworkManager::ClientNetworkManager(SteeringWheelController * controller, QObject *parent)
    : QObject(parent), _socket(nullptr), _connected(false),
      _packetizer(nullptr), _controller(controller), _controlSocket(nullptr)
{
    _packetizer = new PacketManager(this);
    connect(_controller, &SteeringWheelController::new_remoteControlData,
            this, &ClientNetworkManager::updateControlData);
    connect(_controller, &SteeringWheelController::driveModeChanged,
           this, &ClientNetworkManager::updateDriveMode);
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

    _socket->connectToHost(_jetsonIP, _jetsonPort);

    if (!_socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << _socket->errorString();
        emit networkError(3, "Failure on connection to Jetson. Check the IP Address.");
    }
    else
    {
        _packetizer->setState(0);
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
        writeToSocket("Goodbye server...exit now");
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
        _packetizer->clearMessage();
    }
}

void ClientNetworkManager::updateDriveMode()
{
    if (_controller->driveMode())
    {
        _packetizer->setState(1);
        sendCurrentPacket();
        initUdpStream();
    }
    else
    {
        _packetizer->setState(0);
        sendCurrentPacket();
        killUdpStream();
    }
}

void ClientNetworkManager::initUdpStream()
{
    if (_controlSocket == nullptr)
    {
        _controlSocket = new QUdpSocket(this);
    }
    else
    {
        //should not reach this point
    }
}

void ClientNetworkManager::killUdpStream()
{
    if (_controlSocket != nullptr)
    {
        delete _controlSocket;
        _controlSocket = nullptr;
    }
    else
    {
        //should not reach this point
    }
}

void ClientNetworkManager::updateControlData(double steeringValue, double throttle)
{
    QByteArray datagram;
    datagram.append(SERVO_TAG);
    datagram.append(BYTE_SPLIT);
    datagram.append(QString::number(steeringValue));
    qDebug() << datagram;
    _controlSocket->writeDatagram(datagram.data(), datagram.size(),
                                  QHostAddress::Broadcast, 45454);
    _controlSocket->flush();
    datagram.clear();
    datagram.append(MOTOR_TAG);
    datagram.append(BYTE_SPLIT);
    datagram.append(QString::number(throttle));
    qDebug() << datagram;
    qDebug() << "DG Size: " << datagram.size();
    _controlSocket->writeDatagram(datagram.data(), datagram.size(),
                                  QHostAddress::Broadcast, 45454);
    _controlSocket->flush();
}

QString ClientNetworkManager::jetsonIP()
{
    return _jetsonIP;
}

int ClientNetworkManager::jetsonPort()
{
    return _jetsonPort;
}

int ClientNetworkManager::appState()
{
    return _state;
}

void ClientNetworkManager::setAppState(int stateValue)
{
    if (_state != stateValue)
    {
        _state = stateValue;
        _packetizer->setState(_state);
        emit appStateChanged();
    }
}

void ClientNetworkManager::setMessage(QString message)
{
    _packetizer->setMessage(message);
}

