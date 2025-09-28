#include <bits/stdc++.h>
using namespace std;

long long king_army_bt(const long long i)
{
    if (i == 0)
        return 1;
    if (i == 1)
        return 1;

    return king_army_bt(i - 1) + king_army_bt(i - 2);
}

long long king_army_topdown(const long long i)
{
    static vector<long long> memo;
    if (memo.size() <= i)
    {
        memo.resize(i + 1, -1);
    }
    if (i == 0)
        return 1;
    if (i == 1)
        return 1;
    if (memo[i] != -1)
        return memo[i];

    return memo[i] = king_army_topdown(i - 1) + king_army_topdown(i - 2);
}

long long king_army_bottomup(const long long i)
{
    vector<long long> dp(i + 1, 0);
    dp[0] = 1;
    dp[1] = 1;
    for (long long j = 2; j <= i; ++j)
    {
        dp[j] = dp[j - 1] + dp[j - 2];
    }
    return dp[i];
}

long long king_army_bottomup_optimizado(const long long i) {  // mejora complejidad espacial a O(1)
    if (i <= 1) return 1;
    
    long long prev2 = 1;  // dp[0]
    long long prev1 = 1;  // dp[1] 
    long long current;
    
    for (long long j = 2; j <= i; ++j) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 10;
    cout << "n = " << n << ":\n";
    cout << "Top-down: " << king_army_topdown(n) << "\n";
    cout << "Bottom-up: " << king_army_bottomup(n) << "\n";

    return 0;
}