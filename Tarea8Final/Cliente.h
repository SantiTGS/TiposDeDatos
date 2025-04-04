//
// Created by 57318 on 2/04/2025.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <string>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;


class Cliente {
private:
    int id;
    string nombre;
    string direccion;
public:
    Cliente(int id, const string &nombre, const string &direccion)
        : id(id),nombre(nombre),direccion(direccion) {

    }

    int getId() const {
        return id;
    }

    string getNombre() const {
        return nombre;
    }

    string getDireccion() const {
        return direccion;
    }

    void mostrar() const {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Direccion: " << direccion << endl;
    }



    json ToJson() const {
        return json{
            {"id", id},
            {"nombre" ,nombre},
            {"direccion" ,direccion,}

        };
    }

};



#endif //CLIENTE_H
