#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <chrono> // Para medir el tiempo

using namespace std;
using namespace chrono; // Para usar tipos de chrono

#include "Graph.h"
#include "State.h"
#include "ColoringOperation.h"
//Clase que se encarga de jugar el rol de main, en donde se leen los datos del archivo y se ejecuta el algoritmo de Branch and Bound.


/*
Entrada: const string& filename
Salida: vector<vector<int>>
Descripción: Lee las aristas de un grafo desde un archivo y las almacena en un vector de vectores.
*/
vector<vector<int>> readEdgesFromFile(const string& filename) {
    ifstream inputFile(filename);
    vector<vector<int>> edges;

    if (!inputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return edges; // Devuelve un vector vacío si ocurre un error
    }

    int u, v;
    set<int> uniqueVertices; // Para identificar automáticamente los vértices
    while (inputFile >> u >> v) { // Leer aristas
        edges.push_back({u, v}); // Almacenar arista
        uniqueVertices.insert(u); // Almacenar vértices
        uniqueVertices.insert(v); 
    }

    inputFile.close();

    // Mostrar información de los vértices y las aristas leídas
    cout << "Se leyeron " << uniqueVertices.size() << " vértices y " 
         << edges.size() << " aristas del archivo." << endl;

    return edges;
}

/*
Entrada: void
Salida: int
Descripción: Función principal que ejecuta el algoritmo de Branch and Bound para colorear un grafo. 
*/
int main() {
    int choice;
    do {
        // Menú
        cout << "\n--- Menu ---" << endl;
        cout << "1. Ingresar el nombre del archivo con el grafo" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> choice;

        // Validar entrada
        if (cin.fail() || (choice != 1 && choice != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Opcion no valida. Intente nuevamente." << endl;
            continue;
        }

        if (choice == 1) {
            string filename;
            cout << "Ingrese el nombre del archivo: ";
            cin >> filename;

           vector<vector<int>> edges = readEdgesFromFile(filename);

    if (edges.empty()) {
        cout << "No se pudo procesar el archivo o no contiene datos validos." << endl;
        continue;
    }

        // Crear el grafo y el estado inicial
    Graph graph(edges);
    State s(graph);

    // Crear la operación de coloreado
    ColoringOperation co;

    // Ejecutar el algoritmo de Branch and Bound
    auto start = high_resolution_clock::now();
    int c = co.branchAndBound(&s);
    auto stop = high_resolution_clock::now();

    // Mostrar resultados
    
    if (co.best) {
        co.best->printColor();
    }
    cout << "\nNumero de colores (Branch and Bound): " << c << endl;
    cout << "Tiempo de ejecucion: "
         << duration_cast<milliseconds>(stop - start).count() << " ms." << endl;
        }
    } while (choice != 2);

    cout << "Programa terminado." << endl;
    return 0;
}
