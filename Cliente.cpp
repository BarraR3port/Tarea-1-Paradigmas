#include <string>
#include "Cliente.h"
using namespace std;

Cliente::Cliente(const string &nombre, const string &rut) : nombre(nombre), rut(rut)
{
}

string Cliente::getNombre() const
{
    return nombre;
}

string Cliente::getRut() const
{
    return rut;
}

void Cliente::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Cliente::setRut(const string &rut)
{
    this->rut = rut;
}
