# A. Vacaciones

**Límite de tiempo por prueba:** 2 s  
**Límite de memoria por prueba:** 256 MB

---

## Enunciado

¡Vasya tiene $n$ días de vacaciones! Por eso decidió mejorar sus habilidades informáticas y hacer deporte. Vasya conoce la siguiente información sobre cada uno de estos $n$ días: si el gimnasio está abierto y si se realiza una competencia por internet ese día. Para el $i$-ésimo día hay cuatro opciones:

1. ese día el gimnasio está cerrado y no se realiza la competencia por internet;
2. ese día el gimnasio está cerrado y se realiza la competencia por internet;
3. ese día el gimnasio está abierto y no se realiza la competencia por internet;
4. ese día el gimnasio está abierto y se realiza la competencia por internet.

Cada día, Vasya puede descansar, participar en la competencia por internet (si se realiza ese día) o hacer deporte (si el gimnasio está abierto ese día).

Hallar la cantidad mínima de días en los que Vasya descansará (es decir, en los que no hace deporte ni participa en la competencia por internet). La única restricción que tiene Vasya es que *no quiere hacer la misma actividad dos días consecutivos: es decir, no hará deporte dos días consecutivos ni participará en la competencia por internet dos días consecutivos.*

### Input

La primera línea contiene un entero positivo $n$ ($1 \le n \le 100$), la cantidad de días de vacaciones de Vasya.

La segunda línea contiene la secuencia de enteros $a_1, a_2, \dots, a_n$ ($0 \le a_i \le 3$) separados por espacios, donde:

* $a_i$ es igual a $0$ si el $i$-ésimo día de vacaciones el gimnasio está cerrado y no se realiza la competencia por internet;
* $a_i$ es igual a $1$ si el $i$-ésimo día de vacaciones el gimnasio está cerrado, pero se realiza la competencia por internet;
* $a_i$ es igual a $2$ si el $i$-ésimo día de vacaciones el gimnasio está abierto y no se realiza la competencia por internet;
* $a_i$ es igual a $3$ si el $i$-ésimo día de vacaciones el gimnasio está abierto y se realiza la competencia por internet.

### Output

Imprimir la cantidad mínima posible de días en los que Vasya descansará. Recordar que Vasya se niega a:

* hacer deporte dos días consecutivos;
* participar en la competencia por internet dos días consecutivos.

### Examples

#### Ejemplo 1

**Input**
```text
4
1 3 2 0
```

**Output**
```text
2
```

#### Ejemplo 2

**Input**
```text
7
1 3 3 2 1 2 3
```

**Output**
```text
0
```

#### Ejemplo 3

**Input**
```text
2
2 2
```

**Output**
```text
1
```

### Note

En el primer caso de prueba, Vasya puede participar en la competencia por internet el día $1$ y hacer deporte el día $3$. Así, descansará solo $2$ días.

En el segundo caso de prueba, Vasya debe participar en las competencias por internet de los días $1, 3, 5$ y $7$, y hacer deporte los demás días. Así, no descansará ningún día.

En el tercer caso de prueba, Vasya puede hacer deporte el día $1$ o el día $2$. No puede hacer deporte ambos días, porque violaría su restricción. Así, descansará solo un día.

---

## Idea principal

Para cada día, Vasya tiene hasta tres decisiones:

* descansar;
* competir (si hay competencia y no compitió el día anterior);
* hacer deporte (si el gimnasio está abierto y no hizo deporte el día anterior).

La clave es que, para decidir qué conviene hoy, solo importa qué actividad realizó ayer. Por eso el estado de la programación dinámica necesita recordar únicamente la actividad del día anterior.

---

## Modelado de la Solución

El problema se puede resolver utilizando **Programación Dinámica (Enfoque Top-Down con Memoización)**, ya que las decisiones tomadas en el día actual dependen únicamente de la actividad realizada el día inmediatamente anterior y presentan superposición de subproblemas.

### 1. Definición del Estado

Para modelar el problema (reindexando la secuencia de entrada $a_0, a_1, \dots, a_{n-1}$ desde $0$), definimos un estado mediante dos parámetros $(i, j)$:

