#include <bits/stdc++.h>
using namespace std;

 
/**
 * @brief Calcula el costo mínimo para ordenar un vector de palabras alfabéticamente,
 *        permitiendo invertir palabras individuales a un costo dado.
 *
 * Dado un vector de palabras `s` y un vector de costos `c`, la función determina el
 * costo mínimo necesario para que la secuencia de palabras quede ordenada
 * alfabéticamente. Para cada palabra, se puede optar por invertirla (revertir sus
 * caracteres) pagando el costo correspondiente en `c`, o dejarla como está sin costo.
 * El objetivo es que la secuencia resultante (considerando las inversiones) sea
 * no decreciente en orden lexicográfico.
 *
 * @param s Vector de strings con las palabras originales.
 * @param c Vector de costos asociados a invertir cada palabra.
 * @return El costo mínimo para lograr el orden alfabético, o -1 si no es posible.
 */
long long alfabeticamente(const vector<string>& s, const vector<long long>& c) {
    const long long INF = (1LL<<60);
    int n = (int)s.size();
    if (n == 0) return 0;

    // r[i] = s[i] invertida
    vector<string> r(n);
    for (int i = 0; i < n; ++i) {
        r[i] = s[i];
        reverse(r[i].begin(), r[i].end());
    }

    // memo[i][p]: costo mínimo desde i hasta el final
    // si la palabra i-1 quedó con estado p (0 normal, 1 invertida)
    vector<array<long long,2>> memo(n, { -1, -1 });
    const string sentinel = "";  // prev para i==0

    function<long long(int,int)> F = [&](int i, int p) -> long long {
        if (i == n) return 0;              // base
        long long &res = memo[i][p];
        if (res != -1) return res;
        res = INF;

        // palabra anterior según p (o "" si i==0)
        const string& prev = (i == 0 ? sentinel : (p ? r[i-1] : s[i-1]));

        // opción 0: dejar s[i] (no pago)
        if (s[i] >= prev)
            res = min(res, F(i+1, 0));

        // opción 1: invertir r[i] (pago c[i])
        if (r[i] >= prev)
            res = min(res, c[i] + F(i+1, 1));

        return res;
    };

    long long ans = F(0, 0);               // empezamos comparando con ""
    return (ans >= INF/2) ? -1 : ans;
}


void solve(istream& in, ostream& out) {
   
    int N;
    in >> N;

    vector<long long> costos(N);
    for (int i = 0; i < N; ++i) 
        in >> costos[i];
    
    vector<string> palabras(N);
    for (int i = 0; i < N; ++i) 
        in >> palabras[i];
    
    
    const long long res = alfabeticamente(palabras, costos);

    out << res << '\n';
}




// ...existing code...

#ifdef LOCAL
void test_alfabeticamente_extra() {
    {
        // N = 0
        vector<string> p; vector<long long> c;
        assert(alfabeticamente(p, c) == 0);
    }
    {
        // N = 1
        vector<string> p = {"xyz"}; vector<long long> c = {123456789};
        assert(alfabeticamente(p, c) == 0);
    }
    {
        // Conviene invertir la 2da (más barato)
        vector<string> p = {"ba", "az"}; vector<long long> c = {100, 1};
        assert(alfabeticamente(p, c) == 1);
    }
    {
        // Solo se puede ordenar invirtiendo la 1ra
        vector<string> p = {"ca", "bb"}; vector<long long> c = {9, 2};
        assert(alfabeticamente(p, c) == 9);
    }
    {
        // Ya ordenado, costos altos no importan
        vector<string> p = {"aa", "ab", "ac"}; vector<long long> c = {100, 100, 100};
        assert(alfabeticamente(p, c) == 0);
    }
    {
        // Todas iguales
        vector<string> p = {"sol", "sol", "sol"}; vector<long long> c = {5, 5, 5};
        assert(alfabeticamente(p, c) == 0);
    }
    {
        // Requiere invertir 2da y 3ra
        vector<string> p = {"abz", "abx", "aby"}; vector<long long> c = {100, 1, 3};
        assert(alfabeticamente(p, c) == 4);
    }
    {
        // String vacío al inicio
        vector<string> p = {"", "a"}; vector<long long> c = {5, 6};
        assert(alfabeticamente(p, c) == 0);
    }
    {
        // Prefijos crecientes
        vector<string> p = {"a", "aa", "aaa", "aaaa"}; vector<long long> c = {7, 7, 7, 7};
        assert(alfabeticamente(p, c) == 0);
    }
    {
        // Imposible ordenar
        vector<string> p = {"ab", "aa", "ac"}; vector<long long> c = {5, 5, 5};
        assert(alfabeticamente(p, c) == -1);
    }
    {
        // Palíndromos: invertir no cambia
        vector<string> p = {"aba", "aba"}; vector<long long> c = {10, 1};
        assert(alfabeticamente(p, c) == 0);
    }
}
#endif

// ...existing code...

int main() {
    #ifdef LOCAL
    test_alfabeticamente_extra();
    cout << "OK Todos los tests pasaron.\n";
    #else
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve(cin, cout);
    #endif
    return 0;
}
