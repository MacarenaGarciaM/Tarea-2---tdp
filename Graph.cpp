//Clase que representa un grafo no dirigido y no ponderado, con métodos que calculan el número de colores utilizados y verifican si un vértice puede ser coloreado con un color dado.
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "Graph.h"

using namespace std;

/*
Entrada: void
Salida: void
Descripción: Constructor por defecto de la clase Graph.
*/
Graph::Graph() {
}

/*
Entrada: vector<vector<int>> edges
Salida: void
Descripción: Constructor de la clase Graph que recibe una lista de aristas y crea un grafo no dirigido a partir de ellas.
*/
Graph::Graph(std::vector<std::vector<int>> edges) {
    for (const std::vector<int>& edge : edges) { // Crear lista de adyacencia
        vertexNeighbors[edge[0]].insert(edge[1]);
        vertexNeighbors[edge[1]].insert(edge[0]);
    }

   
    for (const auto& pair : vertexNeighbors) { // Inicializar colores de los vértices en -1
        vertexColor[pair.first] = -1; // -1 indica que no está coloreado
    }
}


/*
Entrada: void
Salida: int
Descripción: Obtiene el número de colores utilizados en la coloración actual del grafo.
*/
int Graph::getNumberOfColors() {
    std::set<int> colors;  // set para almacenar colores únicos
    for (const auto& par : vertexColor) { 
        colors.insert(par.second);
    }
    return colors.size();
}

/*
Entrada: int vertex, int color
Salida: bool
Descripción: Consulta si un vértice puede ser coloreado con un color dado, verificando que ninguno de sus vecinos tenga el mismo color.
*/
bool Graph::canColor(int vertex, int color) {
    for (int neighbor : vertexNeighbors[vertex]) {
        if (vertexColor.find(neighbor) != vertexColor.end() && 
            vertexColor[neighbor] == color) {
            return false;  // Si el vecino ya tiene el color, no se puede usar
        }
    }
    return true;
}

/*
Entrada: void
Salida: void
Descripción: Imprime el grafo, mostrando los vértices y sus vecinos.
*/
void Graph::printGraph() {
    for (const auto& par : vertexNeighbors) {
        std::cout << par.first << ": ";
        for (int neighbor : par.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}