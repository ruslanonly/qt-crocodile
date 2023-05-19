
#include "game.h"

Game::Game(Server *server)
{
    this->server = server;
    playerCount = 0;
    currentImage = nullptr;
    isGameRunning = false;

//    connect(server, &Server::connected, this, &Game::waitGame);
    connect(server, &Server::newMessage, this, &Game::parseMessage);
    connect(server, &Server::disconnected, this, &Game::removePlayer);
}

void Game::waitGame(QTcpSocket* socket) {
    if (isGameRunning) {
        server->sendMessage(socket, Guesser);
        if (currentImage) {
            server->sendMessage(socket, UpdateImage, *currentImage);
        }
        return;
    }

    if (socketToPlayer.count() > 1) {
        startGame();
        return;
    }
}

void Game::startGame() {
    currentWord = "test";

    isGameRunning = true;
    currentDrawer = socketToPlayer.keys()[0];
    server->sendMessage(currentDrawer, Drawer, currentWord.toUtf8());

    foreach (auto socket, socketToPlayer.keys()) {
        server->sendMessage(socket, Guesser);
    }
}

void Game::removePlayer(QTcpSocket* socket) {
    socketToPlayer.remove(socket);
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
    if (guess != currentWord) {
        server->sendMessage(socket, WrongAnswer);
    }

//    QString response =
//    server->sendMessage(socket, GameEnded);
    // check input and call endGame
}

void Game::updateImage(QByteArray &message) {
    currentImage = &message;
    qDebug() << socketToPlayer.count();

    foreach (auto socket, socketToPlayer.keys()) {
        if (socket == currentDrawer) continue;
        server->sendMessage(socket, UpdateImage, *currentImage);
    }
    // update drawer image
}


void Game::endGame() {

    // output winner and restart game
}
