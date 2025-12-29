#ifndef SMOOTH_SORT_H
#define SMOOTH_SORT_H

#include <vector>
#include <cstddef>

using namespace std;

// Simplified int-only Smoothsort implementation (derived from the classic
// implementation). This header provides a single function:
//   void smooth_sort(std::vector<int>& a);

// Java-style LP based smoothsort implementation
// Adapted from Wikibooks / Java reference algorithm

namespace smoothsort {

static const int LP[] = { 1,1,3,5,9,15,25,41,67,109,177,287,465,753,1219,1973,3193,5167,8361,13529,21891,35421,57313,92735,150049,242785,392835,635621,1028457,1664079,2692537,4356617,7049155,11405773,18454929,29860703,48315633,78176337,126491971,204668309,331160281,535828591,866988873 };

static inline int ctz(unsigned int x) {
#ifdef __GNUG__
    return __builtin_ctz(x);
#else
    int c = 0;
    while ((x & 1) == 0) { x >>= 1; ++c; }
    return c;
#endif
}

inline void sift(std::vector<int> &m, int pshift, int head) {
    int val = m[head];
    while (pshift > 1) {
        int rt = head - 1;
        int lf = head - 1 - LP[pshift - 2];

        if (val >= m[lf] && val >= m[rt]) break;

        if (m[lf] >= m[rt]) {
            m[head] = m[lf];
            head = lf;
            pshift -= 1;
        } else {
            m[head] = m[rt];
            head = rt;
            pshift -= 2;
        }
    }
    m[head] = val;
}

inline void trinkle(std::vector<int> &m, unsigned int p, int pshift, int head, bool trusty) {
    int val = m[head];
    while (p != 1) {
        int stepson = head - LP[pshift];
        if (m[stepson] <= val) break;

        if (!trusty && pshift > 1) {
            int rt = head - 1;
            int lf = head - 1 - LP[pshift - 2];
            if (m[rt] >= m[stepson] || m[lf] >= m[stepson]) break;
        }

        m[head] = m[stepson];
        head = stepson;

        int trail = ctz(p & ~1u);
        p >>= trail;
        pshift += trail;
        trusty = false;
    }

    if (!trusty) {
        m[head] = val;
        sift(m, pshift, head);
    }
}

inline void smooth_sort(std::vector<int> &m) {
    int n = (int)m.size();
    if (n < 2) return;

    int head = 0;
    unsigned int p = 1;
    int pshift = 1;

    while (head < n) {
        if ((p & 3u) == 3u) {
            sift(m, pshift, head);
            p >>= 2;
            pshift += 2;
        } else {
            if (LP[pshift - 1] >= n - head) {
                trinkle(m, p, pshift, head, false);
            } else {
                sift(m, pshift, head);
            }

            if (pshift == 1) { p <<= 1; pshift = 0; }
            else { p <<= (pshift - 1); pshift = 1; }
        }
        p |= 1u;
        head++;
    }

    trinkle(m, p, pshift, head - 1, false);

    while (pshift != 1 || p != 1u) {
        if (pshift <= 1) {
            int trail = ctz(p & ~1u);
            p >>= trail;
            pshift += trail;
        } else {
            p <<= 2;
            p ^= 7u;
            pshift -= 2;

            trinkle(m, p >> 1, pshift + 1, head - LP[pshift] - 1, true);
            trinkle(m, p, pshift, head - 1, true);
        }
        head--;
    }
}

} // namespace smoothsort

#endif // SMOOTH_SORT_H
