#include <iostream>
#include <vector>
using namespace std;

constexpr int OFFSET = 2005;

long long factorial(int n) {
    vector<long long> dp(n + 1);
    dp[0] = 1; // Caso base
    for (int i = 1; i <= n; ++i) {
        dp[i] = i * dp[i - 1]; // Transición
    }
    return dp[n];
}

long long cantidad_de_caminos(const int movimientos, const int pasos) {
    return factorial(movimientos) / (factorial(pasos) * factorial(movimientos - pasos));
}

long long cant_movimientos_min(const vector<vector<int>>& matriz) {
    return (matriz.size() - 1) + ( matriz[0].size() - 1);
}


bool backtrack(int i, int j, int acumulador, const int n, const int m,
    const vector<vector<int>>& matriz, vector<vector<vector<int>>>& memo) {

    if (i >= n || j >= m) return false;
    acumulador += matriz[i][j];
    if (abs(acumulador) > (n - 1 - i) + (m - 1 - j) || (abs(acumulador) % 2) != ((n - 1 - i) + (m - 1 - j)) % 2) return false;

    if (i == n - 1 && j == m - 1) {
        return acumulador == 0;
    }

    const int key = acumulador + OFFSET;
    if (memo[i][j][key] != -1) return memo[i][j][key];

    const bool res = backtrack(i + 1, j, acumulador, n, m, matriz, memo) ||
                     backtrack(i, j + 1, acumulador, n, m, matriz, memo);
    memo[i][j][key] = res;

    return res;
}

bool existe_camino(const vector<vector<int>>& matriz) {
    const int n = matriz.size();
    const int m = matriz[0].size();

    if ((n + m - 1) % 2 != 0) return false;
    vector<vector<vector<int>>> memo(n, vector<vector<int>>(m, vector<int>(2 * OFFSET + 1, -1)));
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