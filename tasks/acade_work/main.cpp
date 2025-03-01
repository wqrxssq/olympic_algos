// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <set>
 
using namespace std;

// #define int long long
// #define int128 __int128
// #define ld long double
// #define float128 __float128
// #define all(x) x.begin(), x.end()
// #define pb push_back
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1000, K = 30, PW = 179, PW1 = 37, MOD = 1e9 + 1000 - 7, MOD1 = 1e9 + 7, INF = 2e9;
std::mt19937 engine(chrono::steady_clock::now().time_since_epoch().count());

int n;
vector<vector<int>> g;

int randint(int l, int r) {
    return engine() % (r - l + 1) + l;
}

using Edges = std::vector<std::pair<int, int>>;

void printEdges(Edges edges) {
    g.assign(n + 1, {});
    std::shuffle(edges.begin(), edges.end(), engine);
    std::vector<int> labels(edges.size() + 1);
    std::iota(labels.begin(), labels.end(), 1);
    std::shuffle(labels.begin(), labels.end(), engine);
    for (const auto& edge : edges) {
        int u = labels[edge.first];
        int v = labels[edge.second];
        if (engine() % 2) {
            std::swap(u, v);
        }
        // std::cout << u << " " << v << "\n";
        g[u].push_back(v);
        g[v].push_back(u);
    }
}

void prim(int n) {
    Edges edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, randint(0, i - 1));
    }
    printEdges(edges);
}

void primHalf(int n) {
    Edges edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, randint(i / 2, i - 1));
    }
    printEdges(edges);
}

void primNOverFour(int n) {
    Edges edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, randint(std::max(0, i - n / 4), i - 1));
    }
    printEdges(edges);
}

void primWnext(int n, int w) {
    auto wnext = [n, w] (int bound) {
        int x = randint(0, bound - 1);
        for (int i = 0; i < +w; ++i) {
            x = std::max(x, randint(0, bound - 1));
        }
        for (int i = 0; i < -w; ++i) {
            x = std::min(x, randint(0, bound - 1));
        }
        return x;
    };

    Edges edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i, wnext(i));
    }
    printEdges(edges);
}

void doKruskal(int n, Edges allEdges) {
    std::vector<int> dsu(n);
    std::iota(dsu.begin(), dsu.end(), 0);

    std::function<int(int)> findRoot = [&dsu, &findRoot] (int v) {
        if (v == dsu[v]) {
            return v;
        }
        return dsu[v] = findRoot(dsu[v]);
    };

    auto unite = [&dsu, &findRoot] (int u, int v) {
        u = findRoot(u);
        v = findRoot(v);
        if (u == v) {
            return false;
        }
        dsu[u] = v;
        return true;
    };

    std::shuffle(allEdges.begin(), allEdges.end(), engine);

    Edges result;
    for (const auto& edge : allEdges) {
        if (unite(edge.first, edge.second)) {
            result.push_back(edge);
        }
    }

    printEdges(result);

}

void kruskal(int n) {
    Edges allEdges;
    for (int v = 0; v < n; ++v) {
        for (int u = 0; u < v; ++u) {
            allEdges.emplace_back(u, v);
        }
    }

    doKruskal(n, allEdges);
}

void kruskalBipartiteEqualParts(int n) {
    Edges allEdges;
    for (int v = 0; v < n; ++v) {
        for (int u = 0; u < v; ++u) {
            if (u % 2 != v % 2) {
                allEdges.emplace_back(u, v);
            }
        }
    }

    doKruskal(n, allEdges);
}

void kruskalBipartiteDifferentParts(int n) {
    int rightPartSize = randint(std::sqrt(n), std::sqrt(n) * 2);

    Edges allEdges;
    for (int v = 0; v < n; ++v) {
        for (int u = 0; u < v; ++u) {
            if ((u < rightPartSize) != (v < rightPartSize)) {
                allEdges.emplace_back(u, v);
            }
        }
    }

    doKruskal(n, allEdges);
}

