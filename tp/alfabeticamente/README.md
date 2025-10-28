# A. Alfabéticamente
[Problem - A - Codeforces](https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/A)        
**time limit per test:** 1 s  
**memory limit per test:** 256 MB

Juan tiene `n` *strings* de letras minúsculas del alfabeto inglés. Quiere **ordenarlas alfabéticamente**, pero **no tiene permitido cambiarlas de lugar**. Lo único que puede hacer es **dar vuelta** algunas de ellas (dar vuelta un *string* es leerlo de atrás para adelante). Dos palabras iguales consecutivas se consideran ordenadas.

Para dar vuelta el *string* `i` tiene que gastar `c_i` unidades de energía. Él quiere **minimizar** la cantidad de energía que necesita gastar para que las palabras queden en orden alfabético.

## Input

- La primera línea del input contiene un entero `n` (`2 ≤ n ≤ 100.000`), la cantidad de palabras.  
- La siguiente línea contiene los `n` enteros `c_i` (`0 ≤ c_i ≤ 10^9`).  
- Las últimas `n` líneas contienen cada una de los *strings* a ordenar. La **longitud total** de todos los *strings* es menor o igual a `100.000` caracteres.

## Output

Si es imposible invertir algunas (posiblemente `0`) de las *strings* para que queden ordenadas alfabéticamente, imprimir `-1`. En caso contrario, imprimir la **mínima** cantidad de energía que Juan necesita gastar para lograr su objetivo.

## Examples

### input
```
3
100 200 300
abc
efg
hij
```
### output
```
0
```

---

### input
```
3
100 200 300
za
yb
xc
```
### output
```
300
```

---

### input
```
2
0 0
casas
abraza
```
### output
```
-1
```



---

# Proyecto: alfabeticamente

Resumen
- Implementaciones para el problema "alfabéticamente": dada una secuencia de palabras y un costo por invertir (reversar) cada palabra, decidir cuáles invertir para que la secuencia resultante sea no decreciente lexicográficamente y minimizar el costo total.
- Si no es posible, la solución debe devolver `-1`.

Estructura de archivos
- `solucion.cpp`  
  - Implementación recomendada (iterativa, O(N) en estados). Usa dos estados por posición (normal / invertida) y actualiza de forma iterativa. Es la versión más eficiente y sencilla de usar.
  - Interfaz en `solve(istream&, ostream&)` que lee del estándar input y escribe en output.
- `alfabeticamente_top_down.cpp`  
  - Implementación top-down con memoización (recursiva). Usa `std::function` y una lambda recursiva. Mantiene `memo[i][p]` donde `p` indica si la palabra anterior quedó invertida.
  - Usa `sentinel = ""` para unificar el caso base (i == 0).
- `alfabeticamente_bottum_up.cpp`  
  - Implementación bottom-up (iterativa) clásica del problema con DP tabulado.
- `alfabeticamente_bt.cpp`  
  - Backtracking (fuerza bruta), útil solo para N pequeños o para validar soluciones.

Compilación y ejecución (Linux)
- Requisitos: g++ (>= C++17)
- Compilar y ejecutar la solución recomendada:
  - g++ -std=c++17 solucion.cpp -O2 -o run && ./run
- Compilar con tests integrados (macro `LOCAL`) en `solucion.cpp`:
  - g++ -std=c++17 -DLOCAL solucion.cpp -O2 -o run && ./run
- Para `alfabeticamente_top_down.cpp` (archivo a veces con tests locales):
  - g++ -std=c++17 -DLOCAL alfabeticamente_top_down.cpp -O2 -o run_top && ./run_top

Formato de entrada esperado por `solve` (ejemplo usado en `solucion.cpp`)
- Entrada:
  - N
  - N enteros: costos[0..N-1]
  - N strings: palabras[0..N-1]
- Ejemplo:
  ```
  3
  5 1 3
  aba bca aaa
  ```
- Salida: un solo número: costo mínimo o `-1` si no es posible.

APIs principales (resumen)
- solucion.cpp:
  - long long alfabeticamente(const vector<string>& palabras,
                             const vector<string>& reversas,
                             const vector<long long>& costos)
    - Retorna el costo mínimo o `-1`.
    - `reversas[i]` debe ser la reversa de `palabras[i]` (el código genera `reversas` internamente en `solve`).
- alfabeticamente_top_down.cpp:
  - long long alfabeticamente(const vector<string>& s, const vector<long long>& c)
    - Misma semántica: retorna costo mínimo o `-1`.
    - Implementación recursiva con memoización.
- alfabeticamente_bottum_up.cpp:
  - Versión iterativa tabulada. (Puede tener firma distinta en tu archivo; revisar encabezado para uso.)
- alfabeticamente_bt.cpp:
  - Implementación por backtracking para validación o N pequeño.

Puntos importantes y notas de implementación
- sentinel (`""`) en la versión top-down se usa para simplificar la primera comparación (i == 0). Cualquier palabra es >= `""`.
- `memo` suele inicializarse con `-1` para indicar "no calculado": `vector<array<long long,2>> memo(n, { -1, -1 });` — cada elemento es un array de tamaño 2 (estados anteriores 0/1).
- Uso de `INF` y comprobación final `ans >= INF/2` es una práctica defensiva para detectar soluciones imposibles sin riesgos de overflow cuando se suman costos.
- `array<long long, 2>`: el `2` indica el tamaño fijo del array (dos estados por posición).
- `solucion.cpp` es la implementación recomendada por claridad, eficiencia y menor overhead (sin recursión ni std::function).

