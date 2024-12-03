// ColoringOperation.h
#ifndef COLORINGOPERATION_H
#define COLORINGOPERATION_H

#include "State.h"  // Incluir el archivo de cabecera State.h

class ColoringOperation {
public:
    // Atributos
    State* best;  // Mejor estado encontrado

    // Constructor
    ColoringOperation();  // Constructor por defecto

    // Métodos
    int greedyColoring(State* s);  // Algoritmo de coloreado codicioso
    int backtrack(State* s);  // Algoritmo de backtracking para coloreado
};

#endif // COLORINGOPERATION_H
