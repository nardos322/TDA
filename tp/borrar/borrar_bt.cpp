#include<bits/stdc++.h>
using namespace std;



long long f(const string &p, const int l, const int r)
{

    if (l > r)
        return 0;
    if (l == r)
        return 1;

    
    long long ans = 1 + f(p, l + 1, r);
    for (int k = l + 1; k <= r; k++)
    {
        if (p[l] == p[k])
        {
            ans = min(ans, f(p, l + 1, k - 1) + f(p, k, r));
        }
    }

    return ans;
}




int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}