CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SRC_DIR = solutions
BUILD_DIR = build
BIN_DIR = bin

EXERCISES_SRC = $(wildcard $(SRC_DIR)/*.cpp)
EXERCISES_WITH_UTILITIES = $(patsubst $(SRC_DIR)/%.cpp, %, $(EXERCISES_SRC))
EXERCISES = $(filter-out utilities, $(EXERCISES_WITH_UTILITIES))

UTILITIES_SRC = utilities.cpp
UTILITIES_OBJ = $(BUILD_DIR)/utilities.o

all: $(EXERCISES)

$(EXERCISES): %: $(BIN_DIR)/%

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp $(UTILITIES_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(UTILITIES_OBJ): $(SRC_DIR)/$(UTILITIES_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:
	@for exercise in $(EXERCISES); do \
		echo "\n[[MAKE]] RUNNING $$exercise"; \
		./$(BIN_DIR)/$$exercise; \
		echo; \
	done

clean:
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*

.PHONY: all clean run