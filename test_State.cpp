#include "State.h"
#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

void pruebaConstructorState() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    cout << "Prueba Constructor State: "
         << (estado.isAllColored() == false ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaGetVertex() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    int vertice = estado.getVertex();
    cout << "Prueba Obtener Vértice con Mayor Saturación: "
         << (vertice >= 0 && vertice <= 2 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaColorVertex() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    int vertice = estado.getVertex();
    estado.pushColorSelectVertex(vertice, 1);

    cout << "Prueba Colorear Vértice: "
         << (estado.isVertexColored(vertice) ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaActualizarSaturacion() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    int vertice = estado.getVertex();
    estado.pushColorSelectVertex(vertice, 1);

    int vecino = (vertice + 1) % 3;
    int saturacion = estado.saturationLevel[vecino];

    cout << "Prueba Actualizar Saturación: "
         << (saturacion > 0 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaisAllColored() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);
    State estado(grafo);

    while (!estado.isAllColored()) {
        int vertice = estado.getVertex();
        int color = grafo.getNumberOfColors();
        estado.pushColorSelectVertex(vertice, color);
    }

    cout << "Prueba Todos los Vértices Coloreados: "
         << (estado.isAllColored() ? "APROBADA" : "FALLIDA")
         << endl;
}

int main() {
    pruebaConstructorState();
    pruebaGetVertex();
    pruebaColorVertex();
    pruebaActualizarSaturacion();
    pruebaisAllColored();

    return 0;
}