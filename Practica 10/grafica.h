#ifndef GRAFICA_H
#define GRAFICA_H

#define MAX 20

template <class T>
class Grafica {
    private:
        T MatAdy[MAX][MAX];
        int NumVer, Vertices[MAX];

    public:
        Grafica();
        void Lee();
        void Imprime();
        int Minimo (int val1, int val2);
        int Maximo (int val1, int val2);

        /* Metodos que calculan el arbol abarcador de costos mínimo */
        void Prim();
        void Kruskal();
};

#endif // GRAFICA_H