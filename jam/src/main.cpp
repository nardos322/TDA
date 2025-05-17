#include <iostream>
#include <vector>
#include "../include/grafo.h"
#include "../include/dfs.h"
#include "../include/bellmanford.h"

using namespace std;


void dfs_basic(const vector<vector<int>>& grafo, vector<bool>& visitado, const int vertice) {
    visitado[vertice] = true;
    cout << "visitando vertice: " << vertice << endl;
    for (const int vecino : grafo[vertice]) {
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

/**
 * @brief Implementa el algoritmo de Floyd-Warshall para encontrar los caminos más cortos entre
 * todos los pares de vértices en un grafo.
 *
 * @param grafo Una referencia constante a un objeto que implementa la interfaz IGrafoPonderado
 *
 * @return FloydResult Una estructura que contiene:
 *         - distancias: Matriz de distancias mínimas entre todos los pares de vértices
 *         - predecesores: Matriz de predecesores para reconstruir los caminos
 *         - tiene_ciclo_negativo: Indicador de si existe algún ciclo negativo en el grafo
 *
 * @complexity La complejidad temporal del algoritmo es O(V³), donde V es el número de vértices
 * @note El grafo puede contener pesos negativos, pero detectará si hay ciclos negativos
 * @throws No lanza excepciones
 */
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
                    const double nueva_dist = dist[i][k] + dist[k][j];
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
vector<int> reconstuir_camino(const vector<vector<int>>& predecesores, int origen, int destino) {
    if (predecesores[origen][destino] == SIN_PREDECESOR) {
        return {};
    }

    vector<int> camino;
    camino.push_back(destino);

    while (origen != destino) {
        destino = predecesores[origen][destino];
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
                os << setw(8) << fixed << setprecision(1) << distancias[i][j];
            }
        }
        os << "\n";
    }
}

void imprimir_camino(const vector<int>& camino, const vector<vector<double>>& distancias,
                     int origen, int destino, ostream& os = cout) {
    if (camino.empty()) {
        os << "No hay camino entre " << origen << " y " << destino << "\n";
        return;
    }

    os << "Camino de " << origen << " a " << destino << " (distancia: " << distancias[origen][destino] << "): ";
    for (int i = 0; i < camino.size(); i++) {
        os << camino[i];
        if (i < camino.size() - 1) {
            os << "->";
        }
    }
    os << "\n";
}


vector<int> recursive_activity_selector(const vector<int>& s, const vector<int>& f, int k, int n) {
    int m = k + 1;
    // Encontrar la primera actividad a_m que empieza despues de que termina a_k
    while (m <= n && s[m] < f[k]) {
        m++;
    }

    if (m <= n) {
        // Seleccionamos a_m  y llamamos recursivamente desde m
        vector result { m };
        vector<int> next = recursive_activity_selector(s, f, m, n);
        result.insert(result.end(), next.begin(), next.end());
        return result;
    } else {
        // No quedan actividades compatibles
        return {};
    }
}

vector<int> greedy_activity_selector(const vector<int>& s, const vector<int>& f) {
    vector<int> seleccionadas;
    int n = s.size() - 1; // numero de actividades
    seleccionadas.push_back(1); // seleccionamos la primera actividad

    int k = 1; // ultima actividad seleccionada
    for (int m = 1; m <= n; m++) {
        if (s[m] >= f[k]) { // si la actividad m es compatible con la ultima seleccionada
            seleccionadas.push_back(m);
            k = m; // actualizamos la ultima actividad seleccionada
        }
    }
    return seleccionadas;
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

    Grafo f(4, true);

    f.agregar_arista(0, 1, 2.0);
    f.agregar_arista(0, 2, 10.0);
    f.agregar_arista(0, 3, 6.0);
    f.agregar_arista(1, 3, 3.0);
    f.agregar_arista(2, 1, -3.0);
    f.agregar_arista(3, 1, 3.0);
    f.agregar_arista(3, 2, 1.0);


    const FloydResult resultado = floyd_warshall(f);
    const vector<int> camino = reconstuir_camino(resultado.predecesores, 0, 3);


    vector<int> s = {0, 3, 2, 6, 10};   // tiempos de inicio
    vector<int> p = {0, 4, 7,10,11};   // tiempos de fin
    int n = s.size() - 1;   // numero de actividades

    // vector<int> seleccionados = recursive_activity_selector(s,p,0,n);
    vector<int> seleccionados = greedy_activity_selector(s,p);

    cout << "actividades seleccionadas (indices): ";
    for (int idx : seleccionados) {
        cout << idx << " ";
    }
    cout << "\n";
    // imprimir_matriz_distancias(resultado.distancias);
    // cout << resultado.tiene_ciclo_negativo << endl;
    // cout <<"camino de 0 a 3\n";
    // imprimir_camino(camino, resultado.distancias, 0, 3);

    // BellmanFord bf(c);
    //
    // cout << "\nEjecutando Bellman-Ford en el grafo c:\n";
    // bf.encontrar_camino_minimo(0);
    // const vector<vector<int>> caminos = bf.obtener_todos_caminos();
    // bf.imprimir_todos_caminos();
    // bf.imprimir_tabla_distancias();
    //
    // BellmanFord bf2(d);
    // cout << "\n\nEjecutando Bellman-Ford en el grafo d:\n";
    // bf2.encontrar_camino_minimo(0);
    // bf2.imprimir_todos_caminos();
    // bf2.imprimir_tabla_distancias();
    // bf2.imprimir_distancia(2);
    //
    return 0;
}
