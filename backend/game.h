
#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRandomGenerator>
#include "server.h"



class Game : public QObject
{
    Q_OBJECT
private:
    enum MessageCodes {
        Guess = 1,
        UpdateImage,
        GameStarted,
        GameEnded,
        Drawer,
        Guesser,
        WrongAnswer,
        SetNickname
    };

public:
    Game(Server *server);

    void updateImage(QByteArray &newImage);
    void startGame();
    void waitGame(QTcpSocket* socket);
    void parseMessage(QTcpSocket* socket, int code, QByteArray message);
    void removePlayer(QTcpSocket* socket);
    void checkAnswer(QTcpSocket* socket, QString guess);
    void endGame();
private:
    Server *server;

    bool isGameRunning;
    int playerCount;

    QTcpSocket* currentDrawer;
    QByteArray *currentImage;
    QString currentWord;

    QMap<QTcpSocket*, QString> socketToPlayer;
};

#endif // GAME_H
