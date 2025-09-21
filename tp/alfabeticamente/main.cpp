#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

int costo_min_global = INT_MAX;

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
               const int N)
{

    if (r == 0)
    {
        // Construir el arreglo actual sin mutar `palabras`
        vector<string> actual = palabras;
        int costo_local = 0;

        for (auto n : elegidos)
        {
            cout << n << " ";
            actual[n] = reversas[n];
            costo_local += costos[n];
        }

        if (costo_local < costo_min_global && estaEnOrdenAlfabetico(actual))
        {
            costo_min_global = costo_local;
        }

        cout << endl;

        return;
    }

    if (pos >= N)
        return;

    elegidos.push_back(pos);
    backtrack(pos + 1, palabras, reversas, costos, elegidos, r - 1, N);
    elegidos.pop_back();

    // Solo continúa si quedan suficientes elementos para completar la combinación
    if (N - (pos + 1) >= r)
    {
        backtrack(pos + 1, palabras, reversas, costos, elegidos, r, N);
    }
}

int main()
{
    const int N = 3;
    const int r = 2;
    // Valor máximo de un entero (infinito)
    vector<string> palabras = {"za", "yb", "xc"};
    // Precomputar reversas una sola vez
    vector<string> reversas(N);
    for (int i = 0; i < N; ++i)
        reversas[i] = invertir(palabras[i]);
    vector<int> costos = {100, 200, 300};
    vector<int> elegidos;

    backtrack(0, palabras, reversas, costos, elegidos, r, N);

    for (const auto &p : palabras)
    {
        cout << p << " ";
    }
    cout << endl;

    cout << "Costo mínimo: " << costo_min_global << endl;
    return 0;
}