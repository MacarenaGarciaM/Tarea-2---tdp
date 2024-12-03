// State.h
#ifndef STATE_H
#define STATE_H

#include <set>
#include "Graph.h"  // Incluir el archivo de cabecera Graph.h

class State {
public:
    // Atributos
    std::set<int> uncoloredVertices;  // Vértices sin colorear
    std::set<int> coloredVertices;    // Vértices coloreados
    std::set<int> availableColors;    // Colores disponibles
    Graph graph;  // Grafo semi-coloreado durante el desarrollo del algoritmo

    // Constructores
    State();  // Constructor por defecto
    State(Graph graph);  // Constructor con un grafo dado

    // Métodos
    int getVertex();  // Obtiene un vértice no coloreado
    void pushColorSelectVertex(int vertex, int color);  // Colorea un vértice
    bool isVertexColored(int vertex);  // Verifica si un vértice está coloreado
    bool isAllColored();  // Verifica si todos los vértices están coloreados
    void printColor();  // Imprime los colores de los vértices
    void incrementColor();  // Incrementa el número de colores disponibles
};

#endif // STATE_H
