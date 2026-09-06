#include <bits/stdc++.h>
using namespace std;



// Construye una lista de adyacencia a partir del vector de padres.
// Cada posicion representa un nodo y contiene sus hijos directos.
vector<vector<int>> build_grafo(const vector<int> &p)
{
  int n = p.size();
  vector<vector<int>> G(n);

  for(int i = 0; i < n; i++) 
  {
    if(p[i] != -1)
    {
      int r = p[i] - 1;
      G[r].push_back(i);
    }
  }

  return G;
}

// Obtiene los nodos raiz, identificados por tener padre -1.
vector<int> get_raices(const vector<int> &p)
{
  vector<int> raices;

  for(size_t i = 0; i < p.size(); i++)
  {
    if(p[i] == -1)
    {
      raices.push_back(i);
    }
  }

  return raices;
}


// Recorre el grafo en anchura desde todas las raices.
// Guarda el nivel de cada nodo y devuelve el nivel maximo alcanzado.
int bfs(const vector<vector<int>> &grafo, vector<bool> &visitados, const vector<int> &raices, vector<int> &nivel)
{

  queue<int> q;
  int max_nivel = 1;
  for(int r : raices)
  {
    q.push(r);
    visitados[r] = true;
    nivel[r] = 1;

  }

  while(!q.empty())
  {
    int v = q.front();
    q.pop();

    for(int w : grafo[v])
    {
      if(!visitados[w]) 
      {
        visitados[w] = true;
        nivel[w] = nivel[v] + 1;
        max_nivel = max(max_nivel, nivel[w]);
        q.push(w);
      }

    } 

  }

  return max_nivel;



}


// Calcula la altura del esquema piramidal representado por sus padres.
int esquema_piramidal(const vector<int> &p)
{
  vector<bool> visitados(p.size(), false);
  vector<int> nivel(p.size(), 0);
  const vector<vector<int>> G = build_grafo(p);
  const vector<int> raices = get_raices(p);


  return bfs(G, visitados, raices, nivel);
}

// Lee una instancia desde in, calcula su altura y escribe el resultado en out.
void solve(istream &in, ostream &out)
{
  int n;
  in >> n;

  vector<int> p(n);
  for(int i = 0; i < n; i++)
  {
    in >> p[i];
  }

  out << esquema_piramidal(p) << endl;

}


// Configura la entrada y salida, y resuelve la instancia recibida.
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve(cin, cout);

    

    return 0;


}