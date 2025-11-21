#include <bits/stdc++.h>

using namespace std;


// Numero combinatorio
void backtrack(const int pos, vector<int> elegidos, const int r, const int N) {



    if (r == 0)  {
        for (const auto n : elegidos){
            cout << n << " ";
        }
        cout << endl;
        return;
    }

    if (pos >= N) return;


    elegidos.push_back(pos);
    backtrack(pos + 1, elegidos, r - 1, N);
    elegidos.pop_back();
    backtrack(pos + 1, elegidos, r, N);



}

void permutaciones(vector<int>& elegidos, vector<bool>& usado, const int r, const int N) {
    if (r == 0) {
        for (const auto n : elegidos) cout << n << " ";
        cout << endl;
        return;
    }
    for (int i = 1; i <= N; ++i) {
        if (!usado[i]) {
            usado[i] = true;
            elegidos.push_back(i);
            permutaciones(elegidos, usado, r - 1, N);
            elegidos.pop_back();
            usado[i] = false;
        }
    }
}

// primera version de ruta_minima, este enfoque complica podar, hay que pasar costo y mejor_costo como parametro
int f(const vector<vector<int>>& M, vector<int>& camino, const int ciudad_actual){

    if (camino.size() == M.size()) {
        for(const auto& n : camino) cout << n << " ";
        cout << "\n";
        return M[ciudad_actual][camino.front()];
    }

    int mejor_costo = INT_MAX;
    for(int k = 0; k < M.size(); ++k) {
        if (ranges::find(camino, k) == camino.end()) {
            camino.push_back(k);
            mejor_costo = min(mejor_costo, M[ciudad_actual][k] + f(M, camino, k));
            camino.pop_back();

        }
    }

    return mejor_costo;
}

// esta version es mas facil para aplicar podas, me da el mejor costo y el mejor camino
// se actualizan por referencia
void ruta_minima(const vector<vector<int>>& M,
                vector<int>& camino,
                vector<bool>& visitados,
                const int actual,
                const int costo_actual,
                int& mejor_costo,
                vector<int>& mejor_camino) 
{

    if(camino.size() == M.size()) {
        if (const int total = costo_actual + M[actual][camino.front()]; total < mejor_costo) {
            mejor_costo = total;
            mejor_camino = camino;
        }

        return;
    }
       
   
    if (costo_actual >= mejor_costo) return;  //poda simple 
        
    for (int k = 0; k < M.size(); ++k) {
        if (!visitados[k]) {
            const int nuevo_costo = costo_actual + M[actual][k];
            if (nuevo_costo >= mejor_costo) continue; // poda mas agresiva
            visitados[k] = true;
            camino.push_back(k);
            ruta_minima(M, camino, visitados, k, nuevo_costo, mejor_costo, mejor_camino);
            camino.pop_back();
            visitados[k] = false;
        }
    }

} 

// version mas limpia
pair<int, vector<int>> ruta_minima2(const vector<vector<int>>& M) {
    const int n = static_cast<int>(M.size());
    int mejor_costo = INT_MAX;
    vector<bool> visitados(n, false);
    vector<int> camino; camino.reserve(n);
    vector<int> mejor_camino;

    visitados[0] = true;
    camino.push_back(0);

    function<void(int, int)> bt = [&](const int actual, const int costo_actual) -> void {
        if(camino.size() == n) {
            if (const int total = costo_actual + M[actual][camino.front()]; total < mejor_costo) {
                mejor_costo = total;
                mejor_camino = camino;
            }
            return;
        }

        if (costo_actual >= mejor_costo) return;  //poda simple


        for (int k = 0; k < n; ++k) {
            if (!visitados[k]) {
                const int nuevo_costo = costo_actual + M[actual][k];
                if (nuevo_costo >= mejor_costo) continue; // poda mas agresiva
                visitados[k] = true;
                camino.push_back(k);
                bt(k, nuevo_costo);
                camino.pop_back();
                visitados[k] = false;
            }
        }
    };
    bt(0, 0);
    return {mejor_costo, mejor_camino};
}


int main() {

    const vector<vector<int>> D = {
        { 0,  1, 10, 10},
        {10,  0,  3, 15},
        {21, 17,  0,  2},
        { 3, 22, 30,  0}
    };
  

    auto [fst, snd] = ruta_minima2(D);

    for(const vector<int> camino = snd; const auto n : camino) {
        cout << n << " ";
    }
    cout << "\n";
    cout << "y el costo es: " << fst << "\n";

//  cout << res.first << "\n";

    return 0;
}