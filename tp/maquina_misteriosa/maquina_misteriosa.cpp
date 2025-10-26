#include<bits/stdc++.h>
using namespace std;


pair<int, int> get_vecinos(int n) {
    return {n - 1, n * 2};
}

int bfs(int n, int m, vector<bool>& visited, vector<int>& distancia) {
    if(n == m) return 0;
    queue<int> q;
    q.push(n);
    visited[n] = true;
    distancia[n] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (current == m) {
            return distancia[current];
        }
        pair<int, int> vecinos = get_vecinos(current);
        for (int vecino : {vecinos.first, vecinos.second}) {
            if (vecino >= 0 && vecino < visited.size() && !visited[vecino]) {
                visited[vecino] = true;
                distancia[vecino] = distancia[current] + 1;
                q.push(vecino);
            }
        }
    }

    return -1; // Si no se encuentra m
}

int maquina_misteriosa(int n, int m) {
    vector<bool> visited(10001, false);
    vector<int> distancias(10001, -1);
    return bfs(n, m, visited, distancias);
}

void solve(istream& in, ostream& out) {
    int n, m;
    in >> n >> m;
    out << maquina_misteriosa(n, m) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve(cin, cout);

    return 0;
}