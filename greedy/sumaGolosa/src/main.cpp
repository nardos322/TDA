#include <iostream>
#include <vector>
#include <queue>

using namespace std;


// implementacion incorrecta, no funciona para todos los casos
int suma_golosa(vector<int>& v, const int i, int costo_total) {
    if ( i >= v.size()) {
        return 0;
    }

    if (costo_total == 0) {
        costo_total = v[i - 1] + v[i];
    } else {
        costo_total += v[i];
    }

    return costo_total + suma_golosa(v, i + 1, costo_total);

}


// implementacion corecta
long long suma_golosa_2(vector<int>& v) {
    priority_queue<int, vector<int>, greater<int>> heap(v.begin(), v.end());
    long long costo_total = 0;

    while (heap.size() > 1) {
        const int a = heap.top(); heap.pop();
        const int b = heap.top(); heap.pop();

        long long suma = a + b;
        costo_total += suma;
        heap.push(suma);
    }

    return costo_total;
}

int main() {

    vector v = {1, 2, 3, 4, 5};
    const int res = suma_golosa(v, 1, 0);
    cout << "El resultado es: " << res << endl;
    const long long res2 = suma_golosa_2(v);
    cout <<"El resultado es: " << res2 << endl;

    return 0;
}
