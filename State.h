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
    std::unordered_map<int, int> saturationLevel; // Saturación de cada vértice

    State();
    State(Graph graph);
    int getVertex();
    void pushColorSelectVertex(int vertex, int color);
    bool isVertexColored(int vertex);
    bool isAllColored();
    void printColor();
    void updateSaturation(int vertex); // Nuevo método para actualizar saturaciones
};

#endif // STATE_H
