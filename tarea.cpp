#include <iostream>
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
    int opcion = -1;
    while (opcion != 0)
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
        cin >> opcion;
        if (opcion == 0)
        {
            cout << "Saliste correctamente del programa" << endl;
        }
        else if (opcion == 1)
        {
            agregarAuto();
        }
        else if (opcion == 4)
        {
            mostrarVehiculos();
        }
        else
        {
            cout << "Opcion no valida" << endl;
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