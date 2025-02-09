#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int M, N, D, ns, nc, nj;
char temp['z' + 1], o;
int mas[20][20];
int go[20][20][20][20];
bool used[20][20][101];
pair<int, int> S, G;
int dy[] = {0, 1, 0, -1}, dx[] = {-1, 0, 1, 0};

bool isover(int y, int x) {
    return y < 0 || y >= M || x < 0 || x >= N;
}

bool isred(int y, int x, int time, bool istate) {
    return ~mas[y][x] && !istate ^ time / mas[y][x] & 1;
}

int Dijkstra() {
    fill_n(**used, 20 * 20 * 101, false);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> que;
    que.push(make_pair(0, S)); // time, coordinates

    while (!que.empty()) {
        pair<int, pair<int, int>> p = que.top();
        que.pop();
        if (p.second == G) return p.first; // reached goal
        if (used[p.second.first][p.second.second][p.first]) {
            continue;
        }
        used[p.second.first][p.second.second][p.first] = 1;
        for (int i = 0; i < 4; i++) {
            int ny = p.second.first + dy[i], nx = p.second.second + dx[i];
            if (isover(ny, nx)) continue; // went outside
            if (go[p.second.first][p.second.second][ny][nx] == -1) continue; // under construction
            int nexttime = p.first + D + go[p.second.first][p.second.second][ny][nx];
            if (isred(ny, nx, nexttime, i & 1)) continue; // cannot enter intersection
            que.push(make_pair(nexttime, make_pair(ny, nx)));
        }
    }
    return -1;
}

int main() {
    for (int i = 'a', j = 1; i <= 'z'; i++, j++) { // map-like
        temp[i] = j;
    }

    while (cin >> M >> N, M) {
        fill_n(*mas, 400, -1);
        fill_n(***go, 20 * 20 * 20 * 20, 0);

        cin >> D;
        cin >> ns;
        for (int i = 0; i < ns; i++) {
            char h;
            int v, k;
            cin >> h >> o >> v >> k;
            mas[temp[h] - 1][v - 1] = k;
        }

        cin >> nc;
        for (int i = 0; i < nc; i++) {
            char h1, h2;
            int v1, v2;
            cin >> h1 >> o >> v1 >> h2 >> o >> v2; // input is troublesome
            go[temp[h1] - 1][v1 - 1][temp[h2] - 1][v2 - 1] = -1;
            go[temp[h2] - 1][v2 - 1][temp[h1] - 1][v1 - 1] = -1;
        }

        cin >> nj;
        for (int i = 0; i < nj; i++) {
            char h1, h2;
            int v1, v2, d;
            cin >> h1 >> o >> v1 >> h2 >> o >> v2 >> d;
            go[temp[h1] - 1][v1 - 1][temp[h2] - 1][v2 - 1] = d;
            go[temp[h2] - 1][v2 - 1][temp[h1] - 1][v1 - 1] = d;
        }

        char h1, h2;
        int v1, v2;
        cin >> h1 >> o >> v1 >> h2 >> o >> v2;
        S = make_pair(temp[h1] - 1, v1 - 1);
        G = make_pair(temp[h2] - 1, v2 - 1);

        cout << Dijkstra() << endl;
    }
}