#include <iostream>

class Cliente
{
private:
    std::string nombreCliente;
    std::string rutCliente;

public:
    Cliente(std::string nombreCliente, std::string rutCliente);
    ~Cliente();
};