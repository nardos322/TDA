#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * \brief Constante utilizada como un valor de desplazamiento para manejar índices
 *        negativos o valores acumulados en el algoritmo de memoización.
 *
 * En el contexto del algoritmo de backtracking con memoización, `OFFSET` se utiliza
 * para ajustar los valores acumulados (que pueden ser negativos) a un rango positivo,
 * permitiendo que se almacenen de manera segura como claves en el mapa de memoización.
 *
 * \note El valor de 2005 es arbitrario y debe ser lo suficientemente grande para
 *       cubrir los posibles valores negativos acumulados en el problema.
 */
constexpr int OFFSET = 2005;


long long factorial(const int n) {
    vector<long long> dp(n + 1);
    dp[0] = 1; // Caso base
    for (int i = 1; i <= n; ++i) {
        dp[i] = i * dp[i - 1]; // Transición
    }
    return dp[n];
}

/**
 * Calcula la cantidad de caminos posibles en un problema de combinatoria,
 * dado un número total de movimientos y un número específico de pasos en una dirección.
 *
 * La fórmula utilizada es la combinación matemática:
 * C(movimientos, pasos) = movimientos! / (pasos! * (movimientos - pasos)!)
 *
 * @param movimientos El número total de movimientos disponibles.
 * @param pasos El número de pasos en una dirección específica.
 * @return El número total de combinaciones posibles.
 */
long long cantidad_de_caminos(const int movimientos, const int pasos) {
    return factorial(movimientos) / (factorial(pasos) * factorial(movimientos - pasos));
}

/**
 * Realiza una búsqueda recursiva con backtracking para determinar si existe un camino
 * desde la posición (i, j) hasta la esquina inferior derecha de la matriz, cumpliendo
 * ciertas condiciones de suma acumulada.
 *
 * @param i Índice de la fila actual.
 * @param j Índice de la columna actual.
 * @param acumulador Suma acumulada de los valores en el camino actual.
 * @param n Número de filas de la matriz.
 * @param m Número de columnas de la matriz.
 * @param matriz Matriz de enteros que representa el tablero.
 * @param memo Mapa de memoización para almacenar resultados de subproblemas ya calculados.
 * @return `true` si existe un camino válido, `false` en caso contrario.
 */
bool backtrack(int i, int j, int acumulador, const int n, const int m,
    const vector<vector<int>>& matriz, unordered_map<long long, bool>& memo) {

    if (i >= n || j >= m) return false;
    acumulador += matriz[i][j];
    if (abs(acumulador) > (n - 1 - i) + (m - 1 - j) ||
        (abs(acumulador) % 2) != ((n - 1 - i) + (m - 1 - j)) % 2) return false;

    if (i == n - 1 && j == m - 1) {
        return acumulador == 0;
    }

    const long long key = (static_cast<long long>(i) * m + j) * (2LL * OFFSET + 1)
                          + (acumulador + OFFSET);

    if (const auto it = memo.find(key); it != memo.end()) {
        return it->second;
    }
    const bool res = backtrack(i + 1, j, acumulador, n, m, matriz, memo) ||
                     backtrack(i, j + 1, acumulador, n, m, matriz, memo);
    memo[key] = res;

    return res;
}

/**
 * Determina si existe un camino desde la esquina superior izquierda hasta la esquina
 * inferior derecha de una matriz, cumpliendo ciertas condiciones de suma acumulada.
 *
 * La función utiliza un algoritmo de backtracking optimizado con memoización para
 * explorar posibles caminos en la matriz. Un camino es válido si la suma acumulada
 * de los valores en el camino cumple con las restricciones definidas.
 *
 * Restricciones:
 * - La suma acumulada debe ser igual a 0 al llegar a la esquina inferior derecha.
 * - La paridad de la suma acumulada debe coincidir con la paridad de la distancia
 *   restante al destino.
 *
 * @param matriz Matriz de enteros que representa el tablero.
 *               Cada celda contiene un valor que afecta la suma acumulada.
 * @return `true` si existe un camino válido, `false` en caso contrario.
 */
bool existe_camino(const vector<vector<int>>& matriz) {
    const int n = matriz.size();
    const int m = matriz[0].size();

    if ((n + m - 1) % 2 != 0) return false;
    unordered_map<long long, bool> memo;
    return backtrack(0, 0, 0, n, m, matriz, memo);

}



#ifndef LOCAL
int main() {
    int test;

    cin >> test;
    while (test--) {
        int filas, columnas;
        cin >> filas >> columnas;
        vector<vector<int>> input(filas, vector<int>(columnas));
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; j++) {
                cin >> input[i][j];
            }
        }

        if (existe_camino(input)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }



    return 0;
}


#endif