#include <math.h>

#include <algorithm>
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
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;

#define double long double

const double EPS = 1e-6;
const double PI = acos(-1);
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define display(_x)                       \
    for (auto el : _x) cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x) \
    for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(9) << fixed

mt19937 rnd(0);
struct r {
    int x, y;
};

struct KeyHash {
    size_t operator()(const pair<ll, ll>& k) const{
        return (hash<ll>()(k.first) * 382387) ^ 
            hash<ll>()(k.second);
    }
};

istream& operator >>(istream& in, r& p) {
    in >> p.x >> p.y;
    return in;
}
ostream& operator <<(ostream& out, r p) {
    out << p.x << ' ' << p.y;
    return out;
}

r operator +(r a, r b) {
    return {a.x + b.x, a.y + b.y};
}
r operator -(r a, r b) {
    return {a.x - b.x, a.y - b.y};
}
double len(r a) {
    return hypot(a.x, a.y);
}

const int MAXN = 1e5;
int n;
r p[MAXN];
double d;
r best_a, best_b;
unordered_map<pll, vector<r>, KeyHash> q;
const vector<pii> moves = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 0}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

ll lfloor(double x) {
    return (ll)floor(x);
}

void build(int r) {
    q.clear();
    for (int i = 0; i <= r; i++) {
        q[{lfloor(p[i].x / d), lfloor(p[i].y / d)}].pb(p[i]);
    }
}

double check(r a, vector<r> temp) {
    double res = INFLL;
    for (r b : temp) {
        double new_d = min(res, len(a - b));
        res = min(new_d, res);
        if (new_d < d) {
            best_a = a;
            best_b = b;
        }
    }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    shuffle(p, p + n, rnd);

    d = len(p[0] - p[1]);
    best_a = p[0]; best_b = p[1];
    build(1);

    for (int i = 2; i < n; i++) {
        double min_d = INFLL;
        for (pii move : moves) {
            min_d = min(min_d, check(p[i], q[{lfloor(p[i].x / d) + move.ff, lfloor(p[i].y / d) + move.ss}]));
        }

        q[{lfloor(p[i].x / d), lfloor(p[i].y / d)}].pb(p[i]);
        if (min_d < d) {
            d = min_d;
            build(i);
        }
    }
    // setpr;
    // cout << d << '\n';
    cout << best_a << '\n' << best_b << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}
