#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "igrafo_ponderado.h"
#include "types.h"
#include <vector>
#include <algorithm>

class BellmanFord {
private:
    const IGrafoPonderado& grafo;
    std::vector<Vertice> vertices;
    bool hay_ciclos_negativos = false;

    void initialize_single_source(const int origen) {
        // Los vertices ya están inicializados con INFINITO y SIN_PREDECESOR por el constructor
        vertices[origen].distancia = 0;
    }

    void relax(const int u, const int v) {
        if (const double peso_u_v = grafo.obtener_peso(u, v);
            vertices[v].distancia > vertices[u].distancia + peso_u_v) {

            vertices[v].distancia = vertices[u].distancia + peso_u_v;
            vertices[v].predecesor = u;
        }
    }

public:
    explicit BellmanFord(const IGrafoPonderado& g) : grafo(g),
                                    vertices(g.obtener_num_vertices()) {}

    bool encontrar_camino_minimo(const int origen) {
        if (origen < 0 || origen >= grafo.obtener_num_vertices()) {
            throw std::invalid_argument("Vértice origen fuera de rango");
        }

        initialize_single_source(origen);
        const int num_vertices = grafo.obtener_num_vertices();

        // Relajacion de aristas |V| - 1 veces
        for (int i = 1; i < num_vertices; i++) {
            // Para cada arista (u,v) ∈ G.E
            for (int u = 0; u < num_vertices; u++) {
                for (const int v : grafo.obtener_adyacentes(u)) {
                    relax(u, v);
                }
            }
        }

        // Verificacion de ciclos negativos
        for (int u = 0; u < num_vertices; u++) {
            for (const int v : grafo.obtener_adyacentes(u)) {
                const double peso_u_v = grafo.obtener_peso(u, v);
                if (vertices[v].distancia > vertices[u].distancia + peso_u_v) {
                    hay_ciclos_negativos = true;
                    return false; // Hay ciclo negativo
                }
            }
        }

        return true; // No hay ciclos negativos
    }

    [[nodiscard]] double obtener_distancia(const int vertice) const {
        if(hay_ciclos_negativos) {
            throw std::runtime_error("El grafo tiene ciclos negativos");
        }
        return vertices[vertice].distancia;
    }

    [[nodiscard]] std::vector<int> obtener_camino(const int destino) const {
        std::vector<int> camino;
        for (int v = destino; v != SIN_PREDECESOR; v = vertices[v].predecesor) {
            camino.push_back(v);
        }
        std::ranges::reverse(camino);
        return camino;
    }

    [[nodiscard]] std::vector<std::vector<int>> obtener_todos_caminos() const {

        if (hay_ciclos_negativos) {
            throw std::runtime_error("El grafo tiene ciclos negativos");
        }
        std::vector<std::vector<int>> caminos;
        caminos.reserve(vertices.size());
        for (int i = 0; i < vertices.size(); i++) {
            caminos.push_back(obtener_camino(i));
        }
        return caminos;
    }

};

#endif //BELLMANFORD_H
