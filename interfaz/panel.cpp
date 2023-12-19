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
    setupSerial();
    readSerialData();
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

void Panel::buscar_boton(const QString &boton_presionado) {
    //boton_presionado.replace("\r\n", "");
    int paso = 10;

    //qDebug() << "Boton después de eliminar \\r\\n:" << boton_presionado;
    QString boton_modificado = boton_presionado;
    boton_modificado.replace("\r\n", "");
    //qDebug() << "Boton después de eliminar \\r\\n:" << cadena;

    if ("U" == boton_modificado) {
        qDebug() << "El boton presionado es:" << boton_modificado;
        puntoY -= paso;
    } else if ("D" == boton_modificado) {
        qDebug() << "El boton presionado es:" << boton_modificado;
        puntoY += paso;
    } else if ("R" == boton_modificado) {
        qDebug() << "El boton presionado es:" << boton_modificado;
        puntoX += paso;
    } else if ("L" == boton_modificado) {
        qDebug() << "El boton presionado es:" << boton_modificado;
        puntoX -= paso;
    } else if ("S" == boton_modificado) {
        qDebug() << "El boton presionado es:" << boton_modificado;
        btn_sel_presionado = !btn_sel_presionado;
    } else if ("M" == boton_modificado) {
        qDebug() << "El boton presionado es:" << boton_modificado;

    } else if ("" == boton_modificado) {
        qDebug() << "Tecla desconocida" << boton_modificado;
      ;
    }

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

void Panel::setupSerial() {
    serial.setPortName("COM4"); // Reemplaza con el nombre de tu puerto serie
    serial.setBaudRate(QSerialPort::Baud9600); // Establece la velocidad de comunicación
    // Más configuraciones según tus necesidades...

    if (serial.open(QIODevice::ReadOnly)) {
        connect(&serial, &QSerialPort::readyRead, this, &Panel::readSerialData);
        qDebug() << "Puerto serie abierto";
    } else {
        qDebug() << "Error al abrir el puerto serie: " << serial.errorString();
    }
}

void Panel::readSerialData() {
    QByteArray data = serial.readAll();
    qDebug() << "Datos recibidos desde Arduino: " << data;
    // Aquí puedes procesar los datos recibidos desde Arduino

    buscar_boton(data);


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
