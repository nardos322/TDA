#include <bits/stdc++.h>
using namespace std;


int f(string p, int l, int r) {

    if ( l > r) return 0;
    if ( l == r) return 1;
   
    int ans = 1 + f(p, l + 1, r );
    
    

}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a = "acccca";

    a = a.substr(1, 4);

    cout << a << endl;

    return 0;
}