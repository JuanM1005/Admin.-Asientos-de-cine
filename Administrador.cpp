#include "Administrador.h"

Administrador::Administrador(){
    total_Asientos = 0;
}

bool Administrador::lista_Vacia(){
    return total_Asientos == 0;
}

bool Administrador::lista_Llena(){
    return total_Asientos == MAX_ASIENTOS;
}

void Administrador::agregarAsientos(Asiento& a){
    if(lista_Llena()){
        throw std::overflow_error("La lista de asientos esta llena."); 
    }
    lista_Asientos[total_Asientos++] = a;
}

void Administrador::agregarAlInicio(Asiento& nuevo_Asiento){
    if(lista_Llena()){
        throw std::overflow_error("La lista de asientos esta llena."); /*Se lanza una excepcion std::overflow_error
        para indicar que el usuario quiere agregar un elemento 
        mas alla del limite de asientos permitido*/
    }
    for(int i = total_Asientos; i > 0; i--){
        lista_Asientos[i] = lista_Asientos[i - 1];
    }
    lista_Asientos[0] = nuevo_Asiento;
    total_Asientos++;
}

void Administrador::agregarAlFinal(Asiento& nuevo_Asiento){
    if(lista_Llena()){
        throw std::overflow_error("La lista de asientos esta llena.");
    }
    lista_Asientos[total_Asientos++] = nuevo_Asiento;
}

void Administrador::agregarEnPosicion(Asiento& reemplazo_Asiento, int posicion){
    if(lista_Llena()){
       throw std::overflow_error("La lista de asientos esta llena."); 
    } 
    if(posicion < 0 || posicion >= total_Asientos){
        throw std::out_of_range("Error, la posicion no es valida."); //Se lanza una excepcion std::out_of_range que indica que la posicion que ingreso el usuario esta fuera de rango
    } else {
        for(int i = total_Asientos; i > posicion; i--){
            lista_Asientos[i] = lista_Asientos[i - 1];
        }
        lista_Asientos[posicion] = reemplazo_Asiento;
        total_Asientos++;
    }
}

void Administrador::eliminarAlInicio(){
    if(lista_Vacia()){
        throw std::underflow_error("Error, la lista esta vacia."); /*Se lanza una excepción
    std::underflow_error para señalar que la operación no puede completarse debido
    a que la lista no contiene elementos.*/
    }
    for(int i = 0; i < total_Asientos - 1; i++){
        lista_Asientos[i] = lista_Asientos[i + 1]; //Se desplazan los elementos de la lista hacia la izquierda, copiando el valor a la anterior posicion
    }
    total_Asientos--;
}

void Administrador::eliminarAlFinal(){
    if(lista_Vacia()){
        throw std::underflow_error("Error, la lista esta vacia.");
    }
    total_Asientos--;
}

void Administrador::eliminarEnPosicion(int posicion){
    if(lista_Vacia()){
        throw std::underflow_error("Error, la lista esta vacia.");
    } 
    if(posicion < 0 || posicion >= total_Asientos){
        throw std::out_of_range("Error, la posicion no es valida."); 
    } 
    //Mover los elementos a la izquierda
   for(int i = posicion; i < total_Asientos - 1; i++){
        lista_Asientos[i] = lista_Asientos[i + 1];
   }
   total_Asientos--;
}

void Administrador::mostrarAsientos() {
    if (lista_Vacia()) {
        throw std::runtime_error("Error, no hay asientos registrados para mostrar.");
    }

    if(!archivoRecuperado.empty()){
        std::cout<< "Datos recuperados de "<< archivoRecuperado<< std::endl;
    }

    std::cout<< std::endl<< "SALA MIXTA (REGULAR / VIP)" << std::endl;
    std::cout<< std::left<< std::setw(12)<< "[Posicion]" 
             << std::setw(9)<< "Asiento" 
             << std::setw(6)<< "Fila" 
             << std::setw(16)<< "Disponibilidad" 
             << std::setw(10)<< "Tipo"<< std::endl;

    std::cout << "=================================================" << std::endl;

    for (int i = 0; i < total_Asientos; i++) {
        std::cout<< std::left<< std::setw(12) << i
                 << std::setw(10)<< lista_Asientos[i].get_Numero()
                 << std::setw(6)<< lista_Asientos[i].get_Fila()
                 << std::setw(15)<< (lista_Asientos[i].get_Ocupado() ? "Ocupado" : "Libre")
                 << std::setw(10)<< lista_Asientos[i].get_Tipo()<< std::endl;
    }
}

