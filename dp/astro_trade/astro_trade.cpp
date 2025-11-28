#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG_INF = -1e18;

//mgn(p,j,c) = maxima_ganancia_neta usando dias [1..j] y teniendo 
//c asteroides al final del dia j
ll mgn_bt(const vector<ll> &p, int j, int c) {
    // 1. Validaciones de estado imposible
    // c < 0: Stock negativo
    // c > j: Tener más stock que días transcurridos
    if(j < 0 || c > j) return NEG_INF;
    
    // 2. Caso base: Dia 0
    if(j == 0){
        // Solo es valido si terminamos con 0 asteroides
        return (c == 0) ? 0 : NEG_INF;
    }
    // Precio del día actual (j es 1-based, vector es 0-based)
    ll precio_hoy = p[j-1];

    // --- Transiciones ---

    // Opcion A: Comprar un asteroide hoy
    // Significa que ayer (j-1) teníamos c-1 asteroides
    ll res_compre = mgn_bt(p, j - 1, c - 1) - precio_hoy;

    // Opcion B: Vender un asteroide hoy
    // Significa que ayer (j-1) teníamos c+1 asteroides
    ll res_vendi = mgn_bt(p, j - 1, c + 1) + precio_hoy;
    // Opcion C: No hacer nada hoy
    // Significa que ayer (j-1) teníamos c asteroides
    ll res_wait = mgn_bt(p, j - 1, c);

    // Retornar la mejor opción
    return max({res_compre, res_vendi, res_wait});

}

ll mgn_topdown(const vector<ll> &p){
    int n = (int)p.size();

    // 1. Declaramos la MEMO una sola vez aquí (el tamaño es N, no j)
    // Usamos -2e18 como valor de "NO VISITADO" para distinguirlo del "IMPOSIBLE" (-1e18)
    const ll NO_VISITADO = -2e18;
    vector<vector<ll>> memo(n + 1, vector<ll>(n + 1, NO_VISITADO));

    function<ll(int, int)> dp = [&](int j, int c) -> ll {
        // 1. Validaciones de estado imposible
        if(j < 0 || c < 0 || c > j) return NEG_INF;

        // 2. Caso base: Dia 0
        if(j == 0) return (c == 0) ? 0 : NEG_INF;
    
        // 3. Chequeo de Memoización
        // Verificar si ya está calculado
        if(memo[j][c] != NO_VISITADO) return memo[j][c];

        ll precio_hoy = p[j - 1];

        // Opcion A: Comprar un asteroide hoy
        ll res_compre = dp(j - 1, c - 1) - precio_hoy;

        // Opcion B: Vender un asteroide hoy
        ll res_vendi = dp(j - 1, c + 1) + precio_hoy;

        // Opcion C: No hacer nada hoy
        ll res_wait = dp(j - 1, c);

        // Guardar en memo y retornar la mejor opción
        memo[j][c] = max({res_compre, res_vendi, res_wait});
        return memo[j][c];
    };

    // 4. Llamada inicial
    // Queremos saber el resultado del día N con 0 asteroides
    return dp(n, 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<ll> precios = {3, 2, 5, 6};
    vector<ll> precios2 = {3, 6, 10};

    cout << mgn_topdown(precios) << "\n";
    cout << mgn_topdown(precios2) << "\n";
    return 0;
}