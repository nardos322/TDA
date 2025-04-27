#ifndef GRAFO_PONDERADO_H
#define GRAFO_PONDERADO_H
#include <vector>
#include "igrafo_ponderado.h"
#include "types.h"

class GrafoPonderado final: public IGrafoPonderado {
private:
    std::vector<std::vector<AristaPonderada>> lista_adyacencia;
public:
    explicit GrafoPonderado(int num_vertices);
    void agregar_arista(int origen, int destino) override;
    bool existe_arista(int origen, int destino) const override;
    const std::vector<int> obtener_adyacentes(int vertice) const override;
    size_t obtener_num_vertices() const override;
    void agregar_arista(int origen, int destino, double peso) override;
    int obtener_peso(int origen, int destino) const override;
    [[nodiscard]] std::vector<std::vector<int>> obtener_lista_adyacencia() const override;
    [[nodiscard]] std::unique_ptr<IGrafo> obtener_transpuesto() const override;


};

#endif //GRAFO_PONDERADO_H
