
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
    qDebug() << "Game started";

    isGameRunning = true;

    int wordNumber = QRandomGenerator::global()->bounded(0, wordList->count());
    int drawerNumber = QRandomGenerator::global()->bounded(0, socketToPlayer.count());

    currentDrawer = socketToPlayer.keys()[drawerNumber];
    currentWord = wordList->at(wordNumber);

    foreach (auto socket, socketToPlayer.keys()) {
        if (socket == currentDrawer) {
            server->sendMessage(socket, Drawer, currentWord.toUtf8());
            continue;
        }
        server->sendMessage(socket, Guesser, currentImage);
    }
}

void Game::restartGame(QString lastGameStatus) {
    qDebug() << "Game restarted";

    isGameRunning = true;

    int wordNumber = QRandomGenerator::global()->bounded(0, wordList->count());
    int drawerNumber = QRandomGenerator::global()->bounded(0, socketToPlayer.count());

    currentDrawer = socketToPlayer.keys()[drawerNumber];
    currentWord = wordList->at(wordNumber);

    QString gameStatusWithWord = lastGameStatus + ":" + currentWord;

    foreach (auto socket, socketToPlayer.keys()) {
        if (socket == currentDrawer) {
            server->sendMessage(socket, GameEndedDrawer, gameStatusWithWord.toUtf8());
            continue;
        }
        server->sendMessage(socket, GameEndedGuesser, lastGameStatus.toUtf8());
    }
}

void Game::removePlayer(QTcpSocket* socket) {
    socketToPlayer.remove(socket);

    if (socket == currentDrawer) {
        endGame(currentWord);
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

    if (guess != currentWord) {
        server->sendMessage(socket, WrongAnswer);
        return;
    }

    QString response = socketToPlayer[socket] + ":" + currentWord;
    endGame(response);
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


void Game::endGame(QString gameResult) {
    isGameRunning = false;


    if (socketToPlayer.count() > 1) {
        restartGame(gameResult);
        return;
    }

    foreach (auto socket, socketToPlayer.keys()) {
        server->sendMessage(socket, GameEnded, gameResult.toUtf8());
    }
    // output winner and restart game
}
