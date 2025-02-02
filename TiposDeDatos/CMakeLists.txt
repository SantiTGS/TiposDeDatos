cmake_minimum_required(VERSION 3.30)
project(TiposDeDatos)

set(CMAKE_CXX_STANDARD 20)

add_executable(TiposDeDatos main.cpp)
add_executable(conversionTipos cmake-build-debug/conversionTipos.cpp
        cmake-build-debug/main.cpp)
add_executable(conversionExplicita cmake-build-debug/conversionExplícita.cpp)
add_executable(usoDeConstantes cmake-build-debug/usoDeConstantes.cpp)
