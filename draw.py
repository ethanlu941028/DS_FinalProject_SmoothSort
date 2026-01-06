import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline

# 讀取 CSV
try:
    df = pd.read_csv('benchmark_data.csv')
except FileNotFoundError:
    print("找不到 benchmark_data.csv")
    exit()

plt.figure(figsize=(12, 7))

# 定義平滑曲線的點數 (點越多越圓滑)
n_smooth = 300 

for col in df.columns[1:]:
    # 過濾有效數據
    valid_df = df[df[col] > 0]
    x = valid_df['n'].values
    y = valid_df[col].values

    if len(x) < 3: # 數據點太少無法平滑
        plt.plot(x, y, label=col, marker='o')
        continue

    # --- 插值運算：讓線條變圓滑 ---
    x_new = np.linspace(x.min(), x.max(), n_smooth)
    spl = make_interp_spline(x, y, k=3) # k=3 代表三次樣條曲線
    y_smooth = spl(x_new)
    
    # 確保平滑後的數據不會出現負值
    y_smooth = np.maximum(y_smooth, 0)

    # 設定特定樣式
    if col == 'SmoothSortBest':
        plt.plot(x_new, y_smooth, label=f'{col} (O(n))', linewidth=3, color='green', linestyle='--')
    else:
        plt.plot(x_new, y_smooth, label=col, linewidth=2, alpha=0.8)
    
    # 畫出原始數據點，方便對照
    plt.scatter(x, y, s=20, alpha=0.5)

# --- 圖表美化 ---
plt.title('Sorting Performance Comparison (Linear Scale - Smoothed)', fontsize=14)
plt.xlabel('Input Size (n)', fontsize=12)
plt.ylabel('Time (ms)', fontsize=12)

# 重要：限制 Y 軸範圍
# 如果不限制，InsertionSort (O(n^2)) 的幾萬毫秒會讓 SmoothSort (幾毫秒) 消失
# 這裡設定為以 SmoothSort (Random) 的最大值為基準的 5 倍，你可以自行調整
ymax = df['SmoothSort'].max() * 5
plt.ylim(0, ymax) 

plt.legend(loc='upper left')
plt.grid(True, which="both", linestyle=':', alpha=0.6)

plt.savefig('smoothed_linear_plot.png', dpi=300)
print("圓滑版圖表已儲存為 smoothed_linear_plot.png")