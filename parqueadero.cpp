#include <iostream>
#include <string>
using namespace std;


struct nodo {
    string Nombre;
    string CodigoSeguimiento;
    int Prioridad; 
    int Destino;   
    nodo *sig;
};

nodo *cab = 0, *aux, *aux2;


void registrar_envio() {
    aux = new nodo;

    cout << "Nombre del destinatario: ";
    cin.ignore(); 
    getline(cin, aux->Nombre);

    cout << "Código único de seguimiento del paquete: ";
    cin >> aux->CodigoSeguimiento;

    cout << "Prioridad del envío (1: Alta, 2: Media, 3: Baja): ";
    cin >> aux->Prioridad;
    while (aux->Prioridad < 1 || aux->Prioridad > 3) {
        cout << "Prioridad inválida. Ingrese nuevamente (1, 2 o 3): ";
        cin >> aux->Prioridad;
    }

    cout << "Destino (1: Nacional, 2: Internacional): ";
    cin >> aux->Destino;
    while (aux->Destino < 1 || aux->Destino > 2) {
        cout << "Destino inválido. Ingrese nuevamente (1 o 2): ";
        cin >> aux->Destino;
    }

    aux->sig = 0;

    if (!cab) {
        cab = aux; 
    } else {
        aux2 = cab;
        while (aux2->sig != 0) {
            aux2 = aux2->sig; 
        }
        aux2->sig = aux; 
    }

    cout << "Envío registrado exitosamente.\n";
}


void mostrar_envios() {
    if (!cab) {
        cout << "No hay envíos registrados.\n";
        return;
    }

    aux = cab;
    cout << "\nLista de envíos registrados:\n";
    while (aux != 0) {
        cout << "Nombre del destinatario: " << aux->Nombre << endl;
        cout << "Código de seguimiento: " << aux->CodigoSeguimiento << endl;
        cout << "Prioridad del envío: ";
        switch (aux->Prioridad) {
            case 1:
                cout << "Alta\n";
                break;
            case 2:
                cout << "Media\n";
                break;
            case 3:
                cout << "Baja\n";
                break;
        }
        cout << "Destino: " << (aux->Destino == 1 ? "Nacional" : "Internacional") << endl;
        cout << "-----------------------------\n";
        aux = aux->sig;
    }
}


void ordenar_envios() {
    if (!cab || !cab->sig) {
        cout << "No hay suficientes envíos para ordenar.\n";
        return;
    }

    nodo *i, *j;
    string tempNombre, tempCodigo;
    int tempPrioridad, tempDestino;

    for (i = cab; i->sig != 0; i = i->sig) {
        for (j = cab; j->sig != 0; j = j->sig) {
            if (
                j->Prioridad > j->sig->Prioridad || 
                (j->Prioridad == j->sig->Prioridad && j->Destino < j->sig->Destino) || 
                (j->Prioridad == j->sig->Prioridad && j->Destino == j->sig->Destino && j->CodigoSeguimiento > j->sig->CodigoSeguimiento)
            ) {
                
                tempNombre = j->Nombre;
                tempCodigo = j->CodigoSeguimiento;
                tempPrioridad = j->Prioridad;
                tempDestino = j->Destino;

                j->Nombre = j->sig->Nombre;
                j->CodigoSeguimiento = j->sig->CodigoSeguimiento;
                j->Prioridad = j->sig->Prioridad;
                j->Destino = j->sig->Destino;

                j->sig->Nombre = tempNombre;
                j->sig->CodigoSeguimiento = tempCodigo;
                j->sig->Prioridad = tempPrioridad;
                j->sig->Destino = tempDestino;
            }
        }
    }

    cout << "Lista de envíos ordenada correctamente.\n";
}


int main() {
    int opcion;

    do {
        cout << "\n---------- Menú ----------\n";
        cout << "1) Registrar Envío\n";
        cout << "2) Mostrar Envíos\n";
        cout << "3) Ordenar Envíos\n";
        cout << "4) Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrar_envio();
                break;
            case 2:
                mostrar_envios();
                break;
            case 3:
                ordenar_envios();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}