#include <bits/stdc++.h>
using namespace std;

/**
 * potencia_logaritmica
 * --------------------
 * Calcula a^b usando la técnica de exponenciación binaria (divide y vencerás).
 *
 * Parámetros:
 *  - a: base (de tipo `long long`).
 *  - b: exponente no negativo (de tipo `long long`).
 *
 * Devuelve:
 *  - El resultado de elevar `a` a la potencia `b` (tipo `long long`).
 *
 * Complejidad:
 *  - Tiempo: O(log b) — cada llamada reduce el exponente aproximadamente a la mitad.
 *  - Espacio: O(log b) — profundidad de recursión.
 *
 * Observaciones / advertencias:
 *  - La función asume `b >= 0`. No maneja exponentes negativos.
 *  - Las multiplicaciones pueden producir desbordamiento si el resultado no cabe
 *    en un `long long`. Para evitarlo use tipos más grandes (por ejemplo `__int128`)
 *    o algoritmos con módulo cuando corresponda (p. ej. exponenciación modular).
 *  - Para exponentes muy grandes conviene considerar una versión iterativa
 *    para reducir el uso de pila o una versión modular si aplica.
 *
 * Ejemplo:
 *  - potencia_logaritmica(2, 10) -> 1024
 */
long long potencia_logaritmica(const long long a, const long long b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return a;
    }

    const long long mitad = potencia_logaritmica(a, b / 2);

    if (b % 2 == 0)
    {
        return mitad * mitad;
    }
    else
    {
        return a * mitad * mitad;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    cin >> a >> b;

    cout << potencia_logaritmica(a, b) << "\n";

    return 0;
}