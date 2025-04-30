#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include "igrafo.h"
#include "igrafo_ponderado.h"
#include "types.h"

class Grafo final: public IGrafoPonderado {
private:
    std::vector<std::vector<Arista>> lista_adyacencia;
    bool es_ponderado;
    bool es_dirigido;

public:
    explicit Grafo(int num_vertices, bool ponderado = false, bool dirigido = true);
    void agregar_arista(int origen, int destino) override;
    void agregar_arista(int origen, int destino, double peso) override;
    [[nodiscard]] double obtener_peso(int origen, int destino) const override;
    [[nodiscard]] bool existe_arista(int origen, int destino) const override;
    [[nodiscard]] const std::vector<int> obtener_adyacentes(int vertice) const override;
    [[nodiscard]] std::vector<std::vector<int>> obtener_lista_adyacencia() const override;
    [[nodiscard]] std::unique_ptr<IGrafo> obtener_transpuesto() const override;
    [[nodiscard]] size_t obtener_num_vertices() const override { return lista_adyacencia.size();};
    [[nodiscard]] bool es_grafo_dirigido() const override { return es_dirigido; }
    [[nodiscard]] bool es_grafo_ponderado() const override { return es_ponderado; }

};


#endif //GRAFO_H
