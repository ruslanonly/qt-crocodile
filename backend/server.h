
#ifndef SERVER_H
#define SERVER_H


#include <QDebug>
#include <QObject>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT

public:
    Server();
    ~Server();

    void sendMessage(QTcpSocket* socket, int code, QByteArray message = "");

signals:
    void connected(QTcpSocket* socket);
    void newMessage(QTcpSocket* socket, int code, QByteArray message);
    void disconnected(QTcpSocket* socket);

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    //void displayMessage(const QString& str);

    //void sendAttachment(QTcpSocket* socket, QString filePath);

    //void refreshComboBox();
private:
    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;
};

#endif // SERVER_H
