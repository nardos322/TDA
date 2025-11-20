#include <gtest/gtest.h>
#include "sumset_sum.hpp"

class SubsetSumTest : public ::testing::Test {
protected:
    static void verificar_resultado(const SubsetSumResult& resultado, bool es_valido, int sum_target) {
        ASSERT_EQ(resultado.exists, es_valido);
        if (es_valido) {
            int suma_real = 0;
            for (int n : resultado.subset) {
                suma_real += n;
            }
            ASSERT_EQ(suma_real, sum_target);
        }
    }
};

TEST_F(SubsetSumTest, ConjuntoVacio) {
    vector<int> conjunto = {};
    int target = 0;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    verificar_resultado(res_bottomup, true, target);
}

TEST_F(SubsetSumTest, SumaImposible) {
    vector<int> conjunto = {2, 4, 6, 8};
    int target = 3;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    ASSERT_FALSE(res_bottomup.exists);
    ASSERT_FALSE(res_topdown.exists);

}

TEST_F(SubsetSumTest, CasoSimple) {
    vector<int> conjunto = {3, 2, 8, 1};
    int target = 6;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    verificar_resultado(res_bottomup, true, target);
    verificar_resultado(res_topdown, true, target);

}

TEST_F(SubsetSumTest, NumeroNegativo) {
    vector<int> conjunto = {1, 2, 3};
    int target = -1;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    ASSERT_FALSE(res_bottomup.exists);
    ASSERT_FALSE(res_topdown.exists);
}

TEST_F(SubsetSumTest, CasoComplejo) {
    vector<int> conjunto = {2, 3, 5, 7, 8, 10 ,12, 15, 18, 20};
    int target = 25;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    verificar_resultado(res_bottomup, true, target);
    verificar_resultado(res_topdown, true, target);
}

TEST_F(SubsetSumTest, ElementoUnico) {
    vector<int> conjunto = {5};
    int target = 5;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    verificar_resultado(res_bottomup, true, target);
    verificar_resultado(res_topdown, true, target);


}

TEST_F(SubsetSumTest, NumerosRepetidos) {
    vector<int> conjunto = {2, 2, 3, 3, 4, 4};
    int target = 9;

    auto res_bottomup = subset_sum_bottomUp(conjunto, target);
    auto res_topdown = subset_sum_topDown(conjunto, target);

    verificar_resultado(res_bottomup, true, target);
    verificar_resultado(res_topdown, true, target);
}