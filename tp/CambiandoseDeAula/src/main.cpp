#include <iostream>
#include <vector>
using namespace std;


vector<long long> fact_memo;
vector<long long> sum_memo;

long long factorialRecursivo(int n) {
    if (n == 0) return 1;
    return n * factorialRecursivo(n - 1);
}

long long factorial(int n) {
    if (n == 0) return 1;
    if (fact_memo[n] != -1) return fact_memo[n];
    return fact_memo[n] = n * factorial(n - 1);
}

long long suma_factoriales(int n) {
    if (n == 0) return 0;
    if (sum_memo[n] != -1) return sum_memo[n];
    return sum_memo[n] = suma_factoriales(n - 1) + factorial(n);
}

#ifndef LOCAL
int main() {
    vector<vector<int>> aulas = {{1, -1, 1}, {1, 1, -1}, {1, 1, 1}};

    for (int i = 0; i < aulas.size(); i++) {
        for (int j = 0; j < aulas[i].size(); j++) {
            cout << aulas[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}


#endif