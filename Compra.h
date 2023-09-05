#include <iostream>
#include "Vehiculo.h"
#include "Cliente.h"

class Compra
{
private:
    Cliente *cliente;
    Vehiculo *vehiculoComprado;

public:
    Compra(Cliente *cliente, Vehiculo *vehiculoComprado);
    ~Compra();
};