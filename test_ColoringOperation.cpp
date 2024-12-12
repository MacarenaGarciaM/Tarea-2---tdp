#include "ColoringOperation.h"
#include "State.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void pruebaConstructorColoringOperation() {
    ColoringOperation operacion;
    cout << "Prueba Constructor ColoringOperation: "
         << (operacion.upperBound == INT_MAX ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaGreedyColoring() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    ColoringOperation operacion;
    int coloresUsados = operacion.greedyColoring(&estado);

    cout << "Prueba Greedy Coloring: "
         << (coloresUsados == 3 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaBranchAndBound() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    ColoringOperation operacion;
    int coloresOptimos = operacion.branchAndBound(&estado);

    cout << "Prueba Branch and Bound: "
         << (coloresOptimos == 3 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebacalculateLowerBound() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    ColoringOperation operacion;
    int cotaInferior = operacion.calculateLowerBound(&estado);

    cout << "Prueba Calcular Cota Inferior: "
         << (cotaInferior == 3 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebafindLargestClique() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);

    ColoringOperation operacion;
    int Clique = operacion.findLargestClique(grafo);

    cout << "Prueba Encontrar Clique Mas Grande: "
         << (Clique == 3 ? "APROBADA" : "FALLIDA")
         << endl;
}

int main() {
    pruebaConstructorColoringOperation();
    pruebaGreedyColoring();
    pruebaBranchAndBound();
    pruebacalculateLowerBound();
    pruebafindLargestClique();

    return 0;
}
