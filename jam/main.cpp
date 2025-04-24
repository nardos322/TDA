#include <iostream>
#include <vector>
#include "dfs.cpp"
using namespace std;


void dfs_basic(const vector<vector<int>>& grafo, vector<bool>& visitado, int vertice) {
    visitado[vertice] = true;
    cout << "visitando vertice: " << vertice << endl;
    for (int vecino = 0; vecino < grafo.size(); vecino++) {
        if (grafo[vertice][vecino] == 1 && !visitado[vecino]) {
            dfs_basic(grafo, visitado, vecino);
        }
    }
}

void backtrack(const vector<int>& nums, vector<int>& perm, vector<bool>& usados, int i, int& count, vector<vector<int>>& res) {
    if (i == perm.size()) {
        count++;
        res.push_back(perm);
        return;
    }

    for (int k = 0; k < nums.size(); k++) {
        if (!usados[k]) {
            perm[i] = nums[k];
            usados[k] = true;
            backtrack(nums, perm, usados, i + 1, count, res);
            usados[k] = false;
        }
    }
}

vector<vector<int>> permutaciones(const vector<int>& conjunto) {
    vector<int>perm(conjunto.size());
    vector<bool>usados(conjunto.size(), false);
    vector<vector<int>> res;
    int count = 0;
    backtrack(conjunto, perm, usados, 0, count, res);
    return res;

}

// struct Vertice {
//     bool visitado;
//     int descubrimiento;
//     int finalizacion;
//     int predecesor;
// };

// void dfs_visitar(const vector<vector<int>>& grafo, vector<Vertice>& vertices,
//                  int u, int& tiempo) {
//     tiempo = tiempo + 1;
//     vertices[u].descubrimiento = tiempo;
//     vertices[u].visitado = true;
//
//     cout << "Descubriendo vertice " << u
//          << " en tiempo " << tiempo << endl;
//
//     // Explora todos los vertices
//     for (int vecino = 0; vecino < grafo.size(); vecino++) {
//         if (grafo[u][vecino] == 1 && !vertices[vecino].visitado) {
//             vertices[vecino].predecesor = u;  // Guardamos el predecesor
//             dfs_visitar(grafo, vertices, vecino, tiempo);
//         }
//     }
//
//     tiempo = tiempo + 1;
//     vertices[u].finalizacion = tiempo;
//     cout << "Finalizando vertice " << u
//          << " en tiempo " << tiempo << endl;
// }

// void dfs(const vector<vector<int>>& grafo) {
//     const int n = grafo.size();
//     vector<Vertice> vertices(n);
//
//     // Inicialización
//     for (int u = 0; u < n; u++) {
//         vertices[u].visitado = false;
//         vertices[u].predecesor = -1;  // -1 indica que no tiene predecesor
//     }
//
//     int tiempo = 0;
//
//     // Para cada vértice
//     for (int u = 0; u < n; u++) {
//         if (!vertices[u].visitado) {
//             dfs_visitar(grafo, vertices, u, tiempo);
//         }
//     }
//
//     // Podemos imprimir el árbol DFS usando los predecesores
//     cout << "\nÁrbol DFS (vértice: predecesor):\n";
//     for (int i = 0; i < n; i++) {
//         cout << "Vertice " << i << ": predecesor = "
//              << vertices[i].predecesor << endl;
//     }
// }


int main() {
    const vector<vector<int>> grafo = {
        {0, 1, 1, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {0, 0, 1, 0}
    };
    const vector<vector<int>> grafo2 = {
        {0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0 ,0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1}
    };

    DFS dfs(grafo2);

    dfs.ejecutar();

    if (dfs.hay_ciclo()) {
        cout << "El grafo tiene un ciclo." << endl;
    } else {
        cout << "Orden topologico:" << endl;
        for (const int v : dfs.obtener_orden_topologico()) {
            cout << v << " ";
        }
        cout << endl;
    }

    dfs.imprimir_arbol_dfs();

    return 0;
}
