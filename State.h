#ifndef STATE_H
#define STATE_H

#include <set>
#include "Graph.h"

class State {
public:
    Graph graph;
    std::set<int> uncoloredVertices;
    std::set<int> coloredVertices;
    std::set<int> availableColors;

    State();                          // Constructor por defecto
    State(Graph graph);               // Constructor con un grafo
    int getVertex();                  // Obtiene un vértice no coloreado
    void pushColorSelectVertex(int vertex, int color);
    bool isVertexColored(int vertex);
    bool isAllColored();
    void printColor();
    void incrementColor();

    int calculateLowerBound();        // Cálculo del límite inferior
    int calculateUpperBound();        // Cálculo del límite superior
};

#endif // STATE_H
