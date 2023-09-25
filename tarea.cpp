#include <iostream>
#include <limits>
#include <vector>
#include <fstream> // Esto debe venir antes del uso de ifstream
#include "Cliente.h"
#include "Vehiculo.h"
#include "Auto.h"
#include "Camion.h"
#include "Moto.h"
#include "Venta.h"

#ifdef _WIN32

#include <windows.h>

#else
#include <unistd.h>
#include <term.h>
#endif

using namespace std;
/* TODO: SACAR ESTO ANTES DE ENTREGARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR */
#include "json.hpp"

vector<Venta> ventas;

// crea un mapa de clientes por su rut
map<string, Cliente> clientes;

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    // ANSI escape sequence to clear screen
    std::cout << "\033[2J\033[1;1H";
#endif
}

Cliente &getOrCreateCliente(string rut, string nombre) {
    // Busca el cliente por su RUT. Si no se encuentra, lo crea y lo añade al mapa.
    auto it = clientes.find(rut);
    if (it == clientes.end()) {
        auto [new_it, inserted] = clientes.emplace(rut, Cliente(nombre, rut));
        return new_it->second;
    }
    return it->second;
}

using json = nlohmann::json;

void readAndCreateVehicles() {
    ifstream i("vehicles.json");
    if (!i.is_open()) {
        cerr << "No se pudo abrir el archivo vehicles.json" << endl;
        return;
    }
    json j;
    i >> j;

    for (auto &venta: j) {
        Cliente &cliente = getOrCreateCliente(venta["cliente"]["rut"], venta["cliente"]["nombre"]);
        string tipo = venta["vehiculo"]["tipo"];
        int numeroMotor = venta["vehiculo"]["numeroMotor"];
        int numeroRuedas = venta["vehiculo"]["numeroRuedas"];
        string tipoCombustible = venta["vehiculo"]["tipoCombustible"];
        TipoCombustible tipoCombustibleParseado;
        if (tipoCombustible == "Gas") {
            tipoCombustibleParseado = TipoCombustible::Gas;
        } else if (tipoCombustible == "Electrico") {
            tipoCombustibleParseado = TipoCombustible::Electrico;
        } else if (tipoCombustible == "Gasolina") {
            tipoCombustibleParseado = TipoCombustible::Gasolina;
        } else {
            cout << "Tipo de combustible no valido" << endl;
            return;
        }
        int maxLitros = venta["vehiculo"]["maxLitros"];
        string marca = venta["vehiculo"]["marca"];
        long long precio = venta["vehiculo"]["precio"];
        int anio = venta["vehiculo"]["anio"];

        if (tipo == "Auto") {
            int numeroPuertas = venta["vehiculo"]["numeroPuertas"];
            Vehiculo *autoVehiculo = new Auto(numeroMotor, numeroRuedas, tipoCombustibleParseado, maxLitros, marca,
                                              precio, anio, numeroPuertas);
            Venta venta = *new Venta(*autoVehiculo, cliente, ventas.size());
            ventas.push_back(venta); // Agregar la nueva venta al vector
        } else if (tipo == "Camion") {
            int numeroPuertas = venta["vehiculo"]["numeroPuertas"];
            Vehiculo *camionVehiculo = new Camion(numeroMotor, numeroRuedas, tipoCombustibleParseado, maxLitros, marca,
                                                  precio, anio, numeroPuertas);
            Venta venta = *new Venta(*camionVehiculo, cliente, ventas.size());
            ventas.push_back(venta); // Agregar la nueva venta al vector
        } else if (tipo == "Moto") {
            Vehiculo *motoVehiculo = new Moto(numeroMotor, numeroRuedas, tipoCombustibleParseado, maxLitros, marca,
                                              precio, anio);
            Venta venta = *new Venta(*motoVehiculo, cliente, ventas.size());
            ventas.push_back(venta); // Agregar la nueva venta al vector
        }
    }
}



int precioBaseAuto(const std::string &marca) {

    if (marca == "Toyota") {
        return 19000000;
    } else if (marca == "Hyundai") {
        return 16000000;
    } else if (marca == "Suzuki") {
        return 12000000;
    } else if (marca == "Ford") {
        return 17000000;
    } else if (marca == "Chevrolet") {
        return 18000000;
    } else if (marca == "Honda") {
        return 21000000;
    } else {
        cout << "Marca no valida" << endl;
        cout << "Marcas validas: Toyota, Hyundai, Suzuki, Ford, Chevrolet, Honda" << endl;
        return 0;
    }
}
int precioBaseCamion(const std::string &marca) {

    if (marca == "Volvo") {
        return 100000000;
    } else if (marca == "Iveco") {
        return 85000000;
    } else if (marca == "Mercedes") {
        return 110000000;
    } else if (marca == "Isuzu") {
        return 70000000;
    } else if (marca == "MAN") {
        return 105000000;
    } else if (marca == "Scania") {
        return 95000000;
    } else {
        cout << "Marca no valida" << endl;
        cout << "Marcas validas: Volvo, Iveco, Mercedes, Isuzu, MAN, Scania" << endl;
        return 0;
    }
}

