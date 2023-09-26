#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <fstream> // Esto debe venir antes del uso de ifstream
#include <unordered_map>
#include <map>
#include "Cliente.h"
#include "Vehiculo.h"
#include "Auto.h"
#include "Camion.h"
#include "Moto.h"
#include "Venta.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

vector<Venta> ventas;

// crea un mapa de clientes por su rut
map<string, Cliente> clientes;
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    // ANSI escape sequence to clear screen
    cout << "\033[2J\033[1;1H";
#endif
}

Cliente &getOrCreateCliente(string rut, string nombre)
{
    // Busca el cliente por su RUT. Si no se encuentra, lo crea y lo añade al mapa.
    auto it = clientes.find(rut);
    if (it == clientes.end())
    {
        auto [new_it, inserted] = clientes.emplace(rut, Cliente(nombre, rut));
        return new_it->second;
    }
    return it->second;
}

int precioBaseAuto(const string &marca)
{

    if (marca == "Toyota")
    {
        return 19000000;
    }
    else if (marca == "Hyundai")
    {
        return 16000000;
    }
    else if (marca == "Suzuki")
    {
        return 12000000;
    }
    else if (marca == "Ford")
    {
        return 17000000;
    }
    else if (marca == "Chevrolet")
    {
        return 18000000;
    }
    else if (marca == "Honda")
    {
        return 21000000;
    }
    else
    {
        cout << "Marca no valida" << endl;
        cout << "Marcas validas: Toyota, Hyundai, Suzuki, Ford, Chevrolet, Honda" << endl;
        return 0;
    }
}

int precioBaseCamion(const string &marca)
{

    if (marca == "Volvo")
    {
        return 100000000;
    }
    else if (marca == "Iveco")
    {
        return 85000000;
    }
    else if (marca == "Mercedes")
    {
        return 110000000;
    }
    else if (marca == "Isuzu")
    {
        return 70000000;
    }
    else if (marca == "MAN")
    {
        return 105000000;
    }
    else if (marca == "Scania")
    {
        return 95000000;
    }
    else
    {
        cout << "Marca no valida" << endl;
        cout << "Marcas validas: Volvo, Iveco, Mercedes, Isuzu, MAN, Scania" << endl;
        return 0;
    }
}

int precioBaseMoto(const string &marca)
{
    if (marca == "Yamaha")
    {
        return 14000000;
    }
    else if (marca == "Suzuki")
    {
        return 8000000;
    }
    else if (marca == "Honda")
    {
        return 15000000;
    }
    else if (marca == "KTM")
    {
        return 5000000;
    }
    else if (marca == "BMW")
    {
        return 18000000;
    }
    else if (marca == "Kawasaki")
    {
        return 13000000;
    }
    else
    {
        cout << "Marca no valida" << endl;
        cout << "Marcas validas: Yamaha, Suzuki, Honda, KTM, BMW, Kawasaki" << endl;
        return 0;
    }
}