* $i \in \{0, 1, \dots, n\}$: Representa el índice del día actual que estamos evaluando.
* $j \in \{0, 1, 2\}$: Representa la actividad que Vasya realizó el día anterior ($i - 1$), codificada de la siguiente manera:
  * $j = 0$: Descansó (o es el estado inicial antes de comenzar las vacaciones).
  * $j = 1$: Participó en la competencia por internet.
  * $j = 2$: Hizo deporte en el gimnasio.

### 2. Función Recursiva y Transiciones

Definimos la función $\text{dp}(i, j)$ como **la mínima cantidad de días de descanso desde el día $i$ hasta el día $n - 1$, dado que en el día $i - 1$ se realizó la actividad $j$**.

#### Caso Base

Si hemos llegado al final de las vacaciones ($i \ge n$), ya no quedan días por evaluar, por lo que la cantidad de días de descanso adicionales es $0$:

$$\text{dp}(n, j) = 0 \quad \forall j \in \{0, 1, 2\}$$

#### Paso Recursivo (Transiciones)

Para un día $i < n$, evaluamos hasta tres decisiones posibles y nos quedamos con la que minimice el resultado:

1. **Descansar hoy ($j_{\text{nuevo}} = 0$):** Esta opción siempre es válida sin importar qué ocurrió ayer ni qué actividades están disponibles hoy. Suma $1$ al contador de descansos:

   $$\text{Opción}_0 = 1 + \text{dp}(i + 1, 0)$$

2. **Competir hoy ($j_{\text{nuevo}} = 1$):** Solo es válido si ayer **no** compitió ($j \neq 1$) y hoy hay competencia disponible ($a_i = 1$ o $a_i = 3$). No suma días de descanso:

   $$\text{Opción}_1 = \text{dp}(i + 1, 1)$$

3. **Ir al gimnasio hoy ($j_{\text{nuevo}} = 2$):** Solo es válido si ayer **no** fue al gimnasio ($j \neq 2$) y hoy el gimnasio está abierto ($a_i = 2$ o $a_i = 3$). No suma días de descanso:

   $$\text{Opción}_2 = \text{dp}(i + 1, 2)$$

#### Ecuación de Recurrencia General

Combinando el caso base y las transiciones válidas, la función queda definida formalmente como:

$$\text{dp}(i, j) = \begin{cases} 0 & \text{si } i \ge n \\ \min \begin{cases} 1 + \text{dp}(i + 1, 0) \\ \text{dp}(i + 1, 1) & \text{si } j \neq 1 \land (a_i = 1 \lor a_i = 3) \\ \text{dp}(i + 1, 2) & \text{si } j \neq 2 \land (a_i = 2 \lor a_i = 3) \end{cases} & \text{si } i < n \end{cases}$$

### 3. Llamada Inicial

La respuesta al problema se obtiene invocando `dp(0, 0)`. Comenzamos en el día $0$ con `j = 0` para representar el estado inicial **sin actividad previa real**; no significa que Vasya haya descansado un día de vacaciones antes de empezar. Esta codificación simplemente indica que, en el primer día, no hay una actividad anterior que restrinja competir o hacer deporte.

### 4. Análisis de Complejidad

* **Tiempo: O(n).** Hay $n$ días y $3$ posibles valores de actividad previa (`j = 0, 1, 2`), es decir, $3n$ estados. Como esos 3 estados son una constante y cada estado se resuelve una sola vez con memoización, el tiempo total es lineal en $n$.
* **Memoria: O(n).** La tabla `memo` tiene tamaño $n \times 3$ y la recursión tiene profundidad máxima $n$. El factor 3 es constante, por lo que el uso de memoria total también es lineal en $n$.

---

## Compilación y ejecución

```bash
g++ -std=c++17 -O2 -Wall vacaciones.cpp -o vacaciones
./vacaciones
```

---

## Implementación

La solución implementada en [`vacaciones.cpp`](./vacaciones.cpp) utiliza un enfoque **top-down con memoización**:

* define `dp(i, j)` de forma recursiva;
* guarda resultados ya calculados en `memo[i][j]`;
* evita recomputar subproblemas y mantiene la complejidad lineal.

---
*Resuelto por **Nahuel Prieto***