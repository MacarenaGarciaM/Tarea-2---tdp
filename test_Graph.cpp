#include "Graph.h"
#include <iostream>
#include <vector>

using namespace std;

void pruebaConstructorPorDefecto() {
    Graph grafo;
    cout << "Prueba Constructor por Defecto: "
         << (grafo.getNumberOfColors() == 0 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaConstructorConAristas() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);

    cout << "Prueba Constructor con Aristas: " << endl;
    grafo.printGraph();
    cout << "Verifique la salida manualmente." << endl;
}

void pruebagetNumberOfColors() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);

    int coloresIniciales = grafo.getNumberOfColors();
    cout << "Prueba Obtener Número de Colores (Inicial): "
         << (coloresIniciales == 1 ? "APROBADA" : "FALLIDA")
         << endl;
}

void pruebaCanColor() {
    vector<vector<int>> aristas = {{0, 1}, {1, 2}, {2, 0}};
    Graph grafo(aristas);

    // Asignar colores manualmente para la prueba
    grafo.vertexColor[0] = 1;
    grafo.vertexColor[1] = 2;

    bool canColor1 = grafo.canColor(2, 1);
    bool canColor2 = grafo.canColor(2, 2);
    bool canColor3 = grafo.canColor(2, 3);

    cout << "Prueba Puede Colorear: "
         << ((canColor1 == false && canColor2 == false && canColor3 == true) ? "APROBADA" : "FALLIDA")
         << endl;
}

int main() {
    pruebaConstructorPorDefecto();
    pruebaConstructorConAristas();
    pruebagetNumberOfColors();
    pruebaCanColor();

    return 0;
}
