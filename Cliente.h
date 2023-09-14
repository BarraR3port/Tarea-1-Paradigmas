#pragma once
#include <iostream>
using namespace std;
#include <string>

class Cliente
{
private:
    string nombre;
    string rut;

public:
    Cliente(const string &nombre, const string &rut);
    string getNombre() const;
    string getRut() const;
    void setNombre(const string &nombre);
    void setRut(const string &rut);
};
