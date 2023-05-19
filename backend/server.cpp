
#include "server.h"

Server::Server()
{
    m_server = new QTcpServer();

    if(m_server->listen(QHostAddress::Any, 7007))
    {

        //connect(this, &Server::newMessage, this, &Server::displayMessage);
        connect(m_server, &QTcpServer::newConnection, this, &Server::newConnection);
        qDebug() << "Server is listening...";
    }
    else
    {
        qDebug() << m_server->errorString();
        exit(EXIT_FAILURE);
    }
}

Server::~Server()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();
}

void Server::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}

void Server::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &Server::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Server::displayError);
    qDebug() << QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor());
    emit connected(socket);
//    QString str("INFO :: Client with sockd:%1 has just entered the room");
//    str = str.arg(socket->socketDescriptor());
//    foreach (QTcpSocket* socket, connection_set)
//    {
//        sendMessage(socket, str);
//    }
    // ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
//    displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
}

void Server::sendMessage(QTcpSocket* socket, int code, QByteArray message)
{
    if(socket)
    {
        if(socket->isOpen())
        {

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("messageCode:%1").arg(code).toUtf8());
            header.resize(128);

            QByteArray byteArray = message;
            byteArray.prepend(header);

            socketStream.setVersion(QDataStream::Qt_5_15);
            socketStream << byteArray;
        }
        else
            qDebug() << "ERROR: Socket doesn't seem to be opened";
    }
    else
        qDebug() << "ERROR: Not connected";
}



void Server::readSocket() {
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        return;
    }

    QString header = buffer.mid(0,128);
    char messageCode = header.split(":")[1].toInt();

    buffer = buffer.mid(128);

    emit newMessage(socket, messageCode, buffer);

//    if(fileType=="attachment"){
//        currentImageBuffer = buffer.mid(128);
//        emit newMessage("TEST");

//    } else if(fileType=="message"){
//        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
//        emit newMessage("message");
//    }
}

void Server::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.";
        break;
    default:
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        qDebug() << QString("The following error occurred: %1.").arg(socket->errorString());
        break;
    }
}

void Server::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        emit disconnected(socket);

        qDebug() << QString("INFO :: A client has just left the room").arg(socket->socketDescriptor());
        connection_set.remove(*it);
    }

    socket->deleteLater();
}
