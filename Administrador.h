#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Asiento.h"
#include <iomanip>
#include <fstream>

const int MAX_ASIENTOS = 18; //Numero de asientos fijos

class Administrador{
    private:
        std::string archivoRecuperado;
        Asiento lista_Asientos[MAX_ASIENTOS];
        int total_Asientos;
    public:
        Administrador();
        bool lista_Vacia();
        bool lista_Llena();
        void agregarAsientos(Asiento&);
        void agregarAlInicio(Asiento&);
        void agregarAlFinal(Asiento&);
        void agregarEnPosicion(Asiento&, int);
        void eliminarAlInicio();
        void eliminarAlFinal();
        void eliminarEnPosicion(int);
        void mostrarAsientos();
        void respaldar_Datos(std::string);
        void recuperar_Datos(std::string);
        int buscar_Asiento(int, std::string);

        //Sobrecarga
        Asiento operator[] (int posicion){
            if(posicion < 0 || posicion > total_Asientos){
                std::cout<< "Posicion no valida.";
                exit(1);
            }
            return lista_Asientos[posicion];
        }

        void orden_Ascendente();
        void orden_Descendente();
};

#endif