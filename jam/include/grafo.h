#ifndef GRAFO_H
#define GRAFO_H
#include <vector>

class Grafo {
private:
    std::vector<std::vector<int>> lista_adyacencia;

public:
    explicit Grafo(int num_vertices);
    void agregar_arista(int origen, int destino);
    const std::vector<std::vector<int>>& obtener_lista_adyacencia() const;
    int obtener_num_vertices() const;
};


#endif //GRAFO_H
