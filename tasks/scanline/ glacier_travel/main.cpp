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

struct r {
    int x, y;
};

struct r_double {
    double x, y;
};

struct event {
    double t;
    int type, id;
};

r operator -(r a, r b) {
    return {a.x - b.x, a.y - b.y};
}
double len(r a) {
    return sqrt(1LL * a.x * a.x + 1LL * a.y * a.y);
}
r_double operator -(r_double a, r_double b) {
    return {a.x - b.x, a.y - b.y};
}
double len(r_double a) {
    return sqrt(1LL * a.x * a.x + 1LL * a.y * a.y);
}

const int MAXN = 1e6;
int n;
r p[MAXN];
r line[MAXN];
double s;

double f(double t, int id_a, r_double a, int id_b, r_double b) {
    a = {a.x + (double)line[id_a].x * t / len(line[id_a]), 
        a.y + (double)line[id_a].y * t / len(line[id_a])};
    b = {b.x + (double)line[id_b].x * t / len(line[id_b]), 
        b.y + (double)line[id_b].y * t / len(line[id_b])};
    return len(a - b);
}

void solve () {
    cin >> s >> n;

    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    for (int i = 0; i < n - 1; i++) {
        line[i] = p[i + 1] - p[i];
    }

    vector<event> events;
    double cur_time = 0;

    for (int i = 0; i < n - 1; i++) {
        events.push_back({cur_time, 0, i});
        events.push_back({cur_time + s, 1, i});
        cur_time += len(line[i]);
    }
    events.push_back({cur_time, 0, n - 1});

    sort(events.begin(), events.end(), [](event a, event b) {
        return a.t < b.t;
    });

    double ans = INF;

    // в каком отрезке
    int id_a = -1, id_b = -1;

    // текущие коордианты точки a, b
    r_double a = {0, 0}, b = {0, 0};

    // текущее время для точки a, b
    double prev_t;

    for (int i = 0; i < (int)events.size() - 1; i++) {
        auto [t, type, id] = events[i];
        if (type == 0) {
            // вычислим координаты a, b
            id_a = id;
            a = {(double)p[id].x, (double)p[id].y};

            if (id_a == n - 1) {
                break;
            }

            if (id_b == -1) {
                prev_t = t;
                continue;
            }

            b = {b.x + (double)line[id_b].x * (double)(t - prev_t) / len(line[id_b]), 
                b.y + (double)line[id_b].y * (double)(t - prev_t) / len(line[id_b])};
            prev_t = t;
        } else {
            // вычислим координаты a, b
            id_b = id;
            b = {(double)p[id].x, (double)p[id].y};

            a = {a.x + (double)line[id_a].x * (double)(t - prev_t) / len(line[id_a]), 
                a.y + (double)line[id_a].y * (double)(t - prev_t) / len(line[id_a])};
            prev_t = t;
        }

        double l = 0;
        double r = events[i + 1].t - events[i].t;
        while (r - l > EPS) {
            double m1 = l + (r - l) / 3;
            double m2 = r - (r - l) / 3;
            if (f(m1, id_a, a, id_b, b) <= f(m2, id_a, a, id_b, b)) {
                r = m2;
            } else {
                l = m1;
            }
        }
        ans = min(ans, f((l + r) / 2, id_a, a, id_b, b));
    }

    cout << ans << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cout << setprecision(6) << fixed;
    solve();
}
