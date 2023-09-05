#include <iostream>
#include "Vehiculo.h"

class Auto : public Vehiculo
{
private:
    int numeroPuertas;

public:
    Auto(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, std::string marca, long long precio, int año, int numeroPuertas);
    ~Auto();
    long long calculatePrice() override;
};