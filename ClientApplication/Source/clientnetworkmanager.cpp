#include "clientnetworkmanager.h"
#include <QDebug>

ClientNetworkManager::ClientNetworkManager(QObject *parent) :
    QObject(parent), _socket(nullptr), _connected(false)
{
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
        jetsonConnected(true);
    }
}

void ClientNetworkManager::disconnectFromJetson()
{
    if (_socket != nullptr)
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
    writeToSocket("Hello server!");
}

void ClientNetworkManager::disconnected()
{
    qDebug() << "Disconnected...";
}

void ClientNetworkManager::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void ClientNetworkManager::readyRead()
{
    qDebug() << _socket->readAll();
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
    _socket->write(message.toStdString().c_str());
}
