#include "Vehiculo.h"
#include "Cliente.h"
#include "Venta.h"

Venta::Venta(Vehiculo &vehiculo, Cliente &cliente, int id) : vehiculo(vehiculo), cliente(cliente), id(id) {
}

Cliente& Venta::getCliente() const {
    return cliente;
}

Vehiculo& Venta::getVehiculo() const {
    return vehiculo;
}

int Venta::getId() {
    return id;
}
