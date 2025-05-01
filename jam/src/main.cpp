#include <iostream>
#include <vector>
#include "../include/grafo.h"
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



    Grafo g(3);
    g.agregar_arista(0,1);
    g.agregar_arista(0, 2);
    g.agregar_arista(1, 2);


    Grafo t(8, true);
    t.agregar_arista(0, 1, 3.0);
    t.agregar_arista(0, 3, 5.0);
    t.agregar_arista(0, 5, 2.0);
    t.agregar_arista(1, 2, -4.0);
    t.agregar_arista(2, 7, 4.0);
    t.agregar_arista(3, 4, 6.0);
    t.agregar_arista(4, 3, -3.0);
    t.agregar_arista(4, 7, 8.0);
    t.agregar_arista(5, 6, 3.0);
    t.agregar_arista(6, 5, -3.0);
    t.agregar_arista(6, 7, 7.0);

    Grafo c(4, true);
    c.agregar_arista(0, 1, 3.0);
    c.agregar_arista(0, 2, -2.0);
    c.agregar_arista(2, 3, 4.0);
    c.agregar_arista(3, 1, -1.0);

    Grafo d(5, true);
    d.agregar_arista(0, 1, 3.0);
    d.agregar_arista(0, 3, 5.0);
    d.agregar_arista(1, 2, 6.0);
    d.agregar_arista(1, 3, 2.0);
    d.agregar_arista(2, 4, 2.0);
    d.agregar_arista(3, 1, 1.0);
    d.agregar_arista(3, 2, 4.0);
    d.agregar_arista(3, 4, -8.0);
    d.agregar_arista(4, 0, 3.0);
    d.agregar_arista(4, 2, 7.0);

    BellmanFord bf(c);

    cout << "\nEjecutando Bellman-Ford en el grafo c:\n";
    bf.encontrar_camino_minimo(0);
    const vector<vector<int>> caminos = bf.obtener_todos_caminos();
    bf.imprimir_todos_caminos();
    bf.imprimir_tabla_distancias();

    BellmanFord bf2(d);
    cout << "\n\nEjecutando Bellman-Ford en el grafo d:\n";
    bf2.encontrar_camino_minimo(0);
    bf2.imprimir_todos_caminos();
    bf2.imprimir_tabla_distancias();
    bf2.imprimir_distancia(2);

    int grado = d.obtener_grado_salida(0);

    for (auto& arista : d) {
        for (auto& n : arista) {
            cout << "arista: " << n.origen << " -> " << n.destino << endl;
        }
    }

    return 0;




}
