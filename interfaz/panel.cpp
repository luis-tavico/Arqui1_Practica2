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
    Prueba();
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

void Panel::Prueba(){

    const wchar_t* portName = L"COM4";

    // Abrir el puerto serie
    HANDLE hSerial = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error al abrir el puerto serie." << std::endl;
        return 1;
    }

    // Configurar parámetros del puerto serie
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al obtener los parámetros del puerto serie." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al establecer los parámetros del puerto serie." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Buffer para almacenar los datos recibidos
    byte buffer[256];
    DWORD bytesRead;

    // Bucle para recibir datos continuamente
    while (true) {
        // Leer datos desde el puerto serie
        if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
            // Mostrar los datos recibidos en la consola en formato hexadecimal
            std::cout << "Datos recibidos desde Arduino (hex): ";
            for (DWORD i = 0; i < bytesRead; ++i) {
                std::cout << std::hex << static_cast<int>(buffer[i]) << " ";
            }
            std::cout << std::endl;

            // Puedes intentar interpretar los bytes como un número entero
            if (bytesRead == sizeof(int)) {
                int numeroRecibido;
                memcpy(&numeroRecibido, buffer, sizeof(numeroRecibido));

                // Mostrar el número en formato decimal
                std::cout << "Número recibido desde Arduino (decimal): " << numeroRecibido << std::endl;
            }
            else {
                std::cerr << "Error en el tamaño de los datos recibidos desde el puerto serie." << std::endl;
            }
        }
        else {
            std::cerr << "Error al leer datos desde el puerto serie." << std::endl;
            break;  // Salir del bucle si hay un error de lectura
        }
    }




    // Cierra el puerto serie
    CloseHandle(hSerial);

    return 0;

}

/*void Panel::setupSerial()
{
    serial.begin(9600); // Velocidad de comunicación serial (debe coincidir con la configuración del Arduino)
}

void Panel::readSerialData()
{
    if (serial.available() > 0) {
        char receivedChar = serial.read();
        int paso = 10;

        switch (receivedChar) {
        case 'L': // Botón izquierdo en Arduino
            puntoX -= paso;
            break;
        case 'R': // Botón derecho en Arduino
            puntoX += paso;
            break;
        case 'U': // Botón arriba en Arduino
            puntoY -= paso;
            break;
        case 'D': // Botón abajo en Arduino
            puntoY += paso;
            break;
        case 'S': // Botón de selección en Arduino
            btn_sel_presionado = !btn_sel_presionado;
            break;
        }
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
}*/

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
