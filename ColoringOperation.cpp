#include "ColoringOperation.h"
#include "State.h"
#include <climits>
ColoringOperation::ColoringOperation() {
    best = nullptr;        // Inicializamos sin estado conocido
    upperBound = INT_MAX;  // Límite superior inicial
}

// Implementación de greedyColoring
int ColoringOperation::greedyColoring(State* s) {
    while (!s->isAllColored()) {
        int vertex = s->getVertex();  // Obtener un vértice no coloreado

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
    // Corte temprano si ya superamos el límite superior
    if (s->graph.getNumberOfColors() >= upperBound) {
        return upperBound;
    }

    if (s->isAllColored()) {
        int numColors = s->graph.getNumberOfColors();
        if (numColors < upperBound) {
            upperBound = numColors;
            if (best) delete best;
            best = new State(*s);
        }
        return numColors;
    }

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

    // Usar un nuevo color si es necesario
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
