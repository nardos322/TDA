#define LOCAL
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "../src/main.cpp"

TEST(CaminosMinimos, MatrizNxM) {
    for (long long n = 1; n <= 30; ++n) { // Prueba matrices de 1x1 a 5x5
        for (long long m = 1; m <= 30; ++m) {
            vector<vector<int>> matriz(n, vector<int>(m, 1));
            EXPECT_EQ(cantidad_de_caminos((n - 1) + (m - 1), n - 1),
                cantidad_de_caminos((n - 1) + (m - 1), m - 1));
        }
    }
}

TEST(CambiandoseDeAula, ExisteCamino) {


    vector<vector<int>> matriz1 = {
        {1}
    };
    vector<vector<int>> matriz2 = {
        {1, -1}
    };

    vector<vector<int>> matriz3 = {
        {1, -1, 1, -1}
    };

    vector<vector<int>> matriz4 = {
        {1, -1, -1, -1},
        {-1, 1, 1, -1},
        {1, 1, 1, -1}
    };
    vector<vector<int>> matriz5 = {
        {1, -1, 1, -1},
        {-1, 1, 1, -1},
        {1, 1, 1, -1}
    };

    vector<vector<int>> matriz6 = {
        {1, -1, 1, 1},
        {-1, 1, -1, 1},
        {1, -1, 1, 1}
    };

    vector<vector<vector<int>>> matrices = {matriz1, matriz2, matriz3, matriz4, matriz5, matriz6};
    vector<bool> resultados = {false, true, true, true, true, false};

    for (int i = 0; i < matrices.size(); ++i) {
        EXPECT_EQ(existe_camino(matrices[i]), resultados[i]);
    }

}



// Función auxiliar para generar matrices aleatorias de tamaño n x m
vector<vector<int>> generarMatriz(int n, int m) {
    vector<vector<int>> matriz(n, vector<int>(m));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matriz[i][j] = dist(gen) == 0 ? 1 : -1; // Genera valores aleatorios de 1 o -1
        }
    }
    return matriz;
}

// Función auxiliar para calcular si existe un camino (simula la lógica de backtrack)
bool calcularExisteCamino(const vector<vector<int>>& matriz) {
    const int n = matriz.size();
    const int m = matriz[0].size();
    vector<vector<bool>> visitado(n, vector<bool>(m, false));

    function<bool(int, int, int)> dfs = [&](int x, int y, int suma) {
        if (x < 0 || y < 0 || x >= n || y >= m || visitado[x][y]) return false;
        suma += matriz[x][y];
        if (x == n - 1 && y == m - 1) return suma == 0;
        visitado[x][y] = true;
        const bool resultado = dfs(x + 1, y, suma) || dfs(x, y + 1, suma);
        visitado[x][y] = false;
        return resultado;
    };

    return dfs(0, 0, 0);
}

//Test automatizado con matrices grandes y valores aleatorios
TEST(CambiandoseDeAula, MatricesGrandesAleatorias) {
    for (int n = 5; n <= 15; n += 5) { // Tamaños de matriz: 5x5, 10x10, ..., 20x20
        for (int m = 5; m <= 15; m += 5) {
            auto matriz = generarMatriz(n, m);
            bool resultadoEsperado = calcularExisteCamino(matriz);

            EXPECT_EQ(existe_camino(matriz), resultadoEsperado);
        }
    }
}






