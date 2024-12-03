#ifndef COLORING_OPERATION_H
#define COLORING_OPERATION_H

#include "State.h"

class ColoringOperation {
public:
    ColoringOperation();  // Constructor
    int greedyColoring(State* s);  // Algoritmo codicioso
    int branchAndBound(State* s);  // Algoritmo de branch and bound

    State* best;  // Mejor estado encontrado

private:
    int upperBound;  // Límite superior para Branch and Bound
};

#endif // COLORING_OPERATION_H
