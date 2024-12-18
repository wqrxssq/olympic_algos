#pragma GCC optimize("O3,unroll-loops")

#include <math.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <climits>
using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
const double PI = acos(-1);
const double EPS = 1e-6;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

mt19937 rnd(static_cast<unsigned int>(chrono::steady_clock().now().time_since_epoch().count()));

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)        \
    for (auto el : _x)     \
        cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x)     \
    for (auto& el : _x) \
        cin >> el;
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr(_x) cout << setprecision(_x) << fixed
#define debug(x) cout << __FUNCTION__ << ": " << #x " = " << (x) << endl


double func(vector < pair <double, double> > contest) {
    long double sum = 0;
    for (auto [a, b] : contest) {
        sum += (a / b);
    }
    return sum / (int)contest.size();
}

void solve () {
    vector < pair <double, double> > contest;
    contest.push_back({23, 28}); // 1
    contest.push_back({28, 32}); // 2
    contest.push_back({26, 28}); // 3
    contest.push_back({16, 24}); // 4
    contest.push_back({14, 28}); // 5
    contest.push_back({20, 28}); // 6
    contest.push_back({28, 32}); // 7

    double score_hm = func(contest) * 10;
    double score_kollok = 10;
    double score_kr = 3.5;
    double score_lab = 10;
    double score_exam = 1;

    cout << setprecision(3) << fixed << '\n';
    double score = score_hm * 0.25 + score_kollok * 0.25 + score_kr * 0.15 + score_lab * 0.05 + score_exam * 0.3;
    cout << "not rounded = " << score << " " << '\n';
    cout << "rounded score = " << round(score) << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
