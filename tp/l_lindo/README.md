# A. l-lindo

**Límite de tiempo por test:** 2 s  
**Límite de memoria por test:** 256 MB

Un string `s[1…n]`, que solo contiene letras minúsculas del alfabeto inglés, se llama **l‑lindo** si se cumple **al menos una** de las siguientes tres condiciones:

1. **Caso base:** La longitud de `s` es `1` y está compuesta por el carácter `l` (es decir, `s₁ = l`).  
2. **Mitad derecha constante:** La longitud de `s` es mayor que `1`, la **primera mitad** de la cadena consta únicamente del carácter `l` (es decir, `s₁ = s₂ = ⋯ = s_{n/2} = l`) y la **segunda mitad** de la cadena, `s_{n/2+1} s_{n/2+2} … s_n`, es un string `(l+1)`‑lindo.
3. **Mitad izquierda constante:** La longitud de `s` es mayor que `1`, la **segunda mitad** de la cadena consta únicamente del carácter `l` (es decir, `s_{n/2+1} = s_{n/2+2} = ⋯ = s_n = l`) y la **primera mitad** de la cadena, `s₁ s₂ … s_{n/2}`, es un string `(l+1)`‑lindo.

Se garantiza que `n = 2^k` para algún entero `k ≥ 0`.

**Ejemplos:**  
- `"c"` es **c‑lindo**.  
- `"xzyzvwxvw"` es **w‑lindo**.

En un solo movimiento podés elegir un índice `i` de `1` a `n` y **reemplazar `s_i` con cualquier letra minúscula** (cualquier carácter de `'a'` a `'z'`).

Tu tarea es encontrar el **número mínimo de movimientos** necesarios para obtener un string **'a'‑lindo** a partir de `s` (es decir, un string `l`‑lindo para `l = 'a'`). Se garantiza que **la respuesta siempre existe**.

Cada test tendrá `t` casos de prueba independientes. Tené en cuenta el límite de tiempo para la ejecución de todo el programa. Es decir, la suma de los `t` casos de prueba.

---

## Input

- La primera línea de la entrada contiene un entero `t` (`1 ≤ t ≤ 2·10^4`) que corresponde al **número de casos de prueba**.  
- Para cada caso de prueba:
  - La primera línea contiene un entero `n` (`1 ≤ n ≤ 131072`) correspondiente a la **longitud de `s`**. Se garantiza que `n = 2^k` para algún entero `k ≥ 0`.
  - La segunda línea contiene la cadena `s`, compuesta por `n` **letras minúsculas**.

Se garantiza que la **suma de `n`** en todos los casos de prueba no excede `2 · 10^5`.

## Output

Para cada caso de prueba, imprimir un solo número: el **número mínimo de movimientos** necesarios para **obtener un string `'a'‑lindo'** a partir de `s` (es decir, un string `l`‑lindo con `l = 'a'`). **Se garantiza que la respuesta existe**.

---

## Ejemplo

**Input**
```
6
8
aaaadcbb
8
bbaaceaa
8
jkghasdf
1
x
2
da
8
ccddaabb
```

**Output**
```
2
4
7
1
1
5
```

> *Nota:* Este ejemplo corresponde al enunciado. Los valores pueden variar si se usan otros casos.

---

## Explicación breve del concepto

El criterio de “l‑lindo” define recursivamente cadenas de longitud potencia de 2. Para ser `'a'‑lindo`, en cada nivel de la recursión una mitad del string debe ser **constante con la letra actual** (`'a'`, luego `'b'`, etc.) y la otra mitad debe ser **(letra+1)‑linda**.

---

## Idea de solución (opcional)

Un enfoque estándar es **dividir y conquistar** recursivamente:

- Sea `solve(s, l)` el costo mínimo para volver `'l'‑lindo` al string `s`.
- Si `|s| = 1`, el costo es `0` si `s[0] == l`, y `1` en otro caso.
- Si `|s| > 1`, partimos `s` en `sL` y `sR` (mitades). Dos opciones:
  1. Volver **constante `l`** a `sL` (costo = cantidad de caracteres de `sL` distintos de `l`) y recursar `solve(sR, l+1)`.
  2. Volver **constante `l`** a `sR` (costo = cantidad de caracteres de `sR` distintos de `l`) y recursar `solve(sL, l+1)`.
- La respuesta es el **mínimo** entre ambas opciones.

Para acelerar los conteos de “caracteres distintos de `l`” en cada mitad, podés precomputar **prefijos de frecuencias** o, en la implementación clásica para `n = 2^k`, **contar directamente** en cada llamada (cada carácter se procesa `O(log n)` veces).

### Complejidad
- El algoritmo recursivo visita `O(n)` caracteres por **nivel** y hay `O(log n)` niveles (porque `n` siempre es potencia de dos), dando `O(n log n)` en una implementación directa.  
- Con conteos acumulados inteligentes por mitad, se puede mantener el costo práctico bajo y pasar sobrado los límites (`Σ n ≤ 2 · 10^5`). La memoria es `O(log n)` por la pila (o `O(1)` si es iterativo).

---


