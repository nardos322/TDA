# C. Ale y los 1s
[Problem - C - Codeforces](https://codeforces.com/group/yuAAIJ8c1R/contest/631549/problem/C)      
> **Límite de tiempo:** 2 s  
> **Límite de memoria:** 256 MB

Ale quiere llegar a ser profe de algoritmos, pero se encontró con un problema que no puede resolver. Inicialmente, Ale tiene una lista con un solo elemento `n`. Luego debe realizar ciertas operaciones en esta lista. En cada operación, Ale debe **eliminar** algún elemento `x`, tal que `x > 1`, de la lista e **insertar en la misma posición** los tres elementos, **en ese orden**:

```
⌊x/2⌋,  x mod 2,  ⌈x/2⌉
```

(donde `⌊·⌋` es el piso y `⌈·⌉` es el techo). Debe continuar con estas operaciones hasta que **todos** los elementos de la lista sean `0` o `1`.

Los jurados del concurso quieren el **número total de 1s** en el **rango** de `l` a `r` (indexado desde `1`, inclusive) de la **lista final**. Ale lamentablemente no pudo resolver este problema. ¿Podrías escribir un programa que lo ayude?

---

## Entrada

Una única línea con tres enteros:

```
n, l, r
```

con restricciones:

- `0 ≤ n < 2^50`
- `0 ≤ r − l < 10^5`
- `r ≥ 1`
- `l ≥ 1`

Se garantiza que `r` **no** es mayor que la longitud de la lista final.

## Salida

Imprimir un único entero: el **número de 1s** en el rango `[l, r]` de la **secuencia final**.

---

## Ejemplos

### Ejemplo 1
**Entrada**
```
6 3 6
```
**Salida**
```
3
```

**Explicación**  
Evolución (una posible) de la lista:

```
[6] → [3, 0, 3] → … → [1, 1, 0, 1, 1]
```

Los elementos en el rango `[3, 6]` de la lista final son `[1, 0, 1, 1]`. El número total de `1`s es `3`.

---

### Ejemplo 2
**Entrada**
```
9 4 11
```
**Salida**
```
5
```

**Explicación**  
Una evolución posible:

```
[9] → [4, 1, 5] → … → [0, 1, 0, 1, 1, 1, 0, 1]
```

Los elementos en el rango `[4, 11]` contienen `5` unos.

---

## Observaciones importantes

- El proceso termina cuando todos los elementos pasan a ser `0` o `1`.
- La **longitud** de la lista final coincide con el número de nodos en el árbol binario que se obtiene expandiendo recursivamente el valor `n` con la regla `x → (⌊x/2⌋, x mod 2, ⌈x/2⌉)` y recorriéndolo **in-order**.
- No es necesario **construir** la lista explícitamente para resolver el problema.

---

## Idea de solución (sugerida)

La expansión anterior induce un árbol ternario/in-order de tamaño `O(número de bits de n)`. Podemos contar `1`s en el rango `[l, r]` en **tiempo logarítmico** mediante divide & conquer.

1. Definí `len(n)` = longitud de la secuencia final generada por `n`. Se cumple:
   - `len(0) = 1`, `len(1) = 1`  
   - `len(n) = len(⌊n/2⌋) + 1 + len(⌈n/2⌉)` para `n > 1`

2. Definí `ones_prefix(n, t)` = cantidad de `1`s en los **primeros** `t` elementos de la secuencia final de `n`. Con recursión e intersecciones de rangos contra las longitudes de los sub-árboles izquierdo (`⌊n/2⌋`), raíz (`n mod 2`) y derecho (`⌈n/2⌉`), se puede calcular en `O(log n)`.

3. Entonces, la respuesta deseada es:
   ```
   ans = ones_prefix(n, r) − ones_prefix(n, l − 1)
   ```

> Esta estrategia evita construir la lista (que puede medir ~`2 * (#bits de n)`), y cumple el límite `r − l < 1e5` con holgura.

### Pseudocódigo (esbozo)
```text
len(n):
  if n <= 1: return 1
  return len(n//2) + 1 + len((n+1)//2)

ones_prefix(n, t):
  if t <= 0: return 0
  if n <= 1: return min(t, n)        # 0 o 1
  L = len(n//2)
  # contribución izquierda
  res = ones_prefix(n//2, min(t, L))
  # contribución de la raíz
  if t > L: res += (n % 2)
  # contribución derecha
  if t > L + 1:
    res += ones_prefix((n+1)//2, t - (L + 1))
  return res
```

## Complejidad

- `len(n)` se memoriza para `O(log n)` estados.  
- Cada llamada a `ones_prefix` toma `O(log n)`.  
- Responder el rango con dos llamadas: **`O(log n)` tiempo** y **`O(log n)` memoria** (recursión + memo).

---

## Casos borde a considerar

- `n ∈ {0, 1}` (la secuencia es de longitud 1).  
- Rango que empieza en `1` o que termina en la **longitud exacta** de la secuencia.  
- `l = r` (un único elemento a consultar).  
- Rangos que caen por completo en el subárbol izquierdo o derecho.

---

## Notas de implementación

- Usar `int64`/`long long` para `n` (hasta `< 2^50`).  
- Memorizar `len(n)` con un `unordered_map`/`map` o un `dict`.  
- Implementar `ones_prefix` de forma recursiva y **sin** construir la secuencia.
- Para lenguajes sin recursión profunda, se puede convertir a versión iterativa con una pila.

---

## Formato de ejecución

Leer `n l r` desde `stdin` y escribir un único entero en `stdout`.

---

## Créditos

Enunciado adaptado del problema **“C. Ale y los 1s”** (traducción al español).

---
# Documentación del algoritmo `ale_1s`

## Resumen

Este programa implementa una función recursiva que cuenta cuántos "1" (números impares) aparecen en un segmento (rango de posiciones) de una secuencia definida recursivamente a partir de un entero n.

La secuencia S(n) se define de forma in-order recursiva como:
- S(1) = [1]
- S(n) = S(⌊n/2⌋) + [n % 2] + S(⌊n/2⌋)

Cada llamada produce una secuencia de longitud 2^{k+1} - 1 donde k = ⌊log2(n)⌋. El programa responde a consultas del tipo: dado n, l y r (1-indexados), cuántos elementos iguales a 1 hay en S(n)[l..r].

## Entrada / Salida

- Entrada: líneas con tres enteros `n l r` hasta EOF. (Ej.: `6 1 7`).
- Salida: para cada línea de entrada se imprime una línea con el número de 1s en el intervalo [l, r] de la secuencia S(n).

Observaciones:
- Las posiciones `l` y `r` son 1-indexadas.
- Si el rango está completamente fuera de la secuencia, el resultado es `0`.

## Estructura del código (funciones principales)

- `constexpr unsigned flog2_n(const uint64_t n)`: calcula ⌊log2(n)⌋ usando `std::bit_width` (C++20).
- `constexpr uint64_t pow2_64(const unsigned k)`: devuelve 2^k con desplazamiento de enteros de 64 bits.
- `uint64_t ale_1s(const uint64_t n, const unsigned k, const uint64_t l, const uint64_t r, const uint64_t offset)`: función recursiva que devuelve el número de 1s en el intervalo [l, r] dentro del segmento definido por el entero `n` y el desplazamiento `offset`.
  - Parámetros:
    - `n`: valor actual (se divide por 2 en las recursiones).
    - `k`: altura / nivel usado para calcular la longitud del segmento (inicialmente `floor(log2(n))`).
    - `l`, `r`: intervalo de consulta (1-indexado global).
    - `offset`: desplazamiento de la posición inicial del segmento actual (permite trabajar con índices globales sin construir la secuencia).
  - Idea: cada segmento representa una secuencia de longitud `len = 2^{k+1} - 1`, con la posición central `mid = offset + 2^k`. Se comprueba si el intervalo [l,r] intersecta el segmento actual. Si no hay intersección se retorna 0. Si hay intersección, se:
    1. Recurre a la izquierda con `n/2` y `offset` (si hay intersección y `n>1`).
    2. Cuenta `1` en el centro si `n` es impar y `mid` está dentro de [l,r].
    3. Recurre a la derecha con `n/2` y `offset = mid` (si hay intersección y `n>1`).

- `void solve(std::istream& in, std::ostream& out)`: lee líneas `n l r` y para cada una calcula `k0 = flog2_n(n)` y llama a `ale_1s(n, k0, l, r, 0)`.

En el código hay una sección de tests activable con la macro `LOCAL` que ejecuta aserciones de ejemplo.

## Correctitud (idea)

La secuencia S(n) está construida como dos copias idénticas de S(⌊n/2⌋) separadas por el bit central `n % 2`. Por tanto, trabajar con índices globales se puede gestionar recursivamente si conocemos la longitud/posición central del bloque que corresponde a `n`. Utilizando `offset` y `k` podemos calcular el rango de posiciones del bloque y el punto central sin construir la secuencia explícita.

La función `ale_1s` evita explorar ramas enteras cuando el intervalo [l, r] no intersecta el segmento actual, lo que reduce el número de llamadas necesarias.

## Complejidad

- Complejidad temporal: depende del tamaño del intervalo consultado y de `n`. En el peor caso (consultar todo el rango) la cantidad de nodos visitados es del orden del número de elementos de la secuencia: O(2^{k+1}) donde k = ⌊log2(n)⌋ (es decir, O(2^{floor(log2 n)+1}) ≈ O(n) en el peor caso). Sin embargo, para intervalos pequeños la recursión se poda y el número de llamadas suele ser mucho menor.
- Complejidad espacial: profundidad máxima de recursión O(k) = O(log n) (por las llamadas recursivas anidadas).

## Casos borde y supuestos

- Si `l > r` o el rango no intersecta la secuencia, el resultado es `0`.
- El programa asume `n >= 1` (no maneja n = 0). Si en el input aparece `n <= 0`, el comportamiento no está definido por el código actual.
- El tipo usado para conteos y offsets es `uint64_t` para acomodar valores grandes. Aun así, para n extremadamente grande (más allá de 2^63) hay que revisar límites prácticos de memoria/tiempos.

## Ejemplos (tomados de los tests en el código)

- Entrada: `6 1 7` → Salida: `6`  (S(6) ≈ [1,3,1,6,1,3,1] en términos de impar/par)
- Entrada: `6 3 6` → Salida: `3`
- Entrada: `4 1 7` → Salida: `4`
- Entrada: `3 10 20` → Salida: `0` (rango fuera)

## Cómo compilar y ejecutar

El proyecto usa CMake. Comandos genéricos:

```bash
# crear carpeta de build (si no existe)
mkdir -p build
cd build
cmake ..
cmake --build .
# ejecutable resultante (ej. ./ale_1s) estará en el directorio de build
```

Ejecutar con entrada por stdin:

```bash
echo "6 1 7" | ./ale_1s
# salida: 6
```

Si prefieres compilar directamente con g++ (rápido para pruebas):

```bash
g++ -std=c++20 -O2 -o ale_1s ../main.cpp
# o para activar los tests locales (macro LOCAL) y ver asserts
g++ -std=c++20 -O2 -DLOCAL -o ale_1s ../main.cpp && ./ale_1s
```

Nota: la ruta `../main.cpp` asume que estás en `build/` y el archivo fuente está en la raíz del proyecto; ajusta la ruta si trabajas desde otro directorio.

## Cómo activar los tests locales

En el código hay un bloque `#ifndef LOCAL ... #else` con casos de prueba que usan `assert`. Para ejecutarlos define la macro `LOCAL` al compilar (ej.: `-DLOCAL`). Esto hará que el `main` ejecute asserts en lugar de leer stdin.

## Siguientes pasos sugeridos

- Añadir validación de entrada para `n <= 0` si se quiere tolerancia a casos inválidos.
- Si se planea procesar muchos queries en línea, envolver en un bucle que lea y responda por cada consulta ya implementado en `solve`.
- Añadir límites/documentación sobre tamaños máximos esperados de `n, l, r` para usuarios.

---

Archivo principal: `main.cpp` (contiene la implementación y tests locales opcionales).

Si quieres, puedo:
- Ejecutar una compilación rápida para verificar que el ejecutable se produce correctamente.
- Modificar el README para incluir más ejemplos o formatos de entrada específicos.
