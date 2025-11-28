#include<bits/stdc++.h>

using namespace std;

struct Estado {
    int monto_pagado;
    int cant_billetes;
};


const int INF = 1e9;

Estado sumar_estados(const Estado& a, const Estado& b) {
    // Protección: Si alguno de los estados ya es inválido (INF), 
    // el resultado sigue siendo inválido.
    if (a.monto_pagado >= INF || b.monto_pagado >= INF) {
        return {INF, INF};
    }

    return { 
        a.monto_pagado + b.monto_pagado, 
        a.cant_billetes + b.cant_billetes 
    };
}

Estado mejor(const Estado a, const Estado b){
    auto [c1, q1] = a;
    auto [c2, q2] = b;

    if(c1 < c2) return a;
    if(c2 < c1) return b;
    return {c1, min(q1, q2)};
}



Estado optipagos_bt(const vector<int>& B, const int i, const int j){
    if( j <= 0){
        return {0,0}; // Deuda saldada: costo 0, 0 billetes extra
    }

    if(j > 0 && i < 0) {
        return {INF,INF};  // Caso invalido
    }

    // Opción A: Usar el billete B[i]
    // sumamos {B[i], 1} al resultado recursivo
    Estado usar = sumar_estados(
        {B[i], 1}, 
        optipagos_bt(B, i - 1, j - B[i])
    );

    // Opción B: No usar el billete
    Estado no_usar = optipagos_bt(B, i - 1, j);

    return mejor(usar, no_usar);
}


Estado optipagos_topdown(const vector<int>& B, const int c) {
    const int n = B.size();
    vector<vector<Estado>> memo(n, vector<Estado>(c + 1, {-1, -1}));

    function<Estado(int, int)> dp = [&](int i, int j) -> Estado {
        if (j <= 0) return {0,0};
        if (j > 0 && i < 0) return {INF, INF};
        if (memo[i][j].monto_pagado != -1) return memo[i][j];
        
        Estado usar = sumar_estados(
            {B[i], 1}, 
            dp(i - 1, j - B[i])
        );

        Estado no_usar = dp(i - 1, j);

        return memo[i][j] = mejor(usar, no_usar);
    
    };

    return dp(n - 1, c);


}

Estado optipagos_bottomup(const vector<int>& B, const int c) {
    const int n = B.size();

    // 1. Inicialización de la tabla DP
    // Creamos la tabla (n+1) x (c+1).
    // Inicializamos TODAS las celdas con {INF, INF} (estado inválido) por defecto.
    // Esto nos ahorra el bucle manual para llenar la fila 0 con INFs.
    vector<vector<Estado>> dp(n + 1, vector<Estado>(c + 1, {INF, INF}));

    // 2. Caso Base
    // Con 0 billetes y deuda 0, el costo es 0 y usamos 0 billetes.
    dp[0][0] = {0, 0};

    // 3. Relleno de la tabla
    for (int i = 1; i <= n; i++) {
        // El billete actual es B[i-1] porque 'i' va de 1 a n
        int valor_billete = B[i - 1];

        for (int j = 0; j <= c; j++) {
            // Opción A: No usar el billete (copiamos el valor de la fila anterior)
            Estado no_usar = dp[i - 1][j];

            // Opción B: Usar el billete
            // El truco max(0, j - valor) maneja el "pago en exceso":
            // Si (j - valor) < 0, significa que pagamos de más. 
            // En ese caso, miramos la columna 0 (deuda saldada).
            int deuda_restante = max(0, j - valor_billete);
            
            Estado usar = sumar_estados(
                {valor_billete, 1}, 
                dp[i - 1][deuda_restante]
            );

            // Elegimos la mejor opción para esta celda
            dp[i][j] = mejor(usar, no_usar);
        }
    }

    return dp[n][c];
}

Estado optipagos_espacio_optimizado(const vector<int>& B, const int c) {
    const int n = B.size();

    // 1. Vector 'anterior' (representa la fila i-1)
    // Inicializamos con {INF, INF} por defecto (estado inválido).
    vector<Estado> anterior(c + 1, {INF, INF});
    
    // Caso base: Pagar deuda 0 con 0 billetes tiene costo 0 y cantidad 0.
    anterior[0] = {0, 0};

    // 2. Vector 'actual' (representa la fila i que estamos calculando)
    // No hace falta inicializarlo con valores específicos porque lo vamos a sobrescribir.
    vector<Estado> actual(c + 1);

    for (int i = 1; i <= n; i++) {
        int valor_billete = B[i - 1];

        for (int j = 0; j <= c; j++) {
            // Opción A: No usar el billete (miramos la fila 'anterior' en la misma columna)
            Estado no_usar = anterior[j];

            // Opción B: Usar el billete
            // Manejamos el "pago en exceso" con max(0, ...).
            // Miramos la fila 'anterior' en la columna de deuda restante.
            int deuda_restante = max(0, j - valor_billete);
            
            Estado usar = sumar_estados(
                {valor_billete, 1}, 
                anterior[deuda_restante]
            );

            // Elegimos la mejor opción y la guardamos en la fila 'actual'
            actual[j] = mejor(usar, no_usar);
        }

        // Pasamos el relevo: La fila que acabamos de calcular ('actual')
        // se convierte en la 'anterior' para la siguiente iteración del bucle externo.
        anterior = actual;
    }

    // Al terminar, la respuesta final quedó en 'anterior' (debido a la asignación anterior = actual)
    // en la posición 'c'.
    return anterior[c];
}


int main() {
    vector<int> B = {2,3,5,10,20,20};
    int c = 14;


    auto res = optipagos_bt(B, B.size() - 1, c);
    auto res2 = optipagos_topdown(B, c);
    auto res3 = optipagos_bottomup(B,c);
    auto res4 = optipagos_espacio_optimizado(B, c);
    
    cout << "optipagos_bt: "<< res.cant_billetes << endl;
    cout << "optipagos_topdown: "<< res2.cant_billetes << endl;
    cout << "optipagos_bottomup " << res3.cant_billetes << endl;
    cout << "optipagos_espacio_optimizado "<< res4.cant_billetes << "\n";
   
}