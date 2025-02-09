#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 16;
char grid[SIZE][SIZE];

bool check(int i, int j) {
    for (int k = 0; k < SIZE; k++) {
        if (grid[i][k] != '-' && grid[i][k] == grid[i][j] && k != j) {
            return false;
        }
        if (grid[k][j] != '-' && grid[k][j] == grid[i][j] && k != i) {
            return false;
        }
    }
    int block_i = i / 4;
    int block_j = j / 4;
    for (int k = block_i * 4; k < block_i * 4 + 4; k++) {
        for (int l = block_j * 4; l < block_j * 4 + 4; l++) {
            if (i == k && j == l) {
                continue;
            }
            if (grid[k][l] != '-' && grid[k][l] == grid[i][j]) {
                return false;
            }
        }
    }
    return true;
}

vector<int> get_forbidden(int i, int j) {
    vector<int> forbidden(SIZE, false);
    for (int k = 0; k < SIZE; k++) {
        if (grid[i][k] != '-') {
            forbidden[grid[i][k] - 'A'] = true;
        }
        if (grid[k][j] != '-') {
            forbidden[grid[k][j] - 'A'] = true;
        }
    }
    int block_i = i / 4;
    int block_j = j / 4;
    for (int k = block_i * 4; k < block_i * 4 + 4; k++) {
        for (int l = block_j * 4; l < block_j * 4 + 4; l++) {
            if (i == k && j == l) {
                continue;
            }
            if (grid[k][l] != '-') {
                forbidden[grid[k][l] - 'A'] = true;
            }
        }
    }
    return forbidden;
}

bool dfs(int i, int j) {
    if (i == SIZE) {
        return true;
    }
    if (check(i, j)) {
        int next_i = i;
        int next_j = j + 1;
        for (; next_i < SIZE; next_i++) {
            for (; next_j < SIZE; next_j++) {
                if (grid[next_i][next_j] == '-') {
                    break;
                }
            }
            if (next_j < SIZE) {
                break;
            }
            next_j = 0;
        }
        vector<int> forbidden = get_forbidden(i, j);
        for (int c = 0; c < SIZE; c++) {
            if (forbidden[c]) {
                continue;
            }
            grid[i][j] = 'A' + c;
            if (dfs(next_i, next_j)) {
                return true;
            }
            grid[i][j] = '-';
        }
    }
    return false;
}

void solve() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == '-') {
                if (dfs(i, j)) {
                    cout << "NO SOLUTION\n";
                    return;
                } else {
                    break;
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    string s;
    int i = 0;
    while (cin >> s) {
        for (int j = 0; j < 16; j++) {
            grid[i][j] = s[j];
        }
        i++;
        if (i == 16) {
            solve();
            i = 0;
        }
    }
}