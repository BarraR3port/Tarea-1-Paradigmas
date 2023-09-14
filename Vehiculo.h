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

    int getNumeroMotor() const;

    int getNumeroRuedas() const;

    TipoCombustible getTipoCombustible() const;

    string getTipoCombustibleString() const;

    int getMaxLitros() const;

    string getMarca() const;

    long long getPrecio() const;

    int getAnio() const;

    void setNumeroMotor(int numeroMotor);

    void setNumeroRuedas(int numeroRuedas);

    void setTipoCombustible(TipoCombustible tipoCombustible);

    void setMaxLitros(int maxLitros);

    void setMarca(std::string marca);

    void setPrecio(long long precio);

    void setAnio(int anio);

    virtual void imprimir() = 0;

    long long calcularPrecioFinal();
};