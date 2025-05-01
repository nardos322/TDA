#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include "igrafo.h"
#include "igrafo_ponderado.h"
#include "types.h"

/**
 * @brief Representa un grafo ponderado y/o dirigido utilizando una lista de adyacencia.
 *
 * La clase Grafo proporciona diversas funcionalidades para crear, manipular, y consultar
 * las propiedades de un grafo. Puede ser utilizado tanto para grafos dirigidos como no dirigidos,
 * y opcionalmente para grafos ponderados.
 *
 * Hereda de IGrafoPonderado y sobrescribe sus métodos.
 *
 *  Complejidades Tiempo:
 * - Construcción: O(|V|) donde |V| es el número de vértices
 * - Inserción de arista: O(1) amortizado
 * - Eliminación de arista: O(d) donde d es el grado del vértice
 * - Consulta de existencia de arista: O(d)
 * - Obtener adyacentes: O(d)
 * - Inserción de vértice: O(1) amortizado
 * - Eliminación de vértice: O(|V| + |E|) donde |E| es el número de aristas
 *
 * Uso de memoria: O(V + E)

 */
class Grafo final: public IGrafoPonderado {
private:
    std::vector<std::vector<Arista>> lista_adyacencia;
    bool es_ponderado;
    bool es_dirigido;

protected:
    /**
     * @brief Imprime la representación de la lista de adyacencia del grafo.
     *
     * Este método muestra la lista de adyacencia del grafo en el flujo de salida especificado,
     * lo que permite visualizar las conexiones entre los vértices.
     *
     * @param os Flujo de salida donde se imprimirá la lista de adyacencia. Por defecto, se utiliza std::cout.
     */
    void imprimir_lista_adyacencia(std::ostream& os = std::cout) const override;

    /**
     * @brief Imprime la matriz de adyacencia del grafo.
     *
     * Este método imprime la representación de la matriz de adyacencia
     * del grafo en el flujo de salida especificado.
     *
     * @param os Flujo de salida donde se imprimirá la matriz de adyacencia.
     *           Por defecto, es std::cout.
     */
    void imprimir_matriz_adyacencia(std::ostream& os = std::cout) const override;

    /**
     * @brief Constructor de la clase Grafo que inicializa un grafo con el número de vértices, y define si es ponderado y/o dirigido.
     *
     * Este constructor permite crear un grafo especificando el número de vértices. Además, establece si el grafo
     * es ponderado y/o dirigido. Lanza una excepción si el número de vértices proporcionado es negativo.
     *
     * @param num_vertices Número de vértices del grafo. Debe ser un valor no negativo.
     * @param ponderado Indica si el grafo es ponderado (true) o no ponderado (false).
     * @param dirigido Indica si el grafo es dirigido (true) o no dirigido (false).
     * @return No retorna ningún valor, ya que es un constructor.
     * @throws std::invalid_argument Si el número de vértices es negativo.
     */
public:
    /**
     * @brief Constructor que inicializa un grafo con un número específico de vértices.
     *
     * @param num_vertices Número inicial de vértices en el grafo
     * @param ponderado Indica si el grafo admite pesos en las aristas
     * @param dirigido Indica si las aristas tienen dirección
     *
     * @throws std::invalid_argument Si num_vertices es negativo
     *
     * @complexity Tiempo: O(|V|) para inicializar la lista de adyacencia
     * @complexity Espacio: O(|V|) para almacenar la estructura inicial
     */
    explicit Grafo(int num_vertices, bool ponderado = false, bool dirigido = true);

    /**
    * @brief Agrega una arista entre dos vértices en el grafo.
    *
    * Este método permite la creación de una conexión (arista) entre dos vértices
    * dados, especificados por sus índices. Si el grafo es dirigido, la arista será
    * creada desde el vértice de origen hacia el vértice de destino.
    *
    * @param origen Índice del vértice de origen.
    * @param destino Índice del vértice de destino.
    *
    * @complexity Tiempo: O(1) amortizado para la operacion push_back
    * @comlpexity Espacio: O(1)
    */
    void agregar_arista(int origen, int destino) override;

    /**
     * @brief Agrega una arista con un peso específico entre dos nodos.
     *
     * Este método permite añadir una arista al grafo ponderado, especificando
     * el nodo de origen, el nodo de destino y el peso asociado a la conexión.
     *
     * @param origen Nodo origen de la arista que será agregada.
     * @param destino Nodo destino de la arista que será agregada.
     * @param peso Valor del peso asociado a la nueva arista.
     *
     * @complexity Tiempo: O(1) amortizado para la operacion push_back
     * @complexity Espacio: O(1)
     */
    void agregar_arista(int origen, int destino, double peso) override;

