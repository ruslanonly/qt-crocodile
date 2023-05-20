/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *statusBarLayout;
    QLabel *label;
    QLabel *statusBarLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *wordLabel;
    QLineEdit *wordInput;
    QPushButton *sendWordButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *reconnectButton;
    QGraphicsView *graphicsView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(835, 649);
        MainWindow->setMaximumSize(QSize(16777215, 649));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        statusBarLayout = new QVBoxLayout();
        statusBarLayout->setObjectName("statusBarLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font: 700 9.5pt \"Segoe UI\";\n"
"color: black;"));

        statusBarLayout->addWidget(label);

        statusBarLabel = new QLabel(centralwidget);
        statusBarLabel->setObjectName("statusBarLabel");
        statusBarLabel->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusBarLabel->sizePolicy().hasHeightForWidth());
        statusBarLabel->setSizePolicy(sizePolicy);
        statusBarLabel->setStyleSheet(QString::fromUtf8("border: 1.5px solid rgba(4, 102, 200, 0.5);\n"
"color: black;\n"
"border-radius: 5px;\n"
"padding: 3px"));

        statusBarLayout->addWidget(statusBarLabel);


        verticalLayout->addLayout(statusBarLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        wordLabel = new QLabel(centralwidget);
        wordLabel->setObjectName("wordLabel");

        verticalLayout_2->addWidget(wordLabel);

        wordInput = new QLineEdit(centralwidget);
        wordInput->setObjectName("wordInput");
        wordInput->setMinimumSize(QSize(200, 0));

        verticalLayout_2->addWidget(wordInput);


        verticalLayout->addLayout(verticalLayout_2);

        sendWordButton = new QPushButton(centralwidget);
        sendWordButton->setObjectName("sendWordButton");

        verticalLayout->addWidget(sendWordButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        reconnectButton = new QPushButton(centralwidget);
        reconnectButton->setObjectName("reconnectButton");

        verticalLayout->addWidget(reconnectButton);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(600, 600));
        graphicsView->setMaximumSize(QSize(600, 600));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setInteractive(false);
        graphicsView->setSceneRect(QRectF(0, 0, 600, 600));

        gridLayout->addWidget(graphicsView, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201 \320\270\320\263\321\200\321\213", nullptr));
        statusBarLabel->setText(QString());
        wordLabel->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\262\320\276", nullptr));
        sendWordButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        reconnectButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
