#include <iostream>
#include <string>
using namespace std;

void backtrack(string a, int i) {
    if (i == a.length() - 1) {
        cout << "hola" << endl;
        cout << a << endl;
        return;
    }

    if (a[i] == '?') {
        string pos = "+-";
        for (const auto c : pos) {
            a[i] = c;
            backtrack(a, i + 1);
        }

    }

    backtrack(a, i + 1);



}

int main() {
    const string instrucciones = "++?";

    backtrack(instrucciones, 0);




}
