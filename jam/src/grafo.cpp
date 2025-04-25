#include <vector>
#include "../include/grafo.h"
using namespace std;


Grafo::Grafo(const int num_vertices): lista_adyacencia(num_vertices) {}

void Grafo::agregar_arista(const int origen, const int destino) {
    lista_adyacencia[origen].push_back(destino);
}

const vector<vector<int>>& Grafo::obtener_lista_adyacencia() const {
    return lista_adyacencia;
}

int Grafo::obtener_num_vertices() const {
    return lista_adyacencia.size();
}

Grafo Grafo::obtener_transpuesto() const {
    Grafo transpuesto(obtener_num_vertices());

    // Para cada vertice
    for (int v = 0; v < obtener_num_vertices(); v++) {
        // Para vada arista (v -> u) en el grafo original
        for (const int u : lista_adyacencia[v]) {
            // Argegar arista (u -> v) en el transpuesto
            transpuesto.agregar_arista(u, v);
        }
    }

    return transpuesto;
}
