#include "../include/grafo.h"
#include <algorithm>
#include <iomanip>
#include <list>
#include <stdexcept>
#include "types.h"

using namespace std;


Grafo::Grafo(const int num_vertices, const bool ponderado, const bool dirigido)
    : lista_adyacencia(num_vertices), es_ponderado(ponderado), es_dirigido(dirigido) {
    if (num_vertices < 0) {
        throw invalid_argument("El numero de vertices no puede ser negativo");
    }

    for (auto& lista : lista_adyacencia) {
        lista.reserve(num_vertices);
    }
}

void Grafo::agregar_arista(const int origen, const int destino) {
    agregar_arista(origen, destino, 1.0);
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
    const auto it = ranges::find_if(lista_origen,
                                    [destino](const Arista& a) { return a.destino == destino; });
    lista_origen.erase(it);

    // Si el grafo es no dirigido, eliminar la arista inversa
    if (!es_dirigido && origen != destino) {
        auto& lista_destino = lista_adyacencia[destino];
        const auto it_inverso = ranges::find_if(lista_destino,
                                                [origen](const Arista& a) { return a.destino == origen; });
        lista_destino.erase(it_inverso);
    }
}

void Grafo::eliminar_vertice(const int vertice) {
    validar_vertice(vertice, obtener_num_vertices());
    lista_adyacencia.erase(lista_adyacencia.begin() + vertice);

    for (auto& lista: lista_adyacencia) {
        auto it = ranges::find_if(lista, [vertice](const Arista& a) { return a.destino == vertice; });
        if (it != lista.end()) {
            lista.erase(it);
        }
    }
}

void Grafo::limpiar() {
    lista_adyacencia.clear();
    es_ponderado = false;
    es_dirigido = true;
}


void Grafo::modificar_peso(const int origen, const int destino, const double nuevo_peso) {
    validar_vertices(origen, destino, obtener_num_vertices());

    if (!existe_arista(origen, destino)) {
        throw invalid_argument("La arista no existe");
    }

    if (!es_ponderado) {
        throw invalid_argument("El grafo no es ponderado, no se puede modificar el peso");
    }

    for (auto& arista: lista_adyacencia[origen]) {
        if (arista.destino == destino) {
            arista.peso = nuevo_peso;
            break;
        }
    }

    if (!es_dirigido) {
        for (auto& arista: lista_adyacencia[destino]) {
            if (arista.destino == origen) {
                arista.peso = nuevo_peso;
                break;
            }
        }
    }
}


bool Grafo::existe_arista(const int origen, const int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    return std::ranges::find_if(lista_adyacencia[origen],
                                [destino](const Arista& a) { return a.destino == destino; })
           != lista_adyacencia[origen].end();
}

const std::vector<Arista>& Grafo::obtener_aristas(const int vertice) const {
    validar_vertice(vertice, obtener_num_vertices());
    return lista_adyacencia[vertice];
}

size_t Grafo::otener_num_aristas() const {
    size_t total_aristas = 0;
    for (const auto& lista: lista_adyacencia) {
        total_aristas += lista.size();
    }
    return es_dirigido ? total_aristas : total_aristas / 2;
}

int Grafo::obtener_grado(const int vertice) const {
    validar_vertice(vertice, obtener_num_vertices());
    if (es_dirigido) {
        return obtener_grado_entrada(vertice) + obtener_grado_salida(vertice);
    }

    return lista_adyacencia[vertice].size();
}

int Grafo::obtener_grado_entrada(const int vertice) const {
    validar_vertice(vertice, obtener_num_vertices());
    if (!es_dirigido) {
        return lista_adyacencia[vertice].size();
    }
    int grado_entrada = 0;
    for (const auto& lista: lista_adyacencia) {
        grado_entrada += ranges::count_if(lista, [vertice](const Arista& a) { return a.destino == vertice; });
    }
    return grado_entrada;
}

int Grafo::obtener_grado_salida(const int vertice) const {
    validar_vertice(vertice, obtener_num_vertices());
    return lista_adyacencia[vertice].size();
}

double Grafo::obtener_peso(const int origen, const int destino) const {
    validar_vertices(origen, destino, obtener_num_vertices());

    for (const Arista& arista: lista_adyacencia[origen]) {
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
    for (const auto& arista: lista_adyacencia[vertice]) {
        adyacentes.push_back(arista.destino);
    }
    return adyacentes;
}

vector<vector<int>> Grafo::obtener_lista_adyacencia() const {
    vector<vector<int>> lista(lista_adyacencia.size());
    lista.reserve(lista_adyacencia.size());
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        lista[i].reserve(lista_adyacencia[i].size());
        for (const auto& arista: lista_adyacencia[i]) {
            lista[i].push_back(arista.destino);
        }
    }
    return lista;
}

unique_ptr<IGrafo> Grafo::obtener_transpuesto() const {
    auto transpuesto = std::make_unique<Grafo>(obtener_num_vertices(), es_ponderado);

    for (int vertice_origen = 0; vertice_origen < obtener_num_vertices(); vertice_origen++) {
        for (const auto& arista: lista_adyacencia[vertice_origen]) {
            transpuesto->agregar_arista(arista.destino, vertice_origen, arista.peso);
        }
    }

    return transpuesto;
}

bool Grafo::esta_vacio() const {
    return lista_adyacencia.empty();
}

bool Grafo::es_completo() const {
    const size_t n = obtener_num_vertices();

    // Para cada vertice
    for (size_t i = 0; i < n; i++) {
        // En un grafo dirigido completo, cada vertice debe tener n-1 aristas salientes
        // (a todos los demas vertices excepto a si mismo)
        if (lista_adyacencia[i].size() != (n - 1)) {
            return false;
        }

        // Verificar que las aristas van a todos los demas vertices
        vector<bool> conexiones(n, false);
        for (const auto& arista: lista_adyacencia[i]) {
            if (arista.destino == i) {
                // No se puede conectar a si mismo
                return false;
            }
            conexiones[arista.destino] = true;
        }

        // Verificar que este conectado con todos los demas vertices
        for (size_t j = 0; j < n; j++) {
            if (j != i && !conexiones[j]) {
                return false;
            }
        }
    }
    return true;
}

bool Grafo::son_adyacentes(const int v1, const int v2) const {
    validar_vertices(v1, v2, obtener_num_vertices());

    if (es_dirigido) {
        return existe_arista(v1, v2);
    } else {
        return existe_arista(v1, v2) || existe_arista(v2, v1);
    }
}


unique_ptr<IGrafo> Grafo::clonar() const {
    auto clon = make_unique<Grafo>(obtener_num_vertices(), es_ponderado, es_dirigido);
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        for (const auto& arista: lista_adyacencia[i]) {
            if (es_grafo_ponderado()) {
                clon->agregar_arista(arista.origen, arista.destino, arista.peso);
            } else {
                clon->agregar_arista(arista.origen, arista.destino);
            }
        }
    }

    return clon;
}

void Grafo::imprimir_grafo(const bool usar_matriz, std::ostream& os) const {
    if (usar_matriz) {
        imprimir_matriz_adyacencia(os);
    } else {
        imprimir_lista_adyacencia(os);
    }
}

void Grafo::imprimir_lista_adyacencia(std::ostream& os) const {
    for (size_t i = 0; i < lista_adyacencia.size(); i++) {
        os << i << " -> ";
        for (const auto& arista: lista_adyacencia[i]) {
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
