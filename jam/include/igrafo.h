#ifndef IGRAFO_H
#define IGRAFO_H
#include <iostream>
#include <memory>
#include <vector>
#include "types.h"


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

    virtual void imprimir_lista_adyacencia(std::ostream& os = std::cout) const = 0;
    virtual void imprimir_matriz_adyacencia(std::ostream& os = std::cout) const = 0;
public:
    virtual ~IGrafo() = default;
    virtual void agregar_arista(int origen, int destino) = 0;
    virtual void agregar_vertice() = 0;
    virtual void eliminar_arista(int origen, int destino) = 0;
    virtual void eliminar_vertice(int vertice) = 0;
    // virtual void limpiar() = 0;
    [[nodiscard]] virtual bool existe_arista(int origen, int destino) const = 0;
    // [[nodiscard]] virtual std::vector<Arista> obtener_aristas() const = 0;
    [[nodiscard]] virtual size_t obtener_num_vertices() const = 0;
    // [[nodiscard]] virtual size_t otener_num_aristas() const = 0;
    [[nodiscard]] virtual const std::vector<int> obtener_adyacentes(int vertice) const = 0;
    [[nodiscard]] virtual std::vector<std::vector<int>> obtener_lista_adyacencia() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IGrafo> obtener_transpuesto() const = 0;
    // [[nodiscard]] virtual int obtener_grado(int vertice) const = 0;
    // [[nodiscard]] virtual int obtener_grado_entrada(int vertice) = 0;
    // [[nodiscard]] virtual int obtener_grado_salida(int vertice) = 0;
    // [[nodiscard]] virtual bool esta_vacio() const = 0;
    // [[nodiscard]] virtual bool es_completo() const = 0;
    [[nodiscard]] virtual bool es_grafo_dirigido() const  = 0;
    [[nodiscard]] virtual bool es_grafo_ponderado() const = 0;
    // [[nodiscard]] virtual bool son_adyacentes(int v1, int v2) const = 0;
    // [[nodiscard]] virtual std::unique_ptr<IGrafo> clonar() const = 0;
    virtual void imprimir_grafo(bool usar_matriz = false, std::ostream& os = std::cout) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const IGrafo& grafo);
};

inline std::ostream& operator<<(std::ostream& os, const IGrafo& grafo) {
    grafo.imprimir_grafo(false, os);
    return os;
}






#endif //IGRAFO_H
