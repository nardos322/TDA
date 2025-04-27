#include "../include/grafo.h"
#include <stdexcept>

#include "types.h"

using namespace std;


Grafo::Grafo(const int num_vertices) {
    if (num_vertices < 0) {
        throw invalid_argument("El numero de vertices no puede ser negativo");
    }
    lista_adyacencia.resize(num_vertices);
}

void Grafo::agregar_arista(const int origen, const int destino) {
    if (origen < 0 || origen >= obtener_num_vertices() ||
        destino < 0 || destino >= obtener_num_vertices()) {
        throw out_of_range("Vertice fuera de rango");
    }
    if (!existe_arista(origen, destino)) {
        lista_adyacencia[origen].push_back(Arista(destino));
    }
}

bool Grafo::existe_arista(const int origen, const int destino) const {
    const auto num_vertices = obtener_num_vertices();
    if (origen < 0 || origen >= num_vertices) {
        throw out_of_range("Vértice origen fuera de rango");
    }
    if (destino < 0 || destino >= num_vertices) {
        throw out_of_range("Vértice destino fuera de rango");
    }

    return ranges::find(lista_adyacencia[origen].begin(),
                       lista_adyacencia[origen].end(),
                       Arista(destino)) != lista_adyacencia[origen].end();
}


const vector<int> Grafo::obtener_adyacentes(int vertice) const {
    if (vertice < 0 || vertice >= obtener_num_vertices()) {
        throw out_of_range("Vertice fuera de rango");
    }
    vector<int> adyacentes;
    adyacentes.reserve(lista_adyacencia[vertice].size());
    for (const auto& arista : lista_adyacencia[vertice]) {
        adyacentes.push_back(arista.destino);
    }
    return adyacentes;
}

vector<vector<int>> Grafo::obtener_lista_adyacencia() const {
    vector<vector<int>> res(lista_adyacencia.size());
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        res[i].reserve(lista_adyacencia[i].size());
        for (const auto& arista : lista_adyacencia[i]) {
            res[i].push_back(arista.destino);
        }
    }
    return res;
}

size_t Grafo::obtener_num_vertices() const {
    return lista_adyacencia.size();
}

std::unique_ptr<IGrafo> Grafo::obtener_transpuesto() const {
    auto transpuesto = std::make_unique<Grafo>(obtener_num_vertices());

    for (size_t v = 0; v < obtener_num_vertices(); v++) {
        for (const auto& arista : lista_adyacencia[v]) {
            transpuesto->agregar_arista(arista.destino, v);
        }
    }

    return transpuesto;

}
