# Nombre del ejecutable
EXEC = colorear_grafo

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Archivos fuente y de objeto
SRC = main.cpp Graph.cpp ColoringOperation.cpp State.cpp
OBJ = $(SRC:.cpp=.o)

# Archivos de test
TESTS = test_Graph test_ColoringOperation test_State
TEST_SRC = $(TESTS:=.cpp)

# Regla para compilar el ejecutable principal
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar y ejecutar los tests individuales
test_Graph: test_Graph.cpp Graph.o
	$(CXX) $(CXXFLAGS) -o test_Graph test_Graph.cpp Graph.o
	./test_Graph

test_ColoringOperation: test_ColoringOperation.cpp ColoringOperation.o Graph.o State.o
	$(CXX) $(CXXFLAGS) -o test_ColoringOperation test_ColoringOperation.cpp ColoringOperation.o Graph.o State.o
	./test_ColoringOperation

test_State: test_State.cpp State.o Graph.o
	$(CXX) $(CXXFLAGS) -o test_State test_State.cpp State.o Graph.o
	./test_State

# Regla para ejecutar todos los tests
test: $(TESTS)
	@for test in $(TESTS); do \
		echo "Running $$test..."; \
		./$$test; \
	done

# Regla para ejecutar el programa principal
run: $(EXEC)
	./$(EXEC)

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJ) $(EXEC) $(TESTS) *.o

# Regla para limpiar solo los archivos objeto
clean-obj:
	rm -f $(OBJ)