void readAndCreateVehicles()
{
    ifstream i("vehicles.json");
    if (!i.is_open())
    {
        cerr << "No se pudo abrir el archivo vehicles.json" << endl;
        return;
    }
    json j;
    i >> j;

    for (auto &venta : j)
    {
        Cliente &cliente = getOrCreateCliente(venta["cliente"]["rut"], venta["cliente"]["nombre"]);
        string tipo = venta["vehiculo"]["tipo"];
        int numeroMotor = venta["vehiculo"]["numeroMotor"];
        int numeroRuedas = venta["vehiculo"]["numeroRuedas"];
        string tipoCombustible = venta["vehiculo"]["tipoCombustible"];
        TipoCombustible tipoCombustibleParseado;
        if (tipoCombustible == "Gas")
        {
            tipoCombustibleParseado = TipoCombustible::Gas;
        }
        else if (tipoCombustible == "Electrico")
        {
            tipoCombustibleParseado = TipoCombustible::Electrico;
        }
        else if (tipoCombustible == "Gasolina")
        {
            tipoCombustibleParseado = TipoCombustible::Gasolina;
        }
        else
        {
            cout << "Tipo de combustible no valido" << endl;
            return;
        }
        int maxLitros = venta["vehiculo"]["maxLitros"];
        string marca = venta["vehiculo"]["marca"];
        int anio = venta["vehiculo"]["anio"];

        if (tipo == "Auto")
        {
            int numeroPuertas = venta["vehiculo"]["numeroPuertas"];
            long long precio = precioBaseAuto(marca);
            Auto *vehiculo = new Auto(numeroMotor, numeroRuedas, tipoCombustibleParseado, maxLitros, marca,
                                      precio, anio, numeroPuertas);
            Venta nueva_venta = *new Venta(*vehiculo, cliente, ventas.size());
            ventas.push_back(nueva_venta); // Agregar la nueva venta al vector
        }
        else if (tipo == "Camion")
        {
            int numeroPuertas = venta["vehiculo"]["numeroPuertas"];
            long long precio = precioBaseCamion(marca);
            Camion *vehiculo = new Camion(numeroMotor, numeroRuedas, tipoCombustibleParseado, maxLitros, marca,
                                          precio, anio, numeroPuertas);
            Venta nueva_venta = *new Venta(*vehiculo, cliente, ventas.size());
            ventas.push_back(nueva_venta); // Agregar la nueva venta al vector
        }
        else if (tipo == "Moto")
        {
            long long precio = precioBaseMoto(marca);
            Moto *vehiculo = new Moto(numeroMotor, numeroRuedas, tipoCombustibleParseado, maxLitros, marca,
                                      precio, anio);
            Venta nueva_venta = *new Venta(*vehiculo, cliente, ventas.size());
            ventas.push_back(nueva_venta); // Agregar la nueva venta al vector
        }
    }
}

void mostrarVehiculo(Vehiculo *vehiculo, Cliente *cliente)
{
    clearScreen();
    cout << "-------------------" << endl;
    cout << "Cliente: " << cliente->getNombre() << " (Rut: " << cliente->getRut() << ")" << endl;
    cout << "-------------------" << endl;
    cout << "Venta de vehiculo de tipo: " << vehiculo->getTipo() << endl;
    cout << "-------------------" << endl;
    cout << "Marca: " << vehiculo->getMarca() << endl;
    cout << "Anio: " << vehiculo->getAnio() << endl;
    cout << "Numero de motor: " << vehiculo->getNumeroMotor() << endl;
    cout << "Numero de ruedas: " << vehiculo->getNumeroRuedas() << endl;
    cout << "Tipo de combustible: " << vehiculo->getTipoCombustibleString() << endl;
    if (vehiculo->getTipoCombustibleString() == "Gasolina")
    {
        cout << "Tanque: " << vehiculo->getMaxLitros() << endl;
    }
    else
    {
        cout << "Tanque: NO APLICA" << endl;
    }
    cout << "Valor Original: " << vehiculo->getPrecio() << endl;
    cout << "Valor Final: " << vehiculo->calcularPrecioFinal() << endl;
}

void agregarAuto(Cliente *cliente)
{
    int numeroMotor, numeroRuedas, maxLitros, anio, numeroPuertas;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << " <---- Ingresa el Auto ---> " << endl;
    cout << "Marcas validas: Toyota, Hyundai, Suzuki, Ford, Chevrolet, Honda" << endl;
    cout << "Ingresa la marca: ";
    cin >> marca;
    precio = precioBaseAuto(marca);
    if (precio == 0)
    {
        return;
    }
    cout << "Precio base del auto: " << precio << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de motor: ";
    cin >> numeroMotor;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de ruedas: ";
    cin >> numeroRuedas;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Debe ingresar un numero entre 1 y 3. Intente de nuevo." << endl;
        return;
    }
    if (tipoCombustibleVal == 1)
    {
        tipoCombustible = TipoCombustible::Gasolina;
    }
    else if (tipoCombustibleVal == 2)
    {
        tipoCombustible = TipoCombustible::Gas;
    }
    else if (tipoCombustibleVal == 3)
    {
        tipoCombustible = TipoCombustible::Electrico;
    }
    else
    {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    if (tipoCombustible == TipoCombustible::Gasolina)
    {
        cout << "Ingresa el maximo de litros: ";
        cin >> maxLitros;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            return;
        }
    }
    else
    {
        maxLitros = 0;
    }
    cout << "Ingresa el numero de puertas: ";
    cin >> numeroPuertas;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    Vehiculo *autoVehiculo = new Auto(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio,
                                      numeroPuertas);
    if (cliente != NULL)
    {
        Venta venta = *new Venta(*autoVehiculo, *cliente, ventas.size());
        ventas.push_back(venta);
        cout << "Venta agregada correctamente" << endl;
        mostrarVehiculo(autoVehiculo, cliente);
    }
    else
    {
        cout << "Necesitas tener un cliente registrado para hacer una venta." << endl;
    }
    return;
}

