#include "Vehiculo.h"
#include <iostream>

using namespace std;

Vehiculo::Vehiculo(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, string marca, long long precio, int anio) : numeroMotor(numeroMotor), numeroRuedas(numeroRuedas), tipoCombustible(tipoCombustible), maxLitros(maxLitros), marca(marca), precio(precio), anio(anio) {}

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

void Vehiculo::setNumeroMotor(int numeroMotor)
{
    this->numeroMotor = numeroMotor;
}

void Vehiculo::setNumeroRuedas(int numeroRuedas)
{
    this->numeroRuedas = numeroRuedas;
}

void Vehiculo::setTipoCombustible(TipoCombustible tipoCombustible)
{
    this->tipoCombustible = tipoCombustible;
}

void Vehiculo::setMaxLitros(int maxLitros)
{
    this->maxLitros = maxLitros;
}

void Vehiculo::setMarca(string marca)
{
    this->marca = marca;
}

void Vehiculo::setPrecio(long long precio)
{
    this->precio = precio;
}

void Vehiculo::setAnio(int anio)
{
    this->anio = anio;
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

void Vehiculo::imprimir()
{
    cout << "Numero de motor: " << numeroMotor << endl;
    cout << "Numero de ruedas: " << numeroRuedas << endl;
    cout << "Tipo de combustible: " << getTipoCombustibleString() << endl;
    cout << "Maximo de litros: " << maxLitros << endl;
    cout << "Marca: " << marca << endl;
    cout << "Precio: " << precio << endl;
    cout << "Anio: " << anio << endl;
}

long long Vehiculo::calcularPrecioFinal()
{
    return precio;
}