#include <bits/stdc++.h>
using namespace std;

/*
  maquina_misteriosa.cpp

  Problema (descripción breve):
  Dado un entero inicial n y un entero objetivo m, se permiten dos operaciones sobre
  un valor x: x - 1 y x * 2. El programa calcula el número mínimo de operaciones
  necesarias para transformar n en m usando búsqueda en anchura (BFS).

  Suposiciones / límites:
  - El espacio de estados considerado es [0..10000] (tamaño fijo en el vector).
    Si se requieren valores mayores que 10000, hay que aumentar ese límite o adaptar
    la estructura de datos.

  Complejidad (resumen):
  - Tiempo: O(MAX), donde MAX = 10001. Cada nodo del grafo (cada valor en el rango)
    se visita a lo sumo una vez y cada visita explora a lo sumo 2 aristas (x-1, x*2),
    así que el coste es O(V + E) = O(MAX + 2*MAX) = O(MAX).
  - Espacio: O(MAX) por los arrays `visited` y `distancia`.

  Notas: el código está documentado por función más abajo con su complejidad local.
*/

// Devuelve los dos vecinos (operaciones permitidas) de un estado n: n-1 y n*2.
// Coste: O(1) tiempo, O(1) espacio.
pair<int, int> get_vecinos(int n)
{
    return {n - 1, n * 2};
}

// Realiza una búsqueda en anchura desde n hasta m utilizando los vectores
// `visited` y `distancia` ya reservados/existentes.
// - Parámetros:
//   n: estado inicial
//   m: estado objetivo
//   visited: vector<bool> de tamaño MAX indicando si un nodo ya fue visitado
//   distancia: vector<int> que guarda la distancia (nº pasos) desde n
// - Retorno: número mínimo de operaciones para llegar de n a m, o -1 si no es posible
// Complejidad:
// - Tiempo: O(MAX) en el peor caso (cada estado visitado una vez, dos aristas por estado)
// - Espacio: adicional O(MAX) (almacenado fuera de la función; sólo la cola es adicional)
int bfs(int n, int m, vector<bool> &visited, vector<int> &distancia)
{
    if (n == m)
        return 0;

    queue<int> q;
    q.push(n);
    visited[n] = true;
    distancia[n] = 0;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == m)
        {
            // Al encontrar m, `distancia[current]` es la respuesta mínima por BFS
            return distancia[current];
        }

        pair<int, int> vecinos = get_vecinos(current);
        // Iteramos sobre los dos posibles vecinos: current-1 y current*2
        for (int vecino : {vecinos.first, vecinos.second})
        {
            // Comprobamos límite y si no se ha visitado aún
            if (vecino >= 0 && vecino < static_cast<int>(visited.size()) && !visited[vecino])
            {
                visited[vecino] = true;
                distancia[vecino] = distancia[current] + 1;
                q.push(vecino);
            }
        }
    }

    // Si la cola se vació sin encontrar m, no hay solución dentro del rango
    return -1;
}

// Función envoltorio que prepara los vectores `visited` y `distancia` con
// el tamaño máximo esperado (aquí 10001: [0..10000]).
// Complejidad: O(MAX) tiempo y O(MAX) espacio (por la inicialización de vectores).
int maquina_misteriosa(int n, int m)
{
    const int MAX = 10001; // rango considerado para los estados
    vector<bool> visited(MAX, false);
    vector<int> distancias(MAX, -1);
    return bfs(n, m, visited, distancias);
}

// Lectura/escritura: separada para facilitar testing
void solve(istream &in, ostream &out)
{
    int n, m;
    in >> n >> m;
    out << maquina_misteriosa(n, m) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve(cin, cout);

    return 0;
}