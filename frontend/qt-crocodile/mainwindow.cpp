
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

    connect(scene, &PaintScene::mouseUpEvent, this, &MainWindow::onMouseUpSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMouseUpSlot() {
    QByteArray imageBA = exportGraphicsView()->buffer();
    sendMessage(MessageCodes::UpdateImage, imageBA);
}

void MainWindow::on_sendWordButton_clicked()
{
    QString word = ui->wordInput->text();
    QByteArray bArray = word.toUtf8();
    sendMessage(MessageCodes::Guess, bArray);
    ui->wordInput->clear();
}

void MainWindow::on_reconnectButton_clicked()
{
    openConnection();
}

void MainWindow::showWindow(QString Username) {

    this->Username = Username;

    qDebug() << "showWindow" << Username;

    openConnection();

    sendMessage(MessageCodes::SetNickname, this->Username.toUtf8());

    this->show();
}

void MainWindow::openConnection() {
    socket = new QTcpSocket(this);
    socket->setSocketOption(QAbstractSocket::SocketOption::LowDelayOption,0);

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

    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray bArray;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> bArray;

    if(!socketStream.commitTransaction())
    {
        return;
    }

    QString header = bArray.mid(0,128);
    int MESSAGE_CODE = header.split(":")[1].toInt();

    bArray = bArray.mid(128);

    qDebug() << "message_code" << MESSAGE_CODE << QString(bArray);

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
        ui->statusBarLabel->setText("Игра начата");
        break;
    }
    case GameEnded:{//
//        QString text = QString("Конец! Победитель - %1. Загаданное слово - %2")
//                           .arg(QString(bArray).split(":")[0])
//                           .arg(QString(bArray).split(":")[1]);
////        QMessageBox* msgBox = new QMessageBox;
////        msgBox->setText(text);
////        msgBox->show();

//        ui->statusBarLabel->setText(text);
//        if (this->isDrawer)
//        ui->wordInput->clear();
//        break;
    }

    case GameEndedDrawer: {
        QString text = QString("Конец! Победитель - %1. Загаданное слово - %2")
                               .arg(QString(bArray).split(":")[0])
                               .arg(QString(bArray).split(":")[1]);
        QMessageBox* msgBox = new QMessageBox;
        msgBox->setText(text);
        msgBox->show();

        QString wordToDraw = QString(bArray).split(":")[2];
        ui->statusBarLabel->setText("Игра начата. Слово: " + wordToDraw);
        this->ui->wordInput->setDisabled(true);
        ui->wordInput->setText(wordToDraw);
        ui->sendWordButton->hide();
        this->isDrawer = true;

        this->ui->graphicsView->setInteractive(true);

        ui->graphicsView->scene()->clear();

        break;
    }

    case GameEndedGuesser: {
        QString text = QString("Конец! Победитель - %1. Загаданное слово - %2")
                               .arg(QString(bArray).split(":")[0])
                               .arg(QString(bArray).split(":")[1]);
        QMessageBox* msgBox = new QMessageBox;
        msgBox->setText(text);
        msgBox->show();

        ui->statusBarLabel->setText("Игра начата");
        ui->wordInput->setDisabled(false);
        ui->wordInput->clear();
        ui->sendWordButton->show();
        this->isDrawer = false;

        QBuffer* buffer = new QBuffer(&bArray);
        updateGraphicsView(buffer);

        this->ui->graphicsView->setInteractive(false);

        ui->graphicsView->scene()->clear();

        break;
    }

    case Drawer:{//

        ui->statusBarLabel->setText("Игра начата. Слово: " + QString(bArray));
        ui->graphicsView->scene()->clear();

        QString wordToDraw(bArray);

        qDebug() << "wordToDraw" << wordToDraw;
        this->ui->wordInput->setDisabled(true);
        ui->wordInput->setText(wordToDraw);
        ui->sendWordButton->hide();
        this->isDrawer = true;

        this->ui->graphicsView->setInteractive(true);

        ui->graphicsView->scene()->clear();
        break;
    }
    case Guesser:{//
        ui->statusBarLabel->setText("Игра начата");
        ui->graphicsView->scene()->clear();

        ui->wordInput->setDisabled(false);
        ui->wordInput->clear();
        ui->sendWordButton->show();
        this->isDrawer = false;

        QBuffer* buffer = new QBuffer(&bArray);
        updateGraphicsView(buffer);

        this->ui->graphicsView->setInteractive(false);
        break;
    }
    case WrongAnswer:{//
        qDebug() << "WRONG";
        ui->statusBarLabel->setText("Слово неверное");

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
            header.prepend(QString("messageCode: %1").arg(messageCode).toUtf8());
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
    qDebug() << "updateGraphicsView";
    QByteArray pngData = buffer->buffer();

    QBuffer tbuff;
    tbuff.setData(pngData);
    tbuff.open(QIODevice::ReadOnly);

    tbuff.seek(0);

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