void Administrador::respaldar_Datos(std::string nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        throw std::runtime_error("Error al abrir el archivo.");
    }

    // Encabezado
    archivo << "Número, Fila, Ocupado, Tipo" << std::endl;

    // Datos
    for (int i = 0; i < total_Asientos; i++) {
        Asiento a = lista_Asientos[i];
        archivo<< a.get_Numero()<< ","
               << a.get_Fila()<< ","
               << a.get_Ocupado()<< ","
               << a.get_Tipo()<< std::endl;
    }

    archivo.close();
}

void Administrador::recuperar_Datos(std::string nombreArchivo){
    std::ifstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        throw std::runtime_error("Error al abrir el archivo.");
    }

    archivoRecuperado = nombreArchivo;

    std::string hNumero, hFila, hOcupado, hTipo;
    getline(archivo, hNumero, ',');
    getline(archivo, hFila, ',');
    getline(archivo, hOcupado, ',');
    getline(archivo, hTipo, '\n');

    while (true){
        std::string numero, fila, ocupado, tipo;
        getline(archivo, numero, ',');
        if (archivo.eof()) break;
        getline(archivo, fila, ',');
        getline(archivo, ocupado, ',');
        getline(archivo, tipo, '\n');

        Asiento a;
        a.set_Numero(std::stoi(numero));
        a.set_Fila(fila); 
        a.set_Ocupado(ocupado == "1");
        a.set_Tipo(tipo);

        agregarAsientos(a);
        
    }
    archivo.close();
}

int Administrador::buscar_Asiento(int numeroEncontrar, std::string filaEncontrar){
    for(int i = 0; i < total_Asientos; i++){
        if(lista_Asientos[i].get_Numero() == numeroEncontrar && lista_Asientos[i].get_Fila() == filaEncontrar){
            return i;
        }
    }
    return -1; // Si no se encontro el numero de asiento
}

void Administrador::orden_Ascendente() {
    for (int i = 0; i < total_Asientos - 1; i++) {
        int indiceMinimo = i;
        for (int j = i + 1; j < total_Asientos; j++) {
            // Primero comparar por fila
            if (lista_Asientos[j].get_Fila() < lista_Asientos[indiceMinimo].get_Fila()) {
                indiceMinimo = j;
            } 
            // Si las filas son iguales, comparar por número de asiento
            else if (lista_Asientos[j].get_Fila() == lista_Asientos[indiceMinimo].get_Fila() &&
                     lista_Asientos[j].get_Numero() < lista_Asientos[indiceMinimo].get_Numero()) {
                indiceMinimo = j;
            }
        }
        // Si se encontró un índice mínimo diferente al actual, intercambiar asientos
        if (indiceMinimo != i) {
            Asiento temp = lista_Asientos[indiceMinimo];
            lista_Asientos[indiceMinimo] = lista_Asientos[i];
            lista_Asientos[i] = temp;
        }
    }
}

void Administrador::orden_Descendente() {
    for (int i = 0; i < total_Asientos - 1; i++) {
        int indiceMaximo = i;
        for (int j = i + 1; j < total_Asientos; j++) {
            // Primero comparar por fila en orden descendente
            if (lista_Asientos[j].get_Fila() > lista_Asientos[indiceMaximo].get_Fila()) {
                indiceMaximo = j;
            } 
            // Si las filas son iguales, comparar por número de asiento en orden descendente
            else if (lista_Asientos[j].get_Fila() == lista_Asientos[indiceMaximo].get_Fila() &&
                     lista_Asientos[j].get_Numero() > lista_Asientos[indiceMaximo].get_Numero()) {
                indiceMaximo = j;
            }
        }
        // Si se encontró un índice máximo diferente al actual, intercambiar asientos
        if (indiceMaximo != i) {
            Asiento temp = lista_Asientos[indiceMaximo];
            lista_Asientos[indiceMaximo] = lista_Asientos[i];
            lista_Asientos[i] = temp;
        }
    }
}

