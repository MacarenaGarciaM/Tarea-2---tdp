// Graph.cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "Graph.h"

using namespace std;

// Constructor por defecto
Graph::Graph() {
}

// Constructor con lista de aristas
Graph::Graph(std::vector<std::vector<int>> edges) {
    for (const std::vector<int>& edge : edges) {
        vertexNeighbors[edge[0]].insert(edge[1]);
        vertexNeighbors[edge[1]].insert(edge[0]);
    }
}

// Método para obtener el número de colores utilizados
int Graph::getNumberOfColors() {
    std::set<int> colors;  // Usamos un set para almacenar colores únicos
    for (const auto& par : vertexColor) {
        colors.insert(par.second);
    }
    return colors.size();
}

// Método para verificar si un vértice puede ser coloreado con un color dado
bool Graph::canColor(int vertex, int color) {
    for (int neighbor : vertexNeighbors[vertex]) {
        if (vertexColor.find(neighbor) != vertexColor.end() && 
            vertexColor[neighbor] == color) {
            return false;  // Si el vecino ya tiene el color, no se puede usar
        }
    }
    return true;
}

// Método para imprimir el grafo
void Graph::printGraph() {
    for (const auto& par : vertexNeighbors) {
        std::cout << par.first << ": ";
        for (int neighbor : par.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}
