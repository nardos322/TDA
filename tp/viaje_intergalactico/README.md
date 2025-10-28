

---

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
