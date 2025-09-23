#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <cassert>
#include <array>  
using namespace std;

string invertir(const string &s)
{
    return string(s.rbegin(), s.rend());
}


// DP O(N): dp[i][0] = min costo si palabras[i] sin invertir, dp[i][1] si invertida
long long alfabeticamente(const vector<string> &palabras,
                          const vector<string> &reversas,
                          const vector<long long> &costos)
{
    const long long INF = (1LL << 62);
    const int N = (int)palabras.size();
    if (N == 0) return 0;

    vector<array<long long, 2>> dp(N, {INF, INF});
    dp[0][0] = 0;
    dp[0][1] = costos[0];

    for (int i = 1; i < N; ++i) {
        // Dejar i sin invertir
        if (palabras[i] >= palabras[i - 1])
            dp[i][0] = min(dp[i][0], dp[i - 1][0]);
        if (palabras[i] >= reversas[i - 1])
            dp[i][0] = min(dp[i][0], dp[i - 1][1]);

        // Dejar i invertida
        if (reversas[i] >= palabras[i - 1] && dp[i - 1][0] < INF)
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + costos[i]);
        if (reversas[i] >= reversas[i - 1] && dp[i - 1][1] < INF)
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + costos[i]);
    }

    long long ans = min(dp[N - 1][0], dp[N - 1][1]);
    return (ans >= INF) ? -1 : ans;
}

void solve(istream& in, ostream& out) {
    int N;
    in >> N;

    vector<long long> costos(N);
    for (int i = 0; i < N; ++i) in >> costos[i];

    vector<string> palabras(N);
    for (int i = 0; i < N; ++i) in >> palabras[i];

    vector<string> reversas(N);
    for (int i = 0; i < N; ++i) reversas[i] = invertir(palabras[i]);

    const long long res = alfabeticamente(palabras, reversas, costos);
    out << res << '\n';
}



//#define LOCAL
#ifdef LOCAL
void test_invertir() {
    assert(invertir("hola") == "aloh");
    assert(invertir("") == "");
    assert(invertir("a") == "a");
}



void test_alfabeticamente() {
    {
        vector<string> palabras = {"abc", "def", "ghi"};
        vector<string> reversas = {"cba", "fed", "ihg"};
        vector<long long> costos = {1, 2, 3};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 0);
    }
    {
        vector<string> palabras = {"za", "yb", "xc"};
        vector<string> reversas = {"az", "by", "cx"};
        vector<long long> costos = {100, 200, 300};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 300);
    }
    {
        vector<string> palabras = {"casas", "abraza"};
        vector<string> reversas = {"sasac", "azarba"};
        vector<long long> costos = {0, 0};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == -1);
    }
    {
        // Caso 4: palabras repetidas, siempre está ordenado
        vector<string> palabras = {"sol", "sol"};
        vector<string> reversas = {"los", "los"};
        vector<long long> costos = {5, 5};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 0);
    }
    {
        // Caso 5: Dos palabras, invertir la primera para ordenar
        vector<string> palabras = {"ba", "ac"};
        vector<string> reversas = {"ab", "ca"};
        vector<long long> costos = {10, 20};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 10);
    }
    {
        // Caso 6: Todas iguales, costo mínimo es 0
        vector<string> palabras = {"abc", "abc", "abc"};
        vector<string> reversas = {"cba", "cba", "cba"};
        vector<long long> costos = {1, 2, 3};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 0);
    }
    {
        // Caso 7: Invertir 2 y 3 para ordenar
        vector<string> palabras = {"cba", "gad", "aae"};
        vector<string> reversas = {"abc", "dag", "eaa"};
        vector<long long> costos = {5, 10, 40};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 50);
    }
    {
        // Caso 8: No se puede ordenar ni invirtiendo
        vector<string> palabras = {"z", "y", "x"};
        vector<string> reversas = {"z", "y", "x"};
        vector<long long> costos = {1, 1, 1};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == -1);
    }
    {
        // Caso 9: ordenar la del medio
        vector<string> palabras = {"ge", "an","qm"};
        vector<string> reversas = {"eg", "na","mq"};
        vector<long long> costos = {510, 800, 150};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 800);
    }
}
#endif

int main() {
    #ifdef LOCAL
    test_invertir();
    test_alfabeticamente();
    cout << "OK Todos los tests pasaron.\n";
    #else
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve(cin, cout);
    #endif
    return 0;
}