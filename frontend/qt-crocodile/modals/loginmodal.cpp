#include "loginmodal.h"
#include "ui_loginmodal.h"

LoginModal::LoginModal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginModal)
{
    ui->setupUi(this);
}

LoginModal::~LoginModal()
{
    delete ui;
}

void LoginModal::on_loginButton_clicked()
{
    emit this->loginedSignal(this->ui->usernameInput->text());
    this->close();
}

