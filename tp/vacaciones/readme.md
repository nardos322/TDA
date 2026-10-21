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

La respuesta al problema se obtiene invocando `dp(0, 0)`. Comenzamos en el día $0$ y simulamos que el día anterior Vasya descansó ($j = 0$), ya que esto no impone ninguna restricción sobre las actividades que puede elegir en su primer día de vacaciones.

### 4. Análisis de Complejidad

* **Complejidad Temporal:** Existen $n$ posibles valores para el día $i$ y $3$ posibles valores para la actividad previa $j$. Esto nos da un total de $3 \cdot n$ estados únicos. Como cada estado se calcula una única vez (gracias a la tabla de memoización `memo[N][3]`) y realiza a lo sumo $3$ transiciones en tiempo constante $\mathcal{O}(1)$, la complejidad temporal total es $\mathcal{O}(n)$.
* **Complejidad Espacial:** Se utiliza una matriz `memo` de dimensiones $n \times 3$ y la pila de llamadas recursivas alcanza una profundidad máxima de $n$. Por lo tanto, la complejidad espacial es $\mathcal{O}(n)$.

---

## Implementación

La solución completa en C++ se encuentra disponible en [`vacaciones.cpp`](./vacaciones.cpp).

---
*Resuelto por **Nahuel Prieto***