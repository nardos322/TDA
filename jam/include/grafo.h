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
protected:
    void imprimir_lista_adyacencia(std::ostream& os = std::cout) const override;
    void imprimir_matriz_adyacencia(std::ostream& os = std::cout) const override;
public:
    explicit Grafo(int num_vertices, bool ponderado = false, bool dirigido = true);
    void agregar_arista(int origen, int destino) override;
    void agregar_arista(int origen, int destino, double peso) override;
    void agregar_vertice() override;
    void eliminar_arista(int origen, int destino) override;
    void eliminar_vertice(int vertice) override;
    [[nodiscard]] double obtener_peso(int origen, int destino) const override;
    [[nodiscard]] bool existe_arista(int origen, int destino) const override;
    [[nodiscard]] const std::vector<int> obtener_adyacentes(int vertice) const override;
    [[nodiscard]] std::vector<std::vector<int>> obtener_lista_adyacencia() const override;
    [[nodiscard]] std::unique_ptr<IGrafo> obtener_transpuesto() const override;
    [[nodiscard]] size_t obtener_num_vertices() const override { return lista_adyacencia.size();};
    [[nodiscard]] bool es_grafo_dirigido() const override { return es_dirigido; }
    [[nodiscard]] bool es_grafo_ponderado() const override { return es_ponderado; }
    void imprimir_grafo(bool usar_matriz = false, std::ostream& os = std::cout) const override;
};


#endif //GRAFO_H
