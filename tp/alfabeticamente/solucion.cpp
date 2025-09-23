#include <bits/stdc++.h>
using namespace std;

static inline string invertir(const string& s) {
    return string(s.rbegin(), s.rend());
}


/**
 * @brief Calcula el costo mínimo para que una secuencia de palabras sea no decreciente
 *        lexicográficamente, permitiendo invertir algunas palabras con un costo asociado.
 *
 * La función decide, para cada palabra, si se deja tal cual o se usa su versión invertida,
 * de modo que la secuencia resultante (palabra por palabra) sea no decreciente en orden
 * lexicográfico. El costo total es la suma de los costos de las palabras que se invierten.
 *
 * - Si no es posible lograr una secuencia no decreciente bajo estas reglas, devuelve -1.
 * - Si el número de palabras es 0, devuelve 0.
 *
 * Parámetros:
 *   @param palabras  Vector de palabras originales, de tamaño N.
 *   @param reversas  Vector de las palabras correspondientes invertidas, de tamaño N.
 *                    Se asume (no se verifica) que reversas[i] es la inversión de palabras[i].
 *   @param costos    Vector de costos de inversión por posición, de tamaño N, con costos[i] ≥ 0.
 *
 * Valor de retorno:
 *   @return long long  Costo mínimo total para conseguir una secuencia no decreciente usando
 *                      cada palabra en su forma original o invertida; -1 si es imposible.
 *
 * Detalles:
 *   - El orden se evalúa usando la comparación lexicográfica estándar de std::string.
 *   - La secuencia resultante debe ser no decreciente (cada elemento es >= al anterior).
 *
 * Complejidad:
 *   - Tiempo: O(N), donde N es la cantidad de palabras. Cada palabra se procesa una vez.
 *   - Memoria adicional: O(1)
 */
long long alfabeticamente(const vector<string> &palabras,
                          const vector<string> &reversas,
                          const vector<long long> &costos) {
    const long long INF = (1LL << 62);
    int N = (int)palabras.size();
    if (N == 0) return 0;

    long long prev0 = 0;          // i=0 normal
    long long prev1 = costos[0];  // i=0 invertida

    for (int i = 1; i < N; ++i) {
        long long cur0 = INF, cur1 = INF;

        if (palabras[i] >= palabras[i-1]) cur0 = min(cur0, prev0);
        if (palabras[i] >= reversas[i-1]) cur0 = min(cur0, prev1);

        if (reversas[i] >= palabras[i-1]) cur1 = min(cur1, prev0 + costos[i]);
        if (reversas[i] >= reversas[i-1]) cur1 = min(cur1, prev1 + costos[i]);

        prev0 = cur0;
        prev1 = cur1;
    }

    long long ans = min(prev0, prev1);
    return (ans >= INF) ? -1 : ans;
}

void solve(istream& in, ostream& out) {
    int N; in >> N;
    vector<long long> costos(N);
    for (int i = 0; i < N; ++i) in >> costos[i];

    vector<string> palabras(N);
    for (int i = 0; i < N; ++i) in >> palabras[i];

    vector<string> reversas(N);
    for (int i = 0; i < N; ++i) reversas[i] = invertir(palabras[i]);

    out << alfabeticamente(palabras, reversas, costos) << '\n';
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

    {
        // Caso 10: Conviene invertir la 2da (más barato)
        vector<string> palabras = {"ba", "az"};
        vector<string> reversas = {"ab", "za"};
        vector<long long> costos = {100, 1};
        long long res = alfabeticamente(palabras, reversas, costos);
        assert(res == 1);
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