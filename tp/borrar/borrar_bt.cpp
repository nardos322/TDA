#include <bits/stdc++.h>
using namespace std;

/*
    f - backtracking (fuerza bruta)
    --------------------------------
    Descripción:
    - Implementación recursiva sin memoización que calcula el mínimo número de
        operaciones para "borrar" la subcadena p[l..r] siguiendo la misma
        recurrencia que las versiones DP.

    Contrato:
    - Entrada: `p` (string), `l` y `r` (índices 0-based, con l <= r normalmente)
    - Salida: valor mínimo entero (tipo long long)

    Complejidad:
    - Tiempo: exponencial en el peor caso, aproximadamente O(2^n). La función
        explora muchas ramas y recalcula subproblemas repetidamente.
    - Espacio: O(n) por la profundidad de la pila de recursión.

    Nota:
    - Esta versión es útil para entender la lógica. Para resolver instancias
        grandes conviene usar una versión memoizada (top-down) o bottom-up (DP),
        que reducen la complejidad a O(n^3).
*/
long long f(const string &p, const int l, const int r)
{

    if (l > r)
        return 0;
    if (l == r)
        return 1;

    long long ans = 1 + f(p, l + 1, r);
    for (int k = l + 1; k <= r; k++)
    {
        if (p[l] == p[k])
        {
            ans = min(ans, f(p, l + 1, k - 1) + f(p, k, r));
        }
    }

    return ans;
}

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}