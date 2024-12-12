#ifndef STATE_H
#define STATE_H

#include <set>
#include "Graph.h"
//Clase que se encarga de almacenar el estado actual de la coloración de un grafo, así como de realizar operaciones sobre él.
class State {
public:
    // Atributos
    Graph graph;
    std::set<int> uncoloredVertices;
    std::set<int> coloredVertices;
    std::set<int> availableColors;
    std::unordered_map<int, int> saturationLevel; // Saturación de cada vértice

    // Constructores
    State();
    State(Graph graph);

    // Métodos
    int getVertex();
    void pushColorSelectVertex(int vertex, int color);
    bool isVertexColored(int vertex);
    bool isAllColored();
    void printColor();
    void updateSaturation(int vertex); // Nuevo método para actualizar saturaciones
};

#endif // STATE_H
