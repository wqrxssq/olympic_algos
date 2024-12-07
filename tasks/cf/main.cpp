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

struct Node {
    int prior;
    int size = 1;
    int value;
    Node *l, *r;
    Node(int value_) : prior(rand()), size(1), value(value_), l(0), r(0) {
    }
};

int size(Node* v) {
    return (v ? v->size : 0);
}
void upd(Node* v) {
    v->size = 1 + size(v->l) + size(v->r);
}

Node* merge(Node* L, Node* R) {
    if (!L) {
        return R;
    }
    if (!R) {
        return L;
    }
    if (L->prior > R->prior) {
        L->r = merge(L->r, R);
        upd(L);
        return L;
    } else {
        R->l = merge(L, R->l);
        upd(R);
        return R;
    }
}

// вырежи первые k элементов
pair<Node*, Node*> split(Node* v, int k) {
    if (!v) {
        return {0, 0};
    }
    if (size(v->l) >= k) {
        auto [L, R] = split(v->l, k);
        v->l = R;
        upd(v);
        return {L, v};
    } else {
        auto [L, R] = split(v->r, k - size(v->l) - 1);
        v->r = L;
        upd(v);
        return {v, R};
    }
}

Node* push(Node* v, int value_) {
    Node* u = new Node(value_);
    return merge(v, u);
}

Node* push_middle(Node* v, int value_) {
    int n = size(v);
    Node* u = new Node(value_);
    auto [L, R] = split(v, (n + 1) / 2);
    return merge(L, merge(u, R));
}

pair<int, Node*> get_first(Node* v) {
    auto [L, R] = split(v, 1);
    return {L->value, R};
}

const int MAXN = 5e5;

void solve() {
    int n;
    cin >> n;
    Node* root = 0;
    while (n--) {
        char c;
        cin >> c;
        if (c == '+') {
            int id;
            cin >> id;
            root = push(root, id);
        } else if (c == '*') {
            int id;
            cin >> id;
            root = push_middle(root, id);
        } else {
            auto [id, temp] = get_first(root);
            root = temp;
            cout << id << '\n';
        }
    }
}

int main() {
    fast_input;
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}
