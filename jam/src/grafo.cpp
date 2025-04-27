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
    validar_vertices(origen, destino, obtener_num_vertices());

    if (!existe_arista(origen, destino)) {
        lista_adyacencia[origen].emplace_back(destino);
    }
}

bool Grafo::existe_arista(const int origen, const int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    return ranges::find(lista_adyacencia[origen].begin(),
                       lista_adyacencia[origen].end(),
                       Arista(destino)) != lista_adyacencia[origen].end();
}


const vector<int> Grafo::obtener_adyacentes(const int vertice) const {
    validar_vertice(vertice, obtener_num_vertices());

    vector<int> adyacentes;
    adyacentes.reserve(lista_adyacencia[vertice].size());
    for (const auto& arista : lista_adyacencia[vertice]) {
        adyacentes.push_back(arista.destino);
    }
    return adyacentes;
}

size_t Grafo::obtener_num_vertices() const {
    return lista_adyacencia.size();
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

std::unique_ptr<IGrafo> Grafo::obtener_transpuesto() const {
    auto transpuesto = std::make_unique<Grafo>(obtener_num_vertices());

    for (int vertice_origen = 0; vertice_origen < obtener_num_vertices(); vertice_origen++) {
        for (const auto& arista : lista_adyacencia[vertice_origen]) {
            transpuesto->agregar_arista(arista.destino, vertice_origen);
        }
    }

    return transpuesto;

}
