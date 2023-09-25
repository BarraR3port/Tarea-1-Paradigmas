#include "Vehiculo.h"
#include <iostream>

using namespace std;

Vehiculo::Vehiculo(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, string marca, long long precio, int anio) : numeroMotor(numeroMotor), numeroRuedas(numeroRuedas), tipoCombustible(tipoCombustible), maxLitros(maxLitros), marca(marca), precio(precio), anio(anio) {}

Vehiculo::~Vehiculo()
{
}

int Vehiculo::getNumeroMotor() const
{
    return numeroMotor;
}

int Vehiculo::getNumeroRuedas() const
{
    return numeroRuedas;
}

TipoCombustible Vehiculo::getTipoCombustible() const
{
    return tipoCombustible;
}

int Vehiculo::getMaxLitros() const
{
    return maxLitros;
}

string Vehiculo::getMarca() const
{
    return marca;
}

long long Vehiculo::getPrecio() const
{
    return precio;
}

int Vehiculo::getAnio() const
{
    return anio;
}


string Vehiculo::getTipoCombustibleString() const
{
    if (tipoCombustible == TipoCombustible::Gasolina)
    {
        return "Gasolina";
    }
    else if (tipoCombustible == TipoCombustible::Gas)
    {
        return "Gas";
    }
    else if (tipoCombustible == TipoCombustible::Electrico)
    {
        return "Electrico";
    }
    else
    {
        return "Tipo de combustible no válido";
    }
}
