# Makefile for Smooth Sort Project
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra
TARGET = main
SRC_DIR = src
BENCHMARK_DIR = benchmark
BIN_DIR = bin

# Source files
MAIN_SRC = $(SRC_DIR)/main.cpp
BASELINE_SRC = $(BENCHMARK_DIR)/baseline.cpp
SMOOTH_SORT_SRC = $(SRC_DIR)/smooth_sort.cpp

# Header files
HEADERS = $(SRC_DIR)/smooth_sort.h $(BENCHMARK_DIR)/baseline.h $(BENCHMARK_DIR)/timer.h

# Object files
MAIN_OBJ = $(BIN_DIR)/main.o
BASELINE_OBJ = $(BIN_DIR)/baseline.o
SMOOTH_SORT_OBJ = $(BIN_DIR)/smooth_sort.o

# Build main executable
$(BIN_DIR)/$(TARGET): $(MAIN_OBJ) $(BASELINE_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp
$(MAIN_OBJ): $(MAIN_SRC) $(HEADERS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile baseline.cpp
$(BASELINE_OBJ): $(BASELINE_SRC) $(BENCHMARK_DIR)/baseline.h | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile smooth_sort.cpp (if exists)
$(SMOOTH_SORT_OBJ): $(SMOOTH_SORT_SRC) $(SRC_DIR)/smooth_sort.h | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build files
clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_DIR)/$(TARGET)

# Rebuild everything
rebuild: clean $(BIN_DIR)/$(TARGET)

# Run the program
run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

# Quick compile and run (current method)
quick:
	cd $(SRC_DIR) && $(CXX) $(CXXFLAGS) main.cpp ../$(BASELINE_SRC) -o $(TARGET) && ./$(TARGET)

# Test smooth sort only
test:
	cd . && $(CXX) $(CXXFLAGS) test_smooth.cpp -o test_smooth && ./test_smooth

# Help target
help:
	@echo "Available targets:"
	@echo "  $(BIN_DIR)/$(TARGET)  - Build the main executable (default)"
	@echo "  clean      - Remove build files"
	@echo "  rebuild    - Clean and build"
	@echo "  run        - Build and run the program"
	@echo "  quick      - Quick compile and run (no intermediate files)"
	@echo "  test       - Compile and run test_smooth"
	@echo "  help       - Show this help message"

.PHONY: clean rebuild run quick test help
.DEFAULT_GOAL := $(BIN_DIR)/$(TARGET)