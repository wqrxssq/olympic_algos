#pragma GCC optimize("O3,unroll-loops")

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

const double EPS = 1e-9;
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

struct Seg {
    ll x1, y1, x2, y2;
    int id;
    double get_y(double x) const {
        return y1 + (y2 - y1) * (x - x1) / double(x2 - x1);
    }
};

static double currentX;
vector<Seg> segs;

struct Cmp {
    bool operator()(int i, int j) const {
        double yi = segs[i].get_y(currentX);
        double yj = segs[j].get_y(currentX);
        if (yi + EPS < yj) return true;
        if (yj + EPS < yi) return false;
        return i < j;
    }
};

int orient(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
    ll v = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

bool onSeg1D(ll a, ll b, ll c, ll d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersect(int i, int j) {
    auto &A = segs[i], &B = segs[j];
    if (!onSeg1D(A.x1, A.x2, B.x1, B.x2)) return false;
    if (!onSeg1D(A.y1, A.y2, B.y1, B.y2)) return false;
    int o1 = orient(A.x1, A.y1, A.x2, A.y2, B.x1, B.y1);
    int o2 = orient(A.x1, A.y1, A.x2, A.y2, B.x2, B.y2);
    int o3 = orient(B.x1, B.y1, B.x2, B.y2, A.x1, A.y1);
    int o4 = orient(B.x1, B.y1, B.x2, B.y2, A.x2, A.y2);
    if (o1 * o2 < 0 && o3 * o4 < 0) return true;
    if (o1 == 0 && onSeg1D(A.x1, A.x2, B.x1, B.x1) && onSeg1D(A.y1, A.y2, B.y1, B.y1)) return true;
    if (o2 == 0 && onSeg1D(A.x1, A.x2, B.x2, B.x2) && onSeg1D(A.y1, A.y2, B.y2, B.y2)) return true;
    if (o3 == 0 && onSeg1D(B.x1, B.x2, A.x1, A.x1) && onSeg1D(B.y1, B.y2, A.y1, A.y1)) return true;
    if (o4 == 0 && onSeg1D(B.x1, B.x2, A.x2, A.x2) && onSeg1D(B.y1, B.y2, A.y2, A.y2)) return true;
    return false;
}

struct Event {
    ll x;
    int tp, id;
    bool operator<(Event const& e) const {
        if (x != e.x) return x < e.x;
        return tp > e.tp;
    }
};

void solve() {
    int n;
    cin >> n;
    segs.resize(n);
    vector<Event> ev;
    ev.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        segs[i] = {x1, y1, x2, y2, i};
        ev.push_back({x1, +1, i});
        ev.push_back({x2, -1, i});
    }
    sort(all(ev));
    set<int, Cmp> active;
    vector<set<int, Cmp>::iterator> where(n);
    for (auto &e : ev) {
        currentX = e.x;
        int id = e.id;
        if (e.tp == +1) {
            auto it = active.lower_bound(id);
            if (it != active.end() && intersect(*it, id)) {
                cout << "YES\n";
                return;
            }
            if (it != active.begin()) {
                auto jt = prev(it);
                if (intersect(*jt, id)) {
                    cout << "YES\n";
                    return;
                }
            }
            where[id] = active.insert(it, id);
        } else {
            auto it = where[id];
            auto nxt = next(it);
            auto prv = (it == active.begin() ? active.end() : prev(it));
            if (nxt != active.end() && prv != active.end() && intersect(*nxt, *prv)) {
                cout << "YES\n";
                return;
            }
            active.erase(it);
        }
    }
    cout << "NO\n";
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