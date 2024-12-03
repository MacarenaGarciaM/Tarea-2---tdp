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
    // Caso base: Si todos los vértices están coloreados
    if (s->isAllColored()) {
        int numColors = s->graph.getNumberOfColors();
        if (numColors < upperBound) {
            upperBound = numColors;  // Actualizamos el límite superior
            if (best != nullptr) {
                delete best;  // Liberamos la memoria del estado anterior
            }
            best = new State(*s);  // Guardamos el nuevo mejor estado
        }
        return numColors;
    }

    // Seleccionamos un vértice no coloreado
    int vertex = s->getVertex();

    // Intentamos colorearlo con colores factibles
    for (int color : s->availableColors) {
        if (s->graph.canColor(vertex, color)) {
            State* nextState = new State(*s);
            nextState->pushColorSelectVertex(vertex, color);

            // Llamada recursiva
            branchAndBound(nextState);

            delete nextState;  // Liberamos memoria
        }
    }

    // Intentamos usar un nuevo color si es necesario
    int newColor = s->graph.getNumberOfColors();
    if (newColor < upperBound) {  // Solo consideramos un nuevo color si es factible
        State* nextState = new State(*s);
        nextState->pushColorSelectVertex(vertex, newColor);
        nextState->availableColors.insert(newColor);

        // Llamada recursiva
        branchAndBound(nextState);

        delete nextState;  // Liberamos memoria
    }

    return upperBound;  // Retornamos el mejor límite encontrado
}