Tests recomendados (casos básicos)
- N = 0 -> salida 0
- N = 1 -> salida 0 (nunca conviene pagar)
- Casos donde conviene invertir alguna palabra por bajo costo
- Casos imposibles -> `-1`
- Palíndromos (invertir no cambia la palabra)
- Secuencias ya ordenadas -> 0

Ejemplo de test rápido (puedes poner en `#ifdef LOCAL` en cualquier archivo):
- palabras = {"ba", "az"}, costos = {100, 1} -> resultado 1
- palabras = {"ab", "aa", "ac"}, costos = {5, 5, 5} -> resultado -1

Consejo final
- Usar `solucion.cpp` como versión principal para envío/producción.
- Mantener top-down y bottom-up como referencia didáctica y para depuración.
- El backtracking (`alfabeticamente_bt.cpp`) solo para validar con N pequeño.

---

# Proyecto: alfabeticamente — Complejidad y notas técnicas

Resumen rápido
- Problema: dada una secuencia de N palabras y un costo por invertir cada palabra, elegir cuáles invertir para que la secuencia resultante sea no decreciente lexicográficamente, minimizando el costo total. Si no es posible, devolver `-1`.
- Notación:
  - N = número de palabras
  - L = longitud máxima de una palabra (coste de comparar o invertir una palabra)
  - Se asume comparación lexicográfica estándar de `std::string`.

Archivos y complejidades

1) solucion.cpp (recomendado — solución iterativa O(N))
- Idea: DP iterativo con 2 estados por posición (no invertida / invertida) y actualización en una pasada.
- Tiempo:
  - Construcción de `reversas`: O(N * L)
  - Bucle principal: O(N) iteraciones × O(1) comparaciones por iteración, pero cada comparación es O(L) → O(N * L)
  - Total: O(N * L)
- Memoria:
  - Entrada: O(N * L)
  - Memoria extra: O(1) (constantes `prev0`, `prev1`) + `reversas` (O(N * L) si contamos almacenamiento)
  - Total adicional: O(1) (más almacenamiento para las strings ya leídas)
- Ventajas: bajo overhead, sin recursión, uso constante de memoria para DP.

2) alfabeticamente_top_down.cpp (top‑down con memoización)
- Idea: recursion con `std::function` y `memo[i][p]` (2 estados por posición).
- Tiempo:
  - Cada estado (i, p) se calcula a lo sumo una vez. Estados = 2N.
  - Cada transición hace comparaciones de strings O(L).
  - Total: O(N * L)
- Memoria:
  - `memo`: O(N) (cada elemento almacena 2 long long)
  - `r` (reversas): O(N * L)
  - Pila de recursión: O(N) profundidad en el peor caso
  - Total adicional: O(N + N*L) (contando strings), con O(N) extra para memo y stack
- Notas: overhead de `std::function` y riesgo de stack overflow para N grande.

3) alfabeticamente_bottum_up.cpp (bottom‑up tabulado)
- Idea: DP tabulado con 2 estados por índice, similar a `solucion.cpp` pero más explícito.
- Tiempo: O(N * L) (igual razonamiento: O(1) transiciones por i pero comparaciones O(L))
- Memoria:
  - DP tabulado: O(N) (2 estados por i)
  - Reversas: O(N * L)
  - Total adicional: O(N + N*L)
- Ventajas: iterativo, sin recursión; uso de memoria O(N) en DP (vs O(1) en `solucion.cpp`)

4) alfabeticamente_bt.cpp (backtracking / fuerza bruta)
- Idea: probar todas las combinaciones (invertir o no) — útil sólo para N pequeño / validación.
- Tiempo:
  - Hay 2^N combinaciones; verificar una combinación cuesta O(N * L)
  - Total: O(2^N * N * L) — prohibitivo para N medianos/grandes
- Memoria:
  - O(N * L) para entrada; recursión O(N) profundidad
- Uso: pruebas y validación en instancias pequeñas.

Detalles y consideraciones prácticas
- Comparaciones de `std::string` en C++ son O(L) en el peor caso; por eso la complejidad temporal se expresa como O(N * L).
- Construir `reversas[i]` cuesta O(L) por palabra; esto es necesario en la mayoría de implementaciones.
- Uso de INF y comprobación `ans >= INF/2` en top‑down: defensiva para evitar errores por overflow al sumar costos con valores "infinitos".
- `memo` inicializado con `{ -1, -1 }` indica "no calculado" (los costos válidos son no negativos).
- `array<long long,2>`: el `2` indica los dos estados (palabra anterior quedó normal o invertida).

Recomendación
- Para uso práctico y envío, usar `solucion.cpp` (menor overhead, O(N * L) tiempo, O(1) memoria extra).
- Mantener las versiones top‑down / bottom‑up para comparación didáctica y depuración; usar backtracking solo para tests exhaustivos en N pequeño.



