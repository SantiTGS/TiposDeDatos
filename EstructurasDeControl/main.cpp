#include <iostream>
#include <string>
#include <cctype> // Para usar tolower

using namespace std;

int main() {
    string palabra;
    char letra;

    cout << "Ingresa una palabra: "; cin >> palabra;
    cout << "Ingresa una letra para verificar si la palabra comienza con ella: "; cin >> letra;
    if (tolower(palabra[0]) == tolower(letra)) {
        cout << "¡La palabra comienza con la letra '" << letra << "'!" << endl;
    }
    cout << "Verificación completada." << endl;

    return 0;
}