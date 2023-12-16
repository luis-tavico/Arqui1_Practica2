#ifndef MENU_H
#define MENU_H

#include "panel.h"
#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(Panel *panel, QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_btn1_iniciar_clicked();

    void on_btn2_volver_clicked();

    void on_btn4_limpiar_clicked();

    void on_btn5_acercade_clicked();

    void on_btn6_salir_clicked();


private:
    Ui::Menu *ui;
    Panel *panel;
};

#endif // MENU_H
