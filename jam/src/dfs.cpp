#include <iostream>
#include <string>
#include "../include/dfs.h"

#include <algorithm>

using namespace std;


DFS::DFS(const IGrafo& g) : grafo(g),
                            vertices(g.obtener_num_vertices()),
                            tiempo(0), tiene_ciclo(false) {}

void DFS::ejecutar() {
    // Reiniciar estado
    tiempo = 0;
    tiene_ciclo = false;
    orden_topologico.clear();
    aristas_clasificadas.clear();

    // Realiza DFS para cada vertice no visitado
    for (int u = 0; u < grafo.obtener_num_vertices(); u++) {
        if (vertices[u].color == Color::WHITE) {
            dfs_visitar(u);
        }
    }
}


void DFS::encontrar_componentes_fuertemente_conexas() {
    // Paso 1: aplicamos DFS en el grafo original
    ejecutar();
    // Paso 2: Obtener vertices ordenados por tiempo de finalizacion
    const vector<int> orden = obtener_vertices_por_finalizacion();

    // Paso 3: Creamos el grafo transpuesto
    const std::unique_ptr<IGrafo> grafo_transpuesto = grafo.obtener_transpuesto();

    // Paso 4: Reiniciamos el estado de los vertices
    for (auto& v : vertices) {
        v.color = Color::WHITE;
        v.predecesor = SIN_PREDECESOR;
    }

    // Paso 5: Limpiar componentes anteriores
    componentes_fuertemente_conexas.clear();
    tiempo = 0;

    // Paso 6: Segunda pasada DFS en orden descendente de finalización
    for (const int v : orden) {
        if (vertices[v].color == Color::WHITE) {
            componente_actual.clear();
            dfs_visitar_scc(v, *grafo_transpuesto);
            componentes_fuertemente_conexas.push_back(componente_actual);

        }
    }
}

std::vector<std::vector<int>> DFS::obtener_componentes() const {
    return componentes_fuertemente_conexas;
}

bool DFS::hay_ciclo() const { return tiene_ciclo; }

list<int> DFS::obtener_orden_topologico() const {
    return tiene_ciclo ? list<int>() : orden_topologico;
}

vector<pair<int, int>> DFS::obtener_aristas_clasificadas() const {
    return aristas_clasificadas;
}

void DFS::imprimir_tiempos() const {
    cout << "Tiempos de descubrimiento y finalización:\n";
    for (int i = 0; i < vertices.size(); i++) {
        cout << "Vertice " << i << ": descubrimiento = "
                << vertices[i].descubrimiento
                << ", finalizacion = " << vertices[i].finalizacion
                << endl;
    }
}

void DFS::imprimir_arbol_dfs() const {
    cout << "\nÁrbol DFS (vértice: predecesor):\n";
    for (int i = 0; i < vertices.size(); i++) {
        cout << "Vertice " << i << ": predecesor = "
                << vertices[i].predecesor << endl;
    }
}

// Metodos privados

void DFS::clasificar_arista(int u, int v, const TipoArista tipo) {
    aristas_clasificadas.push_back({u, v});
    string tipo_str;
    switch (tipo) {
        case TipoArista::TREE_EDGE: tipo_str = "tree";
            break;
        case TipoArista::BACK_EDGE: tipo_str = "back";
            break;
        case TipoArista::FORWARD_EDGE: tipo_str = "forward";
            break;
        case TipoArista::CROSS_EDGE: tipo_str = "cross";
            break;
    }

    cout << "Arista (" << u << ", " << v << ") es de tipo " << tipo_str << endl;
}

void DFS::dfs_visitar(const int u) {
    tiempo++;
    vertices[u].descubrimiento = tiempo;
    vertices[u].color = Color::GREY;

    for (const int v: grafo.obtener_adyacentes(u)) {
        // solo recorremos los vecinos existentes
        if (vertices[v].color == Color::WHITE) {
            vertices[v].predecesor = u;
            clasificar_arista(u, v, TipoArista::TREE_EDGE);
            dfs_visitar(v);
        } else if (vertices[v].color == Color::GREY) {
            clasificar_arista(u, v, TipoArista::BACK_EDGE);
            tiene_ciclo = true;
        } else {
            if (vertices[u].descubrimiento < vertices[v].descubrimiento) {
                clasificar_arista(u, v, TipoArista::FORWARD_EDGE);
            } else {
                clasificar_arista(u, v, TipoArista::CROSS_EDGE);
            }
        }
    }
    vertices[u].color = Color::BLACK;
    tiempo++;
    vertices[u].finalizacion = tiempo;
    if (!tiene_ciclo) {
        orden_topologico.push_front(u);
    }

}

void DFS::dfs_visitar_scc(const int u, const IGrafo& g_transpuesto) {
    tiempo++;
    vertices[u].descubrimiento = tiempo;
    vertices[u].color = Color::GREY;
    componente_actual.push_back(u);  // Agregar vertice a la componente actual
    for (const int v : g_transpuesto.obtener_adyacentes(u)) {
        if (vertices[v].color == Color::WHITE) {
            vertices[v].predecesor = u;
            dfs_visitar_scc(v, g_transpuesto);
        }
    }
    vertices[u].color = Color::BLACK;
    tiempo++;
    vertices[u].finalizacion = tiempo;


}

std::vector<int> DFS::obtener_vertices_por_finalizacion() const {
    // Crear un vector de pares (tiempo de finalizacion, indice del vertice)
    std::vector<std::pair<int,int>> vertices_tiempo;
    vertices_tiempo.reserve(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        vertices_tiempo.push_back({vertices[i].finalizacion, i});
    }

    // Ordenar por tiempo de finalizacion (descendente)
    ranges::sort(vertices_tiempo,
                 [](const auto& a, const auto& b ) {
                     return a.first > b.first;
                 });

    // Extraer solo los indices de vertices
    std::vector<int> result;
    result.reserve(vertices_tiempo.size());
    for (const auto& par : vertices_tiempo) {
        result.push_back(par.second);
    }
    return result;
}