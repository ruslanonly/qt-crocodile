#include <QCoreApplication>
#include <server.h>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server *server = new Server();

    return a.exec();
}
