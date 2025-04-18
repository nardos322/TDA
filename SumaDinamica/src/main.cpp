#include <iostream>
#include <vector>
using namespace std;
// subset_sub es otra version de backtracking un poco mas clara pero las 2 funciones
//a continuacion son tecnicas de backtracking que hacen lo mismo




/**
 * @brief Determina si existe un subconjunto de un conjunto dado cuya suma sea igual a un valor objetivo.
 *
 * @param set Conjunto de números enteros.
 * @param parcial Vector que almacena temporalmente los elementos del subconjunto actual.
 * @param i Índice actual en el vector `set` que se está evaluando.
 * @param j Valor objetivo que se desea alcanzar con la suma de los elementos del subconjunto.
 * @return true Si existe al menos un subconjunto cuya suma es igual a `j`.
 * @return false Si no existe ningún subconjunto que cumpla con la condición.
 *
 * @details
 * La función utiliza un enfoque recursivo para explorar todas las combinaciones posibles de elementos
 * en el conjunto `set`. Si se encuentra un subconjunto cuya suma es igual a `j`, imprime los elementos
 * del subconjunto y retorna `true`. Si no, continúa explorando otras combinaciones. La función termina
 * cuando se han evaluado todos los elementos del conjunto.
 *
 * Casos base:
 * - Si `i` es 0 y `j` es 0, se imprime el subconjunto actual almacenado en `parcial` y se retorna `true`.
 * - Si `i` es 0 y `j` no es 0, se retorna `false`.
 *
 * Llamadas recursivas:
 * - Incluye el elemento actual (`set[i-1]`) en el subconjunto si no excede el valor objetivo `j`.
 * - Excluye el elemento actual y continúa evaluando el resto del conjunto.
 *
 * La función combina los resultados de ambas ramas (incluir o excluir el elemento actual) utilizando
 * el operador lógico OR.
 */
bool subset_sum(const vector<int>& set, vector<int>& parcial, int i, int j) {

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

    bool res = false;

    // 1. Rama "lo incluyo"
    if (j - set[i - 1] >= 0) {   // solo si no me paso del valor objetivo
        parcial.push_back(set[i - 1]);    // <- lo agrego
        res = subset_sum(set, parcial, i - 1, j - set[i - 1]) || res;
        parcial.pop_back();               // <- lo quito al volver
    }

    // 2. Rama "no lo incluyo"
    res = subset_sum(set, parcial, i - 1, j) || res;


    return res;
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
    vector<int> permutacion;
    backtrack(k, 0, 0, set, permutacion);
}


int main() {
    const vector<int> set = {1, 2, 3};
    vector<int> parcial;
    // subset_sum_k(set, 3);
    cout << subset_sum(set, parcial, set.size(), 7) << endl;



    return 0;
}