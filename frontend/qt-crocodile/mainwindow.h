
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <paintscene.h>
#include <QTimer>
#include <QBuffer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

public slots:
    void showWindow(QString Username);

    void readSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    void discardSocket();

private slots:
    void on_sendWordButton_clicked();
    void onMouseUpSlot();

    void on_reconnectButton_clicked();

private:
    QBuffer* exportGraphicsView();
    void updateGraphicsView(QBuffer* buffer);
    void openConnection();

    void sendMessage(MessageCodes messageCode, QByteArray qArray);

    Ui::MainWindow *ui;

    QString Username;
    bool isDrawer;
    PaintScene *scene;

    QTcpSocket* socket;
};

#endif // MAINWINDOW_H
