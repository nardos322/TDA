#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "igrafo_ponderado.h"
#include "types.h"
#include <vector>
#include <algorithm>
#include <iomanip>

/**
* @class BellmanFord
* @brief Clase que implementa el algoritmo de Bellman-Ford para encontrar los
*        caminos mínimos desde un vértice origen a todos los demás vértices
*        en un grafo dirigido ponderado.
*
* Complejidad temporal: O(|V||E|)
* Complejidad espacial: O(|V|)
* Donde |v| es la cantidad de vértices y |E| es la cantidad de aristas del grafo.
*/
class BellmanFord {
private:
    const IGrafoPonderado& grafo;
    std::vector<Vertice> vertices;
    bool hay_ciclos_negativos = false;
    bool algortimo_ejecutado = false;

    /**
    * @brief Inicializa las distancias y predecesores de todos los vértices,
    *        estableciendo la distancia como 0 para el vértice origen.
    *
    * Este método se utiliza al inicio del algoritmo para configurar el estado inicial
    * de las estructuras de datos internas de la clase. Los vértices ya tienen sus
    * valores predeterminados establecidos por el constructor, excepto el vértice
    * de origen, cuya distancia se actualiza a 0.
    *
    * @param origen Identificador del vértice desde el cual se calcularán
    *               los caminos mínimos.
    */
    void initialize_single_source(const int origen) {
        // Los vertices ya están inicializados con INFINITO y SIN_PREDECESOR por el constructor
        vertices[origen].distancia = 0;
    }

    /**
    * @brief Relaja la arista entre dos vértices si se encuentra un camino
    *        más corto desde el vértice origen al destino.
    *
    * El método actualiza la distancia y el predecesor del vértice destino si
    * la suma del peso de la arista y la distancia al vértice origen resulta
    * en un valor menor para la distancia actual del vértice destino.
    *
    * @param u Vértice de origen desde el cual se está relajando la arista.
    * @param v Vértice de destino al cual se está verificando si se puede reducir
    *          la distancia mediante la relajación de la arista.
    */
    void relax(const int u, const int v) {
        if (const double peso_u_v = grafo.obtener_peso(u, v);
            vertices[v].distancia > vertices[u].distancia + peso_u_v) {
            vertices[v].distancia = vertices[u].distancia + peso_u_v;
            vertices[v].predecesor = u;
        }
    }

    /**
    * @brief Valida que el algoritmo se haya ejecutado y no haya ciclos negativos
    * @throws std::runtime_error Si las condiciones no se cumplen
    */
    void validar_estado() const {
        if (!algortimo_ejecutado) {
            throw std::runtime_error("Debe ejecutar encontrar_camino_minimo() primero");
        }
        if (hay_ciclos_negativos) {
            throw std::runtime_error("El grafo tiene ciclos negativos");
        }
    }

public:
    /**
    * @brief Constructor de la clase BellmanFord que inicializa el algoritmo con un grafo dirigido ponderado.
    *
    * @param g Referencia a un objeto que implementa la interfaz IGrafoPonderado. Representa el grafo a procesar.
    *
    * @throws std::invalid_argument Si el grafo proporcionado no contiene vértices.
    */
    explicit BellmanFord(const IGrafoPonderado& g) : grafo(g) {
        if (g.obtener_num_vertices() == 0) {
            throw std::invalid_argument("El grafo no tiene vertices");
        }
        vertices.resize(g.obtener_num_vertices());
    }


