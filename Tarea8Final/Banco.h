//
// Created by 57318 on 2/04/2025.
//

#ifndef BANCO_H
#define BANCO_H
#include <string>
#include <vector>
#include <numeric>
#include <fstream>
#include "CuentaAhorros.h"
#include "CuentaCorriente.h"
#include "Cliente.h"
#include "Cuenta.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Banco {
private:
    string nombre;
    vector<Cliente> clientes;        //Composicion
    vector<Cuenta*> cuentas;         //Agregacion, se usan apuntadores porque posee herencia con
    int siguienteIdCliente = 100;      //(cuenta ahorros y cuenta corriente),
                                    //necesario para el polimorfismo, Si no lo usara siempre usaria el metodo de la
                                    //superclase y no el de las subclases.
                                    //Contador para el ID autoasignado desde 1 a infinito.
public:
    Banco(const string &nombre)
        : nombre(nombre) {
    }

    ~Banco() {
        // Liberar memoria de las cuentas
        for (auto cuenta : cuentas) {
            delete cuenta;
        }
    }

    string get_nombre() const {
        return nombre;
    }

    const vector<Cliente>& getClientes() const {
        return clientes;
    }

    const vector<Cuenta*>& getCuentas() const {
        return cuentas;
    }

    void agregarCliente(const string &nombre, const string&direccion) {
        clientes.emplace_back(siguienteIdCliente++, nombre, direccion); //Cada vez que haga banco agragar cliente, va a hacer el ++ en la variable siguientecliente dando id´s unicos.
    }

    // Método para agregar un cliente con ID específico (usado al cargar desde JSON)
    void agregarClienteConId(int id, const string &nombre, const string &direccion) {
        clientes.emplace_back(id, nombre, direccion);
        if (id >= siguienteIdCliente) {
            siguienteIdCliente = id + 1;
        }
    }

    void agregarCuentaAhorros(int saldo, int idCliente, double tasaInteres) {
        cuentas.push_back(new CuentaAhorros(siguienteIdCliente++, saldo, idCliente, tasaInteres));
    }

    // Método para agregar una cuenta de ahorros con número específico (usado al cargar desde JSON)
    void agregarCuentaAhorrosConNumero(int numero, int saldo, int idCliente, double tasaInteres) {
        cuentas.push_back(new CuentaAhorros(numero, saldo, idCliente, tasaInteres));
        if (numero >= siguienteIdCliente) {
            siguienteIdCliente = numero + 1;
        }
    }

    // Método para agregar una cuenta corriente
    void agregarCuentaCorriente(int saldo, int idCliente, int limiteSobregiro) {
        cuentas.push_back(new CuentaCorriente(siguienteIdCliente++, saldo, idCliente, limiteSobregiro));
    }

    // Método para agregar una cuenta corriente con número específico (usado al cargar desde JSON)
    void agregarCuentaCorrienteConNumero(int numero, int saldo, int idCliente, int limiteSobregiro) {
        cuentas.push_back(new CuentaCorriente(numero, saldo, idCliente, limiteSobregiro));
        if (numero >= siguienteIdCliente) {
            siguienteIdCliente = numero + 1;
        }
    }

    void mostrarClientes() {
        for(const auto &cliente : clientes) {
            cliente.mostrar();
            cout << "------------------------" << endl;
        }
    }

    void mostrarCuentas() {
        for(const auto &cuenta : cuentas) {
            cuenta->mostrar(); //es polimorfico llamara el mostrar adecuado dependiendo el tipo de cuenta
            cout << "------------------------" << endl;
        }
    }

    // Métodos para estadísticas
    int getTotalClientes() const {
        return clientes.size();
    }

    int getTotalCuentas() const {
        return cuentas.size();
    }

    double getPromedioSaldo() const {
        if (cuentas.empty()) {
            return 0.0;
        }

        double totalSaldo = 0.0;
        for (const auto& cuenta : cuentas) {
            totalSaldo += cuenta->getSaldo();
        }

        return totalSaldo / cuentas.size();
    }

    int getNumCuentasAhorros() const {
        int count = 0;
        for (const auto& cuenta : cuentas) {
            if (cuenta->getTipo() == "ahorros") {
                count++;
            }
        }
        return count;
    }

    int getNumCuentasCorrientes() const {
        int count = 0;
        for (const auto& cuenta : cuentas) {
            if (cuenta->getTipo() == "Corriente") {
                count++;
            }
        }
        return count;
    }

    // Método para aplicar interés a todas las cuentas de ahorro
    void aplicarInteresCuentasAhorro() {
        for (auto& cuenta : cuentas) {
            if (cuenta->getTipo() == "ahorros") {
                // Casteo seguro a CuentaAhorros para acceder a sus métodos específicos
                CuentaAhorros* cuentaAhorros = dynamic_cast<CuentaAhorros*>(cuenta);
                if (cuentaAhorros) {
                    // Aplicar interés: saldo = saldo + (saldo * tasaInteres)
                    double nuevoSaldo = cuentaAhorros->getSaldo() * (1 + cuentaAhorros->get_tasa_interes());
                    // Actualizar el saldo
                    cuentaAhorros->setSaldo(static_cast<int>(nuevoSaldo));
                }
            }
        }
    }

    // Método para guardar los datos del banco en un archivo JSON
    void guardarJSON(const string& nombreArchivo) {
        json bancoJSON;

        // Guardar nombre del banco
        bancoJSON["nombre"] = nombre;

        // Guardar clientes
        bancoJSON["clientes"] = json::array();
        for (const auto& cliente : clientes) {
            bancoJSON["clientes"].push_back(cliente.ToJson());
        }

        // Guardar cuentas
        bancoJSON["cuentas"] = json::array();
        for (const auto& cuenta : cuentas) {
            bancoJSON["cuentas"].push_back(cuenta->toJson());
        }

        // Escribir en archivo
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << bancoJSON.dump(4); // 4 espacios de indentación
            archivo.close();
            cout << "Datos guardados exitosamente en " << nombreArchivo << endl;
        } else {
            cerr << "Error al abrir el archivo para guardar datos" << endl;
        }
    }

    // Método estático para cargar un banco desde un archivo JSON
    static Banco cargarJSON(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se encontró archivo de datos. Creando nuevo banco..." << endl;
            return Banco("Banco Javeriano");
        }

        json bancoJSON;
        try {
            archivo >> bancoJSON;
            archivo.close();

            // Crear banco con el nombre almacenado
            Banco banco(bancoJSON["nombre"]);

            // Cargar clientes
            for (const auto& clienteJSON : bancoJSON["clientes"]) {
                int id = clienteJSON["id"];
                string nombre = clienteJSON["nombre"];
                string direccion = clienteJSON["direccion"];
                banco.agregarClienteConId(id, nombre, direccion);
            }

            // Cargar cuentas
            for (const auto& cuentaJSON : bancoJSON["cuentas"]) {
                int numero = cuentaJSON["numero"];
                int saldo = cuentaJSON["saldo"];
                int idCliente = cuentaJSON["idCliente"];
                string tipo = cuentaJSON["tipo"];

                if (tipo == "ahorros") {
                    double tasaInteres = cuentaJSON["tasaInteres"];
                    banco.agregarCuentaAhorrosConNumero(numero, saldo, idCliente, tasaInteres);
                } else if (tipo == "Corriente") {
                    int limiteSobregiro = cuentaJSON["Limite Sobregiro: "];
                    banco.agregarCuentaCorrienteConNumero(numero, saldo, idCliente, limiteSobregiro);
                }
            }

            cout << "Datos cargados exitosamente desde " << nombreArchivo << endl;
            return banco;
        } catch (const exception& e) {
            cerr << "Error al cargar datos del archivo: " << e.what() << endl;
            return Banco("Banco Javeriano");
        }
    }
};

#endif //BANCO_H