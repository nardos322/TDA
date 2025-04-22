#include <iostream>
#include <vector>
using namespace std;



/**
 * @brief Determina si existe un subconjunto de un conjunto dado cuya suma sea igual a un valor objetivo.
 *
 * @param set Conjunto de números enteros.
 * @param parcial Vector que almacena temporalmente los elementos del subconjunto actual.
 * @param memo Matriz de memoización para almacenar resultados de subproblemas ya calculados.
 * @param i Índice actual en el vector `set` que se está evaluando.
 * @param j Valor objetivo que se desea alcanzar con la suma de los elementos del subconjunto.
 * @return true Si existe al menos un subconjunto cuya suma es igual a `j`.
 * @return false Si no existe ningún subconjunto que cumpla con la condición.
 *
 * @details
 * La función utiliza un enfoque de programación dinámica con memoización para optimizar la búsqueda
 * de subconjuntos cuya suma sea igual a un valor objetivo. Explora recursivamente todas las combinaciones
 * posibles de elementos en el conjunto `set`. Si se encuentra un subconjunto cuya suma es igual a `j`,
 * imprime los elementos del subconjunto y retorna `true`. Si no, continúa explorando otras combinaciones.
 *
 * Casos base:
 * - Si `j` es menor que 0, retorna `false` porque no es posible alcanzar un valor objetivo negativo.
 * - Si `i` es 0 y `j` es 0, imprime el subconjunto actual almacenado en `parcial` y retorna `true`.
 * - Si `i` es 0 y `j` no es 0, retorna `false`.
 *
 * Llamadas recursivas:
 * - Incluye el elemento actual (`set[i-1]`) en el subconjunto si no excede el valor objetivo `j`.
 * - Excluye el elemento actual y continúa evaluando el resto del conjunto.
 *
 * La función combina los resultados de ambas ramas (incluir o excluir el elemento actual) utilizando
 * el operador lógico OR. Los resultados se almacenan en la matriz `memo` para evitar cálculos redundantes.
 */
bool subset_sum_topDown(const vector<int>& set, vector<int>& parcial, vector<vector<int>>& memo, int i, int j) {
    if (j < 0) return false;   // si me pase de la suma, no sirve
    if (i == 0) {
        if (j == 0) {   // solucion encontrada!
            for (const int n : parcial) {
                cout << n << " ";
            }
            cout << endl;
            return true;       // si solo queres uno, crotamos aca
        }
        return false;
    }

    if (memo[i][j] == -1) {
        bool incluir = false;
        if (j - set[i - 1] >= 0) {   // solo si no me paso del valor objetivo
            parcial.push_back(set[i - 1]);    // <- lo agrego
            incluir = subset_sum_topDown(set, parcial, memo, i - 1, j - set[i - 1]);
            if (incluir) return true;        // si ya encontre una solucion, no sigo buscando
            parcial.pop_back();               // <- lo quito al volver
        }

        bool no_incluir = subset_sum_topDown(set, parcial, memo, i - 1, j);
        if (no_incluir) return true;     // si ya encontre una solucion, no sigo buscando
        memo[i][j] = incluir || no_incluir;
    }
    return memo[i][j];
}


/**
 * @brief Determina si existe un subconjunto de un conjunto dado cuya suma sea igual a un valor objetivo utilizando un enfoque iterativo.
 *
 * @param set Conjunto de números enteros.
 * @param k Valor objetivo que se desea alcanzar con la suma de los elementos del subconjunto.
 * @return true Si existe al menos un subconjunto cuya suma es igual a `k`.
 * @return false Si no existe ningún subconjunto que cumpla con la condición.
 *
 * @details
 * La función utiliza programación dinámica para construir una tabla `dp` donde `dp[i][j]` indica si es posible
 * obtener una suma `j` utilizando los primeros `i` elementos del conjunto `set`. Se llena la tabla iterativamente
 * considerando dos opciones para cada elemento:
 * - Incluir el elemento actual en el subconjunto si no excede la suma objetivo.
 * - No incluir el elemento actual en el subconjunto.
 *
 * Una vez completada la tabla, si `dp[n][k]` es `true`, se reconstruye el subconjunto que cumple con la condición
 * y se imprime. Si no es posible formar la suma `k`, la función retorna `false`.
 *
 * Casos base:
 * - Es posible obtener una suma de 0 con 0 elementos (`dp[0][0] = true`).
 *
 * Complejidad:
 * - Tiempo: O(n * k), donde `n` es el tamaño del conjunto y `k` es el valor objetivo.
 * - Espacio: O(n * k) debido a la tabla `dp`.
 */

bool subset_sum_bottomUp(const vector<int>& set, int k) {
    int n = set.size();
    // dp[i][j] indica si es posible obtener una suma `j` utilizando los primeros `i` elementos del conjunto.
    vector<vector<bool>> dp(set.size() + 1, vector<bool>(k + 1, false));

    // Caso base: Es posible obtener una suma de 0 con 0 elementos.
    dp[0][0] = true;

    // Llenado de la tabla dp
    for (int i = 1; i <= n; i++) { // Iteramos sobre los elementos del conjunto
        for (int j = 0; j <= k; j++) { // Iteramos sobre las posibles sumas desde 0 hasta k
            // Opción 1: Usar el elemento actual si no excede la suma objetivo
            bool incluir = (j >= set[i - 1]) && dp[i - 1][j - set[i - 1]];
            // Opción 2: No usar el elemento actual
            bool no_incluir = dp[i - 1][j];
            // Actualizamos dp[i][j] considerando ambas opciones
            dp[i][j] = incluir || no_incluir;
        }
    }

    // Si es posible formar la suma `k`, reconstruimos el subconjunto
    if (dp[n][k]) {
        int j = k;
        vector<int> parcial;
        // Reconstrucción del subconjunto a partir de la tabla dp
        for (int i = n; i > 0 && j > 0; i--) {
            // Si el elemento actual fue usado en la solución
            if (dp[i][j] && !dp[i - 1][j]) {
                parcial.push_back(set[i - 1]); // Añadimos el elemento al subconjunto
                j -= set[i - 1]; // Reducimos la suma objetivo
            }
        }

        // Imprimimos el subconjunto encontrado
        for (int i = 0; i < parcial.size(); i++) {
            cout << parcial[i] << " ";
        }
        return true;
    }

    // Si no es posible formar la suma `k`, retornamos false
    return false;
}


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
 */
bool backtrack(const int k, int i, int suma, const vector<int>& set, vector<int>& parcial) {

    if (suma == k) {
        for (const int n : parcial) {
            cout << n << " ";
        }
        cout << endl;
        return true;
    };

    if (suma > k) return false;

    bool res = false;
    for (int j = i; j < set.size(); j++) {
        parcial.push_back(set[j]);
        res = backtrack(k, j + 1, suma + set[j], set, parcial) || res;
        parcial.pop_back();
    }

    return res;
}

/**
 *
 * @param set Conjunto de numeros enteros
 * @param k Valor objetivo que tiene que alcancar la suma de los elementos del subconjunto
 */
void subset_sum_k(const vector<int>& set, int k) {
    vector<int> sub_set;
    backtrack(k, 0, 0, set, sub_set);
}


int main() {
    const vector<int> set = {3,1,2,5,5};
    int j = 13;
    vector<int> parcial;
    vector<vector<int>> memo(set.size() + 1, vector<int>(j + 1, -1));
    // subset_sum_k(set, j);
    // subset_sum_topDown(set, parcial, memo, set.size(), j);
    subset_sum_bottomUp(set, j);



    return 0;
}