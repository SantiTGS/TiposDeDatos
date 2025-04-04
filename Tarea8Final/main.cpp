#include <iostream>
#include <string>
#include <limits>
#include "Banco.h"
#include "CuentaCorriente.h"

using namespace std;



int main() {
    // Cargar datos desde archivo o crear un nuevo banco
    Banco banco = Banco::cargarJSON("BancoJaveriano.json");

    // Menú principal
    while (true) {
        cout << "\n===== MENU BANCO JAVERIANO =====\n";
        cout << "1) MANTENIMIENTO DE CLIENTES\n";
        cout << "   1.1) Agregar Cliente\n";
        cout << "   1.2) Listar Clientes\n";
        cout << "2) MANTENIMIENTO DE CUENTAS\n";
        cout << "   2.1) Agregar Cuenta\n";
        cout << "   2.2) Listar Cuentas\n";
        cout << "3) ESTADISTICAS\n";
        cout << "   3.1) Total de Clientes\n";
        cout << "   3.2) Total de Cuentas\n";
        cout << "   3.3) Promedio del Saldo de las Cuentas\n";
        cout << "   3.4) Numero de Cuentas de Ahorro\n";
        cout << "   3.5) Numero de Cuentas Corrientes\n";
        cout << "4) OPERACIONES FINANCIERAS\n";
        cout << "   4.1) Aplicar Tasa de Interés a Cuentas de Ahorro\n";
        cout << "5) SALIR\n";
        cout << "   5.1) Guardar los datos en BancoJaveriano.json y cerrar el programa.\n";
        cout << "Seleccione una opción (ingrese el numero completo, ejemplo: 1.1): ";

        string opcionStr;
        getline(cin, opcionStr);

        // Agregar Cliente
        if (opcionStr == "1.1") {
            string nombre, direccion;
            cout << "Ingrese nombre del cliente: ";
            getline(cin, nombre);
            cout << "Ingrese dirección del cliente: ";
            getline(cin, direccion);
            banco.agregarCliente(nombre, direccion);
            cout << "Cliente agregado exitosamente." << endl;
        }
        // Listar Clientes
        else if (opcionStr == "1.2") {
            cout << "\nLISTA DE CLIENTES\n";
            cout << "------------------------" << endl;
            banco.mostrarClientes();
        }
        // Agregar Cuenta
        else if (opcionStr == "2.1") {
            int idCliente, saldo, tipo;
            cout << "Ingrese ID del cliente: ";
            cin >> idCliente;
            cout << "Ingrese saldo inicial: ";
            cin >> saldo;
            cout << "Tipo de cuenta (1: Ahorros, 2: Corriente): ";
            cin >> tipo;


            if (tipo == 1) {
                double tasaInteres;
                cout << "Ingrese tasa de interés : ";
                cin >> tasaInteres;

                banco.agregarCuentaAhorros(saldo, idCliente, tasaInteres);
                cout << "Cuenta de ahorros agregada exitosamente." << endl;
            } else if (tipo == 2) {
                int limiteSobregiro;
                cout << "Ingrese límite de sobregiro: ";
                cin >> limiteSobregiro;

                banco.agregarCuentaCorriente(saldo, idCliente, limiteSobregiro);
                cout << "Cuenta corriente agregada exitosamente." << endl;
            } else {
                cout << "Tipo de cuenta invalido." << endl;
            }
        }
        // Listar Cuentas
        else if (opcionStr == "2.2") {
            cout << "\nLISTA DE CUENTAS\n";
            cout << "------------------------" << endl;
            banco.mostrarCuentas();
        }
        // Total de Clientes
        else if (opcionStr == "3.1") {
            cout << "Total de clientes: " << banco.getTotalClientes() << endl;
        }
        // Total de Cuentas
        else if (opcionStr == "3.2") {
            cout << "Total de cuentas: " << banco.getTotalCuentas() << endl;
        }
        // Promedio del Saldo de las Cuentas
        else if (opcionStr == "3.3") {
            cout << "Promedio de saldo: " << banco.getPromedioSaldo() << endl;
        }
        // Número de Cuentas de Ahorro
        else if (opcionStr == "3.4") {
            cout << "Numero de cuentas de ahorro: " << banco.getNumCuentasAhorros() << endl;
        }
        // Número de Cuentas Corrientes
        else if (opcionStr == "3.5") {
            cout << "Numero de cuentas corrientes: " << banco.getNumCuentasCorrientes() << endl;
        }
        // Aplicar Tasa de Interés a Cuentas de Ahorro
        else if (opcionStr == "4.1") {
            banco.aplicarInteresCuentasAhorro();
            cout << "Intereses aplicados exitosamente a todas las cuentas de ahorro." << endl;
        }
        // Salir y guardar datos
        else if (opcionStr == "5.1" || opcionStr == "5") {
            cout << "Guardando datos y cerrando el programa...\n";
            banco.guardarJSON("BancoJaveriano.json");
            break;
        }
        // Opción inválida
        else {
            cout << "Opcion invalida. Intente nuevamente.\n";
        }
    }

    return 0;
}
