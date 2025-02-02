cmake_minimum_required(VERSION 3.30)
project(EstructurasDeControl)

set(CMAKE_CXX_STANDARD 20)

add_executable(EstructurasDeControl main.cpp)
add_executable(verificaPositivo cmake-build-debug/verificaPositivo.cpp)
add_executable(verificaAprobado cmake-build-debug/verificaAprobado.cpp)
add_executable(verificaCandidato cmake-build-debug/verificaCandidato.cpp)
add_executable(evaluacionCalificacion cmake-build-debug/evaluacionCalificacion.cpp)
