#include "Funciones.h"

void acceso(Administrador& admin){
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

void menu(Administrador& admin){
    Asiento a;
    int opc, posicion;
    string archivo = "Administrador.csv";

    do{
        system("cls");
        cout<< "Administrador de asientos"<< endl
            << "=*=======================*="<< endl
            << "1. Ingresar los asientos."<< endl
            << "2. Agregar al inicio."<< endl
            << "3. Agregar al final."<< endl
            << "4. Agregar en una posicion."<< endl
            << "5. Eliminar al incio."<< endl
            << "6. Eliminar al final"<< endl
            << "7. Eliminar una posicion"<< endl
            << "8. Mostrar asientos."<< endl
            << "9. Respaldo."<< endl
            << "10. Recuperar."<< endl
            << "11. Buscar asiento."<< endl
            << "12. Ordenar (ascendente)."<< endl
            << "13. Ordenar (descendente)."<< endl
            << "14. Salir."<< endl;
        cout<< "Ingrese su opcion: ";
        cin>> opc;
        cin.ignore();

        switch(opc){
            case 1: {
                system("cls"); 
                
                cout<< "----- Datos del asiento -----"<< endl;
                ingresar_Asientos(a);

                try{
                    admin.agregarAsientos(a);
                    cout<< "Datos agregados correctamente!."<< endl;
                } catch(const overflow_error& e){
                    cout<< e.what()<< endl;
                    cin.ignore();
                }

                break;
            } 
            case 2: {
                system("cls");
                
                cout<< "----- Agregar al inicio -----"<< endl;
                ingresar_Asientos(a);

                try{
                    admin.agregarAlInicio(a);
                    cout<< "Asiento agregado al inicio."<< endl; 
                    cin.get();
                } catch(const overflow_error& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                }

                break;
            }
            case 3: {
                system("cls");

                cout<< "----- Agregar al final -----"<< endl;
                ingresar_Asientos(a);
                
                try{
                    admin.agregarAlFinal(a);
                    cout<< "Asiento agregado al final"<< endl;
                    cin.get();
                } catch(const overflow_error& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                }

                break;
            }
            case 4: {
                system("cls");

                admin.mostrarAsientos();
                cout<< "Ingrese la posicion: ";
                cin>> posicion;
                cin.ignore();

                ingresar_Asientos(a);

                try{
                    admin.agregarEnPosicion(a, posicion);
                    cout<< "Asiento agregado en la posicion indicada." << endl;
                    cin.ignore();
                } catch(const overflow_error& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                } catch(const out_of_range& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                }

                break;
            }
            case 5: {
                try{
                    admin.eliminarAlInicio();
                    cout<< "Asiento eliminado al inicio"<< endl;
                    cin.get();
                } catch(const underflow_error& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                }

                break;
            }
            case 6: {
                try{
                    admin.eliminarAlFinal();
                    cout<< "Asiento eliminado al final"<< endl;

                } catch(const underflow_error& e){
                    cout<< e.what()<< endl;
                    cin.ignore();
                }
                
                cin.get();
                break;
            }
            case 7: {
                system("cls");

                admin.mostrarAsientos();
                cout<< "Ingrese la posicion a eliminar: ";
                cin>> posicion;
                cin.ignore();

                try{
                    admin.eliminarEnPosicion(posicion);
                    cout<< "Asiento eliminado exitosamente!."<< endl;
                } catch(const underflow_error& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                } catch(const out_of_range& e){
                    cout<< e.what()<< endl;
                    cin.get();
                    cin.ignore();
                }

                cin.get();
                break;
            }
            case 8: { 
                system("cls");

                try{
                    admin.mostrarAsientos();
                    cin.ignore();
                } catch(const runtime_error& e){
                    cout<< e.what()<< endl;
                    cin.ignore();
                }
                
                break;
            }
            case 9:
                try{
                    cout<< "Haciendo respaldo..."<< endl;
                    Sleep(2000);
                    admin.respaldar_Datos(archivo);
                    cout<< "Asientos cargados correctamente a "<< archivo<< endl;
                } catch (const runtime_error& e){
                    cout<< e.what()<< endl;
                }
                cin.get();
                break;
            case 10:
                try{
                    cout<< "Buscando datos..."<< endl;
                    Sleep(2000);
                    admin.recuperar_Datos(archivo);
                    cout<< "Se han recuperado los datos encontrados."<< endl;
                } catch (const runtime_error& e){
                    cout<< e.what()<< endl;
                }

                cin.get();
                break;
            case 11: {
                int numeroBuscado;
                string filaEncontrada;
                
                cout<< "Ingrese el numero de asiento a buscar: ";
                cin>> numeroBuscado;
                cin.ignore();

                cout<< "Ingrese el numero de fila a buscar: ";
                getline(cin, filaEncontrada);

                int posicion = admin.buscar_Asiento(numeroBuscado, filaEncontrada);

                if(posicion != -1){
                    cout<< "Asiento encontrado en la posicion ["<< posicion<< "]"<< endl;
                    Asiento a = admin[posicion];
                    cout<< "Numero: "<< a.get_Numero()<< endl
                        << "Fila: "<< a.get_Fila()<< endl
                        << "Disponibilidad: "<< (a.get_Ocupado() ? "Ocupado" : "Libre")<< endl
                        << "Tipo: "<< a.get_Tipo()<< endl;
                        cin.get();
                } else {
                    cout<< "Asiento no encontrado."<< endl;
                }

                cin.get();
                break;
            }
            case 12:
                admin.orden_Ascendente();
                cout<< "Asientos ordenados de forma ascendente."<< endl;
                cin.get();
                break;
            case 13:
                admin.orden_Descendente();
                cout<< "Asientos ordenados de forma descendente."<< endl;
                cin.get();
                break;
            case 14:
                cout<< "Saliendo del programa...";
                break;
            default:
                cout<< "Error, opcion no valida. Intentelo de nuevo."<< endl; 
                break;
        }

    }while(opc != 14);
}

void ingresar_Asientos(Asiento& asiento) {
    int numero;
    string fila;
    bool ocupado;
    string tipo;

    cout<< "Ingrese numero de asiento: ";
    cin>> numero;
    cin.ignore();
    asiento.set_Numero(numero);
    
    cout<< "Ingrese la fila (A1, B2 o C3): ";
    cin>> fila;
    cin.ignore();
    asiento.set_Fila(fila);
    
    cout<< "Esta ocupado? (1- Si, 0- No): ";
    cin>> ocupado;
    cin.ignore();
    asiento.set_Ocupado(ocupado);
    
    cout<< "Ingrese tipo de asiento (REGULAR / VIP): ";
    cin>> tipo;
    cin.ignore();
    asiento.set_Tipo(tipo);
}