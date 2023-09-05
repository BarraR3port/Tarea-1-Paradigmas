#include <iostream>
#include "Vehiculo.h"

class Moto : public Vehiculo
{
private:
    /* data */
    int numeroPuertas;

public:
    Moto(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, std::string marca, long long precio, int año, int numeroPuertas);
    ~Moto();
    long long calculatePrice();
};