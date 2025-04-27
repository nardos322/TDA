#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include "igrafo.h"
#include "types.h"

class Grafo final: public IGrafo {
private:
    std::vector<std::vector<Arista>> lista_adyacencia;

public:
    explicit Grafo(int num_vertices);
    void agregar_arista(int origen, int destino) override;
    [[nodiscard]] bool existe_arista(int origen, int destino) const override;
    [[nodiscard]] const std::vector<int> obtener_adyacentes(int vertice) const override;
    [[nodiscard]] size_t obtener_num_vertices() const override;
    [[nodiscard]] std::vector<std::vector<int>> obtener_lista_adyacencia() const override;
    [[nodiscard]] std::unique_ptr<IGrafo> obtener_transpuesto() const override;

};


#endif //GRAFO_H
