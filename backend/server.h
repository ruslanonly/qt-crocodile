
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

signals:
    void newMessage(QString);

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    //void displayMessage(const QString& str);
    void sendMessage(QTcpSocket* socket, int code, QByteArray& message);
    //void sendAttachment(QTcpSocket* socket, QString filePath);

    //void refreshComboBox();
private:
    int playerCount;

    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;

    QByteArray currentImageBuffer;
};

#endif // SERVER_H