void agregarCamion(Cliente *cliente)
{
    int numeroMotor, numeroRuedas, maxLitros, anio, numeroPuertas;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << " <---- Ingresa el Camion ---> " << endl;
    cout << "Marcas validas: Volvo, Iveco, Mercedes, Isuzu, MAN, Scania" << endl;
    cout << "Ingresa la marca: ";
    cin >> marca;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Debe ingresar una marca. Intente de nuevo." << endl;
        return;
    }
    precio = precioBaseCamion(marca);
    if (precio == 0)
    {
        return;
    }
    cout << "Precio base del Camion: " << precio << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de motor: ";
    cin >> numeroMotor;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de ruedas: ";
    cin >> numeroRuedas;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entre 1 y 3. Intente de nuevo." << endl;
        return;
    }
    if (tipoCombustibleVal == 1)
    {
        tipoCombustible = TipoCombustible::Gasolina;
    }
    else if (tipoCombustibleVal == 2)
    {
        tipoCombustible = TipoCombustible::Gas;
    }
    else if (tipoCombustibleVal == 3)
    {
        tipoCombustible = TipoCombustible::Electrico;
    }
    else
    {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    if (tipoCombustible == TipoCombustible::Gasolina)
    {
        cout << "Ingresa el maximo de litros: ";
        cin >> maxLitros;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            return;
        }
    }
    else
    {
        maxLitros = 0;
    }
    cout << "Ingresa el numero de puertas: ";
    cin >> numeroPuertas;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    Vehiculo *autoVehiculo = new Camion(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio,
                                        numeroPuertas);
    if (cliente != NULL)
    {
        Venta venta = *new Venta(*autoVehiculo, *cliente, ventas.size());
        ventas.push_back(venta);
        cout << "Venta agregada correctamente" << endl;
        mostrarVehiculo(autoVehiculo, cliente);
    }
    else
    {
        cout << "Necesitas tener un cliente registrado para hacer una venta." << endl;
    }
    return;
}

void agregarMoto(Cliente *cliente)
{
    int numeroMotor, numeroRuedas, maxLitros, anio;
    TipoCombustible tipoCombustible;
    string marca;
    long long precio;
    cout << " <---- Ingresa la Moto ---> " << endl;
    cout << "Marcas validas: Yamaha, Suzuki, Honda, KTM, BMW, Kawasaki" << endl;
    cout << "Ingresa la marca: ";
    cin >> marca;
    precio = precioBaseMoto(marca);
    if (precio == 0)
    {
        return;
    }
    cout << "Precio base de la moto: " << precio << endl;
    cout << "Ingresa el anio: ";
    cin >> anio;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de motor: ";
    cin >> numeroMotor;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
        return;
    }
    cout << "Ingresa el numero de ruedas: ";
    cin >> numeroRuedas;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Debe ingresar un numero entre 1 y 3. Intente de nuevo." << endl;
        return;
    }
    if (tipoCombustibleVal == 1)
    {
        tipoCombustible = TipoCombustible::Gasolina;
    }
    else if (tipoCombustibleVal == 2)
    {
        tipoCombustible = TipoCombustible::Gas;
    }
    else if (tipoCombustibleVal == 3)
    {
        tipoCombustible = TipoCombustible::Electrico;
    }
    else
    {
        cout << "Tipo de combustible no valido" << endl;
        return;
    }
    if (tipoCombustible == TipoCombustible::Gasolina)
    {
        cout << "Ingresa el maximo de litros: ";
        cin >> maxLitros;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Debe ingresar un numero entero. Intente de nuevo." << endl;
            return;
        }
    }
    else
    {
        maxLitros = 0;
    }
    Vehiculo *autoVehiculo = new Moto(numeroMotor, numeroRuedas, tipoCombustible, maxLitros, marca, precio, anio);
    if (cliente != NULL)
    {
        Venta venta = *new Venta(*autoVehiculo, *cliente, ventas.size());
        ventas.push_back(venta);
        cout << "Venta agregada correctamente" << endl;
        mostrarVehiculo(autoVehiculo, cliente);
    }
    else
    {
        cout << "Necesitas tener un cliente registrado para hacer una venta." << endl;
    }
    return;
}

