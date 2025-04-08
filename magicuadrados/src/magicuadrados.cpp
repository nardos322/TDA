#include "../include/magicuadrados.h"


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


bool poda (const vector<vector<int>>& board, const int i, const int j) {
    const size_t n = board.size();
    const size_t sumaMagica = n * (n * n + 1) / 2;
    int sumaFilaParcial = 0;
    int sumaColumnaParcial = 0;

    // Verificamos la suma de las filas parciales
    for (int k = 0; k <= j; k++) {
        sumaFilaParcial += board[i][k];
    }
    if (sumaFilaParcial > sumaMagica) return false;

    // Si j == n - 1, la fila esta completa, chequeamos que fila completa == sumaMagica
    if (j == n - 1) {
        int sumaFilaCompleta = 0;
        for (int k = 0; k < n; k++) {
            sumaFilaCompleta += board[i][k];
        }
        if (sumaFilaCompleta != sumaMagica) return false;
    }

    // Verificamos la suma de las columnas parciales
    for (int k = 0; k <= i; k++) {
        sumaColumnaParcial += board[k][j];
    }
    if (sumaColumnaParcial > sumaMagica) return false;

    // Si, i = n - 1, la columna esta completa
    if (i == n - 1) {
        int sumaColumnaCompleta = 0;
        for (int k = 0; k < n; k++) {
            sumaColumnaCompleta += board[k][j];
        }

        if (sumaColumnaCompleta != sumaMagica) return false;
    }

    // Verificamos diagonal principal
    if (i == j) {
        int sumaDiagonal1Parcial = 0;
        for (int k = 0; k <= i; k++) {
            sumaDiagonal1Parcial += board[k][k];
        }
        if (sumaDiagonal1Parcial > sumaMagica) return false;

        // Si i == n - 1, la diagonal principal esta completa
        if (i == n - 1) {
            int sumaDiagonal1Completa = 0;
            for (int k = 0; k < n; k++) {
                sumaDiagonal1Completa += board[k][k];
            }
            if (sumaDiagonal1Completa != sumaMagica) return false;
        }
    }

    // Verificamos diagonal secundaria
    if (i + j == n - 1) {
        int sumaDiagonal2Parcial = 0;
        for (int k = 0; k <= i; k++) {
            sumaDiagonal2Parcial += board[k][n - 1 - k];
        }
        if (sumaDiagonal2Parcial > sumaMagica) return false;

        // Si i == n - 1, la diogonal secundaria esta completa
        if (i == n - 1) {
            int sumaDiagonal2Completa = 0;
            for (int k = 0; k < n; k++) {
                sumaDiagonal2Completa += board[k][n - 1 - k];
            }
            if (sumaDiagonal2Completa != sumaMagica) return false;
        }
    }

    // Si no se cumple ninguna condicion de poda, retornamos true
    return true;

}


void backtrack(vector<vector<int>>& board, vector<bool>& used, int i, int j, int& count) {
    const int n = board.size();

    // Caso base i == n, cuando i == n quiere decir que ya tenemos el tablero completo
    if (i == n) {
        if (esMagico(board)) {
            count++;
            for (const auto& vector : board) {
                for (const auto num : vector) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }
        return;
    }

    // Calculamos la siguiente celda (i, j) a llenar
    int nextRow = i, nextCol = j + 1;
    if (nextCol == n) {
        nextRow++;
        nextCol = 0;
    }

    //Probamos todos los valores 1,...,n*n
    for (int v = 1; v <= n * n; v++) {
        if (!used[v]) {
            board[i][j] = v;
            used[v] = true;
            if (poda(board, i, j)) {
                // si poda retorna true continuamos con el backtracking
                backtrack(board, used, nextRow, nextCol, count);
            }

            // restablecemos el tablero para probar otros numeros en otra rama en el mismo nivel
            used[v] = false;
            board[i][j] = 0;
        }
    }
}