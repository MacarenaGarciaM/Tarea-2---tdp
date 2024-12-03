// ColoringOperation.cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;
#include "ColoringOperation.h"


// Constructor por defecto
ColoringOperation::ColoringOperation() {
    best = nullptr;  // Convenimos que nullptr indica que no se ha encontrado ningún estado
}

// Algoritmo de coloreado codicioso
int ColoringOperation::greedyColoring(State* s) {
    while (!s->isAllColored()) {
        // Seleccionamos un vértice y lo coloreamos
        int vertex = s->getVertex();  // Necesitamos obtener un vértice no coloreado

        // Encontramos el primer color disponible que sea factible (no igual al color de los vecinos)
        for (int color : s->availableColors) {
            if (s->graph.canColor(vertex, color)) {
                s->pushColorSelectVertex(vertex, color);
                break;  // Ya encontramos un color y actualizamos el estado
            }
        }

        // Si no se pudo colorear el vértice, asignamos un nuevo color
        if (!s->isVertexColored(vertex)) {
            int c = s->graph.getNumberOfColors();
            s->pushColorSelectVertex(vertex, c);
            s->availableColors.insert(c);
        }

        s->printColor();  // Imprime el estado actual del coloreado
    }
    
    best = s;  // El mejor estado es el estado actual
    return s->graph.getNumberOfColors();  // Retornamos el número de colores utilizados
}

// Algoritmo de backtracking
int ColoringOperation::backtrack(State* s) {
    // Caso base
    if (s->isAllColored()) {  // Si todos los vértices están coloreados
        if (best == nullptr || s->graph.getNumberOfColors() < best->graph.getNumberOfColors()) {
            best = s;  // Actualizamos el mejor estado encontrado
        }
        return best->graph.getNumberOfColors();
    } else {
        // Caso recursivo
        int vertex = s->getVertex();  // Obtenemos un vértice no coloreado
        s->incrementColor();  // Incrementamos el número de colores disponibles

        // Probamos con los colores disponibles
        for (int color : s->availableColors) {
            if (s->graph.canColor(vertex, color)) {
                State* s1 = new State(*s);  // Creamos una copia del estado actual
                s1->pushColorSelectVertex(vertex, color);  // Coloreamos el vértice

                // Llamada recursiva al backtracking
                backtrack(s1);
            }
        }

        return best->graph.getNumberOfColors();  // Retornamos el número de colores del mejor estado
    }
}
