#include <iostream>
#include <vector>
using namespace std;

void backtrack(const int k, int i, int acumulador, const vector<int>& set, vector<int>& permutacion, vector<bool>& visitado) {

    if (acumulador == k) {
        for (const int n : permutacion) {
            cout << n << " ";
        }
        cout << endl;
        return;
    }


    for (int j = 0; j < set.size(); j++) {
        if (!visitado[j]) {
            permutacion[i] = set[j];
            visitado[j] = true;
            backtrack(k, i + 1, acumulador + set[j], set, permutacion, visitado);
            visitado[j] = false;
            permutacion[i] = 0;
        }

    }

}

bool existe_suma_subconjunto(const vector<int>& set) {
    vector<int> permutacion(set.size());
    vector<bool> visitado(set.size(), false);



}


int main() {
    const vector<int> set = {1, 1, 3};
    vector<int> permutacion(set.size());
    vector<bool> visitado(set.size(), false);
    backtrack(5, 0, 0, set, permutacion, visitado);
    return 0;
}