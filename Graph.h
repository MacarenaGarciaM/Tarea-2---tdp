// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <set>
#include <vector>

class Graph {
public:
    // Atributos
    std::unordered_map<int, std::set<int>> vertexNeighbors;  // vertex -> neighbors
    std::unordered_map<int, int> vertexColor;  // vertex -> color

    // Constructores
    Graph();  // Constructor por defecto
    Graph(std::vector<std::vector<int>> edges);  // Constructor con lista de aristas

    // Métodos
    int getNumberOfColors();  // Obtiene el número de colores utilizados
    bool canColor(int vertex, int color);  // Consulta si el vértice puede ser coloreado con el color dado
    void printGraph();  // Imprime el grafo (vértices y sus vecinos)

};

#endif // GRAPH_H
