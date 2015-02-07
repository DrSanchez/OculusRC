#include "networkmanager.h"
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent), _packetManager(nullptr)
{
    //object allocation
    _packetManager = new PacketManager(this);
    _server = new QTcpServer(this);

    //tied newConnection handler to server signal
    connect(_server, &QTcpServer::newConnection, this, &NetworkManager::newConnection);

    //start server listening
    if (!_server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Problem starting server...";
        emit sendBytesToMessageLog("Problem starting server...");
    }
    else
    {
        qDebug() << "Server starting...";
        emit sendBytesToMessageLog("Server starting...");
    }
}

void NetworkManager::Destroy()
{
    //check client socket exists
    if (_clientSocket != nullptr)
    {//is socket active?
        if (_clientSocket->isOpen())
            _clientSocket->close();
        delete _clientSocket;
        _clientSocket = nullptr;
    }//check server object exists
    if (_server != nullptr)
    {//is server active?
        if (_server->isListening())
            _server->close();
        delete _server;
        _server = nullptr;
    }
    emit sendBytesToMessageLog("Server and socket destroyed...");
}

void NetworkManager::readClientBytes()
{
    //socket null check
    if (_clientSocket->isOpen())
    {
        //get client socket bytes
        QByteArray bytes(_clientSocket->readAll());
        ClientPacket * packet = _packetManager->unpack(bytes);
        if (packet != nullptr)
        {
            qDebug() << "unpacked message: " << packet->_message;
            QString steering = QString::number(packet->_steeringAngle);
            QString throttle = QString::number(packet->_throttle);
            QString direction = (packet->_forward ? "Forward" : "Reverse");
            QString boost = (packet->_boost ? "On" : "Off");
            QString clientPacketData = "Client Packet: \nSteering: " + steering +
                                       "\nThrottle: " + throttle + "\nDirection: " + direction +
                                       "\nBoost: " + boost + '\n';
            emit sendBytesToMessageLog(clientPacketData);
        }
        else if (packet == nullptr)
            qDebug() << "something bad happened";

        //close server if bytes contain exit bytes
        if(checkMessageForExit(_packetManager->getMessage()))
            Destroy();
    }
}

void NetworkManager::newConnection()
{
    //obtain socket from connection
    _clientSocket = _server->nextPendingConnection();

    //socket has been created, connect to read slot
    connect(_clientSocket, &QTcpSocket::readyRead, this, &NetworkManager::readClientBytes);

    qDebug() << "In new connection...";
    emit sendBytesToMessageLog("In new connection...\r\n");
    bool test = true;
    emit sendBytesToMessageLog((test == true ? QString::number(test) : "false"));

    //write hello message to client socket
    _packetManager->setMessage("Hello Client");
    sendCurrentPacket();
}

bool NetworkManager::checkBytesForExit(QByteArray bytes)
{
    //convert to QString
    QString dataBytes(bytes.data());

    //check for exit bytes
    if (dataBytes.contains("exit"))
        return true;
    return false;
}

bool NetworkManager::checkMessageForExit(QString message)
{
    //check for exit bytes
    if (message.contains("exit"))
        return true;
    return false;
}

void NetworkManager::writeToSocket(QString message)
{
    if (_clientSocket->isOpen())
    {
        message.prepend("Server: ");
        message.append("\r\n");
        _clientSocket->write(message.toStdString().c_str());
        _clientSocket->flush();
        emit sendBytesToMessageLog(message);
    }
}

void NetworkManager::sendCurrentPacket()
{
    if (_clientSocket->isOpen())
    {
        _packetManager->prependMessage("Server: ");
        _packetManager->appendMessage("\r\n");
        QByteArray bytes(_packetManager->pack());
        _clientSocket->write(bytes.data(), bytes.size() + 1);
        _clientSocket->waitForBytesWritten();
        _clientSocket->flush();
    }
}

NetworkManager::~NetworkManager()
{
    //check client socket exists
    if (_clientSocket != nullptr)
    {//is socket active?
        if (_clientSocket->isOpen())
            _clientSocket->close();
        delete _clientSocket;
        _clientSocket = nullptr;
    }//check server object exists
    if (_server != nullptr)
    {//is server active?
        if (_server->isListening())
            _server->close();
        delete _server;
        _server = nullptr;
    }
}
