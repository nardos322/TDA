#include "../../include/sumset_sum.hpp"


bool backtrack(const int k, int i, int suma, const vector<int>& set, vector<int>& parcial) {
    if (suma == k) {
        for (const int n: parcial) {
            cout << n << " ";
        }
        cout << endl;
        return true;
    };

    if (suma > k) return false;

    bool res = false;
    for (int j = i; j < set.size(); j++) {
        parcial.push_back(set[j]);
        res = backtrack(k, j + 1, suma + set[j], set, parcial) || res;
        parcial.pop_back();
    }

    return res;
}
