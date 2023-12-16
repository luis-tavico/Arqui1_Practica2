#include "panel.h"
#include "menu.h"
#include "./ui_panel.h"
#include <QSize>

Panel::Panel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Panel)
    , puntoX(400)
    , puntoY(260)
{
    ui->setupUi(this);
    setMinimumSize(QSize(800, 550));
    setMaximumSize(QSize(800, 550));
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
    QPixmap pixmap(800, 520);
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

    // Establece coordenadas dentro de los límites de la ventana
    puntoX = qBound(0, puntoX, 790);
    puntoY = qBound(0, puntoY, 510);

    if (btn_sel_presionado) {
        // Agregar el nuevo punto al contenedor
        puntos.push_back(QPoint(puntoX, puntoY));
    }

    // Muestra todos los puntos dibujados
    mostrarPunto();
}

void Panel::imprimirCoordenadas()
{
    // Utilizar qDebug() para imprimir valores en la consola
    //qDebug() << "Coordenadas del punto: (" << puntoX << ", " << puntoY << ")";
    qDebug() << "Accediendo desde otra ventana";
}

void Panel::iniciar()
{
    puntoX = 400;
    puntoY = 260;
    puntos.clear();
    mostrarPunto();
}

void Panel::limpiar()
{
    puntoX = 400;
    puntoY = 260;
    puntos.clear();
    mostrarPunto();
}
