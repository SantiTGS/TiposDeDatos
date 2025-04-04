//
// Created by 57318 on 2/04/2025.
//

#ifndef CUENTA_H
#define CUENTA_H
#include <iostream>
#include <string>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

class Cuenta { //Clase abstracta, similar a una interface(java)
protected:
    int numero;
    int saldo;
    int idCliente;

public:
    Cuenta(int numero, int saldo, int id_cliente)
        : numero(numero),saldo(saldo),idCliente(id_cliente) {
    }

    virtual ~Cuenta() = default; // Destructor virtual para la herencia

    int getNumero() const {
        return numero;
    }

    int getSaldo() const {
        return saldo;
    }

    void setSaldo(int nuevoSaldo) {
        saldo = nuevoSaldo;
    }

    int getIdCliente() const {
        return idCliente;
    }

    virtual void mostrar() const = 0; //Virtual pura

    virtual json toJson() const {
        return json{
            {"numero", numero},
            {"saldo",saldo},
            {"idCliente",idCliente},
            {"tipo","Cuenta"}
        };
    }

    virtual string getTipo() const = 0; //Devolvera si es ahorros o corriente dependiendo el tipo de cuenta.
};


#endif //CUENTA_H