#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <string>
#include <stack>
#include <cassert>
#include <iomanip>
#include <random>
#include <complex>
#include <chrono>
#include <cstring>
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using vi = vector <int>;
using vvi = vector <vi>;
using vll = vector <ll>;
using pii = pair <int, int>;
using vpii = vector <pii>;
using cd = complex<double>;
 
const double eps = 0.0001;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;
const double PI = acos(-1);
 
#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x) for (auto el : _x) cout << el << ' '; cout << '\n'
#define cin_arr(_x) for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(6) << fixed
 
const int KARATSUBA_STOP = 256;
 
vi multiply_naive(vi &a, vi &b) {
    int n = sz(a), m = sz(b);
    vi res(n + m - 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            res[i + j] += a[i] * b[j];
    return res;
}
 
vi poly_add(vi &a, vi &b) {
    int n = max(sz(a), sz(b));
    vi res(n, 0);
    for (int i = 0; i < n; i++) {
        res[i] += (i < sz(a) ? a[i] : 0);
        res[i] += (i < sz(b) ? b[i] : 0);
    }
    return res;
}
 
vi poly_sub(vi &a, vi &b) {
    int n = max(sz(a), sz(b));
    vi res(n, 0);
    for (int i = 0; i < n; i++) {
        res[i] += (i < sz(a) ? a[i] : 0);
        res[i] -= (i < sz(b) ? b[i] : 0);
    }
    return res;
}
 
vi karatsuba(vi &a, vi &b) {
    if (a.empty() || b.empty()) 
        return {0};
    if (sz(a) < KARATSUBA_STOP || b.size() < KARATSUBA_STOP)
        return multiply_naive(a, b);
    int n = max(sz(a), sz(b));
    int m = n / 2;
    vi a_low(a.begin(), a.begin() + min((int)a.size(), m));
    vi a_high(a.begin() + min((int)a.size(), m), a.end());
    vi b_low(b.begin(), b.begin() + min((int)b.size(), m));
    vi b_high(b.begin() + min((int)b.size(), m), b.end());
    vi z0 = karatsuba(a_low, b_low);
    vi z2 = karatsuba(a_high, b_high);
    vi a_sum = poly_add(a_low, a_high);
    vi b_sum = poly_add(b_low, b_high);
    vi z1 = karatsuba(a_sum, b_sum);
    z1 = poly_sub(z1, z0);
    z1 = poly_sub(z1, z2);
    int size = max({ sz(z0), sz(z1) + m, sz(z2) + 2 * m });
    vi res(size);
    for (int i = 0; i < sz(z0); i++) res[i] += z0[i];
    for (int i = 0; i < sz(z1); i++) res[i + m] += z1[i];
    for (int i = 0; i < sz(z2); i++) res[i + 2 * m] += z2[i];
    return res;
}
 
vi poly_multiply(vi &a, vi &b) {
    vi res = karatsuba(a, b);
    return res;
}
 
vi build(string &S, char ch, int k) {
    int n = sz(S);
    vi diff(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (S[i] == ch) {
            int L = max(0, i - k);
            int R = min(n - 1, i + k);
            diff[L]++;
            diff[R + 1]--;
        }
    }
    vi U(n, 0);
    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];
        U[i] = (cur > 0) ? 1 : 0;
    }
    return U;
}
 
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    string S, T;
    cin >> S >> T;
    vector<char> letters = { 'A', 'C', 'G', 'T' };
    vvi conv(4);
    vi cnt(4, 0);
    for (int idx = 0; idx < 4; idx++) {
        char ch = letters[idx];
        vi U = build(S, ch, k);
        vi P(m, 0);
        for (int j = 0; j < m; j++) {
            if (T[j] == ch) {
                P[j] = 1;
                cnt[idx]++;
            }
        }
        reverse(all(P));
        conv[idx] = poly_multiply(U, P);
    }
    int ans = 0;
    for (int i = 0; i <= n - m; i++) {
        bool ok = true;
        for (int idx = 0; idx < 4; idx++) {
            if (conv[idx][i + m - 1] != cnt[idx]) {
                ok = false;
                break;
            }
        }
        if (ok) ans++;
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