    /**
    * @brief Encuentra los caminos mínimos desde un vértice origen a todos los demás
    *        vértices en un grafo dirigido ponderado utilizando el algoritmo de
    *        Bellman-Ford.
    *
    * Este método implementa los pasos principales del algoritmo de Bellman-Ford, que
    * incluyen la inicialización de las distancias para el vértice origen, la relajación
    * de las aristas repetidamente y la detección de ciclos negativos en el grafo.
    * Si se detecta un ciclo negativo, lanza una excepción.
    *
    * @param origen Identificador del vértice desde el cual se calcularán los caminos mínimos.
    *               Debe estar dentro del rango de los identificadores válidos de vértices
    *               del grafo. Si el vértice está fuera de rango, lanza std::invalid_argument.
    *
    * @throws std::invalid_argument Si el vértice origen está fuera del rango permitido.
    * @throws std::runtime_error Si se detecta un ciclo negativo en el grafo.
    */
    void encontrar_camino_minimo(const int origen) {
        if (origen < 0 || origen >= grafo.obtener_num_vertices()) {
            throw std::invalid_argument("Vértice origen fuera de rango");
        }

        initialize_single_source(origen);
        const int num_vertices = grafo.obtener_num_vertices();

        // Relajacion de aristas |V| - 1 veces
        for (int i = 1; i < num_vertices; i++) {
            // Para cada arista (u,v) ∈ G.E
            for (int u = 0; u < num_vertices; u++) {
                for (const int v: grafo.obtener_adyacentes(u)) {
                    relax(u, v);
                }
            }
        }

        // Verificacion de ciclos negativos
        for (int u = 0; u < num_vertices; u++) {
            for (const int v: grafo.obtener_adyacentes(u)) {
                const double peso_u_v = grafo.obtener_peso(u, v);
                if (vertices[v].distancia > vertices[u].distancia + peso_u_v) {
                    hay_ciclos_negativos = true;
                    throw std::runtime_error("El grafo tiene ciclos negativos");
                }
            }
        }

        algortimo_ejecutado = true;
    }


    /**
    * @brief Obtiene la distancia mínima desde el vértice origen al vértice
    *        especificado en un grafo dirigido ponderado.
    *
    * La distancia representa el peso acumulado del camino más corto calculado
    * previamente con el algoritmo de Bellman-Ford.
    *
    * @param vertice Identificador del vértice cuyo valor de distancia se desea obtener.
    * @return La distancia mínima desde el vértice origen al vértice especificado.
    *
    * @throws std::out_of_range Si el índice del vértice está fuera de los límites válidos.
    * @throws std::logic_error Si el estado interno del objeto no es válido para esta operación.
    */
    [[nodiscard]] double obtener_distancia(const int vertice) const {
        validar_estado();
        return vertices[vertice].distancia;
    }


    /**
    * @brief Recupera el camino más corto desde el vértice origen hasta el vértice destino
    *        utilizando los predecesores calculados por el algoritmo de Bellman-Ford.
    *
    * Este método devuelve el camino como una secuencia de vértices en orden desde el origen
    * hasta el destino. Se basa en los datos de predecesores almacenados en la clase.
    * Si no existe un camino hacia el destino, la lista devuelta estará vacía.
    *
    * @param destino Identificador del vértice de destino al que se desea recuperar
    *                el camino más corto. Debe pertenecer al rango válido de vértices
    *                del grafo.
    *
    * @return std::vector<int> Secuencia de identificadores de vértices que representan
    *                          el camino más corto desde el origen hasta el destino,
    *                          en caso de existir. Si no hay un camino, se devuelve un vector vacío.
    *
    * @throws std::logic_error Si el algoritmo de Bellman-Ford no ha sido ejecutado previamente
    *                          para calcular los caminos mínimos.
    */
    [[nodiscard]] std::vector<int> obtener_camino(const int destino) const {
        validar_estado();
        std::vector<int> camino;
        for (int v = destino; v != SIN_PREDECESOR; v = vertices[v].predecesor) {
            camino.push_back(v);
        }
        std::ranges::reverse(camino);
        return camino;
    }


