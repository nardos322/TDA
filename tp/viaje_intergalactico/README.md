# B. Viaje Intergaláctico
[Problem - B - Codeforces](https://codeforces.com/group/yuAAIJ8c1R/contest/644999/problem/B)
**Tiempo límite:** 2 s  
**Memoria límite:** 256 MB

Martínez quiere rescatar a su equipo y debe viajar por una galaxia con `n` planetas (indexados `1..n`).  
Comienza en el planeta **1** en el instante **0**, y Zargon aterrizará en el planeta **n**. Puede moverse usando **portales** bidireccionales entre ciertos pares de planetas; cada viaje por un portal tarda una cantidad **positiva** de segundos.

Hay otros viajeros llegando a los planetas. Si **Martínez está en un planeta en el mismo instante en que llega algún otro viajero a ese planeta**, Martínez **debe esperar exactamente 1 segundo** antes de poder usar cualquier portal desde allí. En particular:

- Si a un planeta `i` llega alguien en el tiempo `t`, Martínez **no puede** usar un portal saliendo de `i` en `t`.  
- Podrá usarlo en `t+1`, **a menos** que también haya llegadas en `t+1`; en ese caso deberá esperar a `t+2`, y así sucesivamente.  
- En otras palabras, si en `i` hay una **racha de tiempos consecutivos** `t, t+1, …, t+k` con llegadas, y Martínez pretende salir a tiempo `t`, el primer instante permitido será `t+k+1`.

Se pide **el menor tiempo** en que Martínez puede llegar de `1` a `n`.  
Si es imposible, imprimir `-1`.

---

## Entrada

1. Línea 1: dos enteros `n` y `m`  
   - `2 ≤ n ≤ 10^5` — número de planetas.  
   - `0 ≤ m ≤ 10^5` — número de portales.

2. Siguen `m` líneas con `a_i b_i c_i`  
   - `1 ≤ a_i, b_i ≤ n`, `a_i ≠ b_i` — extremos del portal (no dirigido).  
   - `1 ≤ c_i ≤ 10^4` — **tiempo de transferencia** en segundos.  
   - A lo sumo **una** conexión entre cada par de planetas.

3. Luego `n` bloques (uno por planeta `i = 1..n`):  
   - Una línea con `k_i` (`0 ≤ k_i ≤ 10^5`) — cantidad de llegadas de otros viajeros al planeta `i`.  
   - Una línea con `k_i` enteros **no decrecientes** `t_{i1}, t_{i2}, …, t_{ik_i}` (`0 < t_{ij} ≤ 10^9`) — tiempos de esas llegadas.  
   - Se garantiza que `sum(k_i) ≤ 10^5`.

## Salida

Un único entero: el **tiempo mínimo** para llegar de `1` a `n`.  
Si no existe ruta válida, imprimir `-1`.

---

## Ejemplos

**Entrada**
```
4 6
1 2 2
1 3 3
2 3 5
2 4 9
3 4 6
3 2 5
3
4
3
0
1
2 3 4
```

**Salida**
```
8
```

**Entrada**
```
3 1
2 3 3
0
1
3
0
```

**Salida**
```
-1
```

> Nota: en los bloques de llegadas, cada planeta aporta primero `k_i` y luego su lista de `k_i` tiempos.

---

## Modelado

- Grafo no dirigido con `n` nodos y `m` aristas ponderadas (`c_i` > 0).  
- **Estados**: estar en un planeta `u` en cierto tiempo `t`.  
- **Costo de esperar en `u`**: si `t` coincide con una llegada en `u` y sigue una racha de tiempos consecutivos de llegadas, hay que **saltar** al primer tiempo libre `t' > t` que no esté en la racha.

Esto es un **camino más corto** con tiempos de **espera dependientes del nodo** (pero **no** dependientes de la arista).

---

## Idea de solución (Dijkstra con esperas)

Como todos los tiempos de arista son positivos, podemos usar **Dijkstra**.  
Al extraer un planeta `u` con distancia provisional `dist[u]`:

1. **Ajuste por esperas**:  
   - Sea `t = dist[u]`.  
   - Mientras `t` pertenezca al conjunto de llegadas de `u`, hacer `t++`.  
   - (Con las listas ordenadas, esto equivale a **saltar una racha consecutiva**; se puede implementar en `O(#racha)`.)

2. **Relajaciones**:  
   - Para cada `(u, v, w)` actualizar `dist[v]` con `t + w` si es menor que el valor actual.

Al finalizar, `dist[n]` es la respuesta (o `-1` si queda infinito).

### Estructuras recomendadas

- Para cada planeta `i`, guardar sus tiempos `t_i` **ordenados** (ya vienen así).  
- Para comprobar la racha:
  - Opción simple: `unordered_set` (hash) y bucle `while (set.count(t)) ++t;`.  
  - Opción más eficiente en memoria y tiempo: recorrer el **vector** con un puntero/`lower_bound(t)` y luego avanzar mientras `t_i[idx] == t`, `++t`, `++idx`.  
  - Como `∑k_i ≤ 10^5` y cada racha se consume a lo sumo una vez cuando `u` queda *definitivo* en Dijkstra, el total de avances sobre todos los nodos sigue siendo `O(∑k_i)`.

### Pseudocódigo

```text
leer n, m
adj = lista de adyacencia
para m veces: leer a, b, c; adj[a].push(b,c), adj[b].push(a,c)

arrivals[i] = vector<int> con k_i tiempos (ordenados)

const INF = muy grande
dist[1..n] = INF
dist[1] = 0
pq = min-heap (dist, nodo)

mientras pq no vacío:
    (d, u) = extraer mínimo
    si d != dist[u]: continuar

    t = d
    // saltar racha de llegadas consecutivas en u
    // versión con vector ordenado:
    idx = lower_bound(arrivals[u].begin(), arrivals[u].end(), t) - begin
    mientras idx < arrivals[u].size() y arrivals[u][idx] == t:
        t++; idx++

    para (v, w) en adj[u]:
        if dist[v] > t + w:
            dist[v] = t + w
            push(dist[v], v) en pq

respuesta = (dist[n] == INF) ? -1 : dist[n]
imprimir respuesta
```

## Análisis de Complejidad

Definamos:
- `N` = número de planetas (nodos).
- `M` = número de portales (aristas no dirigidas; el grafo usa `2M` entradas en la lista de adyacencia).
- `K_total` = suma de todas las llegadas de viajeros en todos los planetas (`∑ k_i`).

La complejidad total es la suma del **costo de leer la entrada** y la **ejecución de Dijkstra** con la lógica de espera.

### 1) Complejidad de Lectura (función `solve`)

1. **Lectura de `N` y `M`:** `O(1)`.
2. **Creación de estructuras:** `O(N)` para inicializar `G`, `tiempo_viajeros`, `dist`/`tiempo`.
3. **Lectura de `M` portales:** se añaden `2M` pares a la lista de adyacencia. Costo: `O(M)`.
4. **Lectura de llegadas:** se realizan `K_total` inserciones en las estructuras por planeta.
   - Con `unordered_set`: costo **promedio** por `insert` es `O(1)` → `O(K_total)`.
   - Con `vector` y *push_back* (ya vienen ordenados): también `O(K_total)`.

**Costo total promedio de lectura:** `O(N + M + K_total)`.

### 2) Complejidad del algoritmo (Dijkstra)

- **Base de Dijkstra:** cada extracción de la cola cuesta `O(log N)`, y cada arista puede relajar una vez → `O((N + M) log N)`.
- **Lógica de espera (optimización clave):** al fijar un planeta `u` con tiempo `d = dist[u]`, ajustamos a `t = d` y saltamos **solo la racha consecutiva** `t, t+1, …`. Ese bucle `while` se ejecuta **a lo sumo** `c_u` veces para `u`, donde `c_u` es el largo de la racha bloqueada. Sumado en todos los nodos, `∑ c_u ≤ K_total`.

**Costo total de la espera (promedio):** `O(K_total)`.

**Complejidad total (promedio):**
```
O( (N + M) log N + K_total )
```

### 3) Nota sobre el peor caso con `unordered_set` (colisiones de hash)

El análisis anterior asume que `unordered_set` tiene operaciones `O(1)` promedio. En el **peor caso patológico** (muchas colisiones), `find/insert` pueden degradar a `O(k_u)` en un planeta con `k_u` llegadas, haciendo que el bucle de espera en ese planeta sea `O(k_u^2)`.

**Complejidad total (peor caso adversario):**
```
O( (N + M) log N + ∑_{u=1..N} k_u^2 )
```
Si casi todo `K_total` se concentra en un solo planeta, esto puede degenerar hasta `O( (N + M) log N + K_total^2 )`.

> **Práctico:** con datos aleatorios o bien distribuidos (y usando `reserve` y un `max_load_factor` razonable), el comportamiento real es cercano al promedio. Si necesitás evitar este peor caso, podés usar la alternativa **determinística** con `vector` ordenado + `lower_bound`, que mantiene el salto de rachas en `O(log k_u + c_u)` y garantiza
```
O( (N + M) log N + K_total )
```
también en el peor caso teórico (sin depender del hash).


---

## Casos borde a tener en cuenta

- `n = 1` → respuesta `0` (ya está en el destino; no necesita portales aunque haya llegadas en el planeta 1).  
- Planetas sin portales (`m = 0`) salvo que `n = 1` → `-1`.  
- Largas rachas consecutivas de llegadas en un nodo.  
- Grafo no conexo o destino aislado.  
- Múltiples caminos con el mismo costo; Dijkstra maneja esto sin cambios.

---

## Notas de implementación

- Usar tipos de 64 bits (`long long`) para los tiempos: `t` puede crecer (`≤ 10^9 + #esperas`) y se suman pesos.  
- No modifiques `arrivals[u]` durante la ejecución; usa `lower_bound` + avance local para mantener `O(log k + largo de racha)`.  
- Asegurate de **no esperar** si `t` no está en la lista (solo se espera cuando coincide exactamente).  
- Si prefieres `unordered_set` para claridad, recuerda reservar (`reserve`) para evitar rehash costoso.

---

## Cómo compilar y correr

```bash
g++ -O2 -std=c++17 -Wall -Wextra main.cpp -o viaje
./viaje < input.txt
```

---

## Estructura sugerida del repo

```
.
├── src/
│   └── main.cpp
├── tests/
│   ├── sample1.in
│   ├── sample1.out
│   ├── sample2.in
│   └── sample2.out
└── README.md
```

---

## Licencia

Agrega aquí la licencia de tu preferencia (MIT, Apache-2.0, etc.).
