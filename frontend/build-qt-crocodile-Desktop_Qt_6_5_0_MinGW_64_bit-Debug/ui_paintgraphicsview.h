/********************************************************************************
** Form generated from reading UI file 'paintgraphicsview.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTGRAPHICSVIEW_H
#define UI_PAINTGRAPHICSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintGraphicsView
{
public:

    void setupUi(QWidget *PaintGraphicsView)
    {
        if (PaintGraphicsView->objectName().isEmpty())
            PaintGraphicsView->setObjectName("PaintGraphicsView");
        PaintGraphicsView->resize(400, 300);

        retranslateUi(PaintGraphicsView);

        QMetaObject::connectSlotsByName(PaintGraphicsView);
    } // setupUi

    void retranslateUi(QWidget *PaintGraphicsView)
    {
        PaintGraphicsView->setWindowTitle(QCoreApplication::translate("PaintGraphicsView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaintGraphicsView: public Ui_PaintGraphicsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTGRAPHICSVIEW_H
