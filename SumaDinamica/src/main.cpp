#include <iostream>
#include <vector>
using namespace std;

void backtrack(const int k, int i, const vector<int>& set, vector<int>& permutacion, vector<bool>& visitado) {
    if (i == set.size()) {
        for (int j = 0; j < permutacion.size(); j++) {
            cout << permutacion[j] << " ";
        }
        cout << endl;
        return;
    }


    for (int j = 0; j < set.size(); j++) {
        if (!visitado[j]) {
            permutacion[i] = set[j];
            visitado[j] = true;
            backtrack(k, i + 1, set, permutacion, visitado);
            visitado[j] = false;
        }

    }

}


int main() {
    const vector<int> set = {6, 12, 6};
    vector<int> permutacion(set.size());
    vector<bool> visitado(set.size(), false);
    backtrack(6, 0, set, permutacion, visitado);

    return 0;
}