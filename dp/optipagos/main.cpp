#include<bits/stdc++.h>

using namespace std;


const int INF = 1e9;

pair<int,int> add_pairs(const pair<int,int>& a,
                        const pair<int,int>& b) {
    return { a.first + b.first, a.second + b.second };
}

pair<int,int> mejor(pair<int,int> a, pair<int,int> b){
    auto [c1, q1] = a;
    auto [c2, q2] = b;

    if(c1 < c2) return a;
    if(c2 < c1) return b;
    return {c1, min(q1, q2)};
}



pair<int,int> optipagos_bt(const vector<int>& B, const int i, const int j){
    if( j <= 0){
        return {0,0};
    }

    if(j > 0 && i < 0) {
        return {INF,INF};
    }

    return mejor(add_pairs({B[i], 1}, optipagos_bt(B, i - 1, j - B[i])), optipagos_bt(B, i - 1, j));
}


pair<int,int> optipagos_topdown(const vector<int>& B, const int c) {
    const int n = B.size();
    vector<vector<pair<int, int>>> memo(n, vector<pair<int, int>>(c + 1, {-1, -1}));

    function<pair<int,int>(int, int)> dp = [&](int i, int j) -> pair<int,int> {
        if (j <= 0) return {0,0};
        if (j > 0 && i < 0) return {INF, INF};
        if (memo[i][j].first != -1) return memo[i][j];

        return memo[i][j] = mejor(
            add_pairs({B[i], 1}, dp(i - 1, j - B[i])), 
            dp(i - 1, j));
    
    };

    return dp(n - 1, c);


}

pair<int, int> optipagos_bottomup(const vector<int>& B, const int c) {
    const int n = B.size();
    // creamos una memo con espacio adicional n + 1 para el caso donde no hay billetes i = 0
    vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>>(c + 1, {-1,-1}));

    //dp[0][0] representa i = 0 no hay billetes, j = 0 no hay dueda que pagar por lo tanto es (0,0)
    dp[0][0] = {0,0};

    // este for llena los casos donde no hay billetes y queda deuda j > 0 que pagar por lo tanto no llegamos {INF,INF}
    for(int j = 1; j <= c; ++j) {
        dp[0][j] = {INF, INF};
    }


    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= c; j++) {
            // accedemos al indice correcto en B, con B[i-1] y no con B[i] memo.size > B.size por 1
            // tomamos el maximo en el caso cuando usamos el billete porque si solo tomamos j - B[i-1] esto nos podria dar un indice
            //negativo y tendriamos un error en accecer en el vector, si j - B[i-1] es negativo quiere decir que pagamos la deuda 
            // pagando demas por eso tomamos entonces el 0 que es la columna de deduda saldada
            dp[i][j] = mejor(add_pairs({B[i-1], 1}, dp[i-1][max(0, j - B[i-1])]), dp[i-1][j]);
        }
    }

    return dp[n][c];
}

int main() {
    vector<int> B = {2,3,5,10,20,20};
    int c = 14;


    auto res = optipagos_bt(B, B.size() - 1, c);
    auto res2 = optipagos_topdown(B, c);
    auto res3 = optipagos_bottomup(B,c);
    
    cout << "optipagos_bt: "<< res.second << endl;
    cout << "optipagos_topdown: "<< res2.second << endl;
    cout << "optipagos_bottomup" << res3.second << endl;
   
}