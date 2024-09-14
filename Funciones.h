#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <stdexcept>
#include <windows.h>

#include "Administrador.cpp"
#include "Asiento.cpp"

const int MAX_INTENTOS = 3;
const int password = 1345;

using namespace std;

void acceso(Administrador&);
void menu(Administrador&);
void ingresar_Asientos(Asiento&);


#endif