#include <bits/stdc++.h>
using namespace std;

// Version fiel a la funcion recursiva original
int vacations(const vector<vector<int>> &actividades, const int dia, const int last, const int N)
{

    if (dia >= N)
        return 0;

    // Opcion de descansar
    int best = 1 + vacations(actividades, dia + 1, 0, N); // descansar

    // Verificar si puedo competir (actividad 1)
    if (last != 1 && find(actividades[dia].begin(), actividades[dia].end(), 1) != actividades[dia].end()) {
        best = min(best, vacations(actividades, dia + 1, 1, N));
    }

    // Verificar si puedo ir al gimnasio (actividad 2)
    if (last != 2 && find(actividades[dia].begin(), actividades[dia].end(), 2) != actividades[dia].end()) {
        best = min(best, vacations(actividades, dia + 1, 2, N));
    }

    return best;
}


int vacations_topdown(const vector<vector<int>> &actividades, const int N)
{

    vector<vector<int>> memo(N, vector<int>(3, -1));

    function<int(int, int)> dp = [&](int dia, int last) -> int {
        if (dia >= N)
            return 0;
        if (memo[dia][last] != -1) return memo[dia][last];
       

        // Opcion de descansar
        int best =  1 + dp(dia + 1, 0); // descansar

        // Solo una actividad disponible (competir O gimnasio)
        if (actividades[dia].size() == 1 && last != actividades[dia][0])
        {
            best = min(best, dp(dia + 1, actividades[dia][0]));
        }

        // Dos actividades disponibles (competir Y gimnasio)
        if (actividades[dia].size() == 2)
        {
            if (last != actividades[dia][0])
            {
                best = min(best, dp(dia + 1, actividades[dia][0]));
            }
            if (last != actividades[dia][1])
            {
                best = min(best, dp(dia + 1, actividades[dia][1]));
            }
        }

        
        return memo[dia][last] = best;
    };

    return dp(0, 0);
}




// otra version mas limpia que la anterior
int vacations_2(const vector<vector<int>> &actividades, const int dia, const int last, const int N)
{

    if (dia >= N)
        return 0;

    int best = INT_MAX;

    // Opcion de descansar
    best = min(best, 1 + vacations_2(actividades, dia + 1, 0, N)); // descansar

    // Iterar actividades disponibles
    for (int act : actividades[dia])
    {
        if (act != last)
        {
            best = min(best, vacations_2(actividades, dia + 1, act, N));
        }
    }

    return best;
}

int vacations_2topdown(const vector<vector<int>> &actividades, const int N)
{
    vector<vector<int>> memo(N, vector<int>(3, -1));
 
    function<int(int, int)> dp = [&](int dia, int last) -> int {
        if (dia >= N) return 0;
        if (memo[dia][last] != -1) return memo[dia][last];

        int best = 1 + dp(dia + 1, 0); // descansar

        for (int act : actividades[dia]) {
            if (act != last) {
                best = min(best, dp(dia + 1, act));
            }
        }

        return memo[dia][last] = best;
    };

    return dp(0, 0);
}


pair<int, vector<int>> vacations_2topdown_with_path(const vector<vector<int>> &actividades, const int N)
{
    vector<vector<int>> memo(N, vector<int>(3, -1));
    vector<vector<int>> choice(N, vector<int>(3, -1)); // Guarda la decisión tomada
    vector<int> path;

    function<int(int, int)> dp = [&](int dia, int last) -> int {
        if (dia >= N) return 0;
        if (memo[dia][last] != -1) return memo[dia][last];

        int best = 1 + dp(dia + 1, 0); // descansar
        choice[dia][last] = 0; // Por defecto: descansar

        for (int act : actividades[dia]) {
            if (act != last) {
                int cost = dp(dia + 1, act);
                if (cost < best) {
                    best = cost;
                    choice[dia][last] = act; // Guardar la mejor actividad
                }
            }
        }

        return memo[dia][last] = best;
    };

    int result = dp(0, 0);
    
    // Reconstruir el path
    int current_last = 0;
    for (int dia = 0; dia < N; dia++) {
        int decision = choice[dia][current_last];
        path.push_back(decision);
        current_last = decision;
    }

    return {result, path};
}

// Versión con bitmask
// actividades[dia] es un entero donde cada bit indica si una actividad está disponible
int vacations_bitmask(const vector<int> &actividades, const int dia, const int last, const int N)
{

    if (dia >= N)
        return 0;

    int best = INT_MAX;

    // Opcion de descansar bit 0
    best = min(best, 1 + vacations_bitmask(actividades, dia + 1, 0, N)); // descansar

    // Iterar actividades disponibles con bitmask
    // actividad 1 (competir) actividad 2 (gimnasio) por eso 1 <= act <= 2
    for (int act = 1; act <= 2; act++)
    {   
        // ¿Está disponible competir (actividad 1)?
        //(6 & (1 << 1)) = (110₂ & 010₂) = 010₂ = 2 ≠ 0 → SÍ
        // ¿Está disponible gimnasio (actividad 2)?  
        //(6 & (1 << 2)) = (110₂ & 100₂) = 100₂ = 4 ≠ 0 → SÍ
        if ((actividades[dia] & (1 << act)) && act != last)
        {
            best = min(best, vacations_bitmask(actividades, dia + 1, act, N));
        }
    }

    return best;
}

int vacations_bitmask_topdown(const vector<int> &actividades, const int N)
{
    vector<vector<int>> memo(N, vector<int>(3, -1));
 
    function<int(int, int)> dp = [&](int dia, int last) -> int {
        if (dia >= N) return 0;
        if (memo[dia][last] != -1) return memo[dia][last];

        int best = 1 + dp(dia + 1, 0); // descansar

        for (int act = 1; act <= 2; act++) {
            if ((actividades[dia] & (1 << act)) && act != last) {
                best = min(best, dp(dia + 1, act));
            }
        }

        return memo[dia][last] = best;
    };

    return dp(0, 0);
}

int main()
{

    vector<vector<int>> a = {{1}, {1, 2}, {2}, {}};

  
    cout << vacations_topdown(a, 4) << "\n";
    cout << vacations_2topdown(a, 4) << "\n";
    cout << vacations(a, 0, 0, 4) << "\n";
    cout << vacations_2(a, 0, 0, 4) << "\n";

    // Prueba con bitmask - misma entrada pero representada con bits
    vector<int> b = {2, 6, 4, 0}; // {010, 110, 100, 000} en binario
    // Día 0: 2 = 010₂ → solo competir (actividad 1)
    // Día 1: 6 = 110₂ → competir y gimnasio (actividades 1 y 2)
    // Día 2: 4 = 100₂ → solo gimnasio (actividad 2)
    // Día 3: 0 = 000₂ → ninguna actividad

    cout << vacations_bitmask(b, 0, 0, 4) << "\n";
    cout << vacations_bitmask_topdown(b, 4) << "\n";
    cout << "Ambas versiones deben dar el mismo resultado!" << "\n";

    cout << "Resultado con path: " << ;
    pair<int, vector<int>> result_with_path = vacations_2topdown_with_path(a, 4);
    cout << "Días mínimos de descanso: " << result_with_path.first << "\n";
    cout << "Secuencia: ";
    for (int i = 0; i < result_with_path.second.size(); i++) {
        int act = result_with_path.second[i];
        cout << "Día" << i << ":";
        if (act == 0) cout << "descansar ";
        else if (act == 1) cout << "competir ";
        else cout << "gimnasio ";
        cout << "| ";
    }
    
    cout << "\n";

    return 0;
}