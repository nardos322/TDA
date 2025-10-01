#include <bits/stdc++.h>
using namespace std;



int vacations(const vector<vector<int>>& actividades, const int dia, const int last, const int N) {


    if (dia >= N) return 0;

   
    int best;
    if(actividades[dia][0] == 1 && last != 1) {
        best = min(vacations(actividades, dia + 1, actividades[dia][0], N),1 + vacations(actividades, dia + 1, 0, N));
    } 
    if (actividades[dia][0] == 2 && last != 2) {
        best = min(vacations(actividades, dia + 1, actividades[dia][0], N),1 + vacations(actividades, dia + 1, 0, N));
    } 
    if (actividades[dia].size() == 2 && last != 1 || last != 2) {
        best = min(min(vacations(actividades, dia + 1, actividades[dia][0], N), 
        vacations(actividades, dia + 1, actividades[dia][0] , N)), 1 + vacations(actividades, dia + 1, 0, N));
    } 
        
    best = 1 + vacations(actividades, dia + 1, 0, N);


    return best;

}


int vacations2(const vector<vector<int>>& actividades, const int dia, const int last, const int N) {
    if (dia >= N) return 0;

    int best = 1 + vacations(actividades, dia + 1, 0, N); // descansar

    for (int act : actividades[dia]) {
        if (act != last) {
            best = min(best, vacations(actividades, dia + 1, act, N));
        }
    }

    return best;
}



int main() {

    vector<vector<int>> a = {{},{1},{1, 2}, {2},{}};
    
    cout << vacations(a, 1, 0, 4) << "\n";
    cout << "holaa" << "\n";


    return 0;
}