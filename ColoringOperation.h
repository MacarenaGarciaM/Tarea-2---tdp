// ColoringOperation.h
#ifndef COLORING_OPERATION_H
#define COLORING_OPERATION_H

#include "State.h"
//Clase que se encarga de realizar la coloración de un grafo mediante los algoritmos de Greedy y Branch and Bound.
class ColoringOperation {
public:
    ColoringOperation();  // Constructor
    int greedyColoring(State* s);  // Algoritmo codicioso
    int branchAndBound(State* s);  // Algoritmo de branch and bound

    State* best;  // Mejor estado encontrado

    int upperBound;  // Límite superior para Branch and Bound
    int calculateLowerBound(State* s);  // Cálculo de la cota inferior
    int findLargestClique(Graph& graph);  // Encontrar tamaño del clique más grande
};

#endif // COLORING_OPERATION_H
