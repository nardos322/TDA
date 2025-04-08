#include <gtest/gtest.h>
#include "../include/magicuadrados.h"



// test para la función esMagico
TEST(cuadradoMagicoTest, esMagico) {
    vector<vector<int>> tableroMagico = {
        {2, 7, 6},
        {9, 5, 1},
        {4, 3, 8}
    };
    EXPECT_TRUE(esMagico(tableroMagico));

    vector<vector<int>> tableroNoMagico = {
        {2, 7, 6},
        {9, 5, 1},
        {4, 3, 7}
    };
    EXPECT_FALSE(esMagico(tableroNoMagico));

}

// test para la funcion poda
TEST(cuadradoMagicoTest, podaFila) {
    vector<vector<int>> tablero = {
        {2, 7, 6},
        {9, 0, 0},
        {0, 0, 0}
    };

    EXPECT_TRUE(poda(tablero,1, 1)); // poda valida
    tablero[1][1] = 10; // la suma parcial excede la sumaMagica
    EXPECT_FALSE(poda(tablero,1, 1));
}

TEST(cuadradoMagicoTest, podaColumna) {
    vector<vector<int>> tablero = {
        {2, 7, 6},
        {9, 5, 1},
        {4, 0, 0}
    };
    EXPECT_TRUE(poda(tablero,2, 0)); // poda valida
    tablero[2][0] = 8; // la suma de la columna excede la sumaMagica
    EXPECT_FALSE(poda(tablero,2, 0));
}

TEST(cuadradoMagicoTest, podaDiagonalPrincipal) {
    vector<vector<int>> tablero = {
        {2, 7, 6},
        {9, 5, 1},
        {4, 3, 8}
    };
    EXPECT_TRUE(poda(tablero,2, 2)); // poda valida
    tablero[1][1] = 8; // la suma de la diagonal principal excede  la sumaMagica
    EXPECT_FALSE(poda(tablero,2, 2));
}

TEST(cuadradoMagicoTest, podaDiagonalSecundaria) {
    vector<vector<int>> tablero = {
        {2, 7, 6},
        {9, 5, 1},
        {0, 3, 8}
    };

    EXPECT_TRUE(poda(tablero, 1, 1));
    tablero[2][0] = 8;
    EXPECT_FALSE(poda(tablero,2, 0));
}



TEST(cuadradoMagicoTest, backtrack) {
    int n = 3;
    vector<vector<int>> tablero(n, vector<int>(n, 0));
    vector<bool> usados(n * n + 1, false);
    int contador = 0;

    backtrack(tablero, usados, 0, 0, contador);

    EXPECT_EQ(contador, 8);
}