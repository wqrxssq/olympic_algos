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
using vpii = vector<pii>;

const double EPS = 1e-9;
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
struct r {
    ll x, y;
    r(ll _x, ll _y) : x(_x), y(_y) {;}
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
bool is_in_angle(r a, r b, r o, r p) {
    return (a - o) % (p - o) >= 0 && (b - o) % (p - o) <= 0;
}

bool is_h_on_ray(r a, r b, r c) {
    return (b - a) * (c - a) >= 0;
}

struct r_double {
    double x, y;
    r_double(double _x, double _y) : x(_x), y(_y) {;}
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
bool is_on_segment(r_double a, r_double b, r_double c) {
    if (fabs((b - a) % (c - a)) < EPS &&
        c.x >= min(a.x, b.x) && c.x <= max(b.x, a.x) &&
        c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y))
        return true;
    return false;
}
bool is_on_line(r_double a, r_double b, r_double c) {
    return fabs((b - a) % (c - a)) < EPS;
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
    ll a, b, c;
    line(ll _a, ll _b, ll _c) : a(_a), b(_b), c(_c) {;}
    line() {;}
};
istream& operator >>(istream& in, line &a) {
    in >> a.a >> a.b >> a.c;
    return in;
}
ostream& operator <<(ostream& out, line a) {
    out << a.a << ' ' << a.b << ' ' << a.c;
    return out;
}
line get_line_from_two_r(r a, r b) {
    return {a.y - b.y, b.x - a.x, a % b};
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
double dist_line_to_r(line n, r p) {
    return fabs((double)(p.x * n.a + p.y * n.b + n.c)) / len(r(n.a, n.b));
}
double dist_line_to_r(line n, r_double p) {
    return fabs((p.x * n.a + p.y * n.b + n.c)) / len(r(n.a, n.b));
}
bool is_on_line(line n, r p) {
    return n.a * p.x + n.b * p.y + n.c == 0;
}
bool is_on_line(line n, r_double p) {
    return fabs(n.a * p.x + n.b * p.y + n.c) < EPS;
}
r_double reflect(r_double a, line n) {
    line n_normal(n.b, -n.a, n.a * a.y - n.b * a.x);
    r_double inter = intersect_lines(n, n_normal);
    return a + ((inter - a) * 2);
}

struct ray {
    r o, a;
    ray(r _o, r _a) : o(_o), a(_a) {;}
    ray() {;}
};
bool is_on_ray(r p, ray l) {
    return (p - l.o) % (l.a - l.o) == 0 && (p - l.o) * (l.a - l.o) >= 0;
}

bool is_on_ray(r_double p, r o, r a) {
    return fabs((p - convert_to_r_double(o)) % (convert_to_r_double(a) - convert_to_r_double(o))) <= EPS
            && (p - convert_to_r_double(o)) * (convert_to_r_double(a) - convert_to_r_double(o)) >= -EPS;
}

inline bool intersect_box_segments(ll a, ll b, ll c, ll d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return max(a, c) <= min(b, d);
}

bool is_segments_intersect(r a, r b, r c, r d) {
    line n = get_line_from_two_r(a, b);
    line m = get_line_from_two_r(c, d);
    if (is_equal(n, m)) {
        return intersect_box_segments(a.x, b.x, c.x, d.x) && intersect_box_segments(a.y, b.y, c.y, d.y);
    } else if (is_parallel(n, m)) {
        return false;
    } else {
        r_double inter = intersect_lines(n, m);
        return is_on_segment(convert_to_r_double(a), convert_to_r_double(b), inter) &&
                is_on_segment(convert_to_r_double(c), convert_to_r_double(d), inter);
    }
}

bool is_segment_ray_intersect(r a, r b, r c, r d) {
    line n = get_line_from_two_r(a, b);
    line m = get_line_from_two_r(c, d);
    if (is_equal(n, m)) {
        ray cd(c, d);
        return is_on_ray(a, cd) || is_on_ray(b, cd);
    } else if (is_parallel(n, m)) {
        return false;
    } else {
        r_double inter = intersect_lines(n, m);
        return is_on_ray(inter, c, d) && is_on_segment(convert_to_r_double(a), convert_to_r_double(b), inter);
    }
}

bool is_segment_line_intersect(r a, r b, r c, r d) {
    line n = get_line_from_two_r(a, b);
    line m = get_line_from_two_r(c, d);
    if (is_equal(n, m)) {
        return true;
    } else if (is_parallel(n, m)) {
        return false;
    } else {
        r_double inter = intersect_lines(n, m);
        return is_on_segment(convert_to_r_double(a), convert_to_r_double(b), inter) && 
                is_on_line(m, inter);
    }
}
bool is_rays_intersect(r a, r b, r c, r d) {
    line n = get_line_from_two_r(a, b);
    line m = get_line_from_two_r(c, d);
    if (is_equal(n, m)) {
        return (b - a) * (d - c) >= 0 || is_segments_intersect(a, b, c, d);
    } else if (is_parallel(n, m)) {
        return false;
    } else {
        r_double inter = intersect_lines(n, m);
        return is_on_ray(inter, c, d) && is_on_ray(inter, a, b);
    }
}

bool is_ray_line_intersect(r a, r b, r c, r d) {
    line n = get_line_from_two_r(a, b);
    line m = get_line_from_two_r(c, d);
    if (is_equal(n, m)) {
        return true;
    } else if (is_parallel(n, m)) {
        return false;
    } else {
        r_double inter = intersect_lines(n, m);
        return is_on_ray(inter, a, b) && is_on_line(m, inter);
    }
}

double dist_dot_dot(r a, r b) {
    return len(a - b);
}

// [a, b], dot c
double dist_dot_segment(r a, r b, r c) {
    if (is_h_on_segment(a, b, c)) {
        return get_h(a, b, c);
    } else {
        return min(dist_dot_dot(a, c), dist_dot_dot(b, c));
    }
}
// [a, b), dot c
double dist_dot_ray(r a, r b, r c) {
    if (is_h_on_ray(a, b, c)) {
        return get_h(a, b, c);
    } else {
        return dist_dot_dot(a, c);
    }
}
// (a, b), dot c
double dist_dot_line(r a, r b, r c) {
    return get_h(a, b, c);
}
// [a, b], [c, d]
double dist_segment_segment(r a, r b, r c, r d) {
    if (is_segments_intersect(a, b, c, d)) {
        return 0;
    } else {
        return min({
            dist_dot_segment(a, b, c),
            dist_dot_segment(a, b, d),
            dist_dot_segment(c, d, a),
            dist_dot_segment(c, d, b)
        });
    }
}
// [a, b], [c, d)
double dist_segment_ray(r a, r b, r c, r d) {
    if (is_segment_ray_intersect(a, b, c, d)) {
        return 0;
    } else {
        return min(dist_dot_ray(c, d, a), dist_dot_ray(c, d, b));
    }
}

// [a, b], (c, d)
double dist_segment_line(r a, r b, r c, r d) {
    if (is_segment_line_intersect(a, b, c, d)) {
        return 0;
    } else {
        return min(dist_dot_line(c, d, a), dist_dot_line(c, d, b));
    }
}

// [a, b), [c, d)
double dist_ray_ray(r a, r b, r c, r d) {
    if (is_rays_intersect(a, b, c, d)) {
        return 0;
    } else {
        return min(dist_dot_ray(a, b, c), dist_dot_ray(c, d, a));
    }
}

// [a, b), (c, d)
double dist_ray_line(r a, r b, r c, r d) {
    if (is_ray_line_intersect(a, b, c, d)) {
        return 0;
    } else {
        return dist_dot_line(c, d, a);
    }
}

// (a, b), (c, d)
double dist_line_line(r a, r b, r c, r d) {
    line n = get_line_from_two_r(a, b);
    line m = get_line_from_two_r(c, d);
    if (is_equal(n, m)) {
        return 0;
    } else if (is_parallel(n, m)) {
        return dist_dot_line(a, b, c);
    } else {
        return 0;
    }
}


void solve() {
    r a, b, c, d;
    cin >> a >> b >> c >> d;

    setpr;

    cout << dist_dot_dot(a, c) << '\n';
    cout << dist_dot_segment(c, d, a) << '\n';
    cout << dist_dot_ray(c, d, a) << '\n';
    cout << dist_dot_line(c, d, a) << '\n';

    cout << dist_dot_segment(a, b, c) << '\n';
    cout << dist_segment_segment(a, b, c, d) << '\n';
    cout << dist_segment_ray(a, b, c, d) << '\n';
    cout << dist_segment_line(a, b, c, d) << '\n';

    cout << dist_dot_ray(a, b, c) << '\n';
    cout << dist_segment_ray(c, d, a, b) << '\n';
    cout << dist_ray_ray(a, b, c, d) << '\n';
    cout << dist_ray_line(a, b, c, d) << '\n';

    cout << dist_dot_line(a, b, c) << '\n';
    cout << dist_segment_line(c, d, a, b) << '\n';
    cout << dist_ray_line(c, d, a, b) << '\n';
    cout << dist_line_line(a, b, c, d) << '\n';
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
