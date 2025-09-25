#include <bits/stdc++.h>
using namespace std;


long long borrar(const string& s, const int n)
{
    static long long memo[500][500];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) memo[i][j] = -1;

    function<long long(int, int)> f = [&](const int l, const int r) -> long long {
        if (l > r) return 0;
        if (l == r) return 1;
        long long &res = memo[l][r];
        if (res != -1) return res;
        
        // Caso A: borrar s[l] por separado
        res = 1 + f(l + 1, r);
        
        // Caso B: juntar s[l] con algun k tal que s[k] == s[l] "borro lo del medio, pego los extremos y los borro juntos"
        for(int k = l + 1; k <= r; ++k) {
            if (s[l] == s[k]) {
                res = min(res, f(l + 1, k - 1) + f(k, r));
            }
        }

        return res;
    };

    long long ans = f(0, n - 1);
    return ans;
} 


void solve(istream &in, ostream &out)
{   
    int n;
    in >> n;
    string p;
    in >> p;
    long long ans = borrar(p, n);
    out << ans << "\n";
}

#ifdef LOCAL

void test_borrar()
{
    
    assert(borrar("ababa", 5) == 3);
    assert(borrar("aaabbb", 6) == 2);
    assert(borrar("abccabccab", 10) == 6);
    assert(borrar("acdeefa", 7) == 5);

   
    cout << "OK todos los tests pasaron" << endl;
}

#endif

int main()
{
#ifdef LOCAL
    test_borrar();
#else

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve(cin, cout);
#endif
    return 0;
}