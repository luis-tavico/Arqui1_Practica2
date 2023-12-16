#include "panel.h"
#include "menu.h"
#include "./ui_panel.h"
#include <QSize>

Panel::Panel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Panel)
    , puntoX(500)
    , puntoY(290)
{
    ui->setupUi(this);
    setMinimumSize(QSize(1000, 600));
    setMaximumSize(QSize(1000, 600));
    setWindowTitle("AppDraw");
    // Llama a la función para mostrar el punto
    mostrarPunto();
}

Panel::~Panel()
{
    delete ui;
}

void Panel::mostrarPunto()
{
    QPixmap pixmap(1000, 580);
    pixmap.fill(Qt::black);

    // Crea un objeto QPainter para dibujar en la QPixmap
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);

    // Dibujar todos los puntos en el contenedor
    for (const auto &point : puntos) {
        painter.drawRect(point.x(), point.y(), 10, 10);
    }

    // Dibuja un punto de 10x10 pixeles (posicion actual)
    painter.fillRect(puntoX, puntoY, 10, 10, Qt::gray);

    // Crear una etiqueta y establecer la QPixmap como su imagen
    QLabel *label = new QLabel(this);
    label->setPixmap(pixmap);

    // Añadir la etiqueta al diseño de la ventana principal
    setCentralWidget(label);
}

void Panel::keyPressEvent(QKeyEvent *event)
{
    // Tamaño del paso al mover el punto
    int paso = 10;

    // Mover el punto según la tecla presionada
    switch (event->key()) {
    case Qt::Key_Left:
        puntoX -= paso;
        break;
    case Qt::Key_Right:
        puntoX += paso;
        break;
    case Qt::Key_Up:
        puntoY -= paso;
        break;
    case Qt::Key_Down:
        puntoY += paso;
        break;
    case Qt::Key_Return:
        btn_sel_presionado = !btn_sel_presionado;
        break;
    case Qt::Key_Space:
    {
        Menu *menu = new Menu(this);
        menu->show();
        break;
    }
    default:
        // No hace nada si se presiona otra tecla
        return;
    }

    // Imprimir los valores de las coordenadas
    //imprimirCoordenadas();

    // Establece coordenadas dentro de los límites de la ventana
    puntoX = qBound(0, puntoX, 990);
    puntoY = qBound(0, puntoY, 570);

    if (btn_sel_presionado) {
        // Verificar si existe interseccion
        for (auto it = puntos.begin(); it != puntos.end(); ++it) {
            if (it->x() == puntoX && it->y() == puntoY) {
                qDebug() << "Interseccion";
                break; // Terminar el bucle si se encuentra el valor
            }
        }
        // Agregar el nuevo punto al contenedor
        puntos.push_back(QPoint(puntoX, puntoY));
    }

    // Muestra todos los puntos dibujados
    mostrarPunto();
}

void Panel::imprimirCoordenadas()
{
    qDebug() << "Coordenadas del punto: (" << puntoX << ", " << puntoY << ")";
}

void Panel::limpiar_valores()
{
    puntoX = 500;
    puntoY = 290;
    puntos.clear();
    mostrarPunto();
}
