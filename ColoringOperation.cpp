#include "ColoringOperation.h"
#include "State.h"
#include <climits>
#include <algorithm>

ColoringOperation::ColoringOperation() {
    best = nullptr;        // Inicializamos sin estado conocido
    upperBound = INT_MAX;  // Límite superior inicial
}

// Implementación de greedyColoring
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

// Implementación de Branch and Bound
int ColoringOperation::branchAndBound(State* s) {
    // Calcular cota inferior
    int lowerBound = calculateLowerBound(s);
    if (lowerBound >= upperBound) {
        return upperBound; // Podar rama si la cota inferior supera la superior
    }

    // Actualizar límite superior si es óptimo
    if (s->isAllColored()) {
        int numColors = s->graph.getNumberOfColors();
        if (numColors < upperBound) {
            upperBound = numColors;
            if (best) delete best;
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
            nextState->pushColorSelectVertex(vertex, color);
            branchAndBound(nextState);
            delete nextState;
        }
    }

    // Intentar con un nuevo color si es necesario
    int newColor = s->graph.getNumberOfColors();
    if (newColor < upperBound) {
        State* nextState = new State(*s);
        nextState->pushColorSelectVertex(vertex, newColor);
        nextState->availableColors.insert(newColor);
        branchAndBound(nextState);
        delete nextState;
    }

    return upperBound;
}


int ColoringOperation::calculateLowerBound(State* s) {
    // 1. Tamaño del clique más grande
    int cliqueSize = findLargestClique(s->graph);

    // 2. Número mínimo de colores por grado máximo
    int maxDegree = 0;
    for (const auto& pair : s->graph.vertexNeighbors) {
        maxDegree = std::max(maxDegree, static_cast<int>(pair.second.size()));
    }

    // 3. Coloración greedy parcial
    int greedyColors = greedyColoring(s);

    return std::max({cliqueSize, maxDegree + 1, greedyColors});
}

int ColoringOperation::findLargestClique(Graph& graph) {
    int maxCliqueSize = 0;

    for (const auto& vertex : graph.vertexNeighbors) {
        std::set<int> clique{vertex.first};

        for (int neighbor : vertex.second) {
            bool isClique = true;
            for (int member : clique) {
                if (graph.vertexNeighbors[member].find(neighbor) == graph.vertexNeighbors[member].end()) {
                    isClique = false;
                    break;
                }
            }
            if (isClique) {
                clique.insert(neighbor);
            }
        }

        maxCliqueSize = std::max(maxCliqueSize, static_cast<int>(clique.size()));
    }

    return maxCliqueSize;
}
