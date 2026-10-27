# B. Gasoducto — Enunciado y modelado de la solución

## 1. Enunciado

Se debe instalar un gasoducto a lo largo de una ruta que, para simplificar, se representa mediante el segmento $[0,n]$ del eje horizontal.

La ruta contiene cruces que se modelan como intervalos $(x,x+1)$, para valores enteros de $x$. La descripción de la ruta se da mediante una cadena binaria $s$ de longitud $n$:

- `0`: el intervalo no contiene un cruce.
- `1`: el intervalo contiene un cruce.

Normalmente, el gasoducto se coloca a **altura 1**. Se construye un pilar de soporte en cada posición entera $0,1,\ldots,n$, es decir, un total de $n+1$ pilares. Sin embargo, para no obstaculizar el tránsito, en los intervalos con cruces el gasoducto debe estar a **altura 2**.

Para cambiar de altura se puede construir un tramo en zigzag dentro de un intervalo sin cruce. Este tramo consiste en:

- $0.5$ unidades de caño horizontal;
- $1$ unidad de caño vertical;
- $0.5$ unidades de caño horizontal.

Por lo tanto, recorrer horizontalmente un intervalo cuesta una unidad de caño; si además se cambia de altura, se necesita una unidad adicional de caño vertical.

Cada unidad de caño cuesta $a$ monedas y cada unidad de longitud de pilar cuesta $b$ monedas. En consecuencia, un pilar de altura 1 cuesta $b$ y uno de altura 2 cuesta $2b$.

**Objetivo:** determinar el costo mínimo de construir todo el gasoducto, cumpliendo las siguientes condiciones:

1. Los intervalos con `1` deben atravesarse a altura 2.
2. El gasoducto debe comenzar y terminar a altura 1.
3. Se garantiza que el primer y el último carácter de $s$ son `0`.

### Entrada

La primera línea contiene un entero $T$ ($1\le T\le 100$), la cantidad de casos de prueba.

Cada caso consta de dos líneas:

1. Tres enteros $n,a,b$, donde $2\le n\le 2\cdot 10^5$ y $1\le a,b\le 10^8$.
2. Una cadena binaria $s$ de longitud $n$, con $s_1=s_n=0$.

La suma de las longitudes de todas las cadenas de entrada no supera $2\cdot 10^5$.

### Salida

Para cada caso de prueba, imprimir un entero: el **costo mínimo** de construir el gasoducto.

### Ejemplo

**Entrada**

```text
4
8 2 5
00110010
8 1 1
00110010
9 100000000 100000000
010101010
2 5 1
00
```

**Salida**

```text
94
25
2900000000
13
```

---

## 2. Modelado de la solución — Programación dinámica

### 2.1. Decisiones y estado

Recorremos la ruta **de izquierda a derecha**. En cada posición entera elegimos la altura del **siguiente pilar**, que puede ser 1 o 2, siempre que el intervalo que estamos atravesando permita esa transición.

Definimos la función:

$$
\boxed{f(i,h)}
$$

con la siguiente interpretación:

> $f(i,h)$ es el **costo mínimo de construir desde la posición $i$ hasta la posición $n$**, sabiendo que en la posición $i$ el gasoducto está a altura $h$ y que el pilar de esa posición **ya fue pagado**.

Los parámetros son:

- $i\in\{0,1,\ldots,n\}$: posición actual, correspondiente al pilar ubicado en $x=i$.
- $h\in\{1,2\}$: altura del gasoducto en esa posición.

Utilizamos índices **desde 1 para la cadena**: $s_{i+1}$ describe el intervalo $(i,i+1)$ que vamos a construir.

### 2.2. Costo de una transición

Si desde la altura actual $h$ avanzamos a la siguiente posición con altura $h'$, pagamos:

