#include <iostream>
#include <limits>
#include <vector>
#include "Cliente.h"
#include "Vehiculo.h"
#include "Auto.h"
using namespace std;

Cliente *cliente = NULL;
vector<Vehiculo *> vehiculos;

void agregarAuto()
{
    int numeroMotor, numeroRuedas, maxLitros, anio, numeroPuertas;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << "-------------------" << endl;
    cout << "Ingresa el numero de motor" << endl;
    cin >> numeroMotor;
    cout << "Ingresa el numero de ruedas" << endl;
    cin >> numeroRuedas;
    cout << "Ingresa el tipo de combustible" << endl;
    cout << "1) Gasolina" << endl;
    cout << "2) Gas" << endl;
    cout << "3) Electrico" << endl;
    int tipoCombustibleVal = 1;
    cin >> tipoCombustibleVal;
    if (tipoCombustibleVal == 1)
    {
        tipoCombustible = TipoCombustible::Gas;
    }
    else if (tipoCombustibleVal == 2)
    {
        tipoCombustible = TipoCombustible::Gas;
    }
    else if (tipoCombustibleVal == 3)
    {
        tipoCombustible = TipoCombustible::Electrico;
    }
    else
    {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    cout << "Ingresa el maximo de litros" << endl;
    cin >> maxLitros;
    cout << "Ingresa la marca" << endl;
    cin >> marca;
    cout << "Ingresa el precio" << endl;
    cin >> precio;
    cout << "Ingresa el anio" << endl;
    cin >> anio;
    cout << "Ingresa el numero de puertas" << endl;
    cin >> numeroPuertas;
    Vehiculo *autoVehiculo = new Auto(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio, numeroPuertas);
    vehiculos.push_back(autoVehiculo);
    cout << "-------------------" << endl;
    cout << "Auto agregado correctamente" << endl;
    cout << "Autos actuales: " << vehiculos.size() << endl;
    cout << "-------------------" << endl;
    return;
}

void mostrarVehiculos()
{
    cout << "-------------------" << endl;
    cout << "Cliente Actual: " << endl;
    cout << "Nombre: " << cliente->getNombre() << endl;
    cout << "Rut: " << cliente->getRut() << endl;
    cout << "-------------------" << endl;
    cout << "Vehiculos" << endl;
    cout << "-------------------" << endl;
    for (size_t i = 0; i < vehiculos.size(); i++)
    {
        cout << "-------------------" << endl;
        cout << "Vehiculo " << i << endl;
        cout << "-------------------" << endl;
        cout << "Numero de motor: " << vehiculos[i]->getNumeroMotor() << endl;
        cout << "Numero de ruedas: " << vehiculos[i]->getNumeroRuedas() << endl;
        cout << "Tipo de combustible: " << vehiculos[i]->getTipoCombustibleString() << endl;
        cout << "Maximo de litros: " << vehiculos[i]->getMaxLitros() << endl;
        cout << "Marca: " << vehiculos[i]->getMarca() << endl;
        cout << "Precio: " << vehiculos[i]->getPrecio() << endl;
        cout << "Anio: " << vehiculos[i]->getAnio() << endl;
        cout << "Valor Original:" << vehiculos[i]->getPrecio() << endl;
        cout << "Valor Final:" << vehiculos[i]->calcularPrecioFinal() << endl;
    }
    return;
}

void menu(void)
{
    int opcion = 0;

    while (opcion != 5)
    {
        cout << "1. Ventas de vehiculos a clientes" << endl;
        cout << "2. Promedio de ventas" << endl;
        cout << "3. Cantidad de vehiculos comprados" << endl;
        cout << "4. Ventas de vehiculos" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion : ";
        cin >> opcion;
        // Verificar si la entrada es válida
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            continue;
        }

        if (opcion == 1)
        {
            int opcion_venta = -1;
            while (opcion_venta != 0)
            {
                if (cliente == NULL)
                {
                    string nombreCliente, rutCliente;
                    cout << "No hay clientes registrados" << endl;
                    cout << "-------------------" << endl;
                    cout << "Ingresa el nombre del cliente" << endl;
                    cin >> nombreCliente;
                    cout << "Ingresa el rut del cliente" << endl;
                    cin >> rutCliente;
                    cliente = new Cliente(nombreCliente, rutCliente);
                    cout << "-------------------" << endl;
                    cout << "Cliente Actual: " << cliente->getRut() << endl;
                }
                else
                {
                    cout << "-------------------" << endl;
                    cout << "Cliente Actual: " << endl;
                }
                cout << "Nombre: " << cliente->getNombre() << endl;
                cout << "Rut: " << cliente->getRut() << endl;
                cout << "-------------------" << endl;
                cout << "[Menu]" << endl;
                cout << "1) Agregar automovil" << endl;
                cout << "2) Agregar moto" << endl;
                cout << "3) Agregar camioneta" << endl;
                cout << "4) Mostrar Vehiculos" << endl;
                cout << "0) Salir" << endl;
                cout << "-------------------" << endl;
                cin >> opcion_venta;
                if (opcion_venta == 0)
                {
                    cout << "Saliste correctamente del programa" << endl;
                }
                else if (opcion_venta == 1)
                {
                    agregarAuto();
                }
                else if (opcion_venta == 4)
                {
                    mostrarVehiculos();
                }
                else
                {
                    cout << "Opcion no valida" << endl;
                }
            }
        }
        else if (opcion == 2)
        {
            int op = 0;
            while (op != 5)
            {
                cout << "1. Promedio de venta de autos" << endl;
                cout << "2. Promedio de venta de motos" << endl;
                cout << "3. Promedio de venta de camiones" << endl;
                cout << "4. Promedio de ventas totales" << endl;
                cout << "5. Volver al menu principal" << endl;
                cout << "Seleccione una opcion : ";
                cin >> op;

                if (op == 1)
                {
                    cout << "Promedio de venta de autos" << endl;
                }
                else if (op == 2)
                {
                    cout << "Promedio de venta de motos" << endl;
                }
                else if (op == 3)
                {
                    cout << "Promedio de venta de camiones" << endl;
                }
                else if (op == 4)
                {
                    cout << "Promedio de ventas totales" << endl;
                }
                else if (op == 5)
                {
                    cout << "Volviendo al menu principal." << endl;
                }
                else
                {
                    cout << "Opcion no valida, ingresa una valida porfavor..." << endl;
                }
            }
        }
        else if (opcion == 3)
        {
            int op = 0;
            while (op != 5)
            {
                cout << "1. Cantidad de autos comprados" << endl;
                cout << "2. Cantidad de motos compradas" << endl;
                cout << "3. Cantidad de camiones comprados" << endl;
                cout << "4. Cantidad de vehiculos comprados" << endl;
                cout << "5. Volver al menu principal" << endl;
                cout << "Seleccione una opcion :  ";
                cin >> op;

                if (op == 1)
                {
                    cout << "Cantidad de autos comprados" << endl;
                }
                else if (op == 2)
                {
                    cout << "Cantidad de motos compradas" << endl;
                }
                else if (op == 3)
                {
                    cout << "Cantidad de camiones comprados" << endl;
                }
                else if (op == 4)
                {
                    cout << "Cantidad de vehiculos" << endl;
                }
                else if (op == 5)
                {
                    cout << "Volviendo al menu principal." << endl;
                }
                else
                {
                    cout << "Opcion no valida, ingresa una valida porfavor..." << endl;
                }
            }
        }
        else if (opcion == 4)
        {
            int op = 0;
            while (op != 5)
            {
                cout << "1. Ventas de autos" << endl;
                cout << "2. Ventas de motos" << endl;
                cout << "3. Ventas de camiones" << endl;
                cout << "4. Ventas totales" << endl;
                cout << "5. Volver al menu principal" << endl;
                cout << "Seleccione una opcion :  ";
                cin >> op;

                if (op == 1)
                {
                    cout << "Ventas de autos" << endl;
                }
                else if (op == 2)
                {
                    cout << "Ventas de motos" << endl;
                }
                else if (op == 3)
                {
                    cout << "Ventas de camiones" << endl;
                }
                else if (op == 4)
                {
                    cout << "Ventas totales" << endl;
                }
                else if (op == 5)
                {
                    cout << "Volviendo al menu principal." << endl;
                }
                else
                {
                    cout << "Opcion no valida, ingresa una valida porfavor..." << endl;
                }
            }
        }
        else if (opcion == 5)
        {
            cout << "Saliendo del programa." << endl;
        }
        else
        {
            cout << "Esa opcion no es valida, ingresa una opcion valida....." << endl;
        }
    }
    return;
}

int main(void)
{
    // For Testing
    cliente = new Cliente("Bruno", "21424401-2");
    menu();
    cout << "-------------------" << endl;
    return 0;
}