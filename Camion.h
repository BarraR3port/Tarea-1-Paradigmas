#include <iostream>
#include "Vehiculo.h"

class Camion : public Vehiculo
{
private:
    int numeroPuertas;

public:
    Camion(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, std::string marca, long long precio, int año, int numeroPuertas);
    ~Camion();
    long long calculatePrice();
};