$$
\boxed{c(h,h')=a+a|h-h'|+bh'}
$$

La expresión incluye:

- $a$: una unidad de caño horizontal.
- $a|h-h'|$: una unidad adicional de caño si cambiamos de altura; cero si la mantenemos.
- $bh'$: el pilar **nuevo** de la posición $i+1$.

| Altura actual $h$ | Altura siguiente $h'$ | Costo del paso |
|:---:|:---:|:---:|
| 1 | 1 | $a+b$ |
| 1 | 2 | $2a+2b$ |
| 2 | 1 | $2a+b$ |
| 2 | 2 | $a+2b$ |

**Restricciones:**

- Si $s_{i+1}=0$, cualquiera de las cuatro transiciones de la tabla está permitida.
- Si $s_{i+1}=1$, el intervalo debe mantenerse a altura 2; la **única** transición permitida es $2\to 2$.

En particular, no está permitido pasar de altura 1 a altura 2 *dentro* de un intervalo con cruce: el zigzag dejaría parte de ese intervalo a altura 1.

### 2.3. Casos base

Al llegar a $i=n$ ya no quedan intervalos ni pilares por construir. Solo es válido terminar a altura 1:

$$
\begin{aligned}
f(n,1)&=0,\\
f(n,2)&=+\infty.
\end{aligned}
$$

El símbolo $+\infty$ representa una configuración imposible o inválida.

### 2.4. Función recursiva por casos

Para evitar anidar entornos matemáticos, podemos escribir **una recurrencia para cada altura**. Son equivalentes a la función $f(i,h)$ definida previamente. La cadena $s$ se indexa desde 1, y $s_{i+1}$ representa el intervalo que se va a construir.

**Si la altura actual es 1:**

$$
f(i,1)=
\begin{cases}
0 & \text{si } i=n, \\
\infty & \text{si } i<n \text{ y } s_{i+1}=1, \\
\min\{a+b+f(i+1,1),\;2a+2b+f(i+1,2)\} & \text{si } i<n \text{ y } s_{i+1}=0.
\end{cases}
$$

**Si la altura actual es 2:**

$$
f(i,2)=
\begin{cases}
\infty & \text{si } i=n, \\
a+2b+f(i+1,2) & \text{si } i<n \text{ y } s_{i+1}=1, \\
\min\{2a+b+f(i+1,1),\;a+2b+f(i+1,2)\} & \text{si } i<n \text{ y } s_{i+1}=0.
\end{cases}
$$

**Interpretación de los casos:**

1. **Fin de la ruta, altura 1:** no queda nada por pagar y cumplimos la condición de finalización.
2. **Fin de la ruta, altura 2:** no es una solución válida.
3. **Intervalo `0`, altura actual 1:** podemos permanecer a altura 1 o subir a 2; elegimos el costo menor.
4. **Intervalo `0`, altura actual 2:** podemos bajar a altura 1 o permanecer a 2; elegimos el costo menor.
5. **Intervalo `1`, altura actual 1:** no podemos atravesar el cruce de manera válida.
6. **Intervalo `1`, altura actual 2:** debemos permanecer a altura 2 y solo existe una transición válida.

**¿Por qué el mínimo no engloba todos los casos?** Cada caso describe un estado diferente. Tomamos el mínimo **solo entre las decisiones válidas que parten del estado actual**. Si hay una sola decisión válida, devolvemos directamente su costo; si no hay ninguna, devolvemos $+\infty$.

### 2.5. Llamada inicial y respuesta

El gasoducto empieza en la posición $0$, a altura 1. Como $f(i,h)$ supone que el pilar actual ya está pagado, primero debemos cobrar el pilar inicial ($b$ monedas):

$$
\boxed{\operatorname{Respuesta}=b+f(0,1)}
$$

**Importante:** cada llamada cobra el siguiente pilar, no el actual; así ningún pilar se cuenta dos veces.

### 2.6. Justificación de la recurrencia

Desde un estado válido $(i,h)$, cualquier construcción posible del resto del gasoducto debe elegir una altura $h'$ válida para el siguiente pilar. Ese primer paso tiene costo $c(h,h')$ y deja pendiente exactamente el subproblema $f(i+1,h')$. Si elegimos una continuación que no fuera óptima para ese subproblema, podríamos reemplazarla por una más barata y mejorar la solución completa.

Por eso, el costo óptimo de cada estado es el **mínimo del costo del primer paso más el costo óptimo restante**, considerando todas y solo las transiciones permitidas. Los casos base verifican la condición de altura final.

### 2.7. Estados y complejidad

La función recibe dos parámetros: $i\in\{0,\ldots,n\}$ y $h\in\{1,2\}$. Por eso existen, como máximo,

$$
2(n+1)=O(n)
$$

estados distintos.

Cada estado compara **a lo sumo dos opciones**, por lo que cuesta $O(1)$, sin contar el costo de los subproblemas ya memoizados.

- **Recursión sin memoización:** en el peor caso, cuando los intervalos son `0`, cada estado puede generar dos llamadas a problemas con una posición menos. La recurrencia temporal es $T(k)=2T(k-1)+O(1)$, de donde $T(n)=\Theta(2^n)$.
- **Top-down con memoización:** cada estado se resuelve una única vez, por lo que el tiempo es $O(n)$.
- **Memoria de memoización:** una tabla `memo[n+1][2]` requiere $O(n)$ espacio; la pila recursiva también puede ocupar $O(n)$.
- **Bottom-up:** como $f(i,h)$ solo depende de estados en $i+1$, se pueden conservar únicamente los dos resultados de la siguiente posición y obtener $O(1)$ espacio auxiliar y $O(n)$ tiempo.

### 2.8. Validación con el ejemplo

Al evaluar $b+f(0,1)$ en cada consulta del enunciado se obtienen, respectivamente:

$$
94,\qquad 25,\qquad 2900000000,\qquad 13.
$$

Coinciden con la salida esperada.
