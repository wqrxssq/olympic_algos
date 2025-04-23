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
    ll x, y;
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
ll dist2(r a) {
    return a.x * a.x + a.y * a.y;
}

ll brute(vector<r>& pts, pair<r,r> &best) {
    ll d = LLONG_MAX;
    for (int i = 0; i < pts.size(); i++) {
        for (int j = i + 1; j < pts.size(); j++) {
            ll d2 = dist2(pts[i] - pts[j]);
            if (d2 < d) {
                d = d2;
                best = {pts[i], pts[j]};
            }
        }
    }
    return d;
}

ll divide_and_conquer(vector<r>& px, vector<r>& py, int L, int R,
                     pair<r,r> &best) {
    int n = R - L;
    if (n <= 3) {
        vector<r> small(px.begin() + L, px.begin() + R);
        return brute(small, best);
    }

    int mid = (L + R) / 2;
    ll x_mid = px[mid].x;

    vector<r> ly, ry;
    ly.reserve(mid-L);
    ry.reserve(R-mid);
    for (auto &p : py) {
        if (p.x < x_mid || (p.x == x_mid && ly.size() < (size_t)(mid-L)))
            ly.push_back(p);
        else
            ry.push_back(p);
    }

    pair<r,r> bestL, bestR;
    ll dL = divide_and_conquer(px, ly, L, mid, bestL);
    ll dR = divide_and_conquer(px, ry, mid, R, bestR);

    ll d = dL < dR ? dL : dR;
    best = (dL < dR ? bestL : bestR);

    vector<r> sy;
    sy.reserve(n);
    ll delta = (ll)ceil(sqrt((long double)d));
    for (auto &p : py) {
        if (llabs(p.x - x_mid) < delta)
            sy.push_back(p);
    }

    int m = sy.size();
    for (int i = 0; i < m; i++) {
        for (int j = i+1; j < m && j <= i + 7; j++) {
            ll d2 = dist2(sy[i] - sy[j]);
            if (d2 < d) {
                d = d2;
                best = {sy[i], sy[j]};
            }
        }
    }
    return d;
}

pair<r,r> closest_pair(vector<r>& pts) {
    int n = pts.size();
    vector<r> Px = pts, Py = pts;

    sort(Px.begin(), Px.end(), [](auto &a, auto &b){
        return a.x < b.x;
    });
    sort(Py.begin(), Py.end(), [](auto &a, auto &b){
        return a.y < b.y;
    });

    pair<r,r> best;
    divide_and_conquer(Px, Py, 0, n, best);
    return best;
}

void solve() {
    int n;
    cin >> n;
    vector<r> pts(n);
    for (auto& p : pts) {
        cin >> p;
    }
    pair<r, r> ans = closest_pair(pts);
    cout << ans.ff << '\n' << ans.ss << '\n';
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
