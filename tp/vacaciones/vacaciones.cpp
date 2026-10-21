#include<bits/stdc++.h>

using namespace std;



int vacaciones(const vector<int> &actividades, const int N)
{

    vector<vector<int>> memo(N, vector<int>(3, -1));

    function<int(int, int)> dp = [&](int i, int j) -> int {
        if (i >= N)
            return 0;
        if (memo[i][j] != -1) return memo[i][j];
       

        // Opcion de descansar
        int best =  1 + dp(i + 1, 0); // descansar

         // Verificar si puedo competir (actividad 1)
        if (j != 1 && (actividades[i] == 1 || actividades[i] == 3)) {
            // opcion de competir
            best = min(best, dp(i + 1, 1));
        }

        // Verificar si puedo ir al gimnasio (actividad 2)
        if (j != 2 && (actividades[i] == 2 || actividades[i] == 3)) {
            // opcion de ir al gimnasio
            best = min(best, dp(i + 1, 2));
        }


        return memo[i][j] = best;

    };

    return dp(0, 0);
}



void solve() {
    int N;
    cin >> N;
    vector<int> actividades(N);
    for (int i = 0; i < N; i++) {
        cin >> actividades[i];
    }
    cout << vacaciones(actividades, N) << endl;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}