    /**
    * @brief Agrega un nuevo vértice al grafo.
    *
    * Este método permite la adición de un vértice al grafo, incrementando
    * así el número total de vértices. La implementación específica del
    * comportamiento depende de la clase derivada.
    *
    * @complexity Tiempo: O(1) amortizado para la operacion push_back
    * @comlpexity Espacio: O(1)
    */
    void agregar_vertice() override;

    /**
    * @brief Elimina la arista entre dos vértices en el grafo.
    *
    * Este método elimina la conexión (arista) entre los vértices especificados
    * por los índices de origen y destino. Si el grafo es dirigido, la eliminación
    * afectará únicamente la dirección especificada (origen -> destino). Si el grafo
    * no es dirigido, eliminará la conexión en ambas direcciones.
    *
    * @param origen Índice del vértice de origen.
    * @param destino Índice del vértice de destino.
    *
    * @complexity Tiempo: O(d) donde d es el grado del vertice origen
    * @complexity Espacio: O(1)
    */
    void eliminar_arista(int origen, int destino) override;

    /**
    * @brief Elimina un vértice del grafo.
    *
    * Este método elimina un vértice especificado del grafo junto con todas
    * las aristas asociadas al mismo. El grafo se reorganiza según sea necesario
    * después de la eliminación del vértice.
    *
    * @param vertice Índice del vértice que se desea eliminar.
    *
    * @throws std::out_of_range Si el índice del vértice está fuera de los límites del grafo.
    *
    * @complexity Tiempo: O(|V| + |E|) donde |V| es el número de vértices y |E| es el número de aristas
    * @complexity Espacio: O(1)
    */
    void eliminar_vertice(int vertice) override;

    /**
    * @brief Elimina todo el contenido del grafo.
    *
    * Este método elimina todos los vértices y aristas presentes en el grafo,
    * dejando su estructura completamente vacía. Después de esta operación,
    * el grafo no contendrá ningún elemento, y su lista de adyacencia, matriz
    * de adyacencia o estructuras internas estarán vacías.
    *
    * @complexity Tiempo: O(|V| + |E|) donde |V| es el número de vértices y |E| es el número de aristas
    * @complexity Espacio: O(1)
    */
    void limpiar() override;

    /**
     * @brief Modifica el peso de la arista entre dos nodos.
     *
     * Este método permite actualizar el peso de una arista existente en el grafo,
     * especificada por su nodo de origen y nodo de destino.
     *
     * @param origen Nodo origen de la arista cuyo peso se desea modificar.
     * @param destino Nodo destino de la arista cuyo peso se desea modificar.
     * @param nuevo_peso Nuevo valor del peso a asignar a la arista.
     */
    void modificar_peso(int origen, int destino, double nuevo_peso) override;

    /**
    * @brief Comprueba la existencia de una arista entre dos vértices.
    *
    * Este método verifica si existe una conexión (arista) entre dos vértices
    * especificados por sus índices. La implementación depende de la clase
    * derivada y puede variar según el tipo de grafo (dirigido o no dirigido).
    *
    * @param origen Índice del vértice de origen.
    * @param destino Índice del vértice de destino.
    * @return true Si la arista entre los vértices existe.
    * @return false Si la arista entre los vértices no existe.
    *
    * @complexity Tiempo: O(d) donde d es el grado del vertice de origen
    * @complexity Espacio: O(1)
    */
    [[nodiscard]] bool existe_arista(int origen, int destino) const override;

    /**
    * @brief Obtiene las aristas asociadas a un vértice específico en el grafo.
    *
    * Este método devuelve una lista de aristas que están conectadas al vértice
    * especificado. La implementación depende del tipo de grafo (dirigido o no dirigido)
    * y puede variar según cómo se almacenen las aristas.
    *
    * @param vertice Índice del vértice para el cual se desean obtener las aristas.
    * @return std::vector<Arista> Lista de aristas conectadas al vértice especificado.
    */
    [[nodiscard]] std::vector<Arista> obtener_aristas(int vertice) const override;

