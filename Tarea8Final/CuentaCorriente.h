//
// Created by 57318 on 2/04/2025.
//

#ifndef CUENTACORRIENTE_H
#define CUENTACORRIENTE_H
#include "Cuenta.h"


class CuentaCorriente : public Cuenta {
private:
    int limiteSobregiro;

public:
    CuentaCorriente(int numero, int saldo, int id_cliente, int limite_sobregiro)
        : Cuenta(numero, saldo, id_cliente),limiteSobregiro(limite_sobregiro) {
    }

    int get_limiteSobregiro() const {
        return limiteSobregiro;
    }

    void mostrar() const override {
        cout << "Numero de la cuenta: " << numero << endl;
        cout << "Saldo :" << saldo << endl;
        cout << "Id del cliente: " << idCliente << endl;
        cout << "tipo: Corriente "
                "LimiteSobregiro: " << limiteSobregiro << endl;
    }

    json toJson() const override {
        return json{
                {"idCliente", idCliente},
                {"tipo", "Corriente"},
                {"Limite Sobregiro: ", limiteSobregiro},
                {"numero", numero},
                {"saldo", saldo}
        };
    }

    string getTipo() const override {
        return "Corriente";
    }
};

#endif //CUENTACORRIENTE_H