#pragma once

#include <iostream>
#include <string>
#include "Vehiculo.h"

using namespace std;

class Camion : public Vehiculo {
private:
    int numeroPuertas;

public:
    Camion(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, string marca,
           long long precio, int anio, int numeroPuertas);

    int getNumeroPuertas() const;

    void imprimir() override;

    long long calcularPrecioFinal() override;

    string getTipo() override;
};