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

const double EPS = 1e-7;
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

struct r_double {
    double x, y;
    r_double(double x, double y) : x(x), y(y) {;}
    r_double() {;}
};
istream& operator >>(istream& in, r_double& a) {
    in >> a.x >> a.y;
    return in;
}
ostream& operator <<(ostream& out, r_double a) {
    out << a.x << ' ' << a.y;
    return out;
}
r_double operator +(r_double a, r_double b) {
    return {a.x + b.x, a.y + b.y};
}
r_double operator -(r_double a, r_double b) {
    return {a.x - b.x, a.y - b.y};
}
r_double operator *(r_double a, double k) {
    return {a.x * k, a.y * k};
}
double operator *(r_double a, r_double b) {
    return a.x * b.x + a.y * b.y;
}
double operator %(r_double a, r_double b) {
    return a.x * b.y - a.y * b.x;
}
double len(r_double a) {
    return hypot(a.x, a.y);
}
r_double convert_to_r_double(r a) {
    return {(double)a.x, (double)a.y};
}
r_double norm(r_double a) {
    return {a.x / len(a), a.y / len(a)};
}
r_double norm(r a) {
    return norm(convert_to_r_double(a));
}
r_double get_bic(r_double a, r_double b, r_double o) {
    r_double oa = norm(a - o);
    r_double ob = norm(b - o);
    return o + oa + ob;
}

struct line {
    double a, b, c;
    line(double a, double b, double c) : a(a), b(b), c(c) {;}
    line() {;}
};
line get_line_parallel(r_double a, line n) {
    return {n.a, n.b, -a.x * n.a -a.y * n.b};
}
line perpendicular(line n) {
    return {n.b, -n.a, n.c};
}
line get_line_from_two_r(r a, r b) {
    return {(double)a.y - b.y, (double)b.x - a.x, (double)(a % b)};
}
bool is_parallel(line n, line m) {
    return n.a * m.b - n.b * m.a == 0;
}
bool is_equal(line n, line m) {
    return n.a * m.b - n.b * m.a == 0 && n.a * m.c - n.c * m.a == 0 && n.b * m.c - n.c * m.b == 0;
}
r_double intersect_lines(line n, line m) {
    return {(double)(n.b * m.c - n.c * m.b) / (n.a * m.b - n.b * m.a),
        (double)(n.a * m.c - n.c * m.a) / (n.b * m.a - n.a * m.b)};
}

struct circle {
    r_double o;
    double radius;
};

circle get_circle_from_3(r a, r b, r c) {
    r_double m1 = convert_to_r_double(a + b) * 0.5;
    r_double m2 = convert_to_r_double(b + c) * 0.5;
    line n = get_line_parallel(m1, perpendicular(get_line_from_two_r(a, b)));
    line m = get_line_parallel(m2, perpendicular(get_line_from_two_r(b, c)));

    r_double o = intersect_lines(n, m);
    return {o, len(o - convert_to_r_double(a))};
}

circle get_circle_from_2(const r &a, const r &b) {
    r_double da = convert_to_r_double(a);
    r_double db = convert_to_r_double(b);
    r_double center = {(da.x + db.x) * 0.5, (da.y + db.y) * 0.5};
    return {center, len(da - center)};
}

bool is_in_circle(r p, circle c) {
    return len(convert_to_r_double(p) - c.o) <= c.radius + EPS;
}

void solve() {
    int n;
    cin >> n;
    vector<r> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i];
    }

    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(pts.begin(), pts.end(), rnd);

    circle c;
    c.o = convert_to_r_double(pts[0]);
    c.radius = 0;

    for (int i = 1; i < n; i++) {
        if (!is_in_circle(pts[i], c)) {
            c.o = convert_to_r_double(pts[i]);
            c.radius = 0;
            for (int j = 0; j < i; ++j) {
                if (!is_in_circle(pts[j], c)) {
                    c = get_circle_from_2(pts[i], pts[j]);
                    for (int k = 0; k < j; ++k) {
                        if (!is_in_circle(pts[k], c)) {
                            c = get_circle_from_3(pts[i], pts[j], pts[k]);
                        }
                    }
                }
            }
        }
    }

    setpr;
    cout << c.o.x << ' ' << c.o.y << '\n' << c.radius << '\n';
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