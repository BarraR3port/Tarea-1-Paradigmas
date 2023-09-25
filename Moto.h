#pragma once

#include <iostream>
#include <string>
#include "Vehiculo.h"

using namespace std;

class Moto : public Vehiculo {

public:
    Moto(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, string marca,
         long long precio, int anio);

    void imprimir() override;

    long long calcularPrecioFinal() override;

    string getTipo() override;
};