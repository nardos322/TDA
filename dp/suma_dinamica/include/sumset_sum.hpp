#ifndef SUMSET_SUM_HPP
#define SUMSET_SUM_HPP
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief Estructura que almacena el resultado de la búsqueda de un subconjunto suma.
 *
 * @details
 * Esta estructura contiene dos miembros:
 * - exists: Indica si se encontró un subconjunto que suma el valor objetivo
 * - subset: Vector que almacena los elementos del subconjunto encontrado (si existe)
 */

struct SubsetSumResult {
    bool exists;
    vector<int> subset;
};



/**
 * @brief Realiza una búsqueda recursiva para determinar si existe un subconjunto cuya suma sea igual a un valor objetivo.
 *
 * @param set Conjunto de números enteros.
 * @param parcial Subconjunto parcial construido durante la búsqueda.
 * @param memo Matriz de memoización utilizada para almacenar cálculos previos y evitar redundancia.
 * @param i Índice actual en el conjunto `set`.
 * @param j Suma objetivo restante que se desea alcanzar.
 * @return SubsetSumResult Estructura que indica si existe un subconjunto válido y contiene el subconjunto encontrado.
 *
 * @details
 * Esta función utiliza un enfoque recursivo con memoización para optimizar el cálculo. En cada llamada, considera
 * dos posibilidades:
 * - Incluir el elemento actual en el subconjunto parcial y reducir `j` en el valor del elemento.
 * - No incluir el elemento actual, manteniendo `j` sin cambios.
 *
 * La matriz `memo` almacena el resultado de subproblemas ya calculados en las posiciones `memo[i][j]`.
 * Si `j` es negativo, se retorna `false` como caso base. Si llegamos a `i == 0`, verificamos si `j == 0` para
 * determinar si la suma objetivo se alcanzó.
 *
 * Casos base:
 * - Cuando `j < 0`, no es posible formar un subconjunto válido.
 * - Cuando `i == 0`, la suma `j` debe ser 0 para que exista una solución.
 *
 * Complejidad:
 * - Tiempo: O(n * k), donde `n` es el tamaño del conjunto y `k` es la suma objetivo.
 * - Espacio: O(n * k) debido a la matriz `memo` y la pila de llamadas recursivas.
 */
SubsetSumResult recursive_search(const vector<int>& set, vector<int>& parcial, vector<vector<int>>& memo, int i, int j);


/**
 * @brief Determina si existe un subconjunto dentro de un conjunto dado cuya suma sea igual a un valor objetivo utilizando un enfoque recursivo con memoización.
 *
 * @param set Conjunto de números enteros.
 * @param k Suma objetivo que se desea alcanzar.
 * @return SubsetSumResult Estructura que contiene un indicador de éxito y el subconjunto encontrado (si existe).
 *
 * @details
 * Este método implementa la resolución del problema de la suma de subconjuntos utilizando la estrategia top-down, delegando
 * el trabajo principal a la función auxiliar `recursive_search`.
 * - Si el conjunto está vacío, se verifica si el valor objetivo `k` es igual a 0.
 * - Si el valor objetivo `k` es menor que 0, el resultado será falso, ya que no se pueden formar subconjuntos válidos.
 *
 * Internamente, este método inicializa una tabla de memoización y un vector parcial que es utilizado por la función recursiva
 * para explorar todas las posibles combinaciones de subconjuntos.
 *
 * Complejidad:
 * - Tiempo: O(n * k), donde `n` es el tamaño del conjunto y `k` es la suma objetivo.
 * - Espacio: O(n * k) debido al almacenamiento de la matriz de memoización y el uso de la pila de llamadas recursivas.
 */
SubsetSumResult subset_sum_topDown(const vector<int>& set, int k);

/**
 * @brief Implementa el algoritmo de programación dinámica para resolver el problema de la suma de subconjuntos.
 *
 * @param set Vector de enteros que representa el conjunto de números.
 * @param k Suma objetivo que se desea formar con los elementos del subconjunto.
 * @return SubsetSumResult Estructura que indica si existe un subconjunto cuya suma sea igual a `k` y, de ser posible,
 * contiene el subconjunto encontrado.
 *
 * @details
 * Esta función utiliza un enfoque Bottom-Up basado en programación dinámica. Construye una tabla `dp` donde
 * `dp[i][j]` indica si es posible obtener una suma `j` utilizando los primeros `i` elementos del conjunto `set`.
 *
 * Proceso:
 * - La tabla `dp` se inicializa con valores base, considerando que se puede obtener la suma de 0 siempre
 *   con un subconjunto vacío.
 * - Cada celda de la tabla se llena iterativamente evaluando si se incluye o no el elemento actual del conjunto.
 * - Si la suma objetivo no es alcanzable tras llenar la tabla, se retorna `false`.
 * - Si es posible formar la suma, se reconstruye el subconjunto a partir de la tabla.
 *
 * Complejidad:
 * - Tiempo: O(n * k), donde `n` es el tamaño del conjunto y `k` es la suma objetivo.
 * - Espacio: O(n * k) debido a la matriz `dp`.
 */
SubsetSumResult subset_sum_bottomUp(const vector<int>& set, int k);


/**
 * @brief Realiza una búsqueda por retroceso para encontrar subconjuntos cuya suma sea igual a un valor dado.
 *
 * @param k El valor objetivo que se desea alcanzar con la suma de los elementos del subconjunto.
 * @param i El índice actual en el vector `set` desde donde se evalúan los elementos.
 * @param suma La suma acumulada de los elementos seleccionados hasta el momento.
 * @param set El conjunto de números enteros disponibles para formar subconjuntos.
 * @param parcial Un vector que almacena temporalmente los elementos del subconjunto actual.
 * @return true Si se encuentra al menos un subconjunto cuya suma sea igual a `k`.
 * @return false Si no se encuentra ningún subconjunto que cumpla con la condición.
 *
 * @details
 * La función utiliza un enfoque de retroceso (backtracking) para explorar todas las combinaciones posibles
 * de elementos en el conjunto `set`. Si la suma acumulada (`suma`) es igual a `k`, imprime el subconjunto
 * actual almacenado en `parcial` y retorna `true`. Si la suma acumulada excede `k`, la función retorna
 * `false` y retrocede. La función explora recursivamente todas las combinaciones posibles a partir del índice
 * actual `i`.
 *
 * Complejidad: O(2^n), donde `n` es el tamaño del conjunto, ya que en el peor de los casos se generan todas las combinaciones posibles.
 */
bool backtrack(const int k, int i, int suma, const vector<int>& set, vector<int>& parcial);

#endif //SUMSET_SUM_HPP