int precioBaseMoto(const std::string &marca) {
    if (marca == "Yamaha") {
        return 14000000;
    } else if (marca == "Suzuki") {
        return 8000000;
    } else if (marca == "Honda") {
        return 15000000;
    } else if (marca == "KTM") {
        return 5000000;
    } else if (marca == "BMW") {
        return 18000000;
    } else if (marca == "Kawasaki") {
        return 13000000;
    }  else {
        cout << "Marca no valida" << endl;
        cout << "Marcas validas: Yamaha, Suzuki, Honda, KTM, BMW, Kawasaki" << endl;
        return 0;
    }
}

void agregarAuto(Cliente *cliente) {
    int numeroMotor, numeroRuedas, maxLitros, anio, numeroPuertas;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << " <---- Ingresa el Auto ---> " << endl;
    cout << "Ingresa la marca: ";
    cin >> marca;
    precio = precioBaseAuto(marca);
    if (precio == 0) {
        return;
    }
    cout << "Precio base del auto: " << precio << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de motor: ";
    cin >> numeroMotor;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de ruedas: ";
    cin >> numeroRuedas;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Tipo de Combustible:" << endl;
    cout << " 1 -> Gasolina" << endl;
    cout << " 2 -> Gas" << endl;
    cout << " 3 -> Electrico" << endl;
    cout << "Selecciona el tipo de combustible: ";
    int tipoCombustibleVal;
    cin >> tipoCombustibleVal;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entre 1 y 3. Intente de nuevo." << endl;
        return;
    }
    if (tipoCombustibleVal == 1) {
        tipoCombustible = TipoCombustible::Gasolina;
    } else if (tipoCombustibleVal == 2) {
        tipoCombustible = TipoCombustible::Gas;
    } else if (tipoCombustibleVal == 3) {
        tipoCombustible = TipoCombustible::Electrico;
    } else {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    if (tipoCombustible == TipoCombustible::Gasolina) {
        cout << "Ingresa el maximo de litros" << endl;
        cin >> maxLitros;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            return;
        }
    } else {
        maxLitros = 0;
    }
    cout << "Ingresa el numero de puertas" << endl;
    cin >> numeroPuertas;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    Vehiculo *autoVehiculo = new Auto(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio,
                                      numeroPuertas);
    if (cliente != NULL) {
        Venta venta = *new Venta(*autoVehiculo, *cliente, ventas.size());
        ventas.push_back(venta);
        cout << "Venta agregada correctamente" << endl;
    } else {
        cout << "Necesitas tener un cliente registrado para hacer una venta." << endl;
    }
    return;
}
void agregarCamion(Cliente *cliente) {
    int numeroMotor, numeroRuedas, maxLitros, anio, numeroPuertas;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << " <---- Ingresa el Camion ---> " << endl;
    cout << "Ingresa la marca: ";
    cin >> marca;
    precio = precioBaseCamion(marca);
    if (precio == 0) {
        return;
    }
    cout << "Precio base del Camion: " << precio << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de motor: ";
    cin >> numeroMotor;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de ruedas: ";
    cin >> numeroRuedas;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Tipo de Combustible:" << endl;
    cout << " 1 -> Gasolina" << endl;
    cout << " 2 -> Gas" << endl;
    cout << " 3 -> Electrico" << endl;
    cout << "Selecciona el tipo de combustible: ";
    int tipoCombustibleVal;
    cin >> tipoCombustibleVal;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entre 1 y 3. Intente de nuevo." << endl;
        return;
    }
    if (tipoCombustibleVal == 1) {
        tipoCombustible = TipoCombustible::Gasolina;
    } else if (tipoCombustibleVal == 2) {
        tipoCombustible = TipoCombustible::Gas;
    } else if (tipoCombustibleVal == 3) {
        tipoCombustible = TipoCombustible::Electrico;
    } else {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    if (tipoCombustible == TipoCombustible::Gasolina) {
        cout << "Ingresa el maximo de litros" << endl;
        cin >> maxLitros;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            return;
        }
    } else {
        maxLitros = 0;
    }
    cout << "Ingresa el numero de puertas" << endl;
    cin >> numeroPuertas;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    Vehiculo *autoVehiculo = new Camion(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio,
                                      numeroPuertas);
    if (cliente != NULL) {
        Venta venta = *new Venta(*autoVehiculo, *cliente, ventas.size());
        ventas.push_back(venta);
        cout << "Venta agregada correctamente" << endl;
    } else {
        cout << "Necesitas tener un cliente registrado para hacer una venta." << endl;
    }
    return;
}

