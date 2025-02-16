#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <string>
using namespace std;

using ll = long long;
using ull = unsigned long long;

const int MAXN = 100000;
const int MOD = 1000000007;
const int power = 31;

int n;
string s;

ull p64[MAXN];
ll pMod[MAXN];

struct Node {
    ull f64, r64;
    ll fMod, rMod;
};

Node t[MAXN << 2];

void init() {
    p64[0] = 1;
    pMod[0] = 1;
    for (int i = 1; i < n; i++) {
        p64[i] = p64[i - 1] * power;
        pMod[i] = (pMod[i - 1] * power) % MOD;
    }
}

void build(int tl, int tr, int v) {
    if (tl == tr) {
        int val = s[tl] - 'a' + 1;
        t[v].f64 = val;
        t[v].r64 = val;
        t[v].fMod = val;
        t[v].rMod = val;
    } else {
        int tm = (tl + tr) >> 1;
        build(tl, tm, v << 1);
        build(tm + 1, tr, v << 1 | 1);
        int rightLen = tr - tm;
        int leftLen = tm - tl + 1;
        t[v].f64 = t[v << 1].f64 * p64[rightLen] + t[v << 1 | 1].f64;
        t[v].fMod = (t[v << 1].fMod * pMod[rightLen] + t[v << 1 | 1].fMod) % MOD;
        t[v].r64 = t[v << 1].r64 + t[v << 1 | 1].r64 * p64[leftLen];
        t[v].rMod = (t[v << 1].rMod + t[v << 1 | 1].rMod * pMod[leftLen]) % MOD;
    }
}

void change(int tl, int tr, int v, int pos, int val) {
    if (tl == tr) {
        t[v].f64 = val;
        t[v].r64 = val;
        t[v].fMod = val;
        t[v].rMod = val;
    } else {
        int tm = (tl + tr) >> 1;
        if (pos <= tm)
            change(tl, tm, v << 1, pos, val);
        else
            change(tm + 1, tr, v << 1 | 1, pos, val);
        int rightLen = tr - tm;
        int leftLen = tm - tl + 1;
        t[v].f64 = t[v << 1].f64 * p64[rightLen] + t[v << 1 | 1].f64;
        t[v].fMod = (t[v << 1].fMod * pMod[rightLen] + t[v << 1 | 1].fMod) % MOD;
        t[v].r64 = t[v << 1].r64 + t[v << 1 | 1].r64 * p64[leftLen];
        t[v].rMod = (t[v << 1].rMod + t[v << 1 | 1].rMod * pMod[leftLen]) % MOD;
    }
}

Node combineNodes(const Node &left, const Node &right, int leftLen, int rightLen) {
    Node res;
    res.f64 = left.f64 * p64[rightLen] + right.f64;
    res.fMod = (left.fMod * pMod[rightLen] + right.fMod) % MOD;
    res.r64 = left.r64 + right.r64 * p64[leftLen];
    res.rMod = (left.rMod + right.rMod * pMod[leftLen]) % MOD;
    return res;
}

Node get_hashes(int tl, int tr, int v, int l, int r) {
    if (tl == l && tr == r) {
        return t[v];
    }
    int tm = (tl + tr) >> 1;
    if (r <= tm) {
        return get_hashes(tl, tm, v << 1, l, r);
    } else if (l > tm) {
        return get_hashes(tm + 1, tr, v << 1 | 1, l, r);
    } else {
        Node leftNode = get_hashes(tl, tm, v << 1, l, tm);
        Node rightNode = get_hashes(tm + 1, tr, v << 1 | 1, tm + 1, r);
        int leftLen = tm - l + 1;
        int rightLen = r - tm;
        return combineNodes(leftNode, rightNode, leftLen, rightLen);
    }
}

void solve() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> s;
    n = s.size();
    init();
    build(0, n - 1, 1);
    
    int q;
    cin >> q;
    while(q--) {
        string op;
        cin >> op;
        if(op == "palindrome?") {
            int l, r;
            cin >> l >> r;
            l--; r--;
            Node res = get_hashes(0, n - 1, 1, l, r);
            if(res.f64 == res.r64 && res.fMod == res.rMod) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            int pos;
            char c;
            cin >> pos >> c;
            pos--;
            int val = c - 'a' + 1;
            change(0, n - 1, 1, pos, val);
        }
    }
}

int main() {
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}
