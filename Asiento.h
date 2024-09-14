#ifndef ASIENTO_H
#define ASIENTO_H

#include <iostream>
#include <string>

class Asiento{
    private:
        int numero; //Numero de asiento
        std::string fila;
        bool ocupado; 
        std::string tipo; //VIP O NORMAL
    public:
        Asiento();
        int get_Numero();
        std::string get_Fila();
        bool get_Ocupado();
        std::string get_Tipo();

        void set_Numero(int);
        void set_Fila(std::string);
        void set_Ocupado(bool);
        void set_Tipo(std::string);
};

#endif