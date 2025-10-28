# B. Convertibilidad
[Problem - B - Codeforces](https://codeforces.com/group/yuAAIJ8c1R/contest/631549/problem/B)    
**Límite de tiempo:** 1 s  
**Límite de memoria:** 256 MB

Carlos tiene un número `x` que quiere convertir en `y`. Tiene dos operaciones:

1. Multiplicar el número actual por `2` (reemplazar `x` por `2·x`).  
2. Añadir el dígito `1` a la derecha (reemplazar `x` por `10·x + 1`).

Las operaciones pueden repetirse múltiples veces.

El objetivo es decir si es posible transformar `x` en `y` usando **solo** esas operaciones. No hace falta minimizar el número de operaciones: alcanza con **encontrar una manera** de transformar `x` en `y` o declarar que es imposible.

---

## Entrada

Una línea con dos enteros positivos `x` y `y` (`1 ≤ x < y ≤ 10^9`):  
el número que Carlos tiene y el número que desea obtener.

## Salida

- Si **no** hay forma de obtener `y` desde `x`, imprimir una sola línea con `NO`.
- En caso contrario, imprimir **tres** líneas:
  1. `YES`
  2. un entero `k` — la **longitud** de la secuencia de transformación
  3. la **secuencia** `x₁, x₂, …, x_k`, donde:
     - `x₁ = x`
     - `x_k = y`
     - y para todo `1 < i ≤ k`, `x_i` se obtiene de `x_{i-1}` aplicando una de las operaciones permitidas.

Si hay varias respuestas válidas, se puede imprimir **cualquiera**.

---

## Ejemplos

**Entrada**
```
1 82
```
**Salida**
```
YES
5
1 2 4 41 82
```

**Entrada**
```
2 45
```
**Salida**
```
NO
```

---

## Idea y Enfoque

En vez de **construir** `y` desde `x`, es más fácil **reconstruir hacia atrás** desde `y` hasta `x`, aplicando las operaciones **inversas**:

- La inversa de `x → 2·x` es: si `y` es **par**, pasar a `y / 2`.
- La inversa de `x → 10·x + 1` es: si `y` **termina en 1**, pasar a `(y - 1) / 10`.

Si `y` no es par **ni** termina en 1, **no** hay ninguna operación inversa válida → es **imposible**.

El proceso termina cuando `y` sea **menor** que `x` (imposible) o cuando `y == x` (éxito).  
Durante la reconstrucción guardamos los valores visitados y al final invertimos el orden para reportar la secuencia desde `x` hasta `y`.

### Correctitud (esbozo)

- Cada paso hacia atrás aplica la **única** posible operación inversa válida.  
- Si alguna vez `y` no es par ni termina en 1, entonces no existe un antecesor que respete las reglas → no hay secuencia válida.  
- Si alcanzamos `x`, al invertir el recorrido obtenemos una secuencia donde cada transición es exactamente una de las dos operaciones originales. Por lo tanto, la secuencia es válida.

### Complejidad

El número de pasos es a lo sumo el número de dígitos de `y` más el número de factores de 2 aplicables; en cualquier caso es `O(log y)`.  
El consumo de memoria es `O(log y)` para guardar la secuencia.

---

## Pseudocódigo

```text
leer x, y
seq = [y]
mientras y > x:
    si y % 2 == 0:
        y = y / 2
    sino si y % 10 == 1:
        y = (y - 1) / 10
    sino:
        imprimir "NO" y terminar
    agregar y a seq

si y != x:
    imprimir "NO"
sino:
    invertir(seq)  // ahora va de x a y
    imprimir "YES"
    imprimir longitud(seq)
    imprimir elementos de seq separados por espacios
```

---

## Detalles de implementación

- Usar enteros de 64 bits si el lenguaje lo requiere (por seguridad).  
- La secuencia debe imprimirse **en orden creciente de transformación** (desde `x` hasta `y`).  
- En C++/Java/Python no hace falta optimización especial; el bucle es muy corto por los límites.

---

## Casos borde a considerar

- `y` termina en un dígito distinto de `1` y es impar → **NO** inmediatamente.  
- `x` muy cercano a `y` (pocos pasos).  
- Secuencias con varios pasos de “quitar 1 y dividir por 10” seguidos (p. ej., `… → 41 → 4`).

---

## Notas

Este problema es clásico de “construcción inversa”. Pensar al revés suele simplificar notablemente la búsqueda de una secuencia válida.




# DOCS

Este repositorio contiene una solución en C++ para el problema de convertir un número entero x en otro número entero y usando únicamente dos operaciones:

- multiplicar por 2: x -> 2*x
- multiplicar por 10 y sumar 1: x -> 10*x + 1

El programa determina si es posible transformar x en y aplicando una secuencia (posiblemente vacía) de estas operaciones. Si es posible, imprime "YES", la longitud de la cadena (cantidad de valores en la secuencia, incluyendo x y y) y la secuencia completa desde x hasta y; en caso contrario imprime "NO".

## Archivo principal

- `main.cpp`: implementación en C++ (función `b_convertibilidad` y `main`).

## Contrato (inputs / outputs)

- Entrada: dos enteros (long long) `x` y `y` leídos desde la entrada estándar.
- Salida:
  - Si no es posible convertir `x` en `y`: imprime `NO` seguido de salto de línea.
  - Si es posible: imprime `YES`, una nueva línea con el número de elementos de la cadena (incluyendo `x` y `y`), y una línea con la secuencia de números separados por espacios.

Ejemplo de entrada:
```
2 162
```
Salida esperada (una posible salida válida):
```
YES
5
2 4 8 16 161
```
(Nota: el ejemplo es ilustrativo — la secuencia mostrada debe corresponder a una ruta válida desde `x` hasta `y` usando las operaciones permitidas.)

## Explicación del algoritmo

La función `b_convertibilidad(long long x, long long y, std::vector<long long>& cadena)` implementa una búsqueda recursiva (DFS) con backtracking:

1. Caso base: si `x == y` devuelve `true` (la cadena actual contiene la transformación completa).
2. Si `x > y`, devuelve `false` (ambas operaciones aumentan el valor, por lo que no tiene sentido continuar).
3. Intenta extender la cadena con `2*x`. Si la llamada recursiva desde ese valor devuelve `true`, se propaga `true` hacia arriba.
4. Si falla, hace backtrack (elimina el último valor) e intenta con `10*x + 1`.
5. Si ambas ramas fallan, devuelve `false`.

El `main` inicializa la cadena con `x`, llama a `b_convertibilidad` y muestra `YES` y la cadena resultante cuando hay éxito.

## Complejidad

Denotemos d el número máximo de pasos (profundidad) necesarios para que el valor sobrepase `y` partiendo de `x`. La operación que más lentamente aumenta el valor es la multiplicación por 2, por lo que

d ≤ floor(log2(y/x)) (aproximadamente).

- Tiempo (peor caso): la búsqueda explora un árbol binario completo de profundidad ≤ d. El número de nodos de un árbol binario completo de profundidad d es O(2^d). Como 2^d ≈ y/x, podemos estimar el coste asintótico aproximado como O(y/x) llamadas recursivas en el peor caso. En términos más intuitivos:
  - Peor caso: exponencial respecto de la profundidad d (O(2^d)), pero dicho valor se puede reexpresar como O(y/x).

- Espacio:
  - Uso de pila de llamadas (recursión): O(d) = O(log(y/x)).
  - Vector `cadena` que almacena la ruta: O(d).

Observación: cuando `y` es muy grande comparado con `x`, el número de nodos a explorar puede ser grande (linear en `y/x` aproximadamente), por lo que el algoritmo puede ser costoso en tiempo.

## Limitaciones y consideraciones

- Overflow: el código usa `long long` y no comprueba overflow al calcular `2*x` o `10*x + 1`. Si `x` es lo bastante grande, estas operaciones pueden desbordar. Recomendaciones:
  - Añadir comprobaciones antes de calcular `2*x` o `10*x + 1` (por ejemplo, verificar `x <= LLONG_MAX/2` y `x <= (LLONG_MAX - 1)/10`).
  - Usar enteros de mayor tamaño (biblioteca de enteros grandes) si se espera trabajar con valores fuera del rango de `long long`.

- Detección de ciclos: con las dos operaciones que siempre aumentan el valor en enteros positivos, no hay ciclos, por lo que no es necesario un set de visitados en este caso; sin embargo, la suposición de que ambas operaciones aumentan depende de que `x >= 0`.

- Mejoras posibles:
  - Búsqueda inversa (desde `y` hacia `x`): en muchos problemas similares conviene intentar revertir las operaciones (si `y` par, considerar `y/2`; si `y % 10 == 1`, considerar `(y-1)/10`) y realizar una búsqueda hacia atrás — esto convierte el problema en una búsqueda determinista en O(d) (seguir pasos únicos), evitando la explosión combinatoria. Concretamente, desde `y` se puede aplicar:
    - Si `y % 2 == 0` entonces `y = y / 2` es una posible preimagen.
    - Si `y % 10 == 1` entonces `y = (y - 1) / 10` es una posible preimagen.
    - Repetir hasta alcanzar `x` o hacerlo imposible. Esta estrategia es más eficiente y comúnmente usada en soluciones óptimas.

## Cómo compilar y ejecutar

Este proyecto incluye un `CMakeLists.txt`. Para compilar desde la raíz del proyecto en Linux (modo out-of-source):

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
# ejecutable resultante (según CMakeLists.txt) presumiblemente `b_convertibilidad` en la carpeta build
./b_convertibilidad
```

Como alternativa rápida (sólo para probar `main.cpp`):

```bash
g++ -std=c++17 -O2 ../main.cpp -o b_convertibilidad
./b_convertibilidad
```

(En el segundo caso asegúrate de ejecutar el comando desde la carpeta `cmake-build-debug` o ajustar la ruta a `main.cpp` según tu ubicación actual.)

## Ejemplos

Entrada:
```
4 42
```
Salida (posible):
```
NO
```
Entrada:
```
1 101
```
Salida (posible):
```
YES
3
1 10 101
```

