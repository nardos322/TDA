#include <bits/stdc++.h>
using namespace std;


long long bst_optimo_bt(vector<long long>& freq, const int i, const int j) {  // O(4^n)

    if (i > j) return 0;
    if (i == j) return freq[i];
    
    long long costo_intervalo = 0;
    
    // Esto se puede optimizar con una suma acumulada
    for (int k = i; k <= j; k++) {
        costo_intervalo += freq[k];
    }
    // queremos el costo minimo  en el intervalo [i, j] por eso declaramos costo_min localmente
    long long costo_min = LLONG_MAX;
    for (int r = i; r <= j; r++) {
        long long costo_izq = bst_optimo_bt(freq, i, r - 1);
        long long costo_der = bst_optimo_bt(freq, r + 1, j);
        long long costo_total = costo_izq + costo_der + costo_intervalo;
        costo_min = min(costo_min, costo_total);
    }

    return costo_min;
}

long long bst_optimo_topdown(vector<long long>& freq) {  // O(n^4)
    vector<vector<long long>> memo(freq.size(), vector<long long>(freq.size(), -1));


    function<long long(int, int)> bt = [&](int i, int j) -> long long {
        if (i > j) return 0;
        if (i == j) return freq[i];
        if (memo[i][j] != -1) return memo[i][j];
        long long costo_intervalo = 0;

        // Esto se puede optimizar con una suma acumulada
        for (int k = i; k <= j; k++) {
            costo_intervalo += freq[k];
        }

        long long costo_min = LLONG_MAX;
        for (int r = i; r <= j; r++) {
            long long costo_izq = bt(i, r - 1);
            long long costo_der = bt(r + 1, j);
            long long costo_total = costo_izq + costo_der + costo_intervalo;
            costo_min = min(costo_min, costo_total);
        }
        return memo[i][j] = costo_min;
    };
    return bt(0, freq.size() - 1);
}

long long bst_optimo_optimizado(vector<long long>& freq) {  // O(n^3)
    int n = freq.size();
    
    // 1. Crear sumas prefijas - O(n)
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + freq[i];
    }
    
    // 2. Memoización
    vector<vector<long long>> memo(n, vector<long long>(n, -1));
    
    function<long long(int, int)> bt = [&](int i, int j) -> long long {
        if (i > j) return 0;
        if (i == j) return freq[i];
        if (memo[i][j] != -1) return memo[i][j];
        
        // 3. Cálculo optimizado - O(1)
        long long costo_intervalo = prefix[j + 1] - prefix[i];
        
        long long costo_min = LLONG_MAX;
        for (int r = i; r <= j; r++) {     // Solo este bucle queda O(n)
            long long costo_izq = bt(i, r - 1);
            long long costo_der = bt(r + 1, j);
            long long costo_total = costo_izq + costo_der + costo_intervalo;
            costo_min = min(costo_min, costo_total);
        }
        return memo[i][j] = costo_min;
    };
    return bt(0, n - 1);
}


long long bst_optimo_bottomup(vector<long long>& freq) {  // O(n^3)
    int n = freq.size();
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    vector<long long> prefix (n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + freq[i];
    }

    for (int length = 1; length <= n; length++) { // Tamaño del intervalo
        for (int i = 0; i <= n - length; i++) { // Posición inicial
            int j = i + length - 1;
            if (i == j) {
                dp[i][j] = freq[i];
                continue;
            }
            long long costo_intervalo = prefix[j + 1] - prefix[i];
            long long costo_min = LLONG_MAX;
            for (int r = i; r <= j; r++) {
                long long costo_izq = (r > i) ? dp[i][r - 1] : 0; // Evita acceso inválido
                long long costo_der = (r < j) ? dp[r + 1][j] : 0;
                long long costo_total = costo_izq + costo_der + costo_intervalo;
                costo_min = min(costo_min, costo_total);
            }
            dp[i][j] = costo_min;
        }
    }
    return dp[0][n - 1];


}

int main() {
    vector<int> keys = {10, 20, 30};
    vector<long long> freq = {3, 1, 2};
    int n = keys.size();
    cout << "Costo mínimo del BST: " << bst_optimo_bt(freq, 0, n - 1) << endl;
    cout << "Costo mínimo del BST (Top-Down con Memoización): " << bst_optimo_topdown(freq) << endl;
    cout << "Costo mínimo del BST (Optimizado con Sumas Prefijas): " << bst_optimo_optimizado(freq) << endl;
    cout << "Costo mínimo del BST (Bottom-Up): " << bst_optimo_bottomup(freq) << endl;
    return 0;


}