void prufer(int n, int numZeroes) {
    std::vector<int> code;
    for (int i = 0; i < n - 2; ++i) {
        code.push_back(randint(0, n - 1));
    }

    std::set<int> zeroes;
    for (int iter = 0; iter < numZeroes; ++iter) {
        while (true) {
            int x = randint(0, n - 3);
            if (zeroes.insert(x).second) {
                code[x] = 0;
                break;
            }
        }
    }

    std::vector<int> degree(code.size() + 2, 1);
    for (int v: code) {
        ++degree[v];
    }

    std::set<int> leaves;
    for (size_t v = 0; v != degree.size(); ++v) {
        if (degree[v] == 1) {
            leaves.insert(v);
        }
    }

    Edges result;

    for (int v: code) {
        assert(!leaves.empty());
        int u = *leaves.begin();
        leaves.erase(leaves.begin());
        if (--degree[v] == 1) {
            leaves.insert(v);
        }

        result.emplace_back(v, u);
    }

    assert(leaves.size() == 2u);
    result.emplace_back(*leaves.begin(), *leaves.rbegin());

    printEdges(result);
}

void generate(int n, int index) {
    switch (index) {
        case 1:  prim(n); break;
        case 2:  primHalf(n); break;
        case 3:  primNOverFour(n); break;
        case 4:  primWnext(n, 2); break;
        case 5:  primWnext(n, -2); break;
        case 6:  kruskal(n); break;
        case 7:  kruskalBipartiteEqualParts(n); break;
        case 8:  kruskalBipartiteDifferentParts(n); break;
        case 9:  prufer(n, 0); break;
        case 10: prufer(n, std::min(n/10, 20)); break;
        default: assert(false);
    }
}
int h[MAXN + 1] = {0}, parent[MAXN + 1] = {0};

void dfs(int v, int p, vector<vector<int>> &g) {
    h[v] = (p != -1 ? h[p] + 1 : 0);
    parent[v] = p;
    for (int u : g[v]) {
        if (u != p) {
            dfs(u, v, g);
        }
    }
}

double get_average_height(int root, int n, vector<vector<int>>& g) {
    double res = 0;
    int cnt = 0;
    for (int v = 1; v <= n; v++) {
        cnt += (g[v].size() == 1 && v != root);
        res += (g[v].size() == 1 && v != root ? h[v] : 0);
    }
    return res / cnt;
}

vector<int> get_diam(vector<vector<int>> &g) {
    h[1] = 0;
    dfs(1, 1, g);
    int best = 1;
    for (int i = 1; i <= n; ++i) {
        if (h[best] < h[i])
            best = i;
    }
    h[best] = 0;
    int start = best;
    dfs(best, best, g);
    vector<int> path;
    for (int i = 1; i <= n; ++i) {
        if (h[best] < h[i])
            best = i;
    }
    while (best != start) {
        path.push_back(best);
        best = parent[best];
    }
    path.push_back(start);
    return path;
}

long double solve() {
    vector<vector<int>> g1 = g;
    vector<int> path = get_diam(g1);
    int root = path[path.size() / 2];
    dfs(root, -1, g1);
    double average_height = get_average_height(root, n, g1);
    return average_height;
}

signed main() {
#ifdef __APPLE__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(6) << fixed;
    int T = 1;
    vector<int> sizes = {10, 25, 50, 100, 200, 300, 400, 500, 750, 1000};
    for (auto it: sizes) {
        n = it;
        cout << "SIZE: " << n << endl << endl;
        for (int i = 0; i < 10; ++i) {
            long double mid = 0;
            for (int j = 0; j < 64; ++j) {
                generate(n, i + 1);
                mid += solve();
            }
            cout << (i + 1) << ": "  << mid / 64 << endl;
        }
        cout << endl << endl;
    }
}
