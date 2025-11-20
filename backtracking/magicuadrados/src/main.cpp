#include "../include/magicuadrados.h"




int main() {
    constexpr int n = 4;
    vector<vector<int>> tablero(n, vector<int>(n, 0));
    vector<bool> used(n * n + 1, false );
    int count = 0;

    backtrack(tablero, used, 0, 0, count);

    cout << "total de cuadrados magicos encontrados: " << count << endl;
    return 0;
}