#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class TipoCombustible
{
    Gasolina,
    Gas,
    Electrico
};

class Vehiculo
{
protected:
    int numeroMotor;
    int numeroRuedas;
    TipoCombustible tipoCombustible;
    int maxLitros;
    std::string marca;
    long long precio;
    int anio;

public:
    Vehiculo(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, std::string marca, long long precio, int anio);

    virtual ~Vehiculo();

    int getNumeroMotor() const;

    int getNumeroRuedas() const;

    TipoCombustible getTipoCombustible() const;

    string getTipoCombustibleString() const;

    int getMaxLitros() const;

    string getMarca() const;

    long long getPrecio() const;

    int getAnio() const;

    virtual void imprimir() = 0;

    virtual long long calcularPrecioFinal() = 0;

    virtual string getTipo() = 0;
};