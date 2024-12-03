#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <chrono>  // Incluir la librería para medir el tiempo
#include "ColoringOperation.h"
using namespace std;
using namespace chrono;  // Para usar los tipos de chrono

int main() {
    // Definimos los bordes del grafo
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 5}, {1, 6},
        {2, 3}, {2, 6}, {2, 7},
        {3, 4}, {3, 7}, {3, 8},
        {4, 8}, {4, 9},
        {5, 6}, {6, 7}, {7, 8}, {8, 9},
        {5, 10}, {6, 10}, {7, 11}, {8, 11},
        {10, 11}, {10, 12}, {11, 12}
    };
    
    // Creamos el grafo
    Graph graph(edges);
    graph.printGraph();

    // Creamos el estado inicial con el grafo
    State s(graph);
    s.printColor();

    // Creamos la operación de coloreo
    ColoringOperation co;

    // Medir tiempo de ejecución para el algoritmo de backtracking
    auto start = high_resolution_clock::now(); // Comienza el temporizador

    int c = co.backtrack(&s);  // Ejecutamos el backtracking

    auto stop = high_resolution_clock::now(); // Detiene el temporizador

    // Calcula la duración
    auto duration = duration_cast<milliseconds>(stop - start);  // Medimos en milisegundos

    // Mostramos resultados
    cout << "Numero de colores backtrack : " << c << endl;
    co.best->printColor();

    // Imprimir el tiempo de ejecución
    cout << "Tiempo de ejecucion: " 
         << duration.count() << " ms." << endl;

    return 0;
}
