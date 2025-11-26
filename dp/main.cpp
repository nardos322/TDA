#include<bits/stdc++.h>

using namespace std;


const int INF = 1e9;

pair<int,int> add_pairs(const pair<int,int>& a,
                        const pair<int,int>& b) {
    return { a.first + b.first, a.second + b.second };
}

pair<int,int> mejor(pair<int,int> a, pair<int,int> b){
    auto [c1, q1] = a;
    auto [c2, q2] = b;

    if(c1 < c2) return a;
    if(c2 < c1) return b;
    return {c1, min(q1, q2)};
}



pair<int,int> optipagos_bt(const vector<int>& B, const int i, const int j){
    if( j <= 0){
        return {0,0};
    }

    if(j > 0 && i < 0) {
        return {INF,INF};
    }

    return mejor(add_pairs({B[i], 1}, optipagos_bt(B, i - 1, j - B[i])), optipagos_bt(B, i - 1, j));
}

int main() {
    vector<int> B = {2,3,5,10,20,20};
    int c = 14;


    auto res = optipagos_bt(B, B.size() - 1, c);
    
    
    cout << res.second << endl;

}