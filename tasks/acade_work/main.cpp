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

double angle(r a) {
    return atan2(a.y, a.x);
}
double norm(double rad) {
    return (rad < 0 ? rad + 2 * PI : rad);
}

struct line {
    ll a, b, c;
};

bool brute(vector<r>& P, line n) {
    if (sz(P) == 1) {
        return P[0].x * n.a + P[0].y * n.b + n.c == 0;
    } else {
        return P[0].x * n.a + P[0].y * n.b + n.c == 0 ||
               P[1].x * n.a + P[1].y * n.b + n.c == 0 ||
               ((P[0].x * n.a + P[0].y * n.b + n.c > 0) != (P[1].x * n.a + P[1].y * n.b + n.c > 0));
    }
}

ll get_c(vector<r>& hull, vector<double>& dirs, r val, line n) {
    double angle_val = norm(angle(val));
    int pos = lower_bound(all(dirs), angle_val) - dirs.begin();

    // Ax + By + C = 0
    // C = -Ax - By

    pos %= sz(hull);

    return -n.a * hull[pos].x - n.b * hull[pos].y;
}

vector<r> graham(vector<r>& P) {
    r p0 = P[0];
    for (r p : P) {
        if (p.y < p0.y || (p.y == p0.y && p.x < p0.x)) {
            p0 = p;
        }
    }

    sort(all(P), [&](r a, r b){
        return (a - p0) % (b - p0) > 0
        || ((a - p0) % (b - p0) == 0 && sqr_len(a - p0) < sqr_len(b - p0));
    });

    vector<r> hull;
    for (r p : P) {
        while ((int)hull.size() > 1) {
            r new_v = p - hull.back();
            r old_v = hull.back() - hull[(int)hull.size() - 2];
            if (new_v % old_v >= 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(p);
    }
    return hull;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<line> lines(n);
    vector<r> p(m);

    for (line& l : lines) {
        cin >> l.a >> l.b >> l.c;
    }
    for (r& point : p) {
        cin >> point;
    }

    vector<r> hull = graham(p);
    vector<double> dirs;
    for (int i = 0; i < sz(hull); i++) {
        dirs.pb(norm(angle(hull[(i + 1) % sz(hull)] - hull[i])));
    }

    // display(dirs);
    assert(is_sorted(all(dirs)));

    vi ans;
    for (int i = 0; i < n; i++) {
        auto [a, b, c] = lines[i];

        if (sz(hull) < 3) {
            if (brute(hull, lines[i])) {
                ans.pb(i + 1);
            }
        } else {
            ll new_c1 = get_c(hull, dirs, r{-b, a}, lines[i]);
            ll new_c2 = get_c(hull, dirs, r{b, -a}, lines[i]);

            if (c >= min(new_c1, new_c2) && c <= max(new_c1, new_c2)) {
                ans.pb(i + 1);
            }
        }
    }

    cout << sz(ans) << '\n';
    for (int pos : ans) {
        cout << pos << ' ';
    }
    cout << '\n';
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