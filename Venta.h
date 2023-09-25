#pragma once
#include <iostream>
#include "Vehiculo.h"
#include "Cliente.h"

using namespace std;

class Venta
{
private:
    Vehiculo &vehiculo;
    Cliente &cliente;
    int id;

public:
    Venta(Vehiculo &vehiculo, Cliente &cliente);

    Cliente& getCliente() const;

    Vehiculo& getVehiculo() const;

    int getId();

    Venta(Vehiculo &vehiculo, Cliente &cliente, int id);
};



