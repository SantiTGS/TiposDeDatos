//
// Created by 57318 on 2/04/2025.
//

#ifndef CUENTAAHORROS_H
#define CUENTAAHORROS_H
#include "Cuenta.h"


class CuentaAhorros : public Cuenta{
private:
    double tasaInteres;

public:
    CuentaAhorros(int numero, int saldo, int id_cliente, double tasa_interes)
        : Cuenta(numero, saldo, id_cliente),tasaInteres(tasa_interes) {
    }

    double get_tasa_interes() const {
        return tasaInteres;
    }

    void mostrar() const override {
        cout << "Numero de la cuenta: " << numero << endl;
        cout << "Saldo :"<< saldo << endl;
        cout << "Id De el Cliente :" << idCliente << endl;
        cout << "Tipo : Ahorros, "
                "Tasa de Interes: " << tasaInteres << endl;
    }

    json toJson() const override {
        return json{
            {"idCliente",idCliente},
            {"tipo","ahorros"},
            {"tasaInteres",tasaInteres},
            {"numero",numero},
            {"saldo",saldo},
        };
    }

    string getTipo() const override {
        return "ahorros";
    }
};



#endif //CUENTAAHORROS_H
