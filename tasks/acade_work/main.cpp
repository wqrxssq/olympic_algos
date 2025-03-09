// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
  
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <math.h>
#include <vector>
#include <string>
#include <stack>
#include <cassert>
#include <random>
#include <chrono>
#include <cstring>
using namespace std;
     
#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define sz(_x) (int)_x.size()
#define ff first
#define ss second
#define cin_arr(a)for (int _ii = 0; _ii < (int)a.size(); _ii++)  \
    cin >> a[_ii];
#define display(a) for (auto _ii : a)                            \
    cout << _ii << ' ';                                          \
cout << '\n';
#define display_pairs(a) for (auto _ii : a)                      \
    cout << _ii.ff << ' ' << _ii.ss << '\n';
#define display_matrix(a) for (auto _row : a)                    \
{                                                                \
    for (auto _cell : _row)                                      \
        cout << _cell << ' ';                                    \
    cout << '\n';                                                \
}                                                                \
cout << '\n'
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define fast_interactive_input ios_base::sync_with_stdio(0)

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;
typedef vector <vi> vvi;

const int INF = 1e9;
const ll INFLL = 1e18;
const int mod = 1e9 + 7;
const double eps = 1e-6;

struct item {
    int a, b, c;
};

int binpow(int base, int n) {
    if (n == 0) {
        return 1;
    }
    if (n & 1) {
        return binpow(base, n - 1) * base;
    } else {
        int temp = binpow(base, n >> 1);
        return temp * temp;
    }
}

vpii enc(int mask, int len) {
    int pos = 0;
    vpii res;
    while (mask) {
        res.pb({mask % 3, pos++});
        mask /= 3;
    }
    while (res.size() < len) {
        res.pb({0, pos++});
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<item> w(n);
    for (auto &[a, b, c] : w) {
        cin >> a >> b >> c;
    }

    int left_half = (n / 2);
    int right_half = n - left_half;

    map<pii, pii> q;

    int end_left = binpow(3, left_half);
    for (int mask = 0; mask < end_left; mask++) {
        vpii choices = enc(mask, left_half);
        // d1 = L - M
        // d2 = M - W
        int L = 0;
        int d1 = 0, d2 = 0;
        for (auto [choice, pos] : choices) {
            if (choice == 0) { // LM
                L += w[pos].a;
                d1 += w[pos].a - w[pos].b;
                d2 += w[pos].b;
            } else if (choice == 1) { // MW
                d1 += -w[pos].b;
                d2 += w[pos].b - w[pos].c;
            } else { // LW
                L += w[pos].a;
                d1 += w[pos].a;
                d2 += -w[pos].c;
            }
        }

        if (q.contains({d1, d2})) {
            if (q[{d1, d2}].ff < L) {
                q[{d1, d2}] = {L, mask};
            }
        } else {
            q[{d1, d2}] = {L, mask};
        }
    }

    int max_L = -INF;
    int best_mask_left = -1;
    int best_mask_right = -1;

    int end_right = binpow(3, right_half);
    for (int mask = 0; mask < end_right; mask++) {
        vpii choices = enc(mask, right_half);
        int L = 0;
        int d1 = 0, d2 = 0;
        for (auto [choice, pos] : choices) {
            if (choice == 0) {
                L += w[pos + left_half].a;
                d1 += w[pos + left_half].a - w[pos + left_half].b;
                d2 += w[pos + left_half].b;
            } else if (choice == 1) {
                d1 += -w[pos + left_half].b;
                d2 += w[pos + left_half].b - w[pos + left_half].c;
            } else {
                L += w[pos + left_half].a;
                d1 += w[pos + left_half].a;
                d2 += -w[pos + left_half].c;
            }
        }

        if (q.contains({-d1, -d2}) && L + q[{-d1, -d2}].ff > max_L) {
            max_L = L + q[{-d1, -d2}].ff;
            best_mask_left = q[{-d1, -d2}].ss;
            best_mask_right = mask;
        }
    }

    if (best_mask_left == -1) {
        cout << "Impossible\n";
    } else {
        vpii left = enc(best_mask_left, left_half);
        vpii right = enc(best_mask_right, right_half);

        for (auto [choice, pos] : left) {
            switch (choice) {
            case 0:
                cout << "LM\n";
                break;
            case 1:
                cout << "MW\n";
                break;
            default:
                cout << "LW\n";
                break;
            }
        }
        for (auto [choice, pos] : right) {
            switch (choice) {
            case 0:
                cout << "LM\n";
                break;
            case 1:
                cout << "MW\n";
                break;
            default:
                cout << "LW\n";
                break;
            }
        }
    }
}

int main() {
    fast_input;
    solve();
}