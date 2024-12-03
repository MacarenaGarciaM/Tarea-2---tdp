// State.cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "ColoringOperation.h"

using namespace std;

#include "State.h"

// Constructor por defecto
State::State() {}

// Constructor con un grafo dado
State::State(Graph graph) {
    this->graph = graph;
    // Sacamos todos los vértices ya que son llaves en el mapa
    for (const auto& par : graph.vertexNeighbors) {
        uncoloredVertices.insert(par.first);
    }
}

// En State.cpp: Obtener el vértice con mayor grado de saturación
int State::getVertex() {
    int maxSaturation = -1;
    int selectedVertex = -1;

    for (int vertex : uncoloredVertices) {
        int saturation = 0;
        std::set<int> uniqueColors;
        for (int neighbor : graph.vertexNeighbors[vertex]) {
            if (isVertexColored(neighbor)) {
                uniqueColors.insert(graph.vertexColor[neighbor]);
            }
        }
        saturation = uniqueColors.size();

        // Desempate por grado del vértice
        int degree = graph.vertexNeighbors[vertex].size();
        if (saturation > maxSaturation || 
            (saturation == maxSaturation && degree > graph.vertexNeighbors[selectedVertex].size())) {
            maxSaturation = saturation;
            selectedVertex = vertex;
        }
    }
    return selectedVertex;
}



// Colorea un vértice, lo agrega a los coloreados y lo elimina de los no coloreados
void State::pushColorSelectVertex(int vertex, int color) {
    graph.vertexColor[vertex] = color;
    coloredVertices.insert(vertex);
    uncoloredVertices.erase(vertex);
}

// Verifica si un vértice está coloreado
bool State::isVertexColored(int vertex) {
    return coloredVertices.find(vertex) != coloredVertices.end();
}

// Verifica si todos los vértices están coloreados
bool State::isAllColored() {
    return uncoloredVertices.size() == 0;
}

// Imprime los colores de los vértices
void State::printColor() {
    for (const auto& par : graph.vertexColor) {
        std::cout << par.first << "->" << par.second << " ";
    }
    std::cout << std::endl;
}

// Incrementa el número de colores disponibles
void State::incrementColor() {
    int c = graph.getNumberOfColors();
    availableColors.insert(c);
}

// Calcula el límite inferior basado en un heurístico
int State::calculateLowerBound() {
    // Crear una copia del estado actual
    State temp(*this);

    // Usar el algoritmo codicioso para obtener el número mínimo de colores posible
    ColoringOperation co;
    return co.greedyColoring(&temp);  // Devuelve el número de colores usados
}


// Calcula el límite superior usando coloreo codicioso
int State::calculateUpperBound() {
    State temp(*this); // Crear copia temporal del estado actual
    ColoringOperation co;
    return co.greedyColoring(&temp); // Pasa correctamente el puntero
}


