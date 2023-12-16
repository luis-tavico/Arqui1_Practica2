#include "menu.h"
#include "panel.h"
#include "ui_menu.h"
#include <QMessageBox>

Menu::Menu(Panel *panel, QWidget *parent)
    : QDialog(parent)
    , panel(panel)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle("Menu Principal");
    // Elimina la equis
    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btn1_iniciar_clicked()
{
    close();
    panel->iniciar();
}


void Menu::on_btn2_volver_clicked()
{
    close();
}


void Menu::on_btn4_limpiar_clicked()
{
    close();
    panel->limpiar();
}


void Menu::on_btn5_acercade_clicked()
{
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setWindowTitle("Acerca De");
    messageBox.setText("Desarrollado por: \n"
                       "202010316 - Joseph Jeferson Marroquin Monroy\n"
                       "201907483 - David Eduardo Lopez Morales\n"
                       "202000562 - Pedro Luis Pu Tavico\n"
                       "201903873 - Joaquin Emmanuel Aldair Coromac Huezo\n"
                       "201902128 - Jorge Mario Cano Blanco\n"
                       "202003220 - Marco Antonio Solis Gonzalez\n"
                       "201807411 - Pablo Daniel Fernandez Chacon\n"
                       "201907156 - Marcos Arnoldo Iztep Ixmay\n\n"
                       "Esta aplicacion fue desarrollada en el IDE Visual Studio Code.");
    messageBox.addButton(QMessageBox::Ok);
    messageBox.exec();
}


void Menu::on_btn6_salir_clicked()
{
    QApplication::quit();
}
