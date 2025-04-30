#ifndef IGRAFO_H
#define IGRAFO_H
#include <memory>
#include <vector>



class IGrafo {
protected:
    static void validar_vertices(const int origen, const int destino , const size_t num_vertices) {
        if (origen < 0 || origen >= num_vertices ||
            destino < 0 || destino >= num_vertices) {
            throw std::out_of_range("Vertice fuera de rango");
        }
    }

    static void validar_vertice(const int vertice, const size_t num_vertices) {
        if (vertice < 0 || vertice >= num_vertices) {
            throw std::out_of_range("Vértice fuera de rango");
        }
    }

public:
    virtual ~IGrafo() = default;
    virtual void agregar_arista(int origen, int destino) = 0;
    [[nodiscard]] virtual bool existe_arista(int origen, int destino) const = 0;
    [[nodiscard]] virtual size_t obtener_num_vertices() const = 0;
    [[nodiscard]] virtual const std::vector<int> obtener_adyacentes(int vertice) const = 0;
    [[nodiscard]] virtual std::vector<std::vector<int>> obtener_lista_adyacencia() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IGrafo> obtener_transpuesto() const = 0;
    [[nodiscard]] virtual bool es_grafo_dirigido() const  = 0;
    [[nodiscard]] virtual bool es_grafo_ponderado() const = 0;

};



#endif //IGRAFO_H
