#include <iostream>
using namespace std;

void menu(void)
{
    bool continuar = true;
    while (continuar)
    {
        int opcion;
        cout << "[Menu]" << endl;
        cout << "1) Agregar vehiculo" << endl;
        cout << "2) Agregar automovil" << endl;
        cout << "3) Agregar camioneta" << endl;
        cout << "0) Salir" << endl;

        if (opcion == 0)
        {
            cout << "Saliste correctamente del programa" << endl;
            continuar = false;
        }
    }
    return;
}

int main(void)
{
    menu();
    return 0;
}