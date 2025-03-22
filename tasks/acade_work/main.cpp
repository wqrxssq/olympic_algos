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

const double eps = 0.0001;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)                       \
    for (auto el : _x) cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x) \
    for (auto &el : _x) cin >> el;
#define fast_input ios_base::sync_with_stdio(0)
#define setpr cout << setprecision(6) << fixed

bool is_operation(int c) {
	return (c == '+' || c == '-');
}
int prior(int op) {
    if (op < 0)
        return 2;
    return (op == '+' || op == '-' ? 1 : -1);
}

void do_operation(vll& st, int op) {
	if (op < 0) { // unary
		ll a = st.back();
        st.pop_back();
		switch (-op) {
			case '+': st.push_back (a); break;
			case '-': st.push_back (-a); break;
		}
	} else {
		ll b = st.back(); st.pop_back();
		ll a = st.back(); st.pop_back();
		switch (op) {
			case '+':  st.push_back (a + b); break;
			case '-':  st.push_back (a - b); break;
		}
	}
}



void solve() {
    string s;
    char trash;
    while (cin >> trash) {
        s.pb(trash);
    }

    vll st;
    vi op;
    bool unary = 1;

    for (int i = 0; i < sz(s); i++) {
        int c = s[i];
        if (c == ' ') {
            continue;
        }
        if (c == '(') {
            op.push_back(c);
            unary = 1;
        } else if (c == ')') {
            while (op.back() != '(') {
                do_operation(st, op.back());
                op.pop_back();
            }
            op.pop_back();
            unary = 0;
        } else if (is_operation(c)) {
			if (unary) {
                c *= -1;
            }
			while (!op.empty() && ((c >= 0 && prior(op.back()) >= prior(c)) || (c < 0 && prior(op.back()) > prior(c)))) {
				do_operation(st, op.back());
                op.pop_back();
            }
			op.push_back(c);
			unary = 1;
        } else {
            int num = 0;
            while (i < sz(s) && isdigit(s[i])) {
                num *= 10;
                num += s[i] - '0';
                i++;
            }
            st.pb(num);
            i--;
            unary = 0;
        }
    }

    while (!op.empty()) {
        do_operation(st, op.back());
        op.pop_back();
    }
    cout << st.back() << '\n';
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
