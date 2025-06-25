CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude $(shell pkg-config --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)
LDFLAGS = $(shell pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/jogo

# Testes
TEST_SRCS := $(wildcard tests/*.cpp)
TEST_BINS := $(patsubst tests/%.cpp, bin/test_%, $(TEST_SRCS))

all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

tests: $(TEST_BINS)

bin/test_%: tests/%.cpp $(filter-out obj/main.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test-run: tests
	@for t in $(TEST_BINS); do echo "Rodando $$t"; ./$$t; done

# Cobertura de código
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

coverage: CXXFLAGS += $(COVERAGE_FLAGS)
coverage: LDFLAGS += $(COVERAGE_FLAGS)
coverage: clean tests
	@mkdir -p coverage
	@for t in $(TEST_BINS); do ./$$t; done
	@lcov --capture --directory . --output-file coverage/coverage.info
	@genhtml coverage/coverage.info --output-directory coverage

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.log *.tmp

clean-tests:
	rm -f bin/test_*

clean-coverage:
	rm -rf coverage *.gcda *.gcno *.gcov

run: all
	@./$(TARGET)