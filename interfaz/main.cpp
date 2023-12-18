#include "panel.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{     
    QApplication a(argc, argv);
    Panel *panel = new Panel();
    Menu *menu = new Menu(panel);

 // panel->setupSerial();
    panel->show();
    menu->show();
    return a.exec();
}
