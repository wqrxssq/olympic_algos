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

const int MAXN = 1e5;

vi g[MAXN];
int is_terminal[MAXN];
int cost[MAXN];

int alpha_beta_pruning(int v, int alpha = -INF, int beta = INF, bool is_max_play = true) {
    if (is_terminal[v]) {
        return cost[v];
    }
    if (is_max_play) {
        for (int u : g[v]) {
            alpha = max(alpha, alpha_beta_pruning(u, alpha, beta, is_max_play ^ 1));
            // beta pruning, min won't go to this vertex
            if (alpha >= beta) {
                return alpha;
            }
        }
        return alpha;
    } else {
        for (int u : g[v]) {
            beta = min(beta, alpha_beta_pruning(u, alpha, beta, is_max_play ^ 1));
            // alpha pruning, max won't go to this vertex
            if (alpha >= beta) {
                return beta;
            }
        }
        return beta;
    }
}

void solve() {
    int n;
    cin >> n >> a >> b >> c >> m;
    cout << alpha_beta_pruning(0, (1 << n) - 1) << '\n';
}

int main() {
    fast_input;
    solve();
}