#include <bits/stdc++.h>
using namespace std;



long long borrar_bottomup(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    
    // dp[i][j] = mínimo número de operaciones para el rango [i, j]
    //aca usamos vector<vector> en vez de array porque para este enfoque bottom-up 
    //no necesitamos inicializar con -1
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    
    // Casos base: substrings de longitud 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;  // Un carácter siempre cuesta 1 operación
    }
    
    // Llenar por longitudes crecientes: 2, 3, 4, ..., n
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;  // Extremo derecho
            
            // Opción 1: Borrar el primer carácter
            dp[i][j] = 1 + dp[i + 1][j];
            
            // Opción 2: Emparejar s[i] con algún s[k]
            for (int k = i + 1; k <= j; k++) {
                if (s[i] == s[k]) {
                    dp[i][j] = min(dp[i][j], dp[i + 1][k - 1] + dp[k][j]);
                }
            }
        }
    }
    
    return dp[0][n - 1];
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}