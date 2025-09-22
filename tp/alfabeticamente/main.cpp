#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;



string invertir(const string &s)
{
    if (s.empty())
        return "";
    return s.back() + invertir(s.substr(0, s.size() - 1));
}

// Verificar si un arreglo está en orden alfabético
bool estaEnOrdenAlfabetico(const vector<string> &palabras)
{
    for (int i = 0; i < palabras.size() - 1; i++)
    {
        if (palabras[i] > palabras[i + 1])
        {
            return false;
        }
    }
    return true;
}

// Numero combinatorio
// Variante B: no muta `palabras`. Usa `reversas` precomputadas y arma un vector temporal en las hojas.
void backtrack(const int pos,
               const vector<string> &palabras,
               const vector<string> &reversas,
               const vector<int> &costos,
               vector<int> &elegidos,
               const int r,
               const int N,
               int &costo_min_global)
{

    if (r == 0) {
        // Construir el arreglo actual sin mutar `palabras`
        vector<string> actual = palabras;
        int costo_local = 0;

        for (auto n : elegidos) {
            cout << n << " ";
            actual[n] = reversas[n];
            costo_local += costos[n];
        }

        if (costo_local < costo_min_global && estaEnOrdenAlfabetico(actual)) {
            costo_min_global = costo_local;
        }

        cout << endl;

        return;
    }

    if (pos >= N)
        return;

    elegidos.push_back(pos);
    backtrack(pos + 1, palabras, reversas, costos, elegidos, r - 1, N, costo_min_global);
    elegidos.pop_back();

    // Solo continúa si quedan suficientes elementos para completar la combinación
    if (N - (pos + 1) >= r) {
        backtrack(pos + 1, palabras, reversas, costos, elegidos, r, N, costo_min_global);
    }
}

int solve(istream& in, ostream& out) {
    int costo_min_global = INT_MAX;
    int N;
    in >> N;

    vector<string> palabras(N);
    for (int i = 0; i < N; ++i)
        in >> palabras[i];
    vector<string> reversas(N);
    for (int i = 0; i < N; ++i)
        reversas[i] = invertir(palabras[i]);
    vector<int> costos(N);
    for (int i = 0; i < N; ++i)
        in >> costos[i];
    vector<int> elegidos;

    for (int r = 0; r <= N; ++r) {
        backtrack(0, palabras, reversas, costos, elegidos, r, N, costo_min_global);
    }

    if(costo_min_global == INT_MAX) {
        return -1; // Indica que no es posible ordenar
    } else {
        return costo_min_global;
    }
}



int main() {
    solve(cin, cout);
    return 0;
}