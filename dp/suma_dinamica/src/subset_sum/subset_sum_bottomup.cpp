#include "../../include/sumset_sum.hpp"

SubsetSumResult subset_sum_bottomUp(const vector<int>& set, int k) {
    if (k < 0) return {false, {}};
    int n = set.size();
    // dp[i][j] indica si es posible obtener una suma `j` utilizando los primeros `i` elementos del conjunto.
    vector<vector<bool>> dp(set.size() + 1, vector<bool>(k + 1, false));

    // Caso base: Es posible obtener una suma de 0 con 0 elementos.
    dp[0][0] = true;

    // Llenado de la tabla dp
    for (int i = 1; i <= n; i++) {
        // Iteramos sobre los elementos del conjunto
        for (int j = 0; j <= k; j++) {
            // Iteramos sobre las posibles sumas desde 0 hasta k
            // Opción 1: Usar el elemento actual si no excede la suma objetivo
            bool incluir = (j >= set[i - 1]) && dp[i - 1][j - set[i - 1]];
            // Opción 2: No usar el elemento actual
            bool no_incluir = dp[i - 1][j];
            // Actualizamos dp[i][j] considerando ambas opciones
            dp[i][j] = incluir || no_incluir;
        }
    }
    // Si no es posible formar la suma `k`, retornamos false
    if (!dp[n][k]) {
        return {false, {}};
    }


    // Reconstrucción del subconjunto a partir de la tabla dp
    int suma_Restante = k;
    vector<int> subset_found;

    for (int i = n; i > 0 && suma_Restante > 0; i--) {
        // Si el elemento actual fue usado en la solución
        if (dp[i][suma_Restante] && !dp[i - 1][suma_Restante]) {
            subset_found.push_back(set[i - 1]); // Añadimos el elemento al subconjunto
            suma_Restante -= set[i - 1]; // Reducimos la suma objetivo
        }
    }


    return {true, subset_found}; // Retornamos el resultado
}
