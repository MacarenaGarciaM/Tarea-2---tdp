// State.cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

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

// Obtiene un vértice no coloreado
int State::getVertex() {
    auto it = uncoloredVertices.begin();
    if (it == uncoloredVertices.end()) {
        return -1;  // Si no hay más vértices, retornamos -1
    }
    return *it;
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
