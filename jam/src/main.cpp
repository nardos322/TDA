#include <iostream>
#include <vector>
#include "../include/grafo.h"
#include  "../include/grafo_ponderado.h"
#include "../include/dfs.h"
#include "../include/bellmanford.h"
using namespace std;


void dfs_basic(const vector<vector<int>>& grafo, vector<bool>& visitado, int vertice) {
    visitado[vertice] = true;
    cout << "visitando vertice: " << vertice << endl;
    for (const int vecino : grafo[vertice]) {
        if (!visitado[vecino]) {
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



int main() {


    GrafoPonderado grafo(8);
    grafo.agregar_arista(0, 1, 3.0);
    grafo.agregar_arista(0, 3, 5.0);
    grafo.agregar_arista(0, 5, 2.0);
    grafo.agregar_arista(1, 2, -4.0);
    grafo.agregar_arista(2, 7, 4.0);
    grafo.agregar_arista(3, 4, 6.0);
    grafo.agregar_arista(4, 3, -3.0);
    grafo.agregar_arista(4, 7, 8.0);
    grafo.agregar_arista(5, 6, 3.0);
    grafo.agregar_arista(6, 5, -3.0);
    grafo.agregar_arista(6, 7, 7.0);


    BellmanFord bf(grafo);


    if (bf.encontrar_camino_minimo(0)) {
        const vector<vector<int>> caminos = bf.obtener_todos_caminos();
        for (int i = 0; i < caminos.size(); i++) {
            cout << "Camino " << i + 1 << ": ";
            for (int j = 0; j < caminos[i].size(); j++) {
                cout << caminos[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No hay camino minimo porque hay ciclos" << endl;
    }













    // Grafo g(3);
    // g.agregar_arista(0,1);
    // g.agregar_arista(0, 2);
    // g.agregar_arista(1, 2);
    //
    // DFS dfs(g);
    // dfs.ejecutar();
    // dfs.imprimir_tiempos();
    // dfs.imprimir_arbol_dfs();
    //
    // GrafoPonderado t(5);
    // t.agregar_arista(0, 1, 3.0);
    // t.agregar_arista(0, 2, 8.0);
    // t.agregar_arista(0, 4, -4.0);
    // t.agregar_arista(1, 4, 7.0);
    // t.agregar_arista(1, 3, 1.0);
    // t.agregar_arista(2, 1, 4.0);
    // t.agregar_arista(3, 0, 2.0);
    // t.agregar_arista(3, 2, -5.0);
    // t.agregar_arista(4, 3, 6.0);
    //
    // DFS dfs_ponderado(t);
    // dfs_ponderado.ejecutar();

    // cout << "Hay ciclo? " << dfs_ponderado.hay_ciclo() << endl;
    // dfs_ponderado.encontrar_componentes_fuertemente_conexas();
    // for (const auto componentes = dfs_ponderado.obtener_componentes(); auto & componente : componentes) {
    //     cout << "Componentes fuertemente conexas: ";
    //     for (const int v : componente) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "orden topologico: ";
    // for (const list<int> orden_topo = dfs.obtener_orden_topologico(); const int v : orden_topo) {
    //     cout << v << " ";
    // }
    // cout << endl;
    // dfs.encontrar_componentes_fuertemente_conexas();
    //
    // for (const vector<vector<int>> componentes = dfs.obtener_componentes(); auto & componente : componentes) {
    //     cout << "Componentes fuertemente conexas: ";
    //     for (const int v : componente) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }
    return 0;
}
