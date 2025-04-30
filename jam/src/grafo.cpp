#include "../include/grafo.h"
#include <stdexcept>
#include "types.h"

using namespace std;


Grafo::Grafo(const int num_vertices, bool ponderado, bool dirigido)
    : lista_adyacencia(num_vertices), es_ponderado(ponderado), es_dirigido(dirigido){
    if (num_vertices < 0) {
        throw invalid_argument("El numero de vertices no puede ser negativo");
    }

}

void Grafo::agregar_arista(const int origen, const int destino) {

    agregar_arista(origen,destino, 1.0);

}

void Grafo::agregar_arista(const int origen, const int destino, const double peso) {
    validar_vertices(origen, destino, obtener_num_vertices());

    if (!es_ponderado && peso != 1.0) {
        throw invalid_argument("El grafo no es ponderado, no se puede agregar arista con peso");
    }

    auto arista = Arista(origen, destino, peso);
    if (!existe_arista(origen, destino)) {
        lista_adyacencia[origen].emplace_back(arista);

        // si el grafo es no dirigido agregamos tambien la arista inversa
        if (!es_dirigido && origen != destino) {
            auto arista_inversa = Arista(destino, origen, peso);
            lista_adyacencia[destino].emplace_back(arista_inversa);
        }
    }
}

bool Grafo::existe_arista(const int origen, const int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    return std::ranges::find_if(lista_adyacencia[origen],
        [destino](const Arista& a) { return a.destino == destino; })
        != lista_adyacencia[origen].end();
}

double Grafo::obtener_peso(int origen, int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    for (const Arista& arista : lista_adyacencia[origen]) {
        if (arista.destino == destino) {
            return arista.peso;
        }
    }

    throw runtime_error("La arista no existe");
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

vector<vector<int>> Grafo::obtener_lista_adyacencia() const {
    vector<vector<int>> lista(lista_adyacencia.size());
    lista.reserve(lista_adyacencia.size());
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        lista[i].reserve(lista_adyacencia[i].size());
        for (const auto& arista : lista_adyacencia[i]) {
            lista[i].push_back(arista.destino);
        }
    }
    return lista;
}

std::unique_ptr<IGrafo> Grafo::obtener_transpuesto() const {
    auto transpuesto = std::make_unique<Grafo>(obtener_num_vertices(), es_ponderado);

    for (int vertice_origen = 0; vertice_origen < obtener_num_vertices(); vertice_origen++) {
        for (const auto& arista : lista_adyacencia[vertice_origen]) {
            transpuesto->agregar_arista(arista.destino, vertice_origen, arista.peso);
        }
    }

    return transpuesto;

}