void agregarMoto(Cliente *cliente) {
    int numeroMotor, numeroRuedas, maxLitros, anio;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << " <---- Ingresa la Moto ---> " << endl;
    cout << "Ingresa la marca: ";
    cin >> marca;
    precio = precioBaseMoto(marca);
    if (precio == 0) {
        return;
    }
    cout << "Precio base de la moto: " << precio << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de motor: ";
    cin >> numeroMotor;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de ruedas: ";
    cin >> numeroRuedas;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Tipo de Combustible:" << endl;
    cout << " 1 -> Gasolina" << endl;
    cout << " 2 -> Gas" << endl;
    cout << " 3 -> Electrico" << endl;
    cout << "Selecciona el tipo de combustible: ";
    int tipoCombustibleVal;
    cin >> tipoCombustibleVal;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entre 1 y 3. Intente de nuevo." << endl;
        return;
    }
    if (tipoCombustibleVal == 1) {
        tipoCombustible = TipoCombustible::Gasolina;
    } else if (tipoCombustibleVal == 2) {
        tipoCombustible = TipoCombustible::Gas;
    } else if (tipoCombustibleVal == 3) {
        tipoCombustible = TipoCombustible::Electrico;
    } else {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    if (tipoCombustible == TipoCombustible::Gasolina) {
        cout << "Ingresa el maximo de litros" << endl;
        cin >> maxLitros;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            return;
        }
    } else {
        maxLitros = 0;
    }
    Vehiculo *autoVehiculo = new Moto(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio);
    if (cliente != NULL) {
        Venta venta = *new Venta(*autoVehiculo, *cliente, ventas.size());
        ventas.push_back(venta);
        cout << "Venta agregada correctamente" << endl;
    } else {
        cout << "Necesitas tener un cliente registrado para hacer una venta." << endl;
    }
    return;
}

void mostrarVehiculos(Cliente *cliente) {
    cout << "-------------------" << endl;
    cout << "Cliente Actual: " << endl;
    cout << "Nombre: " << cliente->getNombre() << endl;
    cout << "Rut: " << cliente->getRut() << endl;
    cout << "-------------------" << endl;
    cout << "Vehiculos" << endl;
    cout << "-------------------" << endl;

    for (size_t i = 0; i < ventas.size(); i++) {
        Vehiculo &vehiculo = ventas[i].getVehiculo();
        Cliente venta_cliente = ventas[i].getCliente();
        if (venta_cliente.getRut() != cliente->getRut()) {
            continue;
        }
        cout << "-------------------" << endl;
        cout << vehiculo.getTipo() << " Id: " << i << endl;
        cout << "-------------------" << endl;
        cout << "Numero de motor: " << vehiculo.getNumeroMotor() << endl;
        cout << "Numero de ruedas: " << vehiculo.getNumeroRuedas() << endl;
        cout << "Tipo de combustible: " << vehiculo.getTipoCombustibleString() << endl;
        cout << "Maximo de litros: " << vehiculo.getMaxLitros() << endl;
        cout << "Marca: " << vehiculo.getMarca() << endl;
        cout << "Precio: " << vehiculo.getPrecio() << endl;
        cout << "Anio: " << vehiculo.getAnio() << endl;
        cout << "Valor Original:" << vehiculo.getPrecio() << endl;
        cout << "Valor Final:" << vehiculo.calcularPrecioFinal() << endl;
    }
    return;
}

void showHeader(Cliente *cliente) {
    clearScreen();
    cout << " " << endl;
    cout << "      Autos Buenos - Menu         " << endl;
    cout << " " << endl;
    cout << "  + Cliente Actual: " << cliente->getNombre() << " (" << cliente->getRut() << ")" << endl;
    cout << " " << endl;
}

