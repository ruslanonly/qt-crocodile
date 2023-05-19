#include <QCoreApplication>
#include <server.h>
#include <game.h>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server *server = new Server();

    Game *game = new Game(server);

    return a.exec();
}
