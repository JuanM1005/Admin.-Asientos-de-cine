#include <iostream>
#include <windows.h>
#include "Funciones.cpp" 

/* Aguirre Mares Juan Antonio
    Actividad 04 - BUSCAR / ORDENAR */

const int MAX_INTENTOS = 3;
void acceso(const int& password, Administrador& admin); 

int main() {
    const int password = 1534;
    Administrador a;

    acceso(password, a); 

    return 0;
}

void acceso(const int& password, Administrador& admin) { 
    int pass;
    int intentos = 0;

    while (intentos < MAX_INTENTOS) {
        cout<< "Ingrese la contrasenia para acceder: ";
        cin>> pass;

        if(pass == password) {
            cout << "Verificando contrasenia, espere un momento..." << endl;
            Sleep(2500);

            system("cls"); 
            menu(admin);  
            return;
        } else {
            intentos++;
            cout<< "Contrasenia no valida. Intento " << intentos << " de " << MAX_INTENTOS << " permitidos." << endl;
        }
    }

    cout<< "Acceso denegado. Demasiados intentos fallidos." << endl;
}
