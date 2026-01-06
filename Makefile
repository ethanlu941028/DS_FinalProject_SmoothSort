# Makefile for Smooth Sort Project
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra
TARGET = main
SRC_DIR = src
BENCHMARK_DIR = benchmark
BIN_DIR = bin
DATA_DIR = data
PLOTS_DIR = plots
SCRIPTS_DIR = scripts

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

# Create directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

$(PLOTS_DIR):
	mkdir -p $(PLOTS_DIR)

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

# Install Python dependencies for plotting
install-deps:
	@echo "Installing Python dependencies..."
	pip3 install pandas matplotlib numpy scipy

# Check if Python dependencies are installed
check-deps:
	@echo "Checking Python dependencies..."
	@python3 -c "import pandas, matplotlib, numpy, scipy; print('All dependencies are installed!')" || (echo "Missing dependencies. Run 'make install-deps' first." && exit 1)

# Run benchmark and generate data
benchmark: $(BIN_DIR)/$(TARGET) | $(DATA_DIR)
	./$(BIN_DIR)/$(TARGET)
	@if [ -f benchmark_data.csv ]; then mv benchmark_data.csv $(DATA_DIR)/; fi

# Generate plots from benchmark data
plot: $(DATA_DIR)/benchmark_data.csv check-deps | $(PLOTS_DIR)
	cd $(SCRIPTS_DIR) && python3 draw.py

# Run complete benchmark and visualization pipeline
visualize: benchmark check-deps plot
	@echo "Benchmark complete and plots generated!"
	@echo "Check $(DATA_DIR)/benchmark_data.csv for raw data"
	@echo "Check $(PLOTS_DIR)/ for visualizations"

# Clean all generated files (including plots and data)
clean-all: clean
	rm -rf $(DATA_DIR)/*.csv $(PLOTS_DIR)/*.png

# Help target
help:
	@echo "Available targets:"
	@echo "  $(BIN_DIR)/$(TARGET)  - Build the main executable (default)"
	@echo "  clean      - Remove build files"
	@echo "  clean-all  - Remove build files, data, and plots"
	@echo "  rebuild    - Clean and build"
	@echo "  run        - Build and run the program"
	@echo "  quick      - Quick compile and run (no intermediate files)"
	@echo "  test       - Compile and run test_smooth"
	@echo "  install-deps - Install Python dependencies for plotting"
	@echo "  check-deps - Check if Python dependencies are installed"
	@echo "  benchmark  - Run benchmark and generate CSV data"
	@echo "  plot       - Generate plots from existing benchmark data"
	@echo "  visualize  - Run complete benchmark and visualization pipeline"
	@echo "  help       - Show this help message"

.PHONY: clean clean-all rebuild run quick test install-deps check-deps benchmark plot visualize help
.DEFAULT_GOAL := $(BIN_DIR)/$(TARGET)