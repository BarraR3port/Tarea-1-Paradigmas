#include "Vehiculo.h"
#include <iostream>
#include "Auto.h"

using namespace std;

Auto::Auto(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, string marca, long long precio, int anio, int numeroPuertas) : Vehiculo(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio), numeroPuertas(numeroPuertas)
{
}

int Auto::getNumeroPuertas() const
{
    return numeroPuertas;
}

void Auto::imprimir()
{
    cout << "-------------------" << endl;
    cout << "Numero de motor: " << numeroMotor << endl;
    cout << "Numero de ruedas: " << numeroRuedas << endl;
    cout << "Tipo de combustible: " << getTipoCombustibleString() << endl;
    cout << "Maximo de litros: " << maxLitros << endl;
    cout << "Marca: " << marca << endl;
    cout << "Precio: " << precio << endl;
    cout << "Anio: " << anio << endl;
    cout << "Numero de puertas: " << numeroPuertas << endl;
    cout << "-------------------" << endl;
}

long long Auto::calcularPrecioFinal()
{
    long long precioFinal = this->precio;

    // Aplicar descuentos por año de fabricación
    if (anio < 2000) {
        precioFinal *= 0.5;
    } else if (anio >= 2000 && anio <= 2017) {
        precioFinal *= 0.7;
    } else {
        precioFinal *= 0.85;
    }

    // Aumentar el precio si es eléctrico o a gas
    if (tipoCombustible == TipoCombustible::Electrico || tipoCombustible == TipoCombustible::Gas) {
        precioFinal *= 1.2;
    }
    return precioFinal;
}

string Auto::getTipo()
{
    return "Auto";
}