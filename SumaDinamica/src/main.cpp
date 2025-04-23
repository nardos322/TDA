#include <iostream>
#include <vector>
#include "../include/sumset_sum.hpp"






int main() {
    const vector<int> set = {1, 1, 2, 5, 5};
    int j = 7;

    try {
        auto res_topDown = subset_sum_topDown(set, j);
        if (res_topDown.exists) {
            cout << "Solucion Top-Down encontrada: ";
            for (const int n: res_topDown.subset) cout << n << " ";
            cout << endl;
        } else {
            cout << "No se encontro solucion top-Down" << endl;
        }

        auto res_bottomUp = subset_sum_bottomUp(set, j);
        if (res_bottomUp.exists) {
            cout << "Solucion Bottom-Up encontrada: ";
            for (const int n: res_bottomUp.subset) cout << n << " ";
            cout << endl;
        } else {
            cout << "No se encontro solucion Bottom-Up" << endl;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
