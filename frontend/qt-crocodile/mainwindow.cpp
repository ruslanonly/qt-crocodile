
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintscene.h"
#include <QDebug>
#include <QTime>
#include <QBuffer>
#include <QImageWriter>
#include <QImageReader>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QAbstractSocket>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);

    connect(scene, PaintScene::mouseUpEvent, this, MainWindow::onMouseUpSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMouseUpSlot() {
    qDebug() << "mouse up";
}

void MainWindow::on_sendWordButton_clicked()
{
    QByteArray imageBA = exportGraphicsView()->buffer();
    sendMessage(MessageCodes::UpdateImage, imageBA);

}


void MainWindow::showWindow(QString Username) {
    this->show();

    this->Username = Username;
    QByteArray UsernameUTFed = Username.toUtf8();
    sendMessage(MessageCodes::SetNickname, UsernameUTFed);
    qDebug() << "showWindow" << Username;

    openConnection();
}

void MainWindow::openConnection() {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    socket->connectToHost(QHostAddress::LocalHost,7007);

    if(socket->waitForConnected())
        qDebug() << "Connected to Server";
//    else {
//        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
//        exit(EXIT_FAILURE);
//    }

}


// Socket

void MainWindow::readSocket() {
    qDebug() << "Соединение установлено";

    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray bArray;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> bArray;

    QString header = bArray.mid(0,128);
    char MESSAGE_CODE = header.split(":")[1].toInt();

    bArray = bArray.mid(128);


    switch (MESSAGE_CODE) {
    case Guess: {


        break;
    }
    case UpdateImage:{//
        QBuffer* buffer = new QBuffer(&bArray);
        updateGraphicsView(buffer);

        break;
    }
    case GameStarted:{//


        break;
    }
    case GameEnded:{//


        break;
    }
    case Drawer:{//


        break;
    }
    case Guesser:{//


        break;
    }
    case WrongAnswer:{//


        break;
    }
    case SetNickname:{


        break;
    }
    default:
        break;
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError) {
    qDebug() << socketError;
    QMessageBox msg;
    msg.setText("Возникла ошибка");
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
}

void MainWindow::discardSocket() {
    QMessageBox msg;
    msg.setText("Соединение внезапно прервано");
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
}



void MainWindow::sendMessage(MessageCodes messageCode, QByteArray qArray) {
    if(socket)
    {
        if(socket->isOpen())
        {
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15);

            QByteArray header;
            header.prepend(QString("messageCode: MESSAGE CODES").toUtf8());
            header.resize(128);

            QByteArray byteArray = qArray;
            byteArray.prepend(header);

            socketStream.setVersion(QDataStream::Qt_5_15);
            socketStream << byteArray;
        }
        else qDebug() << "ERROR: Socket doesn't seem to be opened";
    }
    else qDebug() << "ERROR: Not connected";

}

// GraphicsView

QBuffer* MainWindow::exportGraphicsView() {
    QImage image(ui->graphicsView->viewport()->size(), QImage::Format_ARGB32);
    QPainter painter(&image);
    ui->graphicsView->render(&painter);

    QBuffer* buffer = new QBuffer;
    buffer->open(QIODevice::WriteOnly);

    QImageWriter writer(buffer, "PNG");

    writer.setFormat("PNG");
    writer.setQuality(100);

    writer.write(image);

    buffer->close();

    return buffer;
}

void MainWindow::updateGraphicsView(QBuffer* buffer) {
    QByteArray pngData = buffer->buffer();

    QBuffer tbuff;
    tbuff.setData(pngData);
    tbuff.open(QIODevice::ReadOnly);

    // Seek to the beginning of the QBuffer
    tbuff.seek(0);

    // Create a QImageReader and set the QBuffer as its device
    QImageReader reader;
    reader.setDevice(&tbuff);

    // Read the image from the QImageReader
    QImage image = reader.read();

    // Convert the QImage to a QPixmap
    QPixmap pixmap = QPixmap::fromImage(image);


    ui->graphicsView->scene()->clear();
    ui->graphicsView->scene()->addPixmap(pixmap);
    ui->graphicsView->scene()->setSceneRect(0,0, ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    ui->graphicsView->setScene(scene);

}
