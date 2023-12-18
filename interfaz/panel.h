#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QPoint>



QT_BEGIN_NAMESPACE
namespace Ui {
class Panel;
}
QT_END_NAMESPACE

class Panel : public QMainWindow
{
    Q_OBJECT

public:
    Panel(QWidget *parent = nullptr);
    ~Panel();
    void limpiar_valores();
    void imprimirCoordenadas();
    //void setupSerial();
    //void readSerialData();
    void Prueba();

protected:
    // Agregamos el manejo del evento de teclado
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Panel *ui;

    // Variables para almacenar las coordenadas del punto
    int puntoX;
    int puntoY;
    //int serial;
    bool btn_sel_presionado = false;
    QVector<QPoint> puntos;  // Declaración del contenedor de puntos

    // Función para mostrar un punto en una QPixmap
    void mostrarPunto();
    //void imprimirCoordenadas();
};

#endif // MAINWINDOW_H
