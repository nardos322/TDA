#include <iostream>
#include <vector>
using namespace std;


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

bool poda(int acumulador, int pasosRestantes) {
    return abs(acumulador) > pasosRestantes;
}

void backtrack(int i, int j, const int n, const int m, const vector<vector<int>>& matriz,
   int acumulador, bool& existeCamino) {
    if (existeCamino) return;
    acumulador += matriz[i][j];
    cout << "(" << i << j << ")" << endl;
    if (i == n - 1 && j == m - 1){
        if (acumulador == 0) {
            existeCamino = true;
        }
        return;
    }
    int pasosRestantes = (n - 1 - i) + (m - 1 - j);
    if (i < n - 1 && !poda(acumulador, pasosRestantes)) {
        backtrack(i + 1, j, n, m, matriz, acumulador, existeCamino);

    }
    if (j < m - 1 && !poda(acumulador, pasosRestantes)) {
        backtrack(i, j + 1, n, m, matriz, acumulador, existeCamino);

    }
}

#ifndef LOCAL
int main() {
    int test;
    int filas, columnas;
    int casos = 0;
    vector<string> res;
    cin >> test;
    while (casos < test) {
        int i = 0;
        cin >> filas >> columnas;
        vector<vector<int>> input(filas, vector<int>(columnas));
        while (i < filas) {
            for (int j = 0; j < columnas; j++) {
                cin >> input[i][j];
            }
            i++;
        }
        if ((cant_movimientos_min(input) + 1) % 2 != 0) {
            res.push_back("NO");
            casos++;
        } else {
            bool existeCamino = false;
            int acumulador = 0;
            backtrack(0, 0, filas, columnas, input, acumulador, existeCamino);
            if (existeCamino) {
                res.push_back("YES");
            } else {
                res.push_back("NO");
            }
            casos++;
        }
    }

    for (string r : res) {
        cout << r << endl;
    }


    return 0;
}


#endif