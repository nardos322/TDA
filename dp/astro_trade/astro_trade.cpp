#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll NEG_INF = -1e18;

 // Usamos -2e18 como valor de "NO VISITADO" para distinguirlo del "IMPOSIBLE" (-1e18)
const ll NO_VISITADO = -2e18;

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

ll mgn_bottomup_optimizado(const vector<ll>& p) {
    int n = (int)p.size();

    // 1. Vector 'anterior' representa el Día 0
    // Tamaño n+1 porque el stock puede llegar hasta n.
    // Inicializamos todo en NEG_INF (imposible tener stock > 0 el día 0)
    vector<ll> anterior(n + 1, NEG_INF);
    // Caso base: dia 0, stock 0 => ganancia 0
    anterior[0] = 0;
    // Vector 'actual' para el día en curso
    vector<ll> actual(n + 1, NEG_INF);

    // 2. Iterar sobre los días (1 a n)
    for(int j = 1; j <= n; j++) {
        ll precio_hoy = p[j - 1]; // Precio del día actual j
        // 3. Iterar sobre posibles stocks (0 a j)
        // No tiene sentido mirar c > j (más stock que días)
        for(int c = 0; c <= j; c++) {
            // Opción A: Comprar hoy (vengo de c-1)
            ll res_compre = (c > 0) ? anterior[c - 1] - precio_hoy : NEG_INF;
            // Opción B: Vender hoy (vengo de c+1)
            ll res_vendi = (c < j) ? anterior[c + 1] + precio_hoy : NEG_INF;
            // Opción C: No hacer nada (vengo de c)
            ll res_wait = anterior[c];

            // Mejor opción para el día j con stock c
            actual[c] = max({res_compre, res_vendi, res_wait});
        }
        // 4. Paso de antorcha: El día actual se convierte en el anterior
        swap(anterior, actual);
    }
    // 5. Respuesta: Día n (última vuelta de prev) con 0 asteroides
    return anterior[0];
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