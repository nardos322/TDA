#include <iostream>
#include <vector>

/**
 * b_convertibilidad
 * -----------------
 * Intenta determinar si es posible transformar el entero `x` en el entero `y`
 * usando únicamente las dos operaciones:
 *   1) multiplicar por 2:        v -> 2*v
 *   2) multiplicar por 10 y sumar 1: v -> 10*v + 1
 *
 * Contrato / comportamiento:
 * - Parámetros:
 *     - x: valor actual en esta llamada recursiva (no se modifica por la
 *          función; se pasa por valor).
 *     - y: objetivo buscado.
 *     - cadena: vector por referencia que se usa para construir la ruta
 *       desde el valor inicial hasta el objetivo. La convención usada por
 *       este código es que el llamador empuja el valor actual en `cadena`
 *       antes de invocar `b_convertibilidad` (por ejemplo, `main` hace
 *       `cadena.push_back(x)` antes de la primera llamada). La función
 *       empuja los hijos candidatos (2*x y 10*x+1) antes de recursar y
 *       hace pop si esa rama falla; si una rama tiene éxito, deja la ruta
 *       construida en `cadena` y retorna true.
 * - Valor de retorno:
 *     - true si existe una secuencia de operaciones que transforma x en y,
 *       y en ese caso `cadena` contendrá (junto con el valor inicial que
 *       puso el llamador) los valores de la ruta desde el inicio hasta y.
 *     - false si no existe tal secuencia (o si en esta rama se sobrepasa y
 *       no es posible llegar a y).
 *
 * Implementación:
 * - Búsqueda en profundidad (DFS) con backtracking sobre las dos operaciones
 *   posibles. Se prueba primero 2*x; si falla, se prueba 10*x+1.
 * - Caso base: si x == y se retorna true. Si x > y se corta la rama y se
 *   retorna false (ambas operaciones aumentan el valor para enteros no
 *   negativos así que no tiene sentido seguir).
 *
 * Complejidad:
 * - Sea d la profundidad máxima explorada (número de pasos hasta que el
 *   valor sobrepase y). En la rama más lenta (multiplicar por 2),
 *   d = O(log(y/x)). El árbol de búsqueda es binario y en el peor caso se
 *   exploran O(2^d) nodos. Por tanto:
 *     - Tiempo (peor caso): O(2^d). Reexpresado en términos de y/x, 2^d
 *       es aproximadamente y/x, así que una cota práctica es O(y/x).
 *       En resumen: exponencial en la profundidad d (peor caso), que para
 *       valores grandes de y frente a x puede ser prohibitivo.
 *     - Espacio: O(d) por la pila de recursión y por el vector `cadena`
 *       (la función mantiene la ruta desde la raíz a la hoja actual).
 *
 * Supuestos y limitaciones:
 * - Se asume que x y y son enteros dentro del rango de `long long` y que
 *   son no negativos en el uso típico. El código no realiza comprobaciones
 *   de overflow al calcular 2*x o 10*x+1; para evitar UB es recomendable
 *   añadir cheques como `x <= LLONG_MAX/2` y `x <= (LLONG_MAX-1)/10`.
 * - No se usa memoización ni poda adicional, por lo que el tiempo puede
 *   explotar en casos adversos.
 * - Una mejora clásica es realizar la búsqueda inversa desde `y` hacia
 *   `x`: si `y` es par, `y/2` es preimagen; si `y%10==1`, `(y-1)/10` es
 *   preimagen. La búsqueda inversa suele ser lineal en d y evita la
 *   explosión combinatoria.
 */
bool b_convertibilidad(const long long x, const long long y, std::vector<long long> &cadena)
{

    if (x == y)
    {
        return true;
    }

    if (x > y)
    {
        return false;
    }

    cadena.push_back(2 * x);
    if (b_convertibilidad(2 * x, y, cadena))
        return true;
    cadena.pop_back();

    cadena.push_back(10 * x + 1);
    if (b_convertibilidad(10 * x + 1, y, cadena))
        return true;
    cadena.pop_back();

    return false;
}

int main()
{
    std::vector<long long> cadena;
    long long x;
    long long y;
    std::cin >> x >> y;
    cadena.push_back(x);

    if (!b_convertibilidad(x, y, cadena))
    {
        std::cout << "NO" << std::endl;
    }
    else
    {
        std::cout << "YES" << std::endl;
        std::cout << cadena.size() << std::endl;
        for (const auto i : cadena)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}