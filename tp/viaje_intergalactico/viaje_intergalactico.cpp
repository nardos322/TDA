#include <bits/stdc++.h>
using namespace std;

/*
    Problema: Camino mínimo con esperas en nodos.
    - Grafo no dirigido con pesos (tiempos de viaje).
    - En cada nodo u hay tiempos enteros bloqueados (tiempo_viajeros[u])
        en los que NO se puede salir; si llegás en un tiempo bloqueado,
        esperás hasta el próximo tiempo libre.

    Estrategia: Dijkstra con min-heap.
    - Al extraer un nodo u del heap, ajustamos una sola vez el tiempo de salida
        saltando tiempos bloqueados consecutivos, y reutilizamos ese tiempo para
        relajar todas las aristas salientes.

    Notación:
        n: cantidad de nodos
        m: cantidad de aristas
        K_u: cantidad de tiempos bloqueados listados para u
        k_u: cantidad de tiempos consecutivos bloqueados a partir de tiempo[u]
        ΣK: suma de K_u sobre todos los nodos

    Complejidad temporal (promedio con unordered_set):
        - Construcción entrada: O(n + m) para el grafo y O(ΣK) inserciones para bloqueos
        - Dijkstra base: O((n + m) log n)
        - Ajuste de salida por bloqueos: Σ_u k_u (cada u ajusta una vez)
        - Total: O((n + m) log n + Σ_u k_u + ΣK)
            (en práctica, ΣK ya se paga al leer; el término dominante suele ser (n+m) log n)

    Peor caso teórico del contenedor:
        - Si unordered_set degrada, find puede ser O(K_u) y el ajuste en u costaría O(k_u · K_u),
            pero con buen hashing esto no ocurre en la práctica.

    Complejidad espacial:
        - Grafo: O(n + m), distancias y heap: O(n), bloqueos: O(ΣK)
        - Total: O(n + m + ΣK)
*/

// Inicializa distancias: O(n) tiempo, O(1) espacio extra.
void initialize_single_source(vector<long long> &tiempo, const int source)
{
    fill(tiempo.begin(), tiempo.end(), LLONG_MAX);
    tiempo[source] = 0;
}

// Relaja (u -> v) usando un tiempo de salida ya ajustado para u.
// Complejidad: O(1) por llamada; no consulta estructuras adicionales.
void relax(const long long tiempo_salida, const int v, const long long w, vector<long long> &tiempo)
{
    if (tiempo[v] > tiempo_salida + w)
    {
        tiempo[v] = tiempo_salida + w;
    }
}

// Dijkstra con esperas en nodos.
// Complejidad temporal (promedio): O((n + m) log n + Σ_u k_u)
//   - Heap: cada pop/push cuesta O(log n)
//   - Cada arista se examina al menos una vez
//   - Ajuste de salida por u: Σ k_u (se hace una sola vez por nodo extraído)
// Complejidad espacial: O(n + m)
void dijkstra(const int source, const int n, const vector<vector<pair<int, long long>>> &G, vector<long long> &tiempo,
              const vector<unordered_set<long long>> &tiempo_viajeros)
{

    initialize_single_source(tiempo, source);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto [tiempo_llegada, u] = pq.top();
        pq.pop();
        if (tiempo_llegada > tiempo[u])
            continue;
        if (u == n)
            break; // Early-exit válido: la distancia a n ya es mínima

        // Ajuste de tiempo de salida para u: avanza sobre bloqueos consecutivos.
        // Promedio: O(k_u) con unordered_set.
        long long tiempo_salida = tiempo[u];
        const auto &viajeros_en_planeta = tiempo_viajeros[u];
        while (viajeros_en_planeta.find(tiempo_salida) != viajeros_en_planeta.end())
        {
            tiempo_salida++;
        }

        for (const auto &[v, w] : G[u]) // O(degree(u))
        {
            long long old_tiempo = tiempo[v];
            relax(tiempo_salida, v, w, tiempo); // O(1)
            if (tiempo[v] < old_tiempo)
            {
                pq.push({tiempo[v], v});
            }
        }
    }
}

long long viaje_intergalactico(const int n, const vector<vector<pair<int, long long>>> &G, vector<long long> &tiempo,
                               const vector<unordered_set<long long>> &tiempo_viajeros)
{

    dijkstra(1, n, G, tiempo, tiempo_viajeros);

    return (tiempo[n] == LLONG_MAX) ? -1 : tiempo[n];
}

void solve(istream &in, ostream &out)
{
    int n, m;
    in >> n >> m;
    vector<vector<pair<int, long long>>> G(n + 1);
    vector<unordered_set<long long>> tiempo_viajeros(n + 1);
    vector<long long> tiempo(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        long long w;
        in >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    for (int i = 1; i <= n; ++i)
    {
        int k;
        in >> k;

        auto &set_tiempos = tiempo_viajeros[i];
        set_tiempos.reserve(k);

        for (int j = 0; j < k; ++j)
        {
            long long t;
            in >> t;
            set_tiempos.insert(t);
        }
    }

    out << viaje_intergalactico(n, G, tiempo, tiempo_viajeros) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve(cin, cout);
    return 0;
}