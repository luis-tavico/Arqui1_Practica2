#include <iostream>
#include <Windows.h>

int main() {
    // Nombre del puerto serie, por ejemplo, "COM5"
    const wchar_t* portName = L"COM5";

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