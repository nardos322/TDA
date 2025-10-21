#include <bits/stdc++.h>

using namespace std;

// version basica de DFS para mostrar el recorrido
void dfs_visit(const int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    cout << "Visitando nodo: " << u << endl;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs_visit(v, adj, visited);
        }
    }
}

void dfs(const int n, const vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    cout << "Recorrido DFS:" << endl;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "Iniciando en el componente del nodo: " << i << endl;
            dfs_visit(i, adj, visited);
            cout << "Fin del recorrido desde el nodo: " << i << endl;
        }
    }
}


/**
 * Encuentra todos los puentes en un grafo no dirigido usando el algoritmo de Tarjan.
 * Se basa en un único DFS para calcular los tiempos de descubrimiento (disc)
 * y los valores "low-link" (low).
 */
vector <pair<int,int>> find_puentes(int n, const vector<vector<int>> &adj) {
    vector <pair<int,int>> puentes;

    // disc[i]: Tiempo de descubrimiento del nodo i
    // low[i]: El 'disc' más bajo (ancestro más antiguo) alcanzable desde 'i'
    //         (incluyendo su subárbol) usando a lo sumo UN back-edge.
    // parent[i]: El padre del nodo i en el árbol DFS.
    vector<int> disc(n, -1), low(n, -1), parent(n, -1);

    int time = 0;  // Reloj global para los tiempos de descubrimiento

    function<void(int)> dfs = [&](int u) {

        // --- INICIALIZACIÓN ---
        // Al visitar 'u', su 'disc' y 'low' iniciales son su propio tiempo.
        // Por ahora, el ancestro más antiguo que 'u' puede alcanzar es él mismo.
        disc[u] = low[u] = time++;

        // Explora todos los vecinos v de 'u'
        for (int v : adj[u]) {
            if (disc[v] == -1) { // Caso 1: Vecino 'v' no visitado (Arista de Árbol)
                parent[v] = u;
                dfs(v); // Llamada recursiva (explora el subárbol de v)

                // ---PROPAGACIÓN (Post-orden) ---
                // Esto se ejecuta DESPUÉS de que la llamada dfs(v) haya terminado.
                // 'low[v]' ya contiene el ancestro más antiguo que TODO el subárbol de 'v'
                // pudo alcanzar.
                // 'u' ahora "hereda" ese atajo: si 'v' pudo llegar más alto, 'u' también.
                low[u] = min(low[u], low[v]);   

                
                // --- CONDICIÓN DE PUENTE ---
                // Si el 'low' más bajo de 'v' (o su subárbol) es ESTRICTAMENTE MAYOR
                // que el tiempo de descubrimiento de 'u'...
                // ...significa que 'v' no pudo encontrar NINGÚN atajo
                // que lo conectara con 'u' o con un ancestro de 'u'.
                // Por lo tanto, (u, v) es la única conexión. Es un puente.
                if (low[v] > disc[u]) {
                    puentes.push_back({u, v});
                }
            } else if (v != parent[u]) {  // Caso 2: Vecino 'v' SÍ visitado y v no es el padre (Arista de Retroceso / Back-edge)

                // --- ACTUALIZACIÓN (Back-edge) ---
                // Encontramos un atajo directo a un ancestro 'v' (ya visitado).
                // Actualizamos nuestro 'low[u]' para ver si este ancestro 'v'
                // es más antiguo (tiene un 'disc' más bajo) que el 'low' que teníamos.
                low[u] = min(low[u], disc[v]);
            }
        }
    };


    // Bucle principal: Inicia el DFS en todos los nodos no visitados
    // (Esto maneja grafos no conexos)
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            dfs(i);
        }
    }

    return puentes;
}

int main() {
    int n, m;
    n = 3;
    m = 3;
    vector<vector<int>> adj(n);
    adj[0].push_back(1); adj[1].push_back(0);
    adj[0].push_back(2); adj[2].push_back(0);
  
    vector<pair<int,int>> puentes = find_puentes(n, adj);
    cout << "Puentes encontrados:" << endl;
    for (const auto& puente : puentes) {
        cout << puente.first << " - " << puente.second << endl;
    }

    // Salida esperada: 0 - 1 y 0 - 2
    return 0;
}