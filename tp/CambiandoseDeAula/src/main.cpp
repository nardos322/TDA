#include <iostream>
#include <vector>
using namespace std;

long long factorial_topDown(int n, vector<long long>& memo) {
    if (memo.size() <= n) { memo.resize(n + 1, -1); }
    if (memo[n] != -1) { return memo[n]; }
    if (n <= 1) { return 1; }
    memo[n] = n * factorial_topDown(n - 1, memo);
    return memo[n];
}

long long factorial(int n) {
    vector<long long> dp(n + 1);
    dp[0] = 1; // Caso base
    for (int i = 1; i <= n; ++i) {
        dp[i] = i * dp[i - 1]; // Transición
    }
    return dp[n];
}

long long cantidad_de_caminos(int movimientos,  int pasos) {
    return factorial(movimientos) / (factorial(pasos) * factorial(movimientos - pasos));
}

long long cant_movimientos_min(const vector<vector<int>>& matriz) {
    return (matriz.size() - 1) + ( matriz[0].size() - 1);
}

void backtrack(int i, int j, int n, int m, const vector<vector<int>>& matriz, vector<int> caminos, bool& existeCamino) {
    //cout<< i << j << endl;
    if (i == n - 1 && j == m - 1){
        int contador = 0;
        for (int k = 0; k < caminos.size(); k++) {
            contador += caminos[k];
        }
        if (contador == 0) {
            existeCamino = true;
        }
        return;
    }
    if (i < n - 1) {
        caminos.push_back(matriz[i][j]);
        backtrack(i + 1, j, n, m, matriz, caminos, existeCamino);
    }
    if (j < m - 1) {
        caminos.push_back(matriz[i][j]);
        backtrack(i, j + 1, n, m, matriz, caminos, existeCamino);
    }
}

struct coordenadas {
    int fila;
    int columna;
};
//#ifndef LOCAL
int main() {
    bool existeCamino = false;
    vector<int> caminos;
    vector<vector<int>> matriz = {
        {1, 1, -1, 1},
        {-1, 1, -1, -1},
        {1, 1, 1, -1}
    };

    backtrack(0,0, matriz.size(), matriz[0].size(), matriz, caminos, existeCamino);
    cout << existeCamino << endl;
    return 0;
}


//#endif