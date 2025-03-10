#pragma GCC optimize("O3,unroll-loops")

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
#include <iomanip>
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

const ll BASE = 1000000000;
const int KARATSUBA_STOP = 64;

typedef vector<ll> bigInt;

void normalize(bigInt& a) {
    ll carry = 0;
    for (int i = 0; i < sz(a); i++){
        ll sum = a[i] + carry;
        a[i] = sum % BASE;
        carry = sum / BASE;
    }
    while (carry) {
        a.pb(carry % BASE);
        carry /= BASE;
    }
    while (sz(a) > 1 && a.back() == 0) {
        a.pop_back();
    }
}

bigInt sum(const bigInt& a, const bigInt& b) {
    int n = max(sz(a), sz(b));
    bigInt res(n);
    ll carry = 0;
    for (int i = 0; i < n; i++){
        ll x = (i < sz(a) ? a[i] : 0);
        ll y = (i < sz(b) ? b[i] : 0);
        ll sum = x + y + carry;
        res[i] = sum % BASE;
        carry = sum / BASE;
    }
    if (carry)
        res.push_back(carry);
    return res;
}
bigInt sub(const bigInt& a, const bigInt& b) {
    bigInt res = a;
    ll carry = 0;
    for (int i = 0; i < sz(res); i++) {
        ll sub = (i < sz(b) ? b[i] : 0) + carry;
        if (res[i] < sub){
            res[i] += BASE;
            res[i] -= sub;
            carry = 1;
        } else {
            res[i] -= sub;
            carry = 0;
        }
    }
    while (sz(res) > 1 && res.back() == 0)
        res.pop_back();
    return res;
}
bigInt multiply_naive(const bigInt& a, const bigInt& b) {
    bigInt res(sz(a) + sz(b));
    for (int i = 0; i < sz(a); i++) {
        ll carry = 0;
        for (int j = 0; j < sz(b); j++) {
            ll sum = a[i] * b[j] + res[i + j] + carry;
            res[i + j] = sum % BASE;
            carry = sum / BASE;
        }
        res[i + sz(b)] += carry;
    }
    normalize(res);
    return res;
}
bigInt karatsuba(const bigInt& a, const bigInt& b){
    if(a.empty() || b.empty())
        return bigInt{0};
    if(a.size() < KARATSUBA_STOP || b.size() < KARATSUBA_STOP)
        return multiply_naive(a, b);

    int n = max(a.size(), b.size());
    int m = n / 2;

    bigInt a_low(a.begin(), a.begin() + min((int)a.size(), m));
    bigInt a_high(a.begin() + min((int)a.size(), m), a.end());
    bigInt b_low(b.begin(), b.begin() + min((int)b.size(), m));
    bigInt b_high(b.begin() + min((int)b.size(), m), b.end());
    bigInt z0 = karatsuba(a_low, b_low);
    bigInt z2 = karatsuba(a_high, b_high);
    bigInt a_sum = sum(a_low, a_high);
    bigInt b_sum = sum(b_low, b_high);
    bigInt z1 = karatsuba(a_sum, b_sum);
    z1 = sub(z1, z0);
    z1 = sub(z1, z2);
    int size = max({ sz(z0), sz(z1) + m, sz(z2) + 2 * m });
    bigInt res(size);
    for(int i = 0; i < sz(z0); i++)
        res[i] += z0[i];
    for(int i = 0; i < sz(z1); i++)
        res[i + m] += z1[i];
    for(int i = 0; i < sz(z2); i++)
        res[i + 2 * m] += z2[i];

    normalize(res);
    return res;
}
bigInt s_to_bigInt(const string &s){
    bigInt a;
    for(int i = sz(s); i > 0; i -= 9){
        int start = max(0, i - 9);
        ll num = stoll(s.substr(start, i - start));
        a.pb(num);
    }
    normalize(a);
    return a;
}

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    bool is_neg = false;
    if (s1[0] == '-') {
        is_neg ^= 1;
        s1 = s1.substr(1);
    }
    if (s2[0] == '-') {
        is_neg ^= 1;
        s2 = s2.substr(1);
    }

    bigInt a = s_to_bigInt(s1);
    bigInt b = s_to_bigInt(s2);
    bigInt res = karatsuba(a, b);

    is_neg &= !(sz(res) == 1 && res[0] == 0);
    if (is_neg) {
        cout << '-';
    }
    cout << res.back();
    for (int i = sz(res) - 2; i >= 0; i--) {
        cout << setw(9) << setfill('0') << res[i];
    }
    cout << '\n';
}

int main() {
    fast_input;
    solve();
}
