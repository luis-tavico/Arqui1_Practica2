/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QPushButton *btn1_iniciar;
    QPushButton *btn2_volver;
    QPushButton *btn3_vibrar;
    QPushButton *btn4_limpiar;
    QPushButton *btn5_acercade;
    QPushButton *btn6_salir;
    QLabel *label;

    void setupUi(QDialog *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(451, 478);
        btn1_iniciar = new QPushButton(Menu);
        btn1_iniciar->setObjectName("btn1_iniciar");
        btn1_iniciar->setGeometry(QRect(40, 60, 371, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(11);
        btn1_iniciar->setFont(font);
        btn2_volver = new QPushButton(Menu);
        btn2_volver->setObjectName("btn2_volver");
        btn2_volver->setGeometry(QRect(40, 130, 371, 41));
        btn2_volver->setFont(font);
        btn3_vibrar = new QPushButton(Menu);
        btn3_vibrar->setObjectName("btn3_vibrar");
        btn3_vibrar->setGeometry(QRect(40, 200, 371, 41));
        btn3_vibrar->setFont(font);
        btn4_limpiar = new QPushButton(Menu);
        btn4_limpiar->setObjectName("btn4_limpiar");
        btn4_limpiar->setGeometry(QRect(40, 270, 371, 41));
        btn4_limpiar->setFont(font);
        btn5_acercade = new QPushButton(Menu);
        btn5_acercade->setObjectName("btn5_acercade");
        btn5_acercade->setGeometry(QRect(40, 340, 371, 41));
        btn5_acercade->setFont(font);
        btn6_salir = new QPushButton(Menu);
        btn6_salir->setObjectName("btn6_salir");
        btn6_salir->setGeometry(QRect(40, 410, 371, 41));
        btn6_salir->setFont(font);
        label = new QLabel(Menu);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 10, 371, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font1.setPointSize(12);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QDialog *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Dialog", nullptr));
        btn1_iniciar->setText(QCoreApplication::translate("Menu", "Iniciar Panel", nullptr));
        btn2_volver->setText(QCoreApplication::translate("Menu", "Volver a Panel", nullptr));
        btn3_vibrar->setText(QCoreApplication::translate("Menu", "Vibrar", nullptr));
        btn4_limpiar->setText(QCoreApplication::translate("Menu", "Limpiar Pantalla", nullptr));
        btn5_acercade->setText(QCoreApplication::translate("Menu", "Acerca De", nullptr));
        btn6_salir->setText(QCoreApplication::translate("Menu", "Salir", nullptr));
        label->setText(QCoreApplication::translate("Menu", "Seleccione Una Opcion:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
