#ifndef LOGINMODAL_H
#define LOGINMODAL_H

#include <QWidget>

namespace Ui {
class LoginModal;
}

class LoginModal : public QWidget
{
    Q_OBJECT

public:
    explicit LoginModal(QWidget *parent = nullptr);
    ~LoginModal();
signals:
    void loginedSignal();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginModal *ui;
};

#endif // LOGINMODAL_H
