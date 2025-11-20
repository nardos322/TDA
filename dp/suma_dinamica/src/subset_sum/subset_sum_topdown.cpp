#include "../../include/sumset_sum.hpp"


SubsetSumResult recursive_search(const vector<int>& set, vector<int>& parcial, vector<vector<int>>& memo, int i,
                                 int j) {
    constexpr int NOT_CALCULATED = -1;

    // casos base
    if (j < 0) return {false, {}};
    if (i == 0) return {j == 0, parcial};

    // Verificar memoizacion
    if (memo[i][j] != NOT_CALCULATED) {
        return {static_cast<bool>(memo[i][j]), parcial};
    }

    // Intentar incluyendo el elemento actual
    parcial.push_back(set[i - 1]);
    auto res_incluir = recursive_search(set, parcial, memo, i - 1, j - set[i - 1]);

    if (res_incluir.exists) {
        memo[i][j] = 1;
        return res_incluir;
    }

    // Si no encontro, retroceder
    parcial.pop_back();

    // Intentar sin incluir el elemento actual
    auto res_no_inlcuir = recursive_search(set, parcial, memo, i - 1, j);
    memo[i][j] = res_no_inlcuir.exists ? 1 : 0;
    return res_no_inlcuir;
}

SubsetSumResult subset_sum_topDown(const vector<int>& set, int k) {
    if (k < 0) return {false, {}};
    if (set.empty()) return {k == 0, {}};

    vector<int> parcial;
    vector<vector<int>> memo(set.size() + 1, vector<int>(k + 1, -1));

    auto res = recursive_search(set, parcial, memo, set.size(), k);

    return res;
}
