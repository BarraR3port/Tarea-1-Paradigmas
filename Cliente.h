#pragma once
#include <iostream>
#include <string>
using namespace std;

class Cliente
{
private:
    string nombre;
    string rut;

public:
    Cliente( const string &nombre, const string &rut);
    string getNombre() const;
    string getRut() const;
    void setNombre(const string &nombre);
    void setRut(const string &rut);
};
