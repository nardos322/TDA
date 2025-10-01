#include <bits/stdc++.h>
using namespace std;

// Version fiel a la funcion recursiva original
int vacations(const vector<vector<int>> &actividades, const int dia, const int last, const int N)
{

    if (dia >= N)
        return 0;

    int best = INT_MAX;

    // Opcion de descansar
    best = min(best, 1 + vacations(actividades, dia + 1, 0, N)); // descansar

    // Solo una actividad disponible (competir O gimnasio)
    if (actividades[dia].size() == 1 && last != actividades[dia][0])
    {
        best = min(best, vacations(actividades, dia + 1, actividades[dia][0], N));
    }

    // Dos actividades disponibles (competir Y gimnasio)
    if (actividades[dia].size() == 2)
    {
        if (last != actividades[dia][0])
        {
            best = min(best, vacations(actividades, dia + 1, actividades[dia][0], N));
        }
        if (last != actividades[dia][1])
        {
            best = min(best, vacations(actividades, dia + 1, actividades[dia][1], N));
        }
    }

    return best;
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

int main()
{

    vector<vector<int>> a = {{1}, {1, 2}, {2}, {}};

    cout << vacations_2(a, 0, 0, 4) << "\n";
    cout << vacations(a, 0, 0, 4) << "\n";

    // Prueba con bitmask - misma entrada pero representada con bits
    vector<int> b = {2, 6, 4, 0}; // {010, 110, 100, 000} en binario
    // Día 0: 2 = 010₂ → solo competir (actividad 1)
    // Día 1: 6 = 110₂ → competir y gimnasio (actividades 1 y 2)
    // Día 2: 4 = 100₂ → solo gimnasio (actividad 2)
    // Día 3: 0 = 000₂ → ninguna actividad

    cout << vacations_bitmask(b, 0, 0, 4) << "\n";
    cout << "Ambas versiones deben dar el mismo resultado!" << "\n";

    return 0;
}