#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <functional>
#include <vector>

using namespace std;
using namespace std::chrono;

// 測量函式執行時間的工具
template<typename Func>
long long measure_time(Func sort_func, vector<int>& data) {
    auto start = high_resolution_clock::now();
    sort_func(data);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

#endif // TIMER_H