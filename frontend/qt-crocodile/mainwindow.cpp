
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintscene.h"
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_sendWordButton_clicked()
{

}


void MainWindow::showWindow() {
    this->show();
}
