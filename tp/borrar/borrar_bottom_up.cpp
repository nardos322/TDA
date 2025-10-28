#include <bits/stdc++.h>
using namespace std;

// Documentación: borrar_bottomup
// --------------------------------
// Descripción:
// Calcula el número mínimo de operaciones necesarias para "borrar" toda la
// cadena `s` siguiendo la misma recurrencia que la versión top-down.
//
// Contrato:
// - Entrada: `s` (string) de longitud n
// - Salida: mínimo número de operaciones para eliminar `s`
//
// Enfoque:
// - DP bottom-up: se rellena una tabla `dp[i][j]` que contiene la respuesta
//   para el substring s[i..j]. Se itera por longitudes crecientes para asegurar
//   que los subproblemas necesarios ya estén computados.
//
// Complejidad:
// - Tiempo: O(n^3). Hay O(n^2) estados (i,j) y para cada estado se itera
//   sobre k en [i+1..j], costando O(n) por estado en el peor caso.
// - Espacio: O(n^2) para la tabla `dp`.
//
// Notas:
// - Aquí se usa `vector<vector<long long>>` para que la tabla tenga tamaño
//   exacto `n` (memoria proporcional a n). Si se conoce el límite máximo n ≤ 500,
//   una alternativa es usar `array<array<long long,500>,500>` para evitar
//   realocaciones y obtener acceso ligeramente más rápido.
//
long long borrar_bottomup(const string &s)
{
    int n = s.size();
    if (n == 0)
        return 0;

    // dp[i][j] = mínimo número de operaciones para el rango [i, j]
    // aca usamos vector<vector> en vez de array porque para este enfoque bottom-up
    // no necesitamos inicializar con -1
    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    // Casos base: substrings de longitud 1
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 1; // Un carácter siempre cuesta 1 operación
    }

    // Llenar por longitudes crecientes: 2, 3, 4, ..., n
    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1; // Extremo derecho

            // Opción 1: Borrar el primer carácter
            dp[i][j] = 1 + dp[i + 1][j];

            // Opción 2: Emparejar s[i] con algún s[k]
            for (int k = i + 1; k <= j; k++)
            {
                if (s[i] == s[k])
                {
                    dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k][j]);
                }
            }
        }
    }

    return dp[0][n - 1];
}

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}