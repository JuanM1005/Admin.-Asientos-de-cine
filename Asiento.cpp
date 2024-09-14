#include "Asiento.h"

Asiento::Asiento(){
    numero = 0;
    fila = "";
    ocupado = false;
    tipo = "Regular";
}

int Asiento::get_Numero(){
    return numero;
}

std::string Asiento::get_Fila(){
    return fila;
}

bool Asiento::get_Ocupado(){
    return ocupado;
}

std::string Asiento::get_Tipo(){
    return tipo;
}

void Asiento::set_Numero(int num_asiento){
    numero = num_asiento;
}

void Asiento::set_Fila(std::string num_fila){
    fila = num_fila;
}

void Asiento::set_Ocupado(bool disponibilidad){
    ocupado = disponibilidad;
}

void Asiento::set_Tipo(std::string tipo_boleto){
    tipo = tipo_boleto;
}