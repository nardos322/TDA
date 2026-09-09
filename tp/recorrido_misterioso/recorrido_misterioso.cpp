#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> build_grafo(int n, int m, istream &in) {
  vector<vector<int>> grafo(n + 1);

  for (int i = 0; i < m; i++) {
    int u, v;
    in >> u >> v;
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }

  return grafo;
}


void bfs(const vector<vector<int>> &grafo, vector<bool> &visitado, vector<int> &padre, int s) {

  queue<int> q;
  q.push(s);
  visitado[s] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : grafo[u]) {
      if (!visitado[v]) {
        visitado[v] = true;
        padre[v] = u;
        q.push(v);
      }
    }
  }

}

bool recorrido_misterioso(const vector<vector<int>> &grafo, vector<int> &a, int n) {
  vector<bool> visitado(n + 1, false);
  vector<int> padre(n + 1, -1);
  vector<int> pos(n + 1, -1);

  if(a[0] != 1) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    pos[a[i]] = i;
  }

  bfs(grafo, visitado, padre, 1);

  int anterior = -1;

  for(int i = 1; i < n; i++) {
    int actual = pos[padre[a[i]]];

    if (actual < anterior) {
      return false;
      
    }
    anterior = actual;
  }
  

  return true;
}





void solve(istream &in, ostream &out) {

  int n;
  in >> n;

  vector<vector<int>> grafo = build_grafo(n, n - 1, in);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    in >> a[i];
  }

  if (recorrido_misterioso(grafo, a, n)) {
    out << "YES" << endl;
  } else {
    out << "NO" << endl;
  }


}




int main () {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);


  solve(cin, cout);
}