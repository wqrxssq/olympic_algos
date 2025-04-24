#include <math.h>

#include <algorithm>
#include <array>
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

const double EPS = 1e-4;
const double PI = acos(-1);
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define sz(_x) _x.size()
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

struct event {
    double y;
    int type;
};

const double smile_radius = 100.0;
const double eye_radius = 30.0;
const double teeth_radius = 60.0;

vector<event> ms;
vector<event> s1;
vector<event> s2;

bool in_circle(double x, double x1, double y1, double radius) {
    return x < x1 + radius && x > x1 - radius;
}

pair<double, double> line_circle_intersection(double x, double x1, double y1, double r) {
    double length = sqrt(r * r - (x - x1) * (x - x1));
    return {y1 - length, y1 + length};
}

pair<double, double> line_teeth_intersection(double x, double x1, double y1, double r) {
    double length = sqrt(r * r - (x - x1) * (x - x1));
    return pair<double, double>(y1 - length, y1);
}

void intersect(double x, double x1, double y1, vector<event>& segments) {
    segments.clear();

    if (!in_circle(x, x1, y1, smile_radius)) {
        return;
    }

    auto smile_points = line_circle_intersection(x, x1, y1, smile_radius);
    segments.pb({smile_points.first, 1});

    if (in_circle(x, x1, y1 - 20, teeth_radius)) {
        auto teeth_points = line_teeth_intersection(x, x1, y1 - 20, teeth_radius);
        segments.pb({teeth_points.first, -1});
        segments.pb({teeth_points.second, 1});
    }


    if (in_circle(x, x1 - 40, y1 + 30, eye_radius) || in_circle(x, x1 + 40, y1 + 30, eye_radius)) {
        pair<double, double> eye_points;
        if (in_circle(x, x1 - 40, y1 + 30, eye_radius)) {
            eye_points = line_circle_intersection(x, x1 - 40, y1 + 30, eye_radius);
        } else {
            eye_points = line_circle_intersection(x, x1 + 40, y1 + 30, eye_radius);
        }
        segments.pb({eye_points.first, -1});
        segments.pb({eye_points.second, 1});
    }
    segments.pb({smile_points.second, -1});
}

double len_union() {
    ms.clear();

    int l = 0;
    int r = 0;
    while (l < sz(s1) && r < sz(s2)) {
        if (s1[l].y <= s2[r].y) {
            ms.pb(s1[l]);
            l++;
        } else {
            ms.pb(s2[r]);
            r++;
        }
    }
    while (l < sz(s1)) {
        ms.pb(s1[l]);
        l++;
    }
    while (r < sz(s2)) {
        ms.pb(s2[r]);
        r++;
    }

    double len = 0;
    int cnt = 0;
    double last_open;
    for (auto [y, type] : ms) {
        cnt += type;
        if (cnt == 1 && type == 1) {
            last_open = y;
        }

        if (cnt == 0) {
            len += y - last_open;
        }
    }
    return len;
}

void solve() {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    double lx = min(x1, x2) - 100;
    double rx = max(x1, x2) + 100;

    double square = 0;
    for (double x = lx; x < rx; x += EPS) {
        intersect(x, x1, y1, s1);
        intersect(x, x2, y2, s2);
        square += len_union() * EPS;
    }

    cout << square << '\n';
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    setpr;
    solve();
    return 0;
}