#include "ColoringOperation.h"
#include "State.h"
#include <climits>
#include <algorithm>
//Clase que se encarga de realizar la coloración de un grafo mediante los algoritmos de Greedy y Branch and Bound.

/*
Entrada: void
Salida: void
Descripción: Constructor de la clase ColoringOperation.
*/
ColoringOperation::ColoringOperation() {
    best = nullptr;        // Inicializamos sin estado conocido
    upperBound = INT_MAX;  // Límite superior inicial
}

/*
Entrada: State* s
Salida: int
Descripción: Algoritmo codicioso para colorear un grafo.
*/
int ColoringOperation::greedyColoring(State* s) {
    while (!s->isAllColored()) {
        int vertex = s->getVertex();  // Obtener el vértice con mayor saturación

        // Intentar asignar un color factible
        for (int color : s->availableColors) {
            if (s->graph.canColor(vertex, color)) {
                s->pushColorSelectVertex(vertex, color);
                break;
            }
        }

        // Si no se pudo colorear, asignar un nuevo color
        if (!s->isVertexColored(vertex)) {
            int newColor = s->graph.getNumberOfColors();
            s->pushColorSelectVertex(vertex, newColor);
            s->availableColors.insert(newColor);
        }
    }

    return s->graph.getNumberOfColors();  // Retornar el número de colores usados
}

/*
Entrada: State* s
Salida: int
Descripción: Algoritmo de Branch and Bound para colorear un grafo.
*/
int ColoringOperation::branchAndBound(State* s) {
    // Calcular cota inferior
    int lowerBound = calculateLowerBound(s);
    if (lowerBound >= upperBound) {
        return upperBound; // Podar rama si la cota inferior supera la superior
    }

    // Actualizar límite superior si es óptimo
    if (s->isAllColored()) {
        int numColors = s->graph.getNumberOfColors(); // Número de colores usados
        if (numColors < upperBound) {
            upperBound = numColors;
            if (best) delete best; // Liberar memoria si ya había un mejor estado
            best = new State(*s);
        }
        return numColors;
    }

    // Obtener vértice a colorear
    int vertex = s->getVertex();

    // Intentar con colores existentes primero
    for (int color : s->availableColors) {
        if (s->graph.canColor(vertex, color)) {
            State* nextState = new State(*s);
            nextState->pushColorSelectVertex(vertex, color); // Colorear el vértice
            branchAndBound(nextState); // Llamada recursiva
            delete nextState;
        }
    }

    // Intentar con un nuevo color si es necesario
    int newColor = s->graph.getNumberOfColors();
    if (newColor < upperBound) {
        State* nextState = new State(*s);
        nextState->pushColorSelectVertex(vertex, newColor); // Colorear el vértice
        nextState->availableColors.insert(newColor); // Agregar el color a los disponibles
        branchAndBound(nextState);
        delete nextState;
    }

    return upperBound;
}

/*
Entrada: State* s
Salida: int
Descripción: Cálculo de la cota inferior para el algoritmo de Branch and Bound.
*/
int ColoringOperation::calculateLowerBound(State* s) {
    //Tamaño del clique más grande
    int cliqueSize = findLargestClique(s->graph);

    //Número mínimo de colores por grado máximo
    int maxDegree = 0;
    for (const auto& pair : s->graph.vertexNeighbors) {
        maxDegree = std::max(maxDegree, static_cast<int>(pair.second.size()));
    }

    //Coloración greedy parcial
    int greedyColors = greedyColoring(s);

    return std::max({cliqueSize, maxDegree + 1, greedyColors});
}

/*
Entrada: Graph& graph
Salida: int
Descripción: Encuentra el tamaño del clique más grande en un grafo.
*/
int ColoringOperation::findLargestClique(Graph& graph) {
    int maxCliqueSize = 0;

    for (const auto& vertex : graph.vertexNeighbors) { // Recorrer todos los vértices
        std::set<int> clique{vertex.first};

        for (int neighbor : vertex.second) {
            bool isClique = true;
            for (int member : clique) { // Verificar si es un clique
                if (graph.vertexNeighbors[member].find(neighbor) == graph.vertexNeighbors[member].end()) { // No es vecino
                    isClique = false;
                    break;
                }
            }
            if (isClique) { 
                clique.insert(neighbor); // Agregar al clique
            }
        }

        maxCliqueSize = std::max(maxCliqueSize, static_cast<int>(clique.size())); // Actualizar tamaño máximo
    }

    return maxCliqueSize;
}
