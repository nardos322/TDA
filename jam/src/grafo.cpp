#include "../include/grafo.h"
#include <algorithm>
#include <iomanip>
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

void Grafo::agregar_vertice() {
    //1. Aumentar el tamaño de la lista de adyacencia
    lista_adyacencia.push_back(vector<Arista>());


}

void Grafo::eliminar_arista(int origen, int destino) {
    validar_vertices(origen, destino, obtener_num_vertices());

    // Eliminar la arista del origen al destino
    auto& lista_origen = lista_adyacencia[origen];
    const auto it = find_if(lista_origen.begin(), lista_origen.end(),
        [destino](const Arista& a) {return a.destino == destino; });
    lista_origen.erase(it);

    // Si el grafo es no dirigido, eliminar la arista inversa
    if (!es_dirigido && origen != destino) {
        auto& lista_destino = lista_adyacencia[destino];
        const auto it_inverso = find_if(lista_destino.begin(), lista_destino.end(),
            [origen](const Arista& a) {return a.destino == origen; });
        lista_destino.erase(it_inverso);
    }
}

void Grafo::eliminar_vertice(int vertice) {
    validar_vertice(vertice, obtener_num_vertices());

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

void Grafo::imprimir_grafo(bool usar_matriz, std::ostream& os) const {
    if (usar_matriz) {
        imprimir_matriz_adyacencia(os);
    } else {
        imprimir_lista_adyacencia(os);
    }
}

void Grafo::imprimir_lista_adyacencia(std::ostream& os) const {
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        os << i << " -> ";
        for (const auto& arista : lista_adyacencia[i]) {
            if (es_ponderado) {
                os << "[" << arista.destino << ", peso= " << arista.peso << "] ";
            } else {
                os << arista.destino << " ";
            }
        }
        os << "\n";
    }

}

void Grafo::imprimir_matriz_adyacencia(std::ostream& os) const {
    const size_t num_vertices = obtener_num_vertices();
    os << "    ";
    for (size_t i = 0; i < num_vertices; i++) {
        os << setw(4) << i << " ";
    }
    os << "\n";

    for (size_t i = 0; i < num_vertices; i++) {
        os << setw(2) << i << "| ";
        for (size_t j = 0; j < num_vertices; j++) {
            if (existe_arista(i, j)) {
                if (es_ponderado) {
                    os << setw(4) << obtener_peso(i, j) << " ";
                } else {
                    os << setw(4) << "1" << " ";
                }
            } else {
                os << setw(4) << "0" << " ";
            }
        }
        os << "\n";
    }

}

