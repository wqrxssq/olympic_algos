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
using ld = long double;

const double EPS = 1e-10;
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

struct r {
    ll x, y;
    r(ll x, ll y) : x(x), y(y) {;}
    r() {;}
    bool operator == (r a) {
        return x == a.x && y == a.y;
    }
};
istream& operator >>(istream& in, r& a) {
    in >> a.x >> a.y;
    return in;
}
ostream& operator <<(ostream& out, r a) {
    out << a.x << ' ' << a.y;
    return out;
}
r operator +(r a, r b) {
    return {a.x + b.x, a.y + b.y};
}
r operator -(r a, r b) {
    return {a.x - b.x, a.y - b.y};
}
r operator *(r a, int k) {
    return {a.x * k, a.y * k};
}
ll operator *(r a, r b) {
    return a.x * b.x + a.y * b.y;
}
ll operator %(r a, r b) {
    return a.x * b.y - a.y * b.x;
}
ll sqr_len(r a) {
    return a.x * a.x + a.y * a.y;
}
double len(r a) {
    return hypot(a.x, a.y);
}
bool is_on_segment(r a, r b, r c) {
    if ((b - a) % (c - a) == 0 &&
        c.x >= min(a.x, b.x) && c.x <= max(b.x, a.x) &&
        c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y))
        return true;
    return false;
}
bool is_on_line(r a, r b, r c) {
    return (b - a) % (c - a) == 0;
}
bool is_h_on_segment(r a, r b, r c) {
    return (b - a) * (c - a) >= 0 && (a - b) * (c - b) >= 0;
}
double get_h(r a, r b, r c) {
    if (a == b)
        return len(c - a);
    return fabs(double((b - a) % (c - a)) / len(b - a));
}

double dist_point_to_segment(r a, r b, r c) {
    if (is_h_on_segment(a, b, c)) {
        return get_h(a, b, c);
    } else {
        return min(len(c - a), len(c - b));
    }
}

bool is_in_poly(r a, vector<r>& P) {
    int n = sz(P);
    bool flag = (a - P[0]) % (a - P[1]) >= 0;
    for (int i = 0; i < n; i++) {
        if (((a - P[i]) % (a - P[(i + 1) % n]) >= 0) != flag) {
            return false;
        }
    }
    return true;
}

double dist_dot_polygon(r a, vector<r>& P) {
    if (is_in_poly(a, P)) {
        return 0;
    } else {
        int n = sz(P);
        double res = INFLL;
        for (int i = 0; i < n; i++) {
            res = min(res, dist_point_to_segment(P[i], P[(i + 1) % n], a));
        }
        return res;
    }
}

void reorder_polygon(vector<r> & P){
    int pos = 0;
    for (int i = 1; i < P.size(); i++){
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<r> minkowski(vector<r>& P, vector<r>& Q){
    reorder_polygon(P);
    reorder_polygon(Q);

    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);

    vector<r> result;
    int i = 0, j = 0;
    while (i < P.size() - 2 || j < Q.size() - 2) {
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]) % (Q[j + 1] - Q[j]);
        if (cross >= 0 && i < P.size() - 2)
            i++;
        if (cross <= 0 && j < Q.size() - 2)
            j++;
    }
    return result;
}

double dist_2_polygons(vector<r>& P, vector<r>& Q) {
    for (r& p : Q) {
        p = p * -1;
    }

    vector<r> sum_minkowski = minkowski(P, Q);

    return dist_dot_polygon(r{0, 0}, sum_minkowski);
}

void solve() {
    int n;
    cin >> n;
    vector<r> P(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i];
    }
    reverse(all(P));

    int m;
    cin >> m;
    vector<r> Q(m);
    for (int i = 0; i < m; i++) {
        cin >> Q[i];
    }
    reverse(all(Q));

    cout << dist_2_polygons(P, Q) << '\n';
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