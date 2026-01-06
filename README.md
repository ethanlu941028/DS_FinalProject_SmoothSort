# SmoothSort Performance Analysis 🚀

## 專案簡介

這是一個數據結構課程的期末專案，深入探討並實作了 **Smooth Sort** 排序演算法。Smooth Sort 是由 Edsger Dijkstra 於 1981 年提出的進階排序演算法，具有 **O(n log n)** 最壞時間複雜度和 **O(n)** 最佳時間複雜度的特性。

本專案不僅實作了 Smooth Sort，更與多種經典排序演算法進行全面的效能比較分析，並提供視覺化圖表展示結果。

## ✨ 主要功能

- 🔧 **完整的 Smooth Sort 實作** - 基於 Leonardo 數列的堆積結構
- 📊 **多演算法效能比較** - Smooth Sort vs Heap Sort vs Quick Sort vs Insertion Sort vs STL Sort
- 📈 **自動化基準測試** - 支援不同資料大小的批量測試 (1K ~ 100K)
- 🎯 **最佳情況分析** - 特別測試已排序資料的 O(n) 效能表現
- 📉 **視覺化圖表生成** - 自動生成平滑曲線的效能比較圖
- 🖥️ **跨平台支援** - 支援 Windows、macOS、Linux
- ⚡ **一鍵執行** - 完整的 Makefile 自動化建置系統

## 🏗️ 專案結構

```
DS_FinalProject_SmoothSort/
├── src/                    # 🔧 核心原始碼
│   ├── main.cpp           # 主程式與效能測試
│   ├── smooth_sort.h      # Smooth Sort 標頭檔
│   └── smooth_sort.cpp    # Smooth Sort 實作
├── benchmark/              # 📊 效能測試模組  
│   ├── baseline.cpp       # 其他排序演算法實作
│   ├── baseline.h         # 基準演算法標頭檔
│   └── timer.h            # 高精度計時工具
├── scripts/                # 🐍 Python 腳本
│   └── draw.py           # 視覺化圖表生成
├── data/                   # 📁 測試資料
│   └── benchmark_data.csv # 效能測試結果
├── plots/                  # 📈 生成圖表
│   └── *.png             # 效能比較視覺化
├── bin/                    # 🚀 編譯產物
├── docs/                   # 📖 文檔資料
│   └── reference          # 參考資料
├── Makefile               # 🔨 自動化建置
├── README_Windows.md      # Windows 使用指南
└── README.md              # 專案說明文件
```

## 🚀 快速開始

### 環境需求

- **編譯器**: GCC 4.8+ / Clang 3.3+ / MSVC 2015+
- **C++ 標準**: C++11 或更高版本
- **Python**: 3.6+ (用於視覺化)
- **Make**: GNU Make (建議) 或相容版本

### 安裝 Python 依賴

```bash
make install-deps
```

### 一鍵執行完整分析

```bash
make visualize
```

這個指令會：
1. 🔨 編譯所有源碼
2. 📊 執行效能基準測試 
3. 🖥️ 在終端顯示格式化結果
4. 📈 生成視覺化圖表
5. 📁 整理所有輸出檔案

### 分步執行

```bash
# 只編譯程式
make

# 只執行基準測試
make benchmark

# 只生成圖表 (需要先有資料)
make plot

# 執行單元測試
make test

# 快速編譯執行 (開發用)
make quick
```

## 📊 效能測試結果

### 演算法比較 (n = 100,000)

```
Algorithm         Time (ms)      Time (ns)
-------------------------------------------------------
Smooth Sort       6.77          6767666
Heap Sort         5.30          5296000  
Quick Sort        4.12          4120792
STL Sort          3.85          3847458
-------------------------------------------------------
```

### 最佳情況分析 

Smooth Sort 在處理**已排序資料**時展現出優秀的 O(n) 效能：

- **隨機資料**: ~6.8ms (n=100K)
- **已排序資料**: ~0.21ms (n=100K) ⚡️

### 複雜度分析

|    演算法    |    最佳     |    平均    |    最壞     |    空間   |
-----------------------------------------------------------------
| Smooth Sort |    O(n)    | O(n log n) | O(n log n) |   O(1)   |
| Heap Sort   | O(n log n) | O(n log n) | O(n log n) |   O(1)   |
| Quick Sort  | O(n log n) | O(n log n) |   O(n²)    | O(log n) |
| STL Sort    | O(n log n) | O(n log n) | O(n log n) | O(log n) |

## 🔧 技術細節

### Smooth Sort 核心特性

- **Leonardo 數列**: 使用 Leonardo 數列構建特殊的堆積結構
- **適應性**: 能夠識別並利用資料的已排序特性
- **就地排序**: O(1) 額外空間需求
- **穩定邊界**: 確保 O(n log n) 最壞情況效能

### 實作亮點

```cpp
namespace smoothsort {
    inline void smooth_sort(std::vector<int> &m);
    // 完整實作包含 sift、trinkle 等核心操作
}
```

### 測試方法學

- **多次測試**: 每個資料大小執行 3 次取平均
- **隨機資料**: 使用 Mersenne Twister 生成器
- **高精度計時**: 納秒級計時精度
- **記憶體管理**: 避免記憶體重新分配的干擾

## 🖥️ 跨平台支援

### Windows 使用者

請參閱 [Windows 使用指南](README_Windows.md) 或使用以下方式：

```bash
# 使用 Git Bash (推薦)
make visualize

# 或使用 PowerShell 手動執行
# 詳見 README_Windows.md
```

### 系統資訊

```bash
make info  # 顯示當前系統與編譯器資訊
```

## 📈 視覺化分析

專案會自動生成：

- **效能比較圖**: 顯示各演算法在不同資料大小下的執行時間
- **平滑曲線**: 使用三次樣條插值讓趨勢更清晰
- **特殊標註**: Smooth Sort 最佳情況以綠色虛線特別標示

## 🛠️ 開發說明

### 新增排序演算法

1. 在 `benchmark/baseline.cpp` 中實作
2. 在 `benchmark/baseline.h` 中宣告
3. 在 `src/main.cpp` 中加入測試

### 修改測試參數

編輯 `src/main.cpp`:
```cpp
vector<int> sizes = {1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000};
int num_trials = 3;  // 測試次數
```

## 🎯 未來改進

- [ ] 支援更多資料類型 (string, double)
- [ ] 平行化處理大型資料集
- [ ] 加入更多排序演算法比較
- [ ] 網頁版互動式視覺化
- [ ] 記憶體使用量分析

## 📚 參考文獻

- Dijkstra, E. W. (1981). "Smoothsort, an alternative for sorting in situ"
- Wirth, N. (1986). "Algorithms and Data Structures"
- Various online resources and academic papers

## 🤝 貢獻

歡迎提交 Issue 和 Pull Request！

## 📄 授權

本專案僅用於學術研究目的。
