#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Busca un "índice espejo" en el arreglo A usando búsqueda binaria.
 *
 * Definición usada aquí: un índice espejo es una posición i tal que
 * A[i] == i+1. La función devuelve el índice en base 1 (i+1) cuando existe,
 * o -1 si no existe ninguno.
 *
 * Supuestos / precondiciones:
 * - El vector `A` debe estar ordenado de forma que la función de comparación
 *   A[i] - (i+1) sea monotónica (p. ej. `A` estrictamente creciente). Esto
 *   garantiza que se pueda aplicar búsqueda binaria.
 * - `l` y `r` son los extremos (índices 0-based) del intervalo en el que se
 *   realiza la búsqueda.
 *
 * Parámetros:
 * @param A Vector de enteros (const reference).
 * @param l Límite izquierdo del intervalo (0-based).
 * @param r Límite derecho del intervalo (0-based).
 *
 * Valor devuelto:
 * @return El índice espejo en base 1 (i+1) si se encuentra; -1 en caso contrario.
 *
 * Complejidad:
 * - Tiempo: O(log n) en función del tamaño del intervalo, por búsqueda binaria.
 * - Memoria: O(1) adicional (más la profundidad de recursión: O(log n) en pila).
 *
 * Ejemplo:
 * - Para A = [1, 3, 3, 4], la función puede devolver 1 (porque A[0] == 1).
 */
int indice_espejo(const vector<int> &A, const int l, const int r)
{
    if (l > r)
    {
        return -1; // Caso base: no se encontró el índice espejo
    }

    if (const int i = (l + r) / 2; A[i] == i + 1)
    {
        return i + 1;
    }
    else if (A[i] > i + 1)
    {
        return indice_espejo(A, l, i - 1);
    }
    else
    {
        return indice_espejo(A, i + 1, r);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> A[i];
    }

    const int resultado = indice_espejo(A, 0, n - 1);
    if (resultado == -1)
    {
        cout << "NO EXISTE\n";
    }
    else
    {
        cout << resultado << "\n";
    }

    return 0;
}