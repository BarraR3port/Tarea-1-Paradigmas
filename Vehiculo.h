#include <iostream>

class Vehiculo
{
private:
    int año;
    int numeroMotor;
    int numeroRuedas;
    long long precio;
    int maxLitros;
    std::string marca;
    TipoCombustible tipoCombustible;

public:
    Vehiculo(int numeroMotor, int numeroRuedas, TipoCombustible tipoCombustible, int maxLitros, std::string marca, long long precio, int año);
    ~Vehiculo();
    virtual long long calculatePrice() = 0;
};

enum TipoCombustible
{
    Gasolina,
    Gas,
    Electrico
};