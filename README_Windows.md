# Windows 系統執行指南

## 問題解決

如果您在 Windows 系統上執行 `make visualize` 時遇到「不應該有 -f」的錯誤，請按照以下步驟：

### 方法 1: 使用 Git Bash 或 MSYS2

1. 安裝 Git for Windows (包含 Git Bash)
2. 在 Git Bash 中執行指令：
```bash
make visualize
```

### 方法 2: 手動執行步驟

如果 Makefile 仍有問題，可以手動執行各步驟：

```bash
# 1. 編譯程式
g++ -std=c++11 -O2 -Wall -Wextra -c src/main.cpp -o bin/main.o
g++ -std=c++11 -O2 -Wall -Wextra -c benchmark/baseline.cpp -o bin/baseline.o
g++ -std=c++11 -O2 -Wall -Wextra -o bin/main bin/main.o bin/baseline.o

# 2. 建立必要資料夾
mkdir data
mkdir plots

# 3. 執行 benchmark
./bin/main

# 4. 移動資料檔
mv benchmark_data.csv data/

# 5. 安裝 Python 套件（如果尚未安裝）
pip install pandas matplotlib numpy scipy

# 6. 生成圖表
cd scripts
python draw.py
cd ..
```

### 方法 3: 使用 PowerShell

在 PowerShell 中：

```powershell
# 清理舊檔案
if (Test-Path "bin/main.exe") { Remove-Item "bin/main.exe" }
if (Test-Path "bin/*.o") { Remove-Item "bin/*.o" }

# 編譯
g++ -std=c++11 -O2 -Wall -Wextra -c src/main.cpp -o bin/main.o
g++ -std=c++11 -O2 -Wall -Wextra -c benchmark/baseline.cpp -o bin/baseline.o  
g++ -std=c++11 -O2 -Wall -Wextra -o bin/main bin/main.o bin/baseline.o

# 執行
./bin/main

# 生成圖表
cd scripts; python draw.py; cd ..
```

## 必要環境

1. **編譯器**: MinGW-w64 或 MSVC
2. **Python**: Python 3.x
3. **Python 套件**: pandas, matplotlib, numpy, scipy
4. **Make 工具**: 建議使用 Git Bash 或 MSYS2

## 檔案說明

執行完成後會產生：
- `data/benchmark_data.csv` - 效能測試資料
- `plots/smoothed_linear_plot.png` - 視覺化圖表
- 終端輸出效能比較表格