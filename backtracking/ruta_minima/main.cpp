#include <iostream>
#include <vector>

using namespace std;

int indice_espejo(const vector<int>& A, int l, int r) {
    if (l > r) {
        return -1; // Caso base: no se encontró el índice espejo
    }

    int i = (l + r) / 2;
    if (A[i] ==  i + 1) {
        return i + 1;
    } else if (A[i] > i + 1) {
        return indice_espejo(A, l, i - 1);
    } else {
        return indice_espejo(A, i + 1, r);
    }


}


int potencia_logaritmica(int a, int b) {
    if (b == 0) {
        return 1;
    }
    if (b == 1) {
        return a;
    }

    int mitad = potencia_logaritmica(a, b/2);

    if ( b % 2 == 0) {
        return mitad * mitad;
    } else {
        return a * mitad * mitad;
    }
}


// Numero combinatorio
void backtrack(int pos, vector<int> elegidos, int r, int N) {



    if (r == 0)  {
        for (auto n : elegidos){
            cout << n << " ";
        }
        cout << endl;
        return;
    }

    if (pos >= N) return;


    elegidos.push_back(pos);
    backtrack(pos + 1, elegidos, r - 1, N);
    elegidos.pop_back();
    backtrack(pos + 1, elegidos, r, N);



}

void permutaciones(vector<int>& elegidos, vector<bool>& usado, int r, int N) {
    if (r == 0) {
        for (auto n : elegidos) cout << n << " ";
        cout << endl;
        return;
    }
    for (int i = 1; i <= N; ++i) {
        if (!usado[i]) {
            usado[i] = true;
            elegidos.push_back(i);
            permutaciones(elegidos, usado, r - 1, N);
            elegidos.pop_back();
            usado[i] = false;
        }
    }
}

int main() {
    int N = 5;
    vector<int> elegidos;
    vector<bool> usados(N + 1, false);



    permutaciones(elegidos, usados, 4, N);


    //backtrack(0, elegidos, 4, N);
    return 0;
}