    /**
    * @brief Recupera todos los caminos más cortos desde el vértice origen hasta
    *        todos los demás vértices en el grafo.
    *
    * Este método utiliza los predecesores calculados por el algoritmo de Bellman-Ford
    * para construir los caminos de todos los vértices accesibles desde el origen.
    * Cada camino se representa como una secuencia de identificadores de vértices,
    * en orden desde el origen hasta el destino correspondiente. Si no existe un
    * camino hacia un vértice, la lista asociada será un vector vacío.
    *
    * @return std::vector<std::vector<int>> Una lista de caminos, donde cada elemento
    *                                       es un vector que representa el camino más
    *                                       corto desde el origen hasta un vértice
    *                                       específico. Si algún vértice no es accesible,
    *                                       ese camino será un vector vacío.
    *
    * @throws std::logic_error Si el algoritmo de Bellman-Ford no ha sido ejecutado previamente
    *                          para calcular los caminos mínimos.
    */
    [[nodiscard]] std::vector<std::vector<int>> obtener_todos_caminos() const {
        validar_estado();
        std::vector<std::vector<int>> caminos;
        caminos.reserve(vertices.size());
        for (int i = 0; i < vertices.size(); i++) {
            caminos.push_back(obtener_camino(i));
        }
        return caminos;
    }

    void reiniciar() {
        vertices = std::vector<Vertice>(grafo.obtener_num_vertices());
        hay_ciclos_negativos = false;
        algortimo_ejecutado = false;
    }

    [[nodiscard]] bool tiene_ciclos_negativos() const {
        return hay_ciclos_negativos;
    }

    [[nodiscard]] int obtener_origen() const {
        validar_estado();
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].distancia == 0) return i;
        }
        return SIN_PREDECESOR;
    }

    void imprimir_camino(const int destino, std::ostream& out = std::cout) const {
        validar_estado();
        const std::vector<int> camino = obtener_camino(destino);
        if (camino.empty()) {
            out << "No existe camino al vertice " << destino << "\n";
            return;
        }

        out << "Camino al vertice " << destino << " (distancia total: "
                << vertices[destino].distancia << "):\n ";

        for (size_t i = 0; i < camino.size() - 1; i++) {
            out << camino[i] << " --("
                    << grafo.obtener_peso(camino[i], camino[i + 1])
                    << ")-> ";
        }

        out << camino.back() << "\n";
    }

    void imprimir_todos_caminos(std::ostream& out = std::cout) const {
        validar_estado();

        out << "Resultados del algoritmo Bellman-Ford:\n";
        out << "======================================\n";

        const int origen = obtener_origen();
        out << "Vertice origen: " << origen << "\n\n";

        for (int i = 0; i < vertices.size(); i++) {
            if (i != origen) {
                imprimir_camino(i, out);
            }
        }
    }

    void imprimir_distancia(const int vertice, std::ostream& out = std::cout) const {
        validar_estado();

        out << "\nDistancia al vertice " << vertice << ": ";
        if (vertices[vertice].distancia == INFINITO) {
            out << "INF";
        } else {
            out << std::fixed << std::setprecision((1)) << vertices[vertice].distancia;
        }
        out << "\n";
    }

    void imprimir_tabla_distancias(std::ostream& out = std::cout) const {
        validar_estado();

        if (vertices.empty()) {
            out << "\nTabla vacia - no hay vertices\n";
            return;
        }

        // Configuramos formato de salida
        out << std::fixed << std::setprecision((1));

        out << "\nTabla de distancias:\n";
        out << std::setw(8) << "Vertice" << std::setw(12) << "Distancia"
                << std::setw(12) << "Predecesor\n";
        out << std::string(32, '-') << '\n';

        for (size_t i = 0; i < vertices.size(); i++) {
            out << std::setw(8) << i;
            if (vertices[i].distancia == INFINITO) {
                out << std::setw(12) << "INF";
            } else {
                out << std::setw(12) << vertices[i].distancia;
            }
            out << std::setw(12)
                    << (vertices[i].predecesor == SIN_PREDECESOR
                            ? "N/A"
                            : std::to_string(vertices[i].predecesor)) << '\n';
        }
    }
};

#endif //BELLMANFORD_H
