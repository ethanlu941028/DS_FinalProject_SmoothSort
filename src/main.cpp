#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "smooth_sort.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    if (T == 0) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        smoothsort::smooth_sort(a);
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << a[i];
        }
        cout << '\n';
    }
    return 0;
}
