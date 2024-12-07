#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int C = 16;
const int MEM = (1 << C);
const int MASK = MEM - 1;

void fast_sort(vector<uint32_t>& a) {
    vector<uint32_t> a_copy = a;
    vector<int>cnt(MEM);

    for (uint32_t x : a) {
        cnt[x & MASK]++;
    }
    for (size_t i = 1; i < MEM; ++i) {
        cnt[i] += cnt[i - 1];
    }
    reverse(a.begin(), a.end());
    for (uint32_t x : a) {
        a_copy[--cnt[x & MASK]] = x;
    }
    a.swap(a_copy);

    fill(cnt.begin(), cnt.end(), 0);
    for (uint32_t x : a) {
        cnt[x >> C]++;
    }
    for (size_t i = 1; i < MEM; ++i) {
        cnt[i] += cnt[i - 1];
    }
    reverse(a.begin(), a.end());
    for (uint32_t x : a) {
        a_copy[--cnt[x >> C]] = x;
    }
    a.swap(a_copy);
}

// int main() {
//     vector<uint32_t> a = {216, 125, 215236, 32523523, 1532, 1225};
//     fast_sort(a);
//     for (int x : a) {
//         cout << x << ' ';
//     }
//     cout << '\n';
// }