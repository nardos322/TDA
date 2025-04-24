#include <vector>
#include <list>
#include <iostream>
#include <string>
#include "../include/dfs.h"

using namespace std;


void DFS::clasificar_arista(int u, int v, TipoArista tipo) {
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

void DFS::dfs_visitar(int u) {
    tiempo++;
    vertices[u].descubrimiento = tiempo;
    vertices[u].color = Color::GREY;

    for (const int v: grafo.obtener_lista_adyacencia()[u]) {
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


DFS::DFS(const Grafo& g) : grafo(g) {
    vertices.resize(g.obtener_num_vertices());
    tiempo = 0;
    tiene_ciclo = false;
}

void DFS::ejecutar() {
    for (int u = 0; u < grafo.obtener_num_vertices(); u++) {
        vertices[u].color = Color::WHITE;
        vertices[u].predecesor = SIN_PREDECESOR;
    }
    tiempo = 0;
    tiene_ciclo = false;
    orden_topologico.clear();
    aristas_clasificadas.clear();

    for (int u = 0; u < grafo.obtener_num_vertices(); u++) {
        if (vertices[u].color == Color::WHITE) {
            dfs_visitar(u);
        }
    }
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
