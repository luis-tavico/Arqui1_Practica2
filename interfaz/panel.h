#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QPoint>
#include <QSerialPort>


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
    void setupSerial();
    void readSerialData();
    //void buscar_boton(const QString &boton_presionado);

protected:
    // Manejo del evento de teclado
    void keyPressEvent(QKeyEvent *event);
    void buscar_boton(const QString &boton_presionado);


private:
    Ui::Panel *ui;

    // Variables para almacenar las coordenadas del punto
    int puntoX;
    int puntoY;
    QSerialPort serial;
    bool btn_sel_presionado = false;
    QVector<QPoint> puntos;  // Declaración del contenedor de puntos

    // Función para mostrar un punto en una QPixmap
    void mostrarPunto();
    //void imprimirCoordenadas();
};

#endif // PANEL_H
