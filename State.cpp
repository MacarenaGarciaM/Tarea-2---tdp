#include <iostream>
#include <set>
#include "State.h"

// Constructor por defecto
State::State() {}

// Constructor con un grafo dado
State::State(Graph graph) {
    this->graph = graph;
    for (const auto& par : graph.vertexNeighbors) {
        uncoloredVertices.insert(par.first);
        saturationLevel[par.first] = 0; // Inicializar saturación en 0
    }
}

// Obtener el vértice con mayor grado de saturación (Dsatur)
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
    return selectedVertex;
}

// Actualizar la saturación de los vecinos de un vértice
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

// Colorea un vértice, lo agrega a los coloreados y actualiza saturaciones
void State::pushColorSelectVertex(int vertex, int color) {
    graph.vertexColor[vertex] = color;
    coloredVertices.insert(vertex);
    uncoloredVertices.erase(vertex);
    updateSaturation(vertex); // Actualizar saturaciones
}

// Verifica si un vértice está coloreado
bool State::isVertexColored(int vertex) {
    return coloredVertices.find(vertex) != coloredVertices.end();
}

// Verifica si todos los vértices están coloreados
bool State::isAllColored() {
    return uncoloredVertices.empty();
}

// Imprime los colores de los vértices
void State::printColor() {
    for (const auto& par : graph.vertexColor) {
        std::cout << par.first << " " << par.second << "\n";
    }
    std::cout << std::endl;
}
