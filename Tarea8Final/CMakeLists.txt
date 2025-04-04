cmake_minimum_required(VERSION 3.30)
project(Tarea8Final)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tarea8Final main.cpp
        Cliente.cpp
        Cliente.h
        CuentaAhorros.cpp
        CuentaAhorros.h
        CuentaCorriente.cpp
        CuentaCorriente.h
        Cuenta.cpp
        Cuenta.h
        Banco.cpp
        Banco.h)
