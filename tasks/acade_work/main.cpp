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

void fft(vector<cd> & a, bool invert) {
    int n = sz(a);
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len/2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
 
vi poly_multiply(vi& a, vi& b) {
    int n = 1;
    while (n < sz(a) + sz(b) - 1)
        n <<= 1;
    vector<cd> fa(all(a)), fb(all(b));
    fa.resize(n); fb.resize(n);
 
    fft(fa, 0);
    fft(fb, 0);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, 1);
 
    vi res(n);
    for (int i = 0; i < n; i++)
        res[i] = int(round(fa[i].real()));
    return res;
}
 
vi build(string &S, char ch, int k) {
    int n = sz(S);
    vi diff(n+1, 0);
    for (int i = 0; i < n; i++) {
        if(S[i] == ch) {
            int L = max(0, i - k);
            int R = min(n - 1, i + k);
            diff[L] += 1;
            diff[R+1] -= 1;
        }
    }
    vi U(n, 0);
    int cur = 0;
    for (int i = 0; i < n; i++){
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
 
    vector<char> letters = {'A', 'C', 'G', 'T'};
    vvi conv(4);
    vi cnt(4);
 
    for (int idx = 0; idx < 4; idx++){
        char ch = letters[idx];
        vi U = build(S, ch, k);
 
        vi P(m, 0);
        for (int j = 0; j < m; j++){
            if(T[j] == ch){
                P[j] = 1;
                cnt[idx]++;
            }
        }
 
        reverse(P.begin(), P.end());
 
        conv[idx] = poly_multiply(U, P);
    }
 
    int ans = 0;
    for (int i = 0; i <= n - m; i++){
        bool ok = true;
        for (int idx = 0; idx < 4; idx++){
            if (conv[idx][i + m - 1] != cnt[idx]){
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
