# A. Máquina misteriosa
[Problem - A - Codeforces](https://codeforces.com/group/yuAAIJ8c1R/contest/644999/problem/A)  
> **Tiempo por test:** 2 s  
> **Memoria por test:** 256 MB

Carlos encontró un dispositivo extraño. En el panel frontal hay:
- un **botón rojo**,
- un **botón azul**,
- y una pantalla que muestra un **entero positivo**.

Al presionar:
- **Rojo** → la máquina **multiplica por 2** el número mostrado.
- **Azul** → la máquina **resta 1** al número mostrado.

Si el número en pantalla deja de ser positivo, el dispositivo se descompone.  
La pantalla puede mostrar números arbitrariamente grandes.  
Inicialmente, la pantalla muestra el número **`n`**.

Ana quiere obtener el número **`m`** en la pantalla.  
**¿Cuál es el número mínimo de clics** necesarios para lograrlo?

---

## Formato de entrada

Una única línea con dos enteros **distintos** `n` y `m` (`1 ≤ n, m ≤ 10^4`), separados por un espacio.

## Formato de salida

Imprimir un solo entero: el **mínimo** número de pulsaciones para obtener `m` a partir de `n`.

---

## Ejemplos

### Ejemplo 1
**Entrada**
```
8 12
```
**Salida**
```
3
```

### Ejemplo 2
**Entrada**
```
20 15
```
**Salida**
```
5
```

---

## Pistas / Idea de solución (opcional)

Una forma típica de resolverlo es **invertir el proceso** (ir de `m` hacia `n`):

- Si `m ≤ n`, lo óptimo es solo presionar **azul** `n - m` veces.  
- Si `m > n`:
  - Si `m` es **par**, conviene transformar `m ← m / 2` (inversa del botón rojo).
  - Si `m` es **impar**, conviene hacer `m ← m + 1` (inversa de restar 1).
  - Contar los pasos anteriores hasta que `m ≤ n`, y al final sumar `n - m`.

**Complejidad:** `O(log m)` pasos en el bucle principal, pues al menos en la mitad de las iteraciones `m` se reduce a la mitad.



## Notas

- Asegurate de no dejar que el valor en pantalla sea ≤ 0 durante el proceso directo; por eso pensar el problema “al revés” evita ese riesgo y es óptimo.
