
#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
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
        WrongAnswer
    };

public:
    Game(Server *server);

    void updateImage(QByteArray &newImage);
    void startGame();
private:
    Server *server;

    int playerCount = 0;
    QByteArray currentImage;

};

#endif // GAME_H