    /**
    * @brief Obtiene el número total de vértices en el grafo.
    *
    * Este método devuelve la cantidad de vértices presentes en el grafo
    * en un momento dado. La implementación exacta de cómo se almacena y
    * se cuenta esta información depende de la clase derivada.
    *
    * @return size_t El número total de vértices en el grafo.
    */
    [[nodiscard]] size_t obtener_num_vertices() const override { return lista_adyacencia.size(); }

    /**
    * @brief Obtiene el número de aristas presentes en el grafo.
    *
    * Este método devuelve la cantidad total de aristas almacenadas en la estructura del grafo.
    * Es útil para conocer la densidad o tamaño del grafo.
    *
    * @return El número de aristas en el grafo.
    */
    [[nodiscard]] size_t otener_num_aristas() const override;

    /**
    * @brief Obtiene el grado de un vértice en el grafo.
    *
    * Este método retorna el número de aristas conectadas al vértice especificado.
    * Es útil para determinar la conectividad de un nodo en el grafo.
    *
    * @param vertice El identificador del vértice cuyo grado se desea obtener.
    * @return El grado del vértice indicado.
    */
    [[nodiscard]] int obtener_grado(int vertice) const override;

    /**
    * @brief Obtiene el grado de entrada de un vértice en el grafo.
    *
    * El grado de entrada de un vértice se define como el número de aristas que llegan al vértice especificado.
    * Esto es relevante únicamente en grafos dirigidos.
    *
    * @param vertice El identificador del vértice del cual se desea conocer el grado de entrada.
    * @return El grado de entrada del vértice especificado.
    */
    [[nodiscard]] int obtener_grado_entrada(int vertice) const override;

    /**
    * @brief Obtiene el grado de salida de un vértice específico en el grafo.
    *
    * Este método devuelve el número de aristas salientes desde un vértice dado.
    *
    * @param vertice El identificador del vértice del cual se desea obtener el grado de salida.
    * @return El grado de salida del vértice especificado.
    */
    [[nodiscard]] int obtener_grado_salida(int vertice) const override;


    /**
     * @brief Obtiene el peso de la arista entre dos vértices.
     *
     * Este método devuelve el peso de la arista que conecta los vértices de origen y destino
     * en el grafo. Si la arista no existe, lanza una excepción indicando el error.
     *
     * @param origen El vértice de origen de la arista.
     * @param destino El vértice de destino de la arista.
     * @return El peso de la arista que conecta los vértices especificados.
     * @throws std::runtime_error Si la arista entre los vértices no existe.
     */
    [[nodiscard]] double obtener_peso(int origen, int destino) const override;

    /**
     * @brief Obtiene los vértices adyacentes a un vértice dado.
     *
     * Este método devuelve una lista con los vértices que están directamente conectados
     * al vértice especificado. Es útil para realizar operaciones relacionadas con
     * el análisis o recorrido de grafos.
     *
     * @param vertice El vértice para el cual se desean obtener los vértices adyacentes.
     * @return Un vector constante que contiene los índices de los vértices adyacentes al vértice especificado.
     */
    [[nodiscard]] const std::vector<int> obtener_adyacentes(int vertice) const override;

    /**
    * @brief Obtiene la lista de adyacencia del grafo.
    *
    * Esta función retorna una representación del grafo como una lista de adyacencia,
    * donde cada índice del vector principal corresponde a un vértice y contiene un
    * vector con los vértices adyacentes a dicho vértice.
    *
    * @return Un vector de vectores de enteros que representa la lista de adyacencia del grafo.
    */
    [[nodiscard]] std::vector<std::vector<int>> obtener_lista_adyacencia() const override;

    /**
    * @brief Obtiene un grafo transpuesto basado en el grafo actual.
    *
    * Este método crea y devuelve un grafo transpuesto, donde todas las aristas
    * del grafo original tienen su dirección invertida. Se aplica principalmente
    * en algoritmos donde el grafo transpuesto es necesario para realizar análisis
    * y recorridos específicos.
    *
    * @return Un puntero único que contiene el grafo transpuesto.
    */
    [[nodiscard]] std::unique_ptr<IGrafo> obtener_transpuesto() const override;

    /**
    * @fn virtual bool esta_vacio() const = 0
    * @brief Verifica si el grafo está vacío.
    *
    * Este método comprueba si el grafo no contiene vértices ni aristas.
    *
    * @return true si el grafo está vacío, false en caso contrario.
    */
    [[nodiscard]] bool esta_vacio() const override;

