CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

SRC_DIR = solutions
BUILD_DIR = build
BIN_DIR = bin

EXERCISES = fixed_xor hex_to_base64 single_byte_xor_cipher

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

clean:
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*

.PHONY: all clean
