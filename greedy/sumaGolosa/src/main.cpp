#include <iostream>
#include <vector>

using namespace std;


int suma_golosa(const vector<int>& v, const int i, const int j, int costo_total) {

    if ( j >= v.size()) {
        return 0;
    }

    if (costo_total == 0) {
        costo_total = v[i] + v[j];
    } else {
        costo_total += v[j];
    }

    return costo_total + suma_golosa(v, i + 1, j + 1, costo_total);

}


int main() {

    const vector<int> v = {1, 2, 5};
    const int res = suma_golosa(v, 0, 1, 0);

    cout << "El resultado es: " << res << endl;

    return 0;
}