void menu(void) {
    int opcion = 0;
    Cliente *cliente = NULL;
    while (opcion != 7) {
        if (cliente == NULL) {
            clearScreen();
            string nombreCliente, rutCliente;
            cout << " " << endl;
            cout << " <---- Inicio de Sesion ---> " << endl;
            cout << " " << endl;
            cout << "Ingresa el nombre del cliente: ";
            cin >> nombreCliente;
            cout << "Ingresa el rut del cliente: ";
            cin >> rutCliente;
            cliente = &getOrCreateCliente(rutCliente, nombreCliente);
            cout << " " << endl;
        }
        showHeader(cliente);
        cout << "  1. Ventas de vehiculos a clientes" << endl;
        cout << "  2. Promedio de ventas" << endl;
        cout << "  3. Cantidad de vehiculos comprados" << endl;
        cout << "  4. Ventas de vehiculos" << endl;
        cout << "  5. Cerrar Sesion" << endl;
        cout << "  6. CARGAR VENTAS Y USUARIOS (TEST PARA EL PROFE) " << endl;
        cout << "  7. Salir" << endl;
        cout << "  Seleccione una opcion: ";
        cin >> opcion;
        // Verificar si la entrada es válida
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entre 1 y 6. Intente de nuevo." << endl;
            continue;
        }

        if (opcion == 1) {
            int opcion_venta = -1;
            while (opcion_venta != 0) {
                clearScreen();
                cout << " " << endl;
                cout << " <---- Venta de Vehiculos ---> " << endl;
                cout << " " << endl;
                cout << "  1. Agregar Auto" << endl;
                cout << "  2. Agregar Moto" << endl;
                cout << "  3. Agregar Camion" << endl;
                cout << "  4. Volver " << endl;
                cout << " " << endl;
                cin >> opcion_venta;
                if (opcion_venta == 1) {
                    agregarAuto(cliente);
                } else if (opcion_venta == 2) {
                    agregarMoto(cliente);
                } else if (opcion_venta == 3) {
                    agregarCamion(cliente);
                } else if (opcion_venta == 4) {
                    cout << "Saliste correctamente del programa" << endl;
                } else {
                    cout << "Opcion no valida" << endl;
                }
            }
        } else if (opcion == 2) {
            int op = 0;
            while (op != 5) {
                clearScreen();
                cout << "1. Promedio de venta de autos" << endl;
                cout << "2. Promedio de venta de motos" << endl;
                cout << "3. Promedio de venta de camiones" << endl;
                cout << "4. Promedio de ventas totales" << endl;
                cout << "5. Volver al menu principal" << endl;
                cout << "Seleccione una opcion : ";
                cin >> op;

                if (op == 1) {
                    cout << "Promedio de venta de autos" << endl;
                } else if (op == 2) {
                    cout << "Promedio de venta de motos" << endl;
                } else if (op == 3) {
                    cout << "Promedio de venta de camiones" << endl;
                } else if (op == 4) {
                    cout << "Promedio de ventas totales" << endl;
                } else if (op == 5) {
                    cout << "Volviendo al menu principal." << endl;
                } else {
                    cout << "Opcion no valida, ingresa una valida porfavor..." << endl;
                }
            }
        } else if (opcion == 3) {
            int op = 0;
            while (op != 5) {
                clearScreen();
                cout << "1. Cantidad de autos comprados" << endl;
                cout << "2. Cantidad de motos compradas" << endl;
                cout << "3. Cantidad de camiones comprados" << endl;
                cout << "4. Cantidad de vehiculos comprados" << endl;
                cout << "5. Volver al menu principal" << endl;
                cout << "Seleccione una opcion :  ";
                cin >> op;

                if (op == 1) {
                    cout << "Cantidad de autos comprados" << endl;
                } else if (op == 2) {
                    cout << "Cantidad de motos compradas" << endl;
                } else if (op == 3) {
                    cout << "Cantidad de camiones comprados" << endl;
                } else if (op == 4) {
                    cout << "Cantidad de vehiculos" << endl;
                } else if (op == 5) {
                    cout << "Volviendo al menu principal." << endl;
                } else {
                    cout << "Opcion no valida, ingresa una valida porfavor..." << endl;
                }
            }
        } else if (opcion == 4) {
            int op = 0;
            while (op != 5) {
                clearScreen();
                cout << "1. Ventas de autos" << endl;
                cout << "2. Ventas de motos" << endl;
                cout << "3. Ventas de camiones" << endl;
                cout << "4. Ventas totales" << endl;
                cout << "5. Volver al menu principal" << endl;
                cout << "Seleccione una opcion :  ";
                cin >> op;

                if (op == 1) {
                    cout << "Ventas de autos" << endl;
                } else if (op == 2) {
                    cout << "Ventas de motos" << endl;
                } else if (op == 3) {
                    cout << "Ventas de camiones" << endl;
                } else if (op == 4) {
                    cout << "Ventas totales" << endl;
                } else if (op == 5) {
                    cout << "Volviendo al menu principal." << endl;
                } else {
                    cout << "Opcion no valida, ingresa una valida porfavor..." << endl;
                }
            }
        } else if (opcion == 5) {
            cout << " - Cerrando sesion." << endl;
            cliente = NULL;
            continue;
        } else if (opcion == 6) {
            //TODO: TESTING
            cliente = &getOrCreateCliente("66773571-5", "Cliente_6");
            readAndCreateVehicles();
            //TODO: TESTING
        } else if (opcion == 7) {
            cout << "Saliendo del programa." << endl;
        } else {
            cout << "Esa opcion no es valida, ingresa una opcion valida....." << endl;
        }
    }
    return;
}

int main(void) {
    menu();
    cout << "-------------------" << endl;
    return 0;
}