# 1. 偵測作業系統 (OS 是 Windows 內建環境變數)
ifeq ($(OS),Windows_NT)
    # --- Windows 設定 ---
    TARGET = main.exe
    MKDIR = if not exist "$1" mkdir "$1"
    RM = del /q
    RMDIR = rmdir /s /q
    CP = copy /y
    MV = move /y
    # 使用反斜線修復路徑執行問題
    EXEC = .\$(BIN_DIR)\$(TARGET)
    CLEAN_CMD = if exist $(BIN_DIR)\*.o del /q $(BIN_DIR)\*.o && if exist $(BIN_DIR)\$(TARGET) del /q $(BIN_DIR)\$(TARGET)
    CLEAN_ALL_CMD = if exist $(DATA_DIR)\*.csv del /q $(DATA_DIR)\*.csv && if exist $(PLOTS_DIR)\*.png del /q $(PLOTS_DIR)\*.png
    PYTHON = python
else
    # --- Mac / Linux 設定 ---
    TARGET = main
    MKDIR = mkdir -p "$1"
    RM = rm -f
    RMDIR = rm -rf
    CP = cp
    MV = mv
    EXEC = ./$(BIN_DIR)/$(TARGET)
    CLEAN_CMD = rm -f $(BIN_DIR)/*.o $(BIN_DIR)/$(TARGET)
    CLEAN_ALL_CMD = rm -f $(DATA_DIR)/*.csv $(PLOTS_DIR)/*.png
    PYTHON = python3
endif

# --- 共用變數 ---
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra
SRC_DIR = src
BENCHMARK_DIR = benchmark
BIN_DIR = bin
DATA_DIR = data
PLOTS_DIR = plots
SCRIPTS_DIR = scripts

# 原始碼與物件檔
MAIN_SRC = $(SRC_DIR)/main.cpp
BASELINE_SRC = $(BENCHMARK_DIR)/baseline.cpp
SMOOTH_SORT_SRC = $(SRC_DIR)/smooth_sort.cpp
HEADERS = $(SRC_DIR)/smooth_sort.h $(BENCHMARK_DIR)/baseline.h $(BENCHMARK_DIR)/timer.h

MAIN_OBJ = $(BIN_DIR)/main.o
BASELINE_OBJ = $(BIN_DIR)/baseline.o
SMOOTH_SORT_OBJ = $(BIN_DIR)/smooth_sort.o

# --- 編譯規則 ---

# 預設目標
all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(MAIN_OBJ) $(BASELINE_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MAIN_OBJ): $(MAIN_SRC) $(HEADERS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BASELINE_OBJ): $(BASELINE_SRC) $(BENCHMARK_DIR)/baseline.h | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SMOOTH_SORT_OBJ): $(SMOOTH_SORT_SRC) $(SRC_DIR)/smooth_sort.h | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- 目錄建立 (使用 call 呼叫自定義變數) ---
$(BIN_DIR):
	@$(call MKDIR,$(BIN_DIR))

$(DATA_DIR):
	@$(call MKDIR,$(DATA_DIR))

$(PLOTS_DIR):
	@$(call MKDIR,$(PLOTS_DIR))

# --- 清理指令 ---
clean:
	@echo "Cleaning build files..."
	@$(CLEAN_CMD)

clean-all: clean
	@echo "Cleaning data and plots..."
	@$(CLEAN_ALL_CMD)

# --- 執行與測試 ---
rebuild: clean all

run: $(BIN_DIR)/$(TARGET)
	@$(EXEC)

benchmark: $(BIN_DIR)/$(TARGET) | $(DATA_DIR)
	@$(EXEC)
	@$(PYTHON) -c "import os; os.rename('benchmark_data.csv', os.path.join('$(DATA_DIR)', 'benchmark_data.csv')) if os.path.exists('benchmark_data.csv') else None"
	@echo "Data moved to $(DATA_DIR)"

plot: $(DATA_DIR)/benchmark_data.csv | $(PLOTS_DIR)
	cd $(SCRIPTS_DIR) && $(PYTHON) draw.py

visualize: benchmark plot
	@echo "Benchmark complete and plots generated!"

help:
	@echo "Operating System Detected: $(if $(filter Windows_NT,$(OS)),Windows,Mac/Linux)"
	@echo "Available targets:"
	@echo "  make           - Build the executable"
	@echo "  make run       - Run the program"
	@echo "  make benchmark - Run and move CSV"
	@echo "  make visualize - Run + Plot"
	@echo "  make clean     - Remove object files"

.PHONY: all clean clean-all rebuild run benchmark plot visualize help