void mostrarMejorCliente()
{
    unordered_map<string, int> contadorCompras; // Mapa para contar las compras por RUT de cliente
    Cliente *mejorCliente = nullptr;
    int maximo = 0;

    for (const auto &venta : ventas)
    {
        const string &rut = venta.getCliente().getRut();
        contadorCompras[rut]++; // Incrementa el contador para este cliente

        if (contadorCompras[rut] > maximo)
        {
            maximo = contadorCompras[rut];
            mejorCliente = &const_cast<Cliente &>(venta.getCliente());
        }
    }

    if (mejorCliente != nullptr)
    {
        cout << "El cliente que compro mas vehiculos es: " << mejorCliente->getNombre() << " ("
             << mejorCliente->getRut() << ")" << endl;
        cout << "Con un total de: " << std::fixed << std::setprecision(2) << maximo << " vehiculos comprados" << endl;
    }
    else
    {
        cout << "No hay clientes registrados" << endl;
    }
}

void mostrarCantidadCliente(Cliente *cliente, string tipoDeVehiculo)
{
    int totalCompras = 0;

    for (const auto &venta : ventas)
    {
        const string &rut = venta.getCliente().getRut();

        if (rut == cliente->getRut())
        {
            if (tipoDeVehiculo == "Vehiculo" || venta.getVehiculo().getTipo() == tipoDeVehiculo)
            {
                totalCompras++;
            }
        }
    }
    const string vehiculoPlural = tipoDeVehiculo == "Camion" ? "es" : "s";

    if (totalCompras > 0)
    {
        cout << "El cliente " << cliente->getNombre() << " (" << cliente->getRut() << ")" << endl;
        cout << "Compro " << std::fixed << std::setprecision(2) << totalCompras << " " << tipoDeVehiculo << vehiculoPlural << endl;
    }
    else
    {
        cout << "El cliente " << cliente->getNombre() << " (" << cliente->getRut() << ")" << endl;
        cout << "No ha comprado " << tipoDeVehiculo << vehiculoPlural << endl;
    }
}

void mostrarTotalVentas(string tipoDeVehiculo)
{
    int totalCompras = 0;

    for (const auto &venta : ventas)
    {

        if (tipoDeVehiculo == "Vehiculo" || venta.getVehiculo().getTipo() == tipoDeVehiculo)
        {
            totalCompras++;
        }
    }
    const string vehiculoPlural = tipoDeVehiculo == "Camion" ? "nes" : "s";

    if (totalCompras > 0)
    {
        cout << "Se han comprado " << std::fixed << std::setprecision(2) << totalCompras << " " << tipoDeVehiculo << vehiculoPlural << endl;
    }
    else
    {
        cout << "No se han comprado " << tipoDeVehiculo << vehiculoPlural << endl;
    }
}

void mostrarPromedioVentas(string tipoDeVehiculo)
{
    long long sumaPrecios = 0;
    int contador = 0;

    for (const auto &venta : ventas)
    {
        if (tipoDeVehiculo == "Vehiculo" || venta.getVehiculo().getTipo() == tipoDeVehiculo)
        {
            sumaPrecios += venta.getVehiculo().calcularPrecioFinal();
            contador++;
        }
    }

    if (contador == 0)
    {
        cout << "No hay ventas para este tipo de vehiculo: " << tipoDeVehiculo << endl;
        return;
    }

    double promedio = static_cast<double>(sumaPrecios) / contador;
    cout << "El precio promedio de ventas para " << tipoDeVehiculo << " es: " << std::fixed << std::setprecision(2) << promedio << endl;
}

