#include <iostream>
#include <vector>
#include <algorithm>
#include "src/smooth_sort.h"

using namespace std;

int main() {
    vector<int> test = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    cout << "Original: ";
    for (int x : test) cout << x << " ";
    cout << endl;
    
    smoothsort::smooth_sort(test);
    
    cout << "Sorted:   ";
    for (int x : test) cout << x << " ";
    cout << endl;
    
    // 驗證是否正確排序
    bool is_sorted = is_sorted_until(test.begin(), test.end()) == test.end();
    cout << "Is correctly sorted: " << (is_sorted ? "YES" : "NO") << endl;
    
    return 0;
}