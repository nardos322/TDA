#include <bits/stdc++.h>
using namespace std;


void initialize_single_source(vector<long long>& tiempo, int source) {
    fill(tiempo.begin(), tiempo.end(), LLONG_MAX);
    tiempo[source] = 0;
}

void relax(int u, int v, long long w, vector<long long>& tiempo, vector<unordered_set<long long>>& tiempo_viajeros) {
    long long tiempo_salida = tiempo[u];
    const auto& viajeros_en_planeta = tiempo_viajeros[u];
    while (viajeros_en_planeta.find(tiempo_salida) != viajeros_en_planeta.end()) {
        tiempo_salida++;
    }

    if (tiempo[u] != LLONG_MAX && tiempo[v] > tiempo_salida + w) {
        tiempo[v] = tiempo_salida + w;
    }
}

void dijkstra(int source, int n, const vector<vector<pair<int, long long>>>& G, vector<long long>& tiempo, vector<unordered_set<long long>>& tiempo_viajeros) {
    initialize_single_source(tiempo, source);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [tiempo_llegada, u] = pq.top();
        pq.pop();
        if (tiempo_llegada > tiempo[u]) continue;
        if (u == n) break;  // llegamos al destino, dijkstra puede terminar esta garantizado que es el camino mínimo
        for (const auto& [v, w] : G[u]) {
            long long old_tiempo = tiempo[v];
            relax(u, v, w, tiempo, tiempo_viajeros);
            if (tiempo[v] < old_tiempo) {
                pq.push({tiempo[v], v});
            }
        }
    }
    
}

int viaje_intergalactico(int n, vector<vector<pair<int, long long>>>& G, vector<long long>& tiempo, vector<unordered_set<long long>>& tiempo_viajeros) {

    dijkstra(1, n, G, tiempo, tiempo_viajeros);

    return (tiempo[n] == LLONG_MAX) ? -1 : tiempo[n];

}


void solve(istream& in, ostream& out) {
    int n, m;
    in >> n >> m;
    vector<vector<pair<int, long long>>> G(n + 1);
    vector<unordered_set<long long>> tiempo_viajeros(n + 1);
    vector<long long> tiempo(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        in >> u >> v >> w;
        G[u].push_back({v, w});
    }

    for (int i = 1; i <= n; ++i) {
        int k;
        in >> k;
        for (int j = 0; j < k; ++j) {
            long long t;
            in >> t;
            tiempo_viajeros[i].insert(t);
        }
    }

    out << viaje_intergalactico(n, G, tiempo, tiempo_viajeros) << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve(cin, cout);
    return 0;

}