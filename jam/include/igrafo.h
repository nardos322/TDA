#ifndef IGRAFO_H
#define IGRAFO_H
#include <iostream>
#include <memory>
#include <vector>
#include "types.h"


/**
 * @brief Valida que un vértice sea válido dentro de los límites del grafo.
 *
 * Este método comprueba que el índice del vértice esté dentro del
 * rango permitido por el número total de vértices del grafo.
 * Si el índice está fuera del rango, lanza una excepción de tipo std::out_of_range.
 *
 * @param vertice Índice del vértice a validar.
 * @param num_vertices Cantidad total de vértices en el grafo.
 *
 * @throws std::out_of_range Si el índice del vértice está fuera del rango válido.
 */

class IGrafo {
protected:
    /**
    * @brief Valida que dos vértices sean válidos dentro de los límites de un grafo.
    *
    * Esta función comprueba que los índices de los vértices de origen y destino
    * estén dentro del rango permitido por el número total de vértices del grafo.
    * Si alguno de los índices está fuera del rango, lanza una excepción de tipo
    * std::out_of_range.
    *
    * @param origen Índice del vértice de origen.
    * @param destino Índice del vértice de destino.
    * @param num_vertices Cantidad total de vértices en el grafo.
    *
    * @throws std::out_of_range Si los índices de los vértices están fuera del rango válido.
    */
    static void validar_vertices(const int origen, const int destino, const size_t num_vertices) {
        if (origen < 0 || origen >= num_vertices ||
            destino < 0 || destino >= num_vertices) {
            throw std::out_of_range("Vertice fuera de rango");
        }
    }

    /**
     * @brief Verifica que un vértice sea válido dentro de un rango de vértices permitido.
     *
     * Este método valida si el índice del vértice proporcionado está dentro del rango
     * válido definido por la cantidad total de vértices en el grafo. Si no lo está,
     * lanza una excepción de tipo std::out_of_range.
     *
     * @param vertice Índice del vértice a verificar.
     * @param num_vertices Número total de vértices en el grafo.
     *
     * @throws std::out_of_range Si el índice del vértice no está dentro del rango válido.
     */
    static void validar_vertice(const int vertice, const size_t num_vertices) {
        if (vertice < 0 || vertice >= num_vertices) {
            throw std::out_of_range("Vértice fuera de rango");
        }
    }

    virtual void imprimir_lista_adyacencia(std::ostream& os = std::cout) const = 0;

    virtual void imprimir_matriz_adyacencia(std::ostream& os = std::cout) const = 0;

public:
    /**
    * @brief Destructor virtual para la clase IGrafo.
    *
    * Este destructor permite que la clase IGrafo actúe como una interfaz base polimórfica.
    * Garantiza que los destructores de las clases derivadas sean llamados correctamente
    * al destruir un objeto a través de un puntero a IGrafo.
    */
    virtual ~IGrafo() = default;
    virtual void agregar_arista(int origen, int destino) = 0;
    virtual void agregar_vertice() = 0;
    virtual void eliminar_arista(int origen, int destino) = 0;
    virtual void eliminar_vertice(int vertice) = 0;
    virtual void limpiar() = 0;
    [[nodiscard]] virtual bool existe_arista(int origen, int destino) const = 0;
    [[nodiscard]] virtual std::vector<Arista> obtener_aristas(int vertice) const = 0;
    [[nodiscard]] virtual size_t obtener_num_vertices() const = 0;
    [[nodiscard]] virtual size_t otener_num_aristas() const = 0;
    [[nodiscard]] virtual int obtener_grado(int vertice) const = 0;
    [[nodiscard]] virtual int obtener_grado_entrada(int vertice) const = 0;
    [[nodiscard]] virtual int obtener_grado_salida(int vertice) const = 0;
    [[nodiscard]] virtual const std::vector<int> obtener_adyacentes(int vertice) const = 0;
    [[nodiscard]] virtual std::vector<std::vector<int>> obtener_lista_adyacencia() const = 0;
    [[nodiscard]] virtual std::unique_ptr<IGrafo> obtener_transpuesto() const = 0;
    [[nodiscard]] virtual bool esta_vacio() const = 0;
    [[nodiscard]] virtual bool es_completo() const = 0;
    [[nodiscard]] virtual bool es_grafo_dirigido() const = 0;
    [[nodiscard]] virtual bool es_grafo_ponderado() const = 0;
    [[nodiscard]] virtual bool son_adyacentes(int v1, int v2) const = 0;
    [[nodiscard]] virtual std::unique_ptr<IGrafo> clonar() const = 0;
    virtual void imprimir_grafo(bool usar_matriz = false, std::ostream& os = std::cout) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const IGrafo& grafo);

    // Metodos de iteracion
    using const_iterator = std::vector<std::vector<Arista>>::const_iterator;
    using iterator = std::vector<std::vector<Arista>>::iterator;
    [[nodiscard]] virtual const_iterator begin() const = 0;
    [[nodiscard]] virtual const_iterator end() const = 0;
    [[nodiscard]] virtual iterator begin() = 0;
    [[nodiscard]] virtual iterator end() = 0;
};


inline std::ostream& operator<<(std::ostream& os, const IGrafo& grafo) {
    grafo.imprimir_grafo(false, os);
    return os;
}


#endif //IGRAFO_H