    /**
    * @brief Verifica si el grafo es completo.
    *
    * Un grafo completo es aquel donde todos los vértices están conectados entre sí
    * mediante una arista. Esta función permite determinar si el grafo tiene esta propiedad.
    *
    * @return true si el grafo es completo, false en caso contrario.
    */
    [[nodiscard]] bool es_completo() const override;

    /**
    * @brief Determina si dos vértices son adyacentes en el grafo.
    *
    * Esta función verifica si existe una arista entre los vértices especificados.
    *
    * @param v1 El identificador del primer vértice.
    * @param v2 El identificador del segundo vértice.
    * @return true si los vértices son adyacentes, false en caso contrario.
    */
    [[nodiscard]] bool son_adyacentes(int v1, int v2) const override;

    /**
     * @brief Crea una copia profunda del grafo actual.
     *
     * Este método permite obtener un nuevo objeto que es una copia autónoma del grafo
     * original, incluyendo su estructura y propiedades. Garantiza que los cambios
     * realizados en el clon no afecten al grafo original ni viceversa.
     *
     * @return Un objeto único que contiene la copia profunda del grafo actual.
     */
    [[nodiscard]] std::unique_ptr<IGrafo> clonar() const override;

    /**
    * @brief Indica si el grafo es dirigido.
    *
    * Este método verifica si el grafo está configurado como un grafo dirigido,
    * es decir, un grafo en el que las aristas tienen una dirección definida.
    *
    * @return true si el grafo es dirigido, false en caso contrario.
    */
    [[nodiscard]] bool es_grafo_dirigido() const override { return es_dirigido; }

    /**
     * @brief Determina si el grafo es ponderado.
     *
     * Este método indica si el grafo tiene asignados pesos a sus aristas.
     * Los grafos ponderados asocian valores (pesos) a las conexiones entre vértices,
     * lo cual puede ser utilizado en varios algoritmos como los de rutas mínimas.
     *
     * @return true si el grafo es ponderado, false en caso contrario.
     */
    [[nodiscard]] bool es_grafo_ponderado() const override { return es_ponderado; }

    /**
     * @brief Imprime la representación del grafo.
     *
     * Esta función permite imprimir el grafo en un formato legible, ya sea utilizando
     * una matriz de adyacencia o una lista de adyacencia.
     *
     * @param usar_matriz Indica si se debe utilizar una matriz de adyacencia para la representación.
     *        Si es false, se usará una lista de adyacencia.
     * @param os Flujo de salida donde se imprimirá la representación del grafo. Por defecto, utiliza std::cout.
     */
    void imprimir_grafo(bool usar_matriz = false, std::ostream& os = std::cout) const override;

    /**
    * @brief Devuelve un iterador constante al inicio de la colección.
    *
    * Este método proporciona un iterador constante que apunta al primer elemento
    * de la colección asociada. Es útil para realizar recorridos en un contexto
    * constante donde no se pueden modificar los elementos.
    *
    * @return const_iterator Iterador constante al primer elemento de la colección.
    */
    [[nodiscard]] const_iterator begin() const override { return lista_adyacencia.begin(); }

    /**
     * @brief Devuelve el iterador constante al final de la colección de elementos del grafo.
     *
     * Este método proporciona un iterador constante que apunta al final
     * de la estructura de almacenamiento utilizada por el grafo,
     * permitiendo recorrer su contenido en operaciones de iteración.
     *
     * @return const_iterator Iterador constante que representa la posición
     * final en la colección de elementos.
     */
    [[nodiscard]] const_iterator end() const override { return lista_adyacencia.end(); }

    /**
     * @brief Devuelve un iterador al inicio de la colección.
     *
     * Este método proporciona un iterador que apunta al primer elemento
     * de la colección asociada a la instancia.
     *
     * @return iterator Un iterador que apunta al inicio de la colección.
     */
    [[nodiscard]] iterator begin() override { return lista_adyacencia.begin(); }

    /**
     * @brief Obtiene un iterador al final de la colección de elementos del grafo.
     *
     * Este método devuelve un iterador representando la posición final de la
     * colección, que no corresponde a ningún elemento válido.
     * Usar este iterador es útil para comparar límites en procesos de iteración.
     *
     * @return Un iterador al final de la colección de elementos del grafo.
     */
    [[nodiscard]] iterator end() override { return lista_adyacencia.end(); }
};


#endif //GRAFO_H
