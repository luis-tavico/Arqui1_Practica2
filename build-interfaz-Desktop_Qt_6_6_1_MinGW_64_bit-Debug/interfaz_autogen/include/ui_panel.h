/********************************************************************************
** Form generated from reading UI file 'panel.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Panel
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Panel)
    {
        if (Panel->objectName().isEmpty())
            Panel->setObjectName("Panel");
        Panel->resize(1000, 600);
        centralwidget = new QWidget(Panel);
        centralwidget->setObjectName("centralwidget");
        Panel->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Panel);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        Panel->setMenuBar(menubar);
        statusbar = new QStatusBar(Panel);
        statusbar->setObjectName("statusbar");
        Panel->setStatusBar(statusbar);

        retranslateUi(Panel);

        QMetaObject::connectSlotsByName(Panel);
    } // setupUi

    void retranslateUi(QMainWindow *Panel)
    {
        Panel->setWindowTitle(QCoreApplication::translate("Panel", "Panel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Panel: public Ui_Panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
