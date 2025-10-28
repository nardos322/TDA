#include <bits/stdc++.h>
using namespace std;

/*
    borrar
    ------
    Descripción:
        Versión top-down memoizada para calcular el número mínimo de operaciones
        necesarias para "borrar" toda la cadena `s` siguiendo la misma
        recurrencia usada en la versión backtracking.

    Contrato:
        - Entrada: `s` (string) y `n` = s.size() (se asume n <= 500)
        - Salida: long long con el resultado mínimo

    Enfoque / implementación:
        - Se usa un arreglo estático `memo[500][500]` inicializado a -1 para
            memoizar resultados de subproblemas `memo[l][r]` = f(s,l,r).
        - La función recursiva se implementa como un `lambda` que captura por
            referencia para acceder a `memo` y `s` sin pasarlos como parámetros.

    Complejidad:
        - Tiempo: O(n^3) en el peor caso. Hay O(n^2) estados (pares (l,r)). Para
            cada estado se ejecuta un bucle sobre k de tamaño O(n), por ello O(n^3).
        - Espacio: O(n^2) para la tabla `memo`. Además la recursión usa O(n)
            de stack (profundidad máxima n).

    Notas:
        - Usar un arreglo estático con límite 500 evita realocaciones repetidas y
            es eficiente cuando el límite superior está garantizado. Si se
            prefiere flexibilidad, puede usarse `vector<vector<long long>>`.
        - La inicialización de `memo` con -1 se realiza antes de llamar al lambda.
*/
long long borrar(const string &s, const int n)
{
    static long long memo[500][500];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            memo[i][j] = -1;

    function<long long(int, int)> f = [&](const int l, const int r) -> long long
    {
        if (l > r)
            return 0;
        if (l == r)
            return 1;
        long long &res = memo[l][r];
        if (res != -1)
            return res;

        // Caso A: borrar s[l] por separado
        res = 1 + f(l + 1, r);

        // Caso B: juntar s[l] con algun k tal que s[k] == s[l] "borro lo del medio, pego los extremos y los borro juntos"
        for (int k = l + 1; k <= r; ++k)
        {
            if (s[l] == s[k])
            {
                res = min(res, f(l + 1, k - 1) + f(k, r));
            }
        }

        return res;
    };

    long long ans = f(0, n - 1);
    return ans;
}

void solve(istream &in, ostream &out)
{
    int n;
    in >> n;
    string p;
    in >> p;
    long long ans = borrar(p, n);
    out << ans << "\n";
}

#ifdef LOCAL

void test_borrar()
{

    assert(borrar("ababa", 5) == 3);
    assert(borrar("aaabbb", 6) == 2);
    assert(borrar("abccabccab", 10) == 6);
    assert(borrar("acdeefa", 7) == 5);

    cout << "OK todos los tests pasaron" << endl;
}

#endif

int main()
{
#ifdef LOCAL
    test_borrar();
#else

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve(cin, cout);
#endif
    return 0;
}