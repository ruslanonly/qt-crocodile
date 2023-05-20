
#include "game.h"

Game::Game(Server *server)
{
    this->server = server;
    playerCount = 0;
    currentImage;
    isGameRunning = false;

//    connect(server, &Server::connected, this, &Game::waitGame);
    connect(server, &Server::newMessage, this, &Game::parseMessage);
    connect(server, &Server::disconnected, this, &Game::removePlayer);
}

void Game::waitGame(QTcpSocket* socket) {


    if (isGameRunning) {
        server->sendMessage(socket, Guesser, currentImage);

        return;
    }

    if (socketToPlayer.count() > 1) {
        startGame();
        return;
    }
}

void Game::startGame() {
    isGameRunning = true;

    int wordNumber = QRandomGenerator::global()->bounded(0, wordList->count());
    int drawerNumber = QRandomGenerator::global()->bounded(0, socketToPlayer.count());

    currentDrawer = socketToPlayer.keys()[drawerNumber];
    currentWord = wordList->at(wordNumber);

    foreach (auto socket, socketToPlayer.keys()) {
        if (socket == currentDrawer) server->sendMessage(socket, Drawer, currentWord.toUtf8());
        server->sendMessage(socket, Guesser, currentImage);
    }
}

void Game::removePlayer(QTcpSocket* socket) {
    socketToPlayer.remove(socket);

    if (socket == currentDrawer) {
        endGame(currentWord.toUtf8());
    }
}

void Game::parseMessage(QTcpSocket* socket, int code, QByteArray message) {
    qDebug() << code;

    switch (code) {
    case SetNickname: {
        socketToPlayer[socket] = QString(message);

        waitGame(socket);
        break;
    }
    case Guess: {
        checkAnswer(socket, QString(message));
        break;
    }
    case UpdateImage: {
        updateImage(message);
        break;
    }
    default:
        break;
    }
}

void Game::checkAnswer(QTcpSocket* socket, QString guess) {
    qDebug() << (guess == currentWord ? "Right" : "Wrong");

    if (guess != currentWord) {
        server->sendMessage(socket, WrongAnswer);
        return;
    }

    QString response = socketToPlayer[socket] + ":" + currentWord;
    endGame(response.toUtf8());
    // check input and call endGame
}

void Game::updateImage(QByteArray &message) {
    currentImage = message;
    qDebug() << socketToPlayer.count();

    foreach (auto socket, socketToPlayer.keys()) {
        if (socket == currentDrawer) continue;
        server->sendMessage(socket, UpdateImage, currentImage);
    }
    // update drawer image
}


void Game::endGame(QByteArray gameResult) {
    isGameRunning = false;

    foreach (auto socket, socketToPlayer.keys()) {
        server->sendMessage(socket, GameEnded, gameResult);
    }

    QThread::sleep(5);
    if (socketToPlayer.count() > 1) {
        startGame();
    }
    // output winner and restart game
}
