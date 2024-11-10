#include <iostream>
#include <random>
#include <set>
#include <chrono>
#include <vector>
#include <assert.h>
using namespace std;

const int MAXN = 5;
const int MAXH = 10;
const int MAXW = 5;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<int> generate_vector(int n, int l, int r) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = rnd() % (r - l + 1) + l; // [0, r - l] -> [l, r]
    }
    return res;
}

int sum(vector<int>& a) {
    int s = 0;
    for (int val : a) {
        s += val;
    }
    return s;
}

int main() {
    int n = rnd() % 23 + 1; // [1, 23]
    int H = rnd() % 100 + 1; // [1, 100]
    cout << n << ' ' << H << '\n';

    vector<int> h, w;
    h = generate_vector(n, 1, 100);
    do {
        w = generate_vector(n, 1, 100);
    } while (sum(w) < H);

    for (int hi : h) {
        cout << hi << ' ';
    }
    cout << '\n';

    for (int wi : w) {
        cout << wi << ' ';
    }
    cout << '\n';
}
