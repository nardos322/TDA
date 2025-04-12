#define LOCAL
#include <gtest/gtest.h>
#include <vector>
#include "../src/main.cpp"


TEST(CaminosMinimos, MatrizNxM) {
    for (long long n = 1; n <= 30; ++n) { // Prueba matrices de 1x1 a 5x5
        for (long long m = 1; m <= 30; ++m) {
            std::vector<std::vector<int>> matriz(n, std::vector<int>(m, 1));
            EXPECT_EQ((n - 1) + (m - 1), cant_movimientos_min(matriz));
            EXPECT_EQ(cantidad_de_caminos((n - 1) + (m - 1), n - 1),
                cantidad_de_caminos((n - 1) + (m - 1), m - 1));
        }
    }
}