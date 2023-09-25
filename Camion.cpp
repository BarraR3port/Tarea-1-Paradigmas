#include "Vehiculo.h"
#include <iostream>
#include "Camion.h"
using namespace std;

Camion::Camion(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, string marca, long long precio, int anio, int numeroPuertas) : Vehiculo(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio), numeroPuertas(numeroPuertas)
{
}

int Camion::getNumeroPuertas() const
{
    return numeroPuertas;
}

void Camion::imprimir()
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

long long Camion::calcularPrecioFinal()
{
    double precioFinal = precio; // Empezamos con el precio base

    // Descuentos basados en el anio de fabricación
    if (anio < 2000)
    {
        precioFinal *= 0.50;
    }
    else if (anio >= 2000 && anio <= 2017)
    {
        precioFinal *= 0.70;
    }
    else if (anio > 2017)
    {
        precioFinal *= 0.85;
    }

    // Incremento basado en el tipo de combustible
    if (tipoCombustible == TipoCombustible::Electrico || tipoCombustible == TipoCombustible::Gas)
    {
        precioFinal *= 1.20;
    }

    return static_cast<long long>(precioFinal); // Convertimos a long long antes de devolver
}

string Camion::getTipo()
{
    return "Camion";
}