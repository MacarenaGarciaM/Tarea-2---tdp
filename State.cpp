#include <iostream>
#include <set>
#include <algorithm>
#include "State.h"
//Clase que se encarga de almacenar el estado actual de la coloración de un grafo, así como de realizar operaciones sobre él.


/*
Entrada: void
Salida: void
Descripción: Constructor por defecto de la clase State.
*/
State::State() {}

/*
Entrada: Graph graph
Salida: void
Descripción: Constructor de la clase State que recibe un grafo y lo inicializa.
*/
State::State(Graph graph) {
    this->graph = graph;
    for (const auto& par : graph.vertexNeighbors) {
        uncoloredVertices.insert(par.first);
        saturationLevel[par.first] = 0; // Inicializar saturación en 0
    }
}

/*
Entrada: void
Salida: int
Descripción: Obtiene el vértice con mayor saturación y grado máximo, utiliza un algoritmo DSATUR.
*/
int State::getVertex() {
    int maxSaturation = -1;
    int selectedVertex = -1;

    for (int vertex : uncoloredVertices) {
        int saturation = saturationLevel[vertex];
        int degree = graph.vertexNeighbors[vertex].size();

        if (saturation > maxSaturation || 
            (saturation == maxSaturation && degree > graph.vertexNeighbors[selectedVertex].size())) {
            maxSaturation = saturation;
            selectedVertex = vertex;
        }
    }

    // Opción de desempate aleatorio (opcional)
    std::vector<int> candidates;
    for (int vertex : uncoloredVertices) {
        int saturation = saturationLevel[vertex];
        int degree = graph.vertexNeighbors[vertex].size();
        if (saturation == maxSaturation && degree == graph.vertexNeighbors[selectedVertex].size()) {
            candidates.push_back(vertex);
        }
    }

    if (!candidates.empty()) {
        selectedVertex = candidates[rand() % candidates.size()]; // Desempate aleatorio
    }

    return selectedVertex;
}


/* 
Entrada: int vertex
Salida: void
Descripción: Actualiza la saturación de los vecinos de un vértice dado.
*/
void State::updateSaturation(int vertex) {
    for (int neighbor : graph.vertexNeighbors[vertex]) {
        if (!isVertexColored(neighbor)) {
            std::set<int> uniqueColors;
            for (int n : graph.vertexNeighbors[neighbor]) {
                if (isVertexColored(n)) {
                    uniqueColors.insert(graph.vertexColor[n]);
                }
            }
            saturationLevel[neighbor] = uniqueColors.size();
        }
    }
}

/*
Entrada: int vertex, int color
Salida: void
Descripción: Colorea un vértice, lo agrega a los coloreados y actualiza saturaciones
 */
void State::pushColorSelectVertex(int vertex, int color) {
    graph.vertexColor[vertex] = color;
    coloredVertices.insert(vertex);
    uncoloredVertices.erase(vertex);
    updateSaturation(vertex); // Actualizar saturaciones
}

/*
Entrada: int vertex
Salida: bool
Descripción: Verifica si un vértice está coloreado.
*/
bool State::isVertexColored(int vertex) {
    return coloredVertices.find(vertex) != coloredVertices.end();
}

/*
Entrada: void
Salida: bool
Descripción: Verifica si todos los vértices están coloreados.
*/
bool State::isAllColored() {
    return uncoloredVertices.empty();
}

/*
Entrada: void
Salida: void
Descripción: Imprime los vértices y sus colores.
*/
void State::printColor() {
    // Vector para almacenar las claves y luego ordenarlas
    std::vector<int> vertices;
    for (const auto& pair : graph.vertexColor) {
        vertices.push_back(pair.first);
    }

    // Vértices en orden creciente
    std::sort(vertices.begin(), vertices.end());

    // Imprimir los colores en orden de los vértices
    for (int vertex : vertices) {
        std::cout << vertex << " " << graph.vertexColor[vertex] << "\n";
    }
    std::cout << std::endl;
}
