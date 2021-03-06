#include "networkmanager.h"
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent), _server(nullptr), _clientSocket(nullptr),
      _packetManager(nullptr), _rc(nullptr), _driveMode(false),
      _controlSocket(nullptr)//_camManager(nullptr)
{
    //object allocation
    _server = new QTcpServer(this);
    _packetManager = new PacketManager(this);

    _rc = new RCManager(this);
    _rc->updateRunning(false);

    //tied newConnection handler to server signal
    connect(_server, &QTcpServer::newConnection, this, &NetworkManager::newConnection);

    //connect driving signals
    connect(this, &NetworkManager::startDriving, this, &NetworkManager::setupControlStream);
    connect(this, &NetworkManager::stopDriving, this, &NetworkManager::endControlStream);

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

void NetworkManager::customDestroy()
{
    _rc->ensureShutdown();
    QThreadPool::globalInstance()->waitForDone();


 //   _camManager->stop();
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
 //   delete _camManager;
    delete _rc;
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
            //debug
            QString steering = QString::number(packet->_steeringAngle);
            QString throttle = QString::number(packet->_throttle);
            QString direction = (packet->_forward ? "Forward" : "Reverse");
            QString boost = (packet->_boost ? "On" : "Off");
            QString clientPacketData = "Client Packet: \nSteering: " + steering +
                                       "\nThrottle: " + throttle + "\nDirection: " + direction +
                                       "\nBoost: " + boost + '\n';
            emit sendBytesToMessageLog(clientPacketData);
            //end debug

            //check drive mode
            driveModeSet(packet->_state);

            //close server if bytes contain exit bytes
            if(checkMessageForExit(packet->_message))
                customDestroy();
        }
        else if (packet == nullptr)
        {
            qDebug() << "something bad happened";
            qDebug() << bytes;
        }

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
    {
        if (_driveMode)
            _driveMode = false;
        return true;
    }
    return false;
}

void NetworkManager::driveModeSet(int state)
{
    bool currentDriveValue = false;
    if (state == 0)
        currentDriveValue = false;
    else if (state == 1)
        currentDriveValue = true;
    //stored value for drive mode is the previous
    if (_driveMode != currentDriveValue)
    {
        _driveMode = currentDriveValue;
        if (currentDriveValue)
            emit startDriving();
        else
            emit stopDriving();
    }
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
        _packetManager->clearMessage();
    }
}

void NetworkManager::setupControlStream()
{
    if (_controlSocket == nullptr)
    {
        qDebug() << "Creating udp socket...\n";
        _controlSocket = new QUdpSocket(this);
        if (!_controlSocket->bind(45454, QUdpSocket::ShareAddress))
        {
            qDebug() << "Could not bind to udp socket using tcp client address...\n";
        }
        qDebug() << "Starting rc....\n";
        connect(_controlSocket, &QUdpSocket::readyRead, this, &NetworkManager::udpControlBytes);
        _rc->updateRunning(true);
        QThreadPool::globalInstance()->setMaxThreadCount(4);
        QThreadPool::globalInstance()->start(_rc, QThread::HighPriority);
    }
    else //don't expect this case to occur
    {//_controlSocket should be cleaned on stopDriving
        if (_controlSocket->isOpen())
            _controlSocket->close();
        delete _controlSocket;
        _controlSocket = nullptr;
    }
}

void NetworkManager::endControlStream()
{
    if (_controlSocket != nullptr)
    {
        if (_controlSocket->isOpen())
            _controlSocket->close();
        delete _controlSocket;
        _controlSocket = nullptr;
    }
    else //don't expect this case to occur
    {//_controlSocket should never be nullptr in this method
    //nothing to be done
    }
}

void NetworkManager::udpControlBytes()
{
    QByteArray buffer;
    buffer.resize(_controlSocket->pendingDatagramSize());
    _controlSocket->readDatagram(buffer.data(), buffer.size());
    _rc->enqueueControl(&buffer);
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

