
#include "../include/grafo_ponderado.h"
#include <stdexcept>
#include "../include/types.h"

using namespace std;

GrafoPonderado::GrafoPonderado(const int num_vertices) {
    if (num_vertices < 0) {
        throw invalid_argument("El numero de vertices no puede ser negativo");
    }
    lista_adyacencia.resize(num_vertices);
}

void GrafoPonderado::agregar_arista(const int origen, const int destino) {
    agregar_arista(origen, destino, PESO_PREDETERMINADO);
}

void GrafoPonderado::agregar_arista(const int origen, const int destino, const double peso) {
    validar_vertices(origen, destino, obtener_num_vertices());

    // Si la arista no existe , la agregamos
    if (!existe_arista(origen, destino)) {
        lista_adyacencia[origen].emplace_back(destino, peso);
    }

}

bool GrafoPonderado::existe_arista(const int origen, const int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    for (const auto& arista : lista_adyacencia[origen]) {
        if (arista.destino == destino) {
            return true;
        }
    }

    return false;
}


const std::vector<int> GrafoPonderado::obtener_adyacentes(const int vertice) const {
    validar_vertice(vertice, obtener_num_vertices());

    vector<int> adyacentes;
    adyacentes.reserve(lista_adyacencia[vertice].size());

    for (const auto& arista : lista_adyacencia[vertice]) {
        adyacentes.push_back(arista.destino);
    }
    return adyacentes;
}

size_t GrafoPonderado::obtener_num_vertices() const {
    return lista_adyacencia.size();
}


int GrafoPonderado::obtener_peso(const int origen, const int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    for (const auto& arista : lista_adyacencia[origen]) {
        // Si encontramos la arista que va al destino buscado
        if (arista.destino == destino) {
            // Retornamos su peso
            return arista.peso;
        }
    }

    // Si no encontramos la arista, lanzamos una excepción
    throw out_of_range("No existe arista entre los vertices");

}

std::vector<std::vector<int>> GrafoPonderado::obtener_lista_adyacencia() const {
    vector<vector<int>> res(lista_adyacencia.size());
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        res[i].reserve(lista_adyacencia[i].size());
        for (const auto& arista : lista_adyacencia[i]) {
            res[i].push_back(arista.destino);
        }
    }

    return res;
}

unique_ptr<IGrafo> GrafoPonderado::obtener_transpuesto() const {
    auto transpuesto = make_unique<GrafoPonderado>(obtener_num_vertices());

    for (size_t vertice_origen = 0; vertice_origen < obtener_num_vertices(); vertice_origen++) {
        for (const auto& arista : lista_adyacencia[vertice_origen]) {
            transpuesto->agregar_arista(arista.destino, vertice_origen, arista.peso);
        }
    }

    return transpuesto;

}




