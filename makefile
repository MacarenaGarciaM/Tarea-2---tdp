# Nombre del ejecutable
EXEC = colorear_grafo

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Archivos fuente y de objeto
SRC = main.cpp Graph.cpp ColoringOperation.cpp State.cpp
OBJ = $(SRC:.cpp=.o)

# Archivos de test
TEST_GRAPH = test_Graph
TEST_COLORINGOPERATION = test_ColoringOperation
TEST_STATE = test_State 

# Regla para compilar el ejecutable principal
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Reglas para compilar y ejecutar los tests
test_graph: $(TEST_GRAPH).cpp Graph.o
	$(CXX) $(CXXFLAGS) -o $(TEST_GRAPH) $(TEST_GRAPH).cpp Graph.o
	./$(TEST_GRAPH)

test_coloringoperation: $(TEST_COLORINGOPERATION).cpp test_ColoringOperation.o Graph.o State.o
	$(CXX) $(CXXFLAGS) -o $(TEST_COLORINGOPERATION) $(TEST_COLORINGOPERATION).cpp test_ColoringOperation.o Graph.o State.o
	./$(TEST_COLORINGOPERATION)

test_state: $(TEST_STATE).cpp State.o Graph.o
	$(CXX) $(CXXFLAGS) -o $(TEST_STATE) $(TEST_STATE).cpp State.o Graph.o
	./$(TEST_STATE)

# Regla para ejecutar todos los tests
test: test_graph test_coloringoperation test_state  

# Regla para ejecutar el programa principal
run: $(EXEC)
	./$(EXEC)

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJ) $(EXEC) $(TEST_GRAPH) $(TEST_COLORINGOPERATION) $(TEST_STATE) *.o

# Regla para limpiar solo los archivos objeto
clean-obj:
	rm -f $(OBJ)