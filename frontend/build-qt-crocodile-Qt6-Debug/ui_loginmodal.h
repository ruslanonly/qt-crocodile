/********************************************************************************
** Form generated from reading UI file 'loginmodal.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINMODAL_H
#define UI_LOGINMODAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginModal
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *formLayout_2;
    QVBoxLayout *inputsLayout_2;
    QVBoxLayout *inputGroup_3;
    QLabel *usernameLabel_2;
    QLineEdit *usernameInput;
    QSpacerItem *verticalSpacer_3;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *LoginModal)
    {
        if (LoginModal->objectName().isEmpty())
            LoginModal->setObjectName("LoginModal");
        LoginModal->resize(400, 200);
        LoginModal->setMaximumSize(QSize(16777215, 200));
        verticalLayout = new QVBoxLayout(LoginModal);
        verticalLayout->setSpacing(30);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(LoginModal);
        label->setObjectName("label");
        label->setAcceptDrops(false);
        label->setStyleSheet(QString::fromUtf8("font-weight: 600; font-size: 10pt; color: black;"));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        formLayout_2 = new QVBoxLayout();
        formLayout_2->setSpacing(20);
        formLayout_2->setObjectName("formLayout_2");
        inputsLayout_2 = new QVBoxLayout();
        inputsLayout_2->setSpacing(10);
        inputsLayout_2->setObjectName("inputsLayout_2");
        inputGroup_3 = new QVBoxLayout();
        inputGroup_3->setSpacing(5);
        inputGroup_3->setObjectName("inputGroup_3");
        usernameLabel_2 = new QLabel(LoginModal);
        usernameLabel_2->setObjectName("usernameLabel_2");

        inputGroup_3->addWidget(usernameLabel_2);

        usernameInput = new QLineEdit(LoginModal);
        usernameInput->setObjectName("usernameInput");

        inputGroup_3->addWidget(usernameInput);


        inputsLayout_2->addLayout(inputGroup_3);


        formLayout_2->addLayout(inputsLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->addItem(verticalSpacer_3);

        loginButton = new QPushButton(LoginModal);
        loginButton->setObjectName("loginButton");
        loginButton->setCursor(QCursor(Qt::PointingHandCursor));

        formLayout_2->addWidget(loginButton);


        horizontalLayout_2->addLayout(formLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalLayout_2->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(LoginModal);

        QMetaObject::connectSlotsByName(LoginModal);
    } // setupUi

    void retranslateUi(QWidget *LoginModal)
    {
        LoginModal->setWindowTitle(QCoreApplication::translate("LoginModal", "Form", nullptr));
        label->setText(QCoreApplication::translate("LoginModal", "\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214 \320\262 \320\272\321\200\320\276\320\272\320\276\320\264\320\270\320\273", nullptr));
        usernameLabel_2->setText(QCoreApplication::translate("LoginModal", "\320\235\320\270\320\272\320\275\320\265\320\271\320\274", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginModal", "\320\222\320\276\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginModal: public Ui_LoginModal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINMODAL_H
