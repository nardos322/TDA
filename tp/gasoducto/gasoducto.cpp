#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gasoducto(const int n, const ll a, const ll b, vector<int> &s) {
  

  vector<vector<ll>> memo(n + 1, vector<ll>(3, -1));
  const ll INF = LLONG_MAX / 4;

  function<ll(int, int)> f = [&](int i, int h) -> ll {
    if (i == n) return h == 1 ? 0 : INF;
    
    if (memo[i][h] != -1) return memo[i][h];

    ll cost;

    if (s[i] == 0 && h == 1) {
      cost = min(a + b + f(i + 1, 1), 2*a + 2*b + f(i + 1, 2));
    } else if (s[i] == 0 && h == 2) {
      cost = min(2*a + b + f(i + 1, 1), a + 2*b + f(i + 1, 2));
    } else if (s[i] == 1 && h == 1) {
      cost = INF;
    } else {
      cost = a + 2*b + f(i + 1, 2);
    }
    
    return memo[i][h] = cost;
    
  };



  return b + f(0, 1); 
}

void solve() {
  int T;
  cin >> T;

  
  while (T--) {
    int n;
    ll a, b;
    string ruta;
    cin >> n >> a >> b;
    cin >> ruta;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
      s[i] = ruta[i] - '0';
    }

    ll res = gasoducto(n, a, b, s);
    cout << res << endl;
  
  }
  
}


int main() {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();

  return 0;



}