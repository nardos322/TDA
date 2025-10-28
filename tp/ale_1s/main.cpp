#include <iostream>
#include <bits/stdc++.h>
#include <bit>

constexpr unsigned flog2_n(const uint64_t n) { return std::bit_width((n)) - 1; }
constexpr uint64_t pow2_64(const unsigned k)
{
    return uint64_t{1} << k;
}

/**
 * Cuenta el número de "1" (números impares) en el subintervalo [l, r] de la
 * secuencia recursiva S(n) definida como:
 *   S(1) = [1]
 *   S(n) = S(floor(n/2)) + [n % 2] + S(floor(n/2))
 *
 * Estrategia:
 * - Cada llamada representa un bloque de longitud len = 2^{k+1} - 1 con
 *   posición central mid = offset + 2^k.
 * - Si el intervalo [l, r] no intersecta el bloque se retorna 0 (poda).
 * - En caso de intersección: se suman recursivamente los 1s de la izquierda,
 *   se cuenta el bit central si está dentro del rango y es impar, y se suman
 *   los 1s de la derecha.
 *
 * Parámetros:
 * - n: valor actual (se utiliza n%2 para el bit central y n/2 para las recursiones).
 * - k: piso(log2(n)), usado para calcular la longitud del bloque y mid.
 * - l, r: límites del intervalo de consulta (1-indexados, relativos a la secuencia completa).
 * - offset: desplazamiento (posición anterior al inicio del bloque); para la
 *   llamada raíz debe ser 0.
 *
 * Retorna:
 * - número de elementos iguales a 1 dentro de S(n)[l..r].
 *
 * Complejidad:
 * - Tiempo (peor caso): O(len) donde len = 2^{k+1}-1 = Θ(2^{floor(log2 n)}) = Θ(n).
 *   Esto ocurre, por ejemplo, si la consulta cubre casi todo el bloque y la
 *   recursión visita la mayoría de los elementos.
 * - Tiempo (mejor/ponderado): la poda evita explorar ramas fuera de [l,r]; para
 *   intervalos muy pequeños la cantidad de llamadas es proporcional a la
 *   profundidad O(k) = O(log n) más una pequeña cantidad por los bordes.
 * - Espacio (pila): O(k) = O(log n) por la recursión.
 *
 * Observaciones:
 * - Las posiciones l y r son 1-indexadas.
 * - El código asume n >= 1. Para n == 0 el comportamiento no está definido.
 */
uint64_t ale_1s(const uint64_t n, const unsigned k, const uint64_t l, const uint64_t r, const uint64_t offset)
{

    // Longitud del segmento actual: len = 2^(k+1) - 1
    const uint64_t len = pow2_64(k + 1) - 1;
    const uint64_t start = offset + 1;
    const uint64_t end = offset + len;

    if (r < start || l > end)
        return 0;

    const uint64_t mid = offset + pow2_64(k);
    uint64_t contador_1s = 0;

    // Izquierda: [start, mid-1]
    if (l < mid && n > 1)
    {
        contador_1s += ale_1s(n / 2, k - 1, l, r, offset);
    }

    // Centro
    if (l <= mid && mid <= r && (n % 2 == 1))
    {
        contador_1s++;
    }

    // Derecha: [mid+1, end]
    if (r > mid && n > 1)
    {
        contador_1s += ale_1s(n / 2, k - 1, l, r, mid);
    }

    // std::cout << n << ":" << mid << n%2 << " " << "["<<l << ":" << r << "]"<< std::endl;

    return contador_1s;
}

void solve(std::istream &in, std::ostream &out)
{
    long long n, l, r;
    while (in >> n >> l >> r)
    {
        const unsigned k0 = flog2_n(n);
        const uint64_t res = ale_1s(n, k0, l, r, 0);
        out << res << '\n';
    }
}

// #define LOCAL
#ifndef LOCAL

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve(std::cin, std::cout);

    return 0;
}
#else
#include <sstream>
#include <cassert>

static std::string run_solve(const std::string &input)
{
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    return out.str();
}

int main()
{

    assert(run_solve("6 1 7\n") == "6\n");   // inorder 6: [1,3,1,6,1,3,1]
    assert(run_solve("6 3 6\n") == "3\n");   // [1,1,1,0,1,1,1] => 3 impares
    assert(run_solve("4 1 7\n") == "4\n");   // [1,0,1,0,1,0,1]
    assert(run_solve("3 1 3\n") == "3\n");   // [1,0,1]
    assert(run_solve("3 10 20\n") == "0\n"); // rango fuera -> 0
    assert(run_solve("9 4 11\n") == "5\n");  // [1,0,1,0,1,0,1,1,1,0,1,0,1,0,1]
    assert(run_solve("6 1 1\n") == "1\n");   // [1,1,1,0,1,1,1]
    assert(run_solve("11 3 7\n") == "4\n");  // [1,0,1,1,1,0,1,1,1,0,1,1,1,0,1]
    assert(run_solve("11 3 8\n") == "5\n");  // [1,0,1,1,1,0,1,1,1,0,1,1,1,0,1]
    std::cerr << "Tests LOCAL OK\n";
    return 0;
}

#endif
