#include <iostream>
#include <vector>
#include "../include/grafo.h"
#include "../include/dfs.h"
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
    Grafo g(3);
    g.agregar_arista(0,1);
    g.agregar_arista(0, 2);
    g.agregar_arista(1, 2);

    DFS dfs(g);
    dfs.ejecutar();
    dfs.imprimir_tiempos();
    dfs.imprimir_arbol_dfs();
    const list<int> orden_topo = dfs.obtener_orden_topologico();

    for (const int v : orden_topo) {
        cout << v << " ";
    }
    cout << endl;
    dfs.encontrar_componentes_fuertemente_conexas();
    const vector<vector<int>> componentes = dfs.obtener_componentes();

    for (auto & componente : componentes) {
        cout << "Componentes fuertemente conexas: ";
        for (const int v : componente) {
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}
