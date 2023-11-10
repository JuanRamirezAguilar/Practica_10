#include "grafica.h"

#include <iostream>
#include <fstream>

#define KRUSKALFILE "kruskal.txt"
#define PRIMFILE "prim.txt"

using namespace std;

template <class T>
Grafica<T>::Grafica() {
    int Ind1, Ind2;
    for (Ind1 = 0; Ind1 < MAX; Ind1++) {
        for (Ind2 = 0; Ind2 < MAX; Ind2++) {
            if (Ind1 != Ind2)
                MatAdy[Ind1][Ind2] = 999;
            else
                MatAdy[Ind1][Ind2] = 0;
        }
    }
    NumVer = 0;
}

template<class T>
void Grafica<T>::Lee() {
    int Aristas, Costo, Ind1, Origen, Destino;

    cout << "\n\nIngrese total de vértices de la gráfica:  ";
    cin >> NumVer;
    for (Ind1 = 0; Ind1 < NumVer; Ind1++) {
        cout << "\nIngrese el nombre del vértice:  ";
        cin >> Vertices[Ind1];
    }

    cout << "\n\nIngrese total de aristas de la gráfica:  ";
    cin >> Aristas;
    Ind1 = 0;

    while (Ind1 < Aristas) {
        cout << "\nVértice origen:  ";
        cin >> Origen;
        cout << "\nVértice destino:  ";
        cin >> Destino;
        cout << "\nCostos de ir de " << Origen << " a " << Destino << ": ";
        cin >> Costo;

        MatAdy[Origen - 1][Destino - 1] = Costo;
        MatAdy[Destino - 1][Origen - 1] = Costo;
        Ind1++;
    }
}

template<class T>
void Grafica<T>::Imprime() {
    cout << "\nMatriz de Adyacencia:\n\n";
    cout << "    ";
    for (int i = 0; i < NumVer; i++) {
        cout << Vertices[i] << "  ";
    }
    cout << "\n";

    for (int i = 0; i < NumVer; i++) {
        cout << Vertices[i] << "   ";
        for (int j = 0; j < NumVer; j++) {
            if (MatAdy[i][j] == 999) {
                cout << "INF ";
            } else {
                cout << MatAdy[i][j] << "   ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

template<class T>
void Grafica<T>::Prim() {
    int MCosto[MAX], VerAux[MAX], ind1, ind2, VerMen, MenCos;

    ofstream primArchivo;
    primArchivo.open(PRIMFILE, ios::out);
    if (!primArchivo) {
        throw ios::failure("Error al abrir el archivo");
    }

    for (ind1 = 0; ind1 < NumVer; ind1++) {
        MCosto[ind1] = MatAdy[0][ind1];
        VerAux[ind1] = 0;
    }

    cout << "\n\n\nArcos y costos del árbol abarcador de costo mínimo\n\n";
    cout << "\nVértice Vértice Costo \n";

    primArchivo << "Arcos y costos del árbol abarcador de costo mínimo" <<endl;
    primArchivo << endl << "Vértice Vértice Costo " <<endl;

    for (ind1 = 0; ind1 < NumVer - 1; ind1++) {
        MenCos = MCosto[1];
        VerMen = 1;
        for (ind2 = 2; ind2 < NumVer; ind2++)
            if (MCosto[ind2] < MenCos) {
                MenCos = MCosto[ind2];
                VerMen = ind2;
            }
        
        cout << "\n     " << Vertices[VerMen] << "  -   " << Vertices[VerAux[VerMen]] << "      " << MatAdy[VerMen][VerAux[VerMen]];
        
        primArchivo << "     " << Vertices[VerMen] << "   -   " << Vertices[VerAux[VerMen]] << "     " << MatAdy[VerMen][VerAux[VerMen]] <<endl;

        MCosto[VerMen] = 1000;
        for (ind2 = 1; ind2 < NumVer; ind2++)
            if  ((MatAdy[VerMen][ind2] < MCosto[ind2]) and MCosto[ind2] < 1000) {
                MCosto[ind2] = MatAdy[VerMen][ind2];
                VerAux[ind2] = VerMen;
            }
    }
    cout << "\n\n";
    primArchivo.close();
}

template<class T>
void Grafica<T>::Kruskal() {
    int ArisCosto[2 * MAX][3], Partic[MAX], Ind1, Ind2, Ver1, Ver2, TotalAris, Menor, Mayor, Band;

    ofstream kruskalArchivo;
    kruskalArchivo.open(KRUSKALFILE, ios::out);
    if (!kruskalArchivo) {
        throw ios::failure("Error al abrir el archivo");
    }

    for (Ind1 = 0; Ind1 < NumVer; Ind1++)
        Partic[Ind1] = Ind1;

    Ver1 = 0;
    Ver2 = 0;
    TotalAris = 0;

    for (Ind1 = 0; Ind1 < NumVer; Ind1++)
        for (Ind2 = 0; Ind2 < NumVer; Ind2++)
            if (MatAdy[Ind1][Ind2] != 0 and MatAdy[Ind1][Ind2] != 999) {
                ArisCosto[Ver1][Ver2++] = Ind1;
                ArisCosto[Ver1][Ver2++] = Ind2;
                ArisCosto[Ver1++][Ver2] = MatAdy[Ind1][Ind2];
                Ver2 = 0;
                TotalAris++;
            }

    Band = 0;
    while (Band != 1) {
        Menor = 999;
        for (Ind1 = 0; Ind1 < TotalAris; Ind1++)
            if (ArisCosto[Ind1][2] < Menor) {
                Ver1 = ArisCosto[Ind1][0];
                Ver2 = ArisCosto[Ind1][1];
                Menor = ArisCosto[Ind1][2];
                Ind2 = Ind1;
            }

        ArisCosto[Ind2][2] = 999;
        if (Partic[Ver1] != Partic[Ver2]) {
            cout << "\nVértice: " << Vertices[Ver1] << " Vértice: " << Vertices[Ver2] << " Costo: " << MatAdy[Ver1][Ver2] << "\n\n";
            kruskalArchivo << "Vértice: " << Vertices[Ver1] << " Vértice: " << Vertices[Ver2] << " Costo: " << MatAdy[Ver1][Ver2] <<endl;
            Mayor = Maximo(Partic[Ver1], Partic[Ver2]);

            for (Ind1 = 0; Ind1 < NumVer; Ind1++)
                if (Ind1 == Ver1 or Ind1 == Ver2 or Partic[Ind1] == Mayor)
                    Partic[Ind1] = Minimo(Partic[Ver1], Partic[Ver2]);
        }

        Ind1 = 0;
        while (Ind1 < NumVer and !Band) {
            if (Partic[Ind1] != 0)
                Band = 1;
            Ind1++;
        }
        Band = !Band;
    }
    kruskalArchivo.close();
}

template<class T>
int Grafica<T>::Minimo (int val1, int val2) {
    return val1 < val2 ?  val1 : val2;
}

template<class T>
int Grafica<T>::Maximo (int val1, int val2) {
    return val1 > val2 ?  val1 : val2;
}