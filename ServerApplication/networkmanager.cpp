#include "networkmanager.h"
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent) :
    QObject(parent)
{
    //object allocation
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
    if (_clientSocket != nullptr)
    {
        //get client socket bytes
        QByteArray bytes = _clientSocket->readAll();
        emit sendBytesToMessageLog(QString(bytes));

        //processBytes, or is this method process bytes?

        //echo message back to client: debugging assistance
        _clientSocket->write(bytes);
        qDebug() << bytes << bytes.length();

        //close server if bytes contain exit bytes
        if(checkBytesForExit(bytes))
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

    //write hello message to client socket
    _clientSocket->write("Hello client\r\n");
    emit sendBytesToMessageLog("In new connection...\r\nHello client\r\n");
    _clientSocket->flush();
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
