# B. Borrar
[Problem - B - Codeforces](https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/B)    
**Tiempo límite por test:** 3 s  
**Memoria límite por test:** 256 MB

## Descripción
Tienes un string `s` de `n` letras del alfabeto latino. Puedes aplicar la siguiente operación cualquier cantidad de veces:

- Elige un **substring contiguo** formado por **caracteres iguales** y **bórralo**. Luego concatena las partes restantes.  
  Por ejemplo, en `accacd` podemos borrar el rango `[1, 4)` (los índices del ejemplo son semiabiertos) y obtener `aad`.

Tu objetivo es calcular la **mínima cantidad de operaciones** necesaria para **eliminar por completo** el string `s`.

## Entrada
- La primera línea contiene un entero `n = |s|` ( `1 ≤ n ≤ 500` ).  
- La segunda línea contiene el string `s`.

## Salida
Imprime un único entero: la **mínima cantidad de operaciones** necesaria para borrar `s`.

## Ejemplo
**Entrada**
```
6
aaabbb
```

**Salida**
```
2
```

**Explicación:** primero se borra `aaa` y luego `bbb` (o al revés).

## Notas
- El substring que se borra en cada operación debe estar formado por **un solo carácter repetido** (por ejemplo, `aaa` o `zzzz`).
- Tras cada borrado, las partes restantes se concatenan y pueden generar **nuevos grupos** contiguos de caracteres iguales.

## Ideas de solución (pista)
- Una solución clásica usa **programación dinámica** sobre intervalos: `dp[l][r]` = mínimo número de operaciones para borrar `s[l..r]`.
- Transiciones típicas:
  - Borrar el primer carácter solo: `dp[l][r] = 1 + dp[l+1][r]`.
  - Si `s[l] == s[k]` para algún `k` en `(l, r]`, se puede **unir** el borrado: `dp[l][r] = min(dp[l][r], dp[l+1][k-1] + dp[k][r])`.
- Complejidad esperada: `O(n^3)` por las tres variables `(l, r, k)` con `n ≤ 500`, lo cual es suficiente para los límites dados.

---

> Este README resume el enunciado y deja una guía breve para implementar la solución.



# Documentación - borrar.cpp

## Resumen

Este repositorio contiene una implementación para resolver un problema de "borrar" caracteres con reglas de agrupamiento.
Hay dos implementaciones en `borrar.cpp`:

- `borrar(const string&)`: versión top-down memoizada (recomendada).
- `f(const string&, int, int)`: versión backtracking (fuerza bruta), incluida como referencia.


## Contratos de funciones

- `long long borrar(const string &s)`
  - Entrada: `s` (string), se asume `|s| <= 500`.
  - Salida: entero con el resultado mínimo.

- `long long borrar_bottom_up(const string &s)`
  - Entrada: `s` (string), se asume `|s| <= 500`.
  - Salida: entero con el resultado mínimo.

- `long long f(const string &p, int l, int r)`
  - Entrada: string `p` y rango `[l, r]` (0-based).
  - Salida: resultado recursivo sin memoización.


## Complejidades

- Versión top-down (`borrar` con memo estático):
  - Tiempo: O(n^3) en el peor caso.
  - Espacio: O(n^2) para la tabla de memoización + O(n) de stack.

- Versión bottom-up (equivalente):
  - Tiempo: O(n^3)
  - Espacio: O(n^2)

- Versión backtracking (`f` sin memo):
  - Tiempo: exponencial (O(2^n) en el peor caso)
  - Espacio: O(n) stack


## Notas de implementación

- La versión `borrar` usa `static long long memo[500][500]` y un `lambda`
  recursivo para encapsular la lógica. Esto evita pasar `memo` como parámetro y
  es eficiente cuando se conoce el límite superior `n`.
 

## Cómo compilar y ejecutar tests locales

Para compilar y ejecutar los tests locales que están dentro de `#ifdef LOCAL`:

```bash
g++ -DLOCAL -o borrar_test borrar.cpp
./borrar_test
```

Para compilar sin tests y usar `stdin`/`stdout`:

```bash
g++ -o borrar borrar.cpp
./borrar < input.txt > output.txt
```