void mostrarCabecera(Cliente *cliente)
{
    clearScreen();
    cout << " " << endl;
    cout << "      Autos Buenos         " << endl;
    cout << " " << endl;
    cout << "  + Cliente Actual: " << cliente->getNombre() << " (" << cliente->getRut() << ")" << endl;
    cout << " " << endl;
}

void menu(void)
{
    int opcion = 0;
    Cliente *cliente = NULL;

    /*
    // TODO: TESTING Profe cuando vea esto, lo puede descomentar para poder cargar el archivo con 100 ventas para diferentes usuarios
    readAndCreateVehicles();
    cliente = &getOrCreateCliente("22222222-2", "Pedro");
    // TODO: TESTING
    */
    while (opcion != 4)
    {
        if (cliente == NULL)
        {
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
        mostrarCabecera(cliente);
        cout << "  1. Ventas" << endl;
        cout << "  2. Estadisticas" << endl;
        cout << "  3. Cerrar Sesion" << endl;
        cout << "  4. Salir" << endl;
        cout << "  Seleccione una opcion: ";
        cin >> opcion;
        // Verificar si la entrada es válida
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Debe ingresar un numero entre 1 y 4. Intente de nuevo." << endl;
            continue;
        }

        if (opcion == 1)
        {
            int opcion_venta = -1;
            while (opcion_venta != 4)
            {
                clearScreen();
                cout << " " << endl;
                cout << " <---- Venta de Vehiculos ---> " << endl;
                cout << " " << endl;
                cout << "  1. Agregar Auto" << endl;
                cout << "  2. Agregar Moto" << endl;
                cout << "  3. Agregar Camion" << endl;
                cout << "  4. Volver " << endl;
                cout << " " << endl;
                cout << "  Seleccione una opcion: ";
                cin >> opcion_venta;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Debe ingresar un numero entre 1 y 4. Intente de nuevo." << endl;
                    continue;
                }
                if (opcion_venta == 1)
                {
                    agregarAuto(cliente);
                    cout << "Presione ENTER para continuar...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                }
                else if (opcion_venta == 2)
                {
                    agregarMoto(cliente);
                    cout << "Presione ENTER para continuar...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                }
                else if (opcion_venta == 3)
                {
                    agregarCamion(cliente);
                    cout << "Presione ENTER para continuar...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                }
                else if (opcion_venta == 4)
                {
                    cout << "Volviendo al menu anterior" << endl;
                }
                else
                {
                    cout << "Ingresa una opcion entre 1 y 4" << endl;
                }
            }
        }
        else if (opcion == 2)
        {
            int opcion_stats = 0;
            while (opcion_stats != 5)
            {
                clearScreen();
                cout << " " << endl;
                cout << " <---- Estadisticas de Ventas ---> " << endl;
                cout << " " << endl;
                cout << "  1.  Cliente que compro mas Vehiculos" << endl;
                cout << "  2.  Total de Compras" << endl;
                cout << "  3.  Total de Ventas" << endl;
                cout << "  4.  Promedio de Ventas" << endl;
                cout << "  5.  Volver" << endl;
                cout << "Seleccione una opcion : ";
                cin >> opcion_stats;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Debe ingresar un numero entre 1 y 5. Intente de nuevo." << endl;
                    continue;
                }

                if (opcion_stats == 1)
                {
                    mostrarMejorCliente();
                    // hacer una pausa
                    cout << "Presione ENTER para continuar...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin.get();
                }
                else if (opcion_stats == 2)
                {
                    int opcion_stats_promedio = 0;
                    while (opcion_stats_promedio != 5)
                    {
                        clearScreen();
                        cout << " " << endl;
                        cout << " <---- Estadisticas | Cantidad de ventas del Usuario ---> " << endl;
                        cout << " " << endl;
                        cout << "  1.  Cantidad de Autos comprados" << endl;
                        cout << "  2.  Cantidad de Motos compradas" << endl;
                        cout << "  3.  Cantidad de Camiones comprados" << endl;
                        cout << "  4.  Cantidad de Vehiculos comprados" << endl;
                        cout << "  5.  Volver" << endl;
                        cout << "Seleccione una opcion : ";
                        cin >> opcion_stats_promedio;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout << "Debe ingresar un numero entre 1 y 5. Intente de nuevo." << endl;
                            continue;
                        }

                        if (opcion_stats_promedio == 1)
                        {
                            mostrarCantidadCliente(cliente, "Auto");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_promedio == 2)
                        {
                            mostrarCantidadCliente(cliente, "Moto");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_promedio == 3)
                        {
                            mostrarCantidadCliente(cliente, "Camion");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_promedio == 4)
                        {
                            mostrarCantidadCliente(cliente, "Vehiculo");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_promedio == 5)
                        {
                            cout << "Volviendo al menu anterior" << endl;
                        }
                        else
                        {
                            cout << "Ingresa una opcion entre 1 y 5" << endl;
                        }
                    }
                }
                else if (opcion_stats == 3)
                {
                    int opcion_stats_total = 0;
                    while (opcion_stats_total != 5)
                    {
                        clearScreen();
                        cout << " " << endl;
                        cout << " <---- Estadisticas | Ventas Total de la empresa ---> " << endl;
                        cout << " " << endl;
                        cout << "  1.  Total de ventas de Autos" << endl;
                        cout << "  2.  Total de ventas de Motos" << endl;
                        cout << "  3.  Total de ventas de Camiones" << endl;
                        cout << "  4.  Total de ventas de Vehiculos" << endl;
                        cout << "  5.  Volver" << endl;
                        cout << "Seleccione una opcion : ";
                        cin >> opcion_stats_total;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout << "Debe ingresar un numero entre 1 y 5. Intente de nuevo." << endl;
                            continue;
                        }

                        if (opcion_stats_total == 1)
                        {
                            mostrarTotalVentas("Auto");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_total == 2)
                        {
                            mostrarTotalVentas("Moto");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_total == 3)
                        {
                            mostrarTotalVentas("Camion");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_total == 4)
                        {
                            mostrarTotalVentas("Vehiculo");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_total == 5)
                        {
                            cout << "Volviendo al menu anterior" << endl;
                        }
                        else
                        {
                            cout << "Ingresa una opcion entre 1 y 5" << endl;
                        }
                    }
                }
                else if (opcion_stats == 4)
                {
                    int opcion_stats_prom = 0;
                    while (opcion_stats_prom != 5)
                    {
                        clearScreen();
                        cout << " " << endl;
                        cout << " <---- Estadisticas | Promedios Totales de la empresa ---> " << endl;
                        cout << " " << endl;
                        cout << "  1.  Promedio de ventas de Autos" << endl;
                        cout << "  2.  Promedio de ventas de Motos" << endl;
                        cout << "  3.  Promedio de ventas de Camiones" << endl;
                        cout << "  4.  Promedio de ventas de Vehiculos" << endl;
                        cout << "  5.  Volver" << endl;
                        cout << "Seleccione una opcion : ";
                        cin >> opcion_stats_prom;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout << "Debe ingresar un numero entre 1 y 5. Intente de nuevo." << endl;
                            continue;
                        }

                        if (opcion_stats_prom == 1)
                        {
                            mostrarPromedioVentas("Auto");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_prom == 2)
                        {
                            mostrarPromedioVentas("Moto");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_prom == 3)
                        {
                            mostrarPromedioVentas("Camion");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_prom == 4)
                        {
                            mostrarPromedioVentas("Vehiculo");
                            cout << "Presione ENTER para continuar...";
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin.get();
                        }
                        else if (opcion_stats_prom == 5)
                        {
                            cout << "Volviendo al menu anterior" << endl;
                        }
                        else
                        {
                            cout << "Ingresa una opcion entre 1 y 5" << endl;
                        }
                    }
                }
                else if (opcion_stats == 5)
                {
                    cout << "Volviendo al menu anterior" << endl;
                }
                else
                {
                    cout << "Ingresa una opcion entre 1 y 5" << endl;
                }
            }
        }
        else if (opcion == 3)
        {
            cout << " - Cerrando sesion." << endl;
            cliente = NULL;
            continue;
        }
        else if (opcion == 4)
        {
            cout << "Saliendo del programa." << endl;
        }
        else
        {
            cout << "Ingresa una opcion entre 1 y 4" << endl;
        }
    }
    return;
}

int main(void)
{

    menu();
    cout << "-------------------" << endl;
    return 0;
}