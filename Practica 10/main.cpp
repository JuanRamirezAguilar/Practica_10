#include <iostream>
#include <fstream>
#include <windows.h>

#include "grafica.h"
#include "grafica.cpp"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

enum OPCIONES {INGRESAR = 0, KRUSKAL, PRIM, SALIR};

using namespace std;

void pausa();
int menu ();
void ingresar(Grafica<int> &);
void kruskal(Grafica<int> &);
void prim(Grafica<int> &);
void default_mesage();

int main () {
    int opc;
    Grafica<int> grafo;

    SetConsoleOutputCP(CP_UTF8);
    do {
        switch (opc = menu()) {
            case INGRESAR: ingresar(grafo); break;
            case KRUSKAL: kruskal(grafo); break;
            case PRIM: prim(grafo); break;
            case SALIR: break;
            default: default_mesage(); break;
        }
    } while (opc != SALIR);

    return 0;
}

void pausa() { cin.clear(); cin.sync(); cin.ignore(); }

int menu () {
    system(CLEAR);

    int opcMenu;
    cout << "\t* Menú - Red de carreteras *" <<endl<<endl;
    cout << "0) Ingresar datos e imprimir matriz de adyacencias." <<endl;
    cout << "1) Kruskal." <<endl;
    cout << "2) Prim." <<endl;
    cout << "3) Salir." <<endl;
    cout << "Elige tu opcion: ";
    cin >> opcMenu;

    return opcMenu;
}

void ingresar(Grafica<int> & miGrafo) {
    system(CLEAR);
    miGrafo.Lee();
    miGrafo.Imprime();
    pausa();
}

void kruskal(Grafica<int> & miGrafo) {
    miGrafo.Kruskal();
    pausa();
}

void prim(Grafica<int> & miGrafo) {
    miGrafo.Prim();
    pausa();
}

void default_mesage() {
    cout << "Respuesta incorrecta, intentelo de nuevo..."; pausa();
}
