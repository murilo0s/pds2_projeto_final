CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude $(shell pkg-config --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)
LDFLAGS = $(shell pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
TEST_BIN = $(BIN_DIR)/tests
COVERAGE_DIR = coverage

# Arquivos do projeto
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SOURCES_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES))
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/jogo

# Arquivos de teste
TEST_SOURCES = $(wildcard $(TEST_DIR)/main_test.cpp \
                          $(TEST_DIR)/Cadastro/*.cpp \
                          $(TEST_DIR)/Jogo/*.cpp)
TEST_OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.test.o,$(TEST_SOURCES))

# Flags para cobertura
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage

# Alvo padrão
all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

# Criar diretórios
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilação dos arquivos do jogo
ifeq ($(MAKECMDGOALS),tests)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -c $< -o $@
else
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

# Executável principal
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compilação dos arquivos de teste
$(OBJ_DIR)/%.test.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -Itests/third_party -c $< -o $@

# Binário de testes (sem incluir main.cpp!)
$(TEST_BIN): $(TEST_OBJECTS) $(SOURCES_NO_MAIN)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -Itests/third_party $^ -o $@ $(LDFLAGS)

# Alvo para rodar os testes e gerar cobertura
tests: $(BIN_DIR) $(OBJ_DIR) $(TEST_BIN)
	@echo "Executando testes..."
	./$(TEST_BIN)
	@echo "Gerando relatório de cobertura..."
	mkdir -p $(COVERAGE_DIR)
	gcovr --root . --filter src --html --html-details -o $(COVERAGE_DIR)/index.html --exclude tests --print-summary

# Alvo para rodar o jogo normalmente
run: all
	@./$(TARGET)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.gcda *.gcno *.gcov $(COVERAGE_DIR) *.log *.tmp
	find . -name "*.gcda" -o -name "*.gcno" -delete
