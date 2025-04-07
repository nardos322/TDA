#include <iostream>
#include <vector>
using namespace std;

/**
 * Verifica si un tablero es un cuadrado mágico.
 * @param board Tablero a verificar.
 * @return true si el tablero es un cuadrado mágico, false en caso contrario.
 */
bool esMagico(const vector<vector<int>>& board) {
    const size_t n = board.size();
    const size_t sumaMagica = n * (n * n + 1) / 2;
    int sumaDiagonal1 = 0, sumaDiagonal2 = 0;

    for (const auto& fila : board) {
        int sumaFila = 0;
        for (const auto num : fila) {
            sumaFila += num;
        }
        if (sumaFila != sumaMagica) {
            return false;
        }
    }
    for (int j = 0; j < n; j ++) {
        int sumaColumna = 0;
        for (int i = 0; i < n; i ++) {
            sumaColumna += board[i][j];
        }
        if (sumaColumna != sumaMagica) {
            return false;
        }
    }

    for (int k = 0; k < n; k++) {
        sumaDiagonal1 += board[k][k];
    }
    for (int j = n - 1; j >= 0; j--) {
        sumaDiagonal2 += board[j][n - 1 - j];
    }
    if (sumaDiagonal1 != sumaMagica || sumaDiagonal2 != sumaMagica) {
        return false;
    }

    return true;
}


/**
 * Función que realiza el backtracking para encontrar y mostrar todos los cuadrados mágicos.
 * @param board Tablero actual.
 * @param used Vector que indica qué números ya han sido usados.
 * @param i Fila actual.
 * @param j Columna actual.
 */
void backtrack(vector<vector<int>>& board, vector<bool>& used, int i, int j) {
    const int n = board.size();
    if (i == n) {
        if (esMagico(board)) {
            for (const auto& vector : board) {
                for (const auto num : vector) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }
        return;
    }

    int nextRow = i, nextCol = j + 1;
    if (nextCol == n) {
        nextRow++;
        nextCol = 0;
    }

    for (int v = 1; v <= n * n; v++) {
        if (!used[v]) {
            board[i][j] = v;
            used[v] = true;
            backtrack(board, used, nextRow, nextCol);
            used[v] = false;
            board[i][j] = 0;
        }
    }

}

bool poda (const vector<vector<int>>& board, int i, int j) {
    const size_t n = board.size();
    const size_t sumaMagica = n * (n * n + 1) / 2;
    int sumaFila = 0, sumaColumna = 0;

    for (int k = 0; k <= j; k++) {
        sumaFila += board[i][k];
        if (sumaFila > sumaMagica) {
            return false;
        }
    }

    for (int l = i; l >= j; l--) {
        sumaColumna += board[l][j];
        if (sumaColumna > sumaMagica) {
            return false;
        }
    }

    if (i == j) {
        int sumaDiagonal1 = 0;
        for (int k = i; k >= 0; k--) {
            sumaDiagonal1 += board[k][k];
            if (sumaDiagonal1 > sumaMagica) {
                return false;
            }
        }
    }

}


int main() {
    constexpr int n = 3;
    vector<vector<int>> tablero(n, vector<int>(n, 0));
    vector<bool> used(n * n + 1, false );

    backtrack(tablero, used, 0, 0);

    return 0;
}