#ifndef GRAFO_H
#define GRAFO_H
#include <vector>

class Grafo {
private:
    std::vector<std::vector<int>> lista_adyacencia;

public:
    explicit Grafo(int num_vertices);
    void agregar_arista(int origen, int destino);
    [[nodiscard]] const std::vector<std::vector<int>>& obtener_lista_adyacencia() const;
    [[nodiscard]] int obtener_num_vertices() const;
    [[nodiscard]] Grafo obtener_transpuesto() const;
};


#endif //GRAFO_H
