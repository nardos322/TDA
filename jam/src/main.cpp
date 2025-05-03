#include <iostream>
#include <vector>
#include "../include/grafo.h"
#include "../include/dfs.h"
#include "../include/bellmanford.h"

using namespace std;


void dfs_basic(const vector<vector<int>>& grafo, vector<bool>& visitado, const int vertice) {
    visitado[vertice] = true;
    cout << "visitando vertice: " << vertice << endl;
    for (const int vecino: grafo[vertice]) {
        if (!visitado[vecino]) {
            dfs_basic(grafo, visitado, vecino);
        }
    }
}

void backtrack(const vector<int>& nums, vector<int>& perm, vector<bool>& usados, int i, int& count,
               vector<vector<int>>& res) {
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
    vector<int> perm(conjunto.size());
    vector<bool> usados(conjunto.size(), false);
    vector<vector<int>> res;
    int count = 0;
    backtrack(conjunto, perm, usados, 0, count, res);
    return res;
}

struct FloydResult {
    vector<vector<double>> distancias;
    vector<vector<int>> predecesores;
    bool tiene_ciclo_negativo;

    explicit FloydResult(const size_t n) : distancias(n, vector<double>(n)),
                                           predecesores(n, vector<int>(n)),
                                           tiene_ciclo_negativo(false) {
    }
};

FloydResult floyd_warshall(const IGrafoPonderado& grafo) {
    const int n = grafo.obtener_num_vertices();
    FloydResult result(n);
    auto& dist = result.distancias;
    auto& pred = result.predecesores;

    // Inicializacion
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (grafo.existe_arista(i, j)) {
                dist[i][j] = grafo.obtener_peso(i, j);
                pred[i][j] = i;
            } else {
                dist[i][j] = INFINITO;
                pred[i][j] = SIN_PREDECESOR;
            }
        }
    }

    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INFINITO && dist[k][j] != INFINITO) {
                    double nueva_dist = dist[i][k] + dist[k][j];
                    if (nueva_dist < dist[i][j]) {
                        dist[i][j] = nueva_dist;
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }

    // Verificacion de ciclos negativos
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            result.tiene_ciclo_negativo = true;
            break;
        }
    }

    return result;
}

// Funiones auxiliares para recuperar caminos y mostrar resultados
vector<int> reconstuir_camino(const vector<vector<int>>& pred, int origen, int destino) {
    if (pred[origen][destino] == SIN_PREDECESOR) {
        return {};
    }

    vector<int> camino;
    camino.push_back(destino);

    while (origen != destino) {
        destino = pred[origen][destino];
        camino.push_back(destino);
    }

    ranges::reverse(camino);
    return camino;
}

void imprimir_matriz_distancias(const vector<vector<double>>& distancias, ostream& os = cout) {
    const int n = distancias.size();
    os << "\nMatriz de distancias:\n";

    // Encabezado
    os << "  ";
    for (int j = 0; j < n; j++) {
        os << setw(8) << j;
    }
    os << "\n";

    // Contenido
    for (int i = 0; i < n; i++) {
        os << setw(2) << i << " ";
        for (int j = 0; j < n; j++) {
            if (distancias[i][j] == INFINITO) {
                os << setw(8) << "INF";
            } else {
                os << setw(8) << fixed << setprecision(2) << distancias[i][j];
            }
        }
        os << "\n";
    }
}

void imprimir_camino(const vector<int>& camino, const vector<vector<double>>& dist,
                     int origen, int destino, ostream& os = cout) {
    if (camino.empty()) {
        os << "No hay camino entre " << origen << " y " << destino << "\n";
        return;
    }

    os << "Camino de " << origen << " a " << destino << " (distancia: " << dist[origen][destino] << "): ";
    for (int i = 0; i < camino.size(); i++) {
        os << camino[i];
        if (i < camino.size() - 1) {
            os << "->";
        }
    }
    os << "\n";
}

int main() {
    Grafo g(3);
    g.agregar_arista(0, 1);
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



    return 0;
}
