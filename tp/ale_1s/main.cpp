#include <iostream>
#include <vector>


std::vector<int> combinar(std::vector<int> a, std::vector<int> b, std::vector<int> c) {


    std::vector<int> res;
    res.reserve(a.size() + b.size() + c.size());
    res.insert(res.end(), a.begin(), a.end());
    res.insert(res.end(), b.begin(), b.end());
    res.insert(res.end(), c.begin(), c.end());
    return res;
}

std::vector<int> ale_1s(std::vector<int>&v, const int n) {
    std::vector<int> res;

    if (n > 1) {
        const std::vector<int> a = ale_1s(v, n / 2);
        const std::vector<int> b = ale_1s(v, n % 2);
        const std::vector<int> c = ale_1s(v, n / 2);
        res = combinar(a , b , c);
        return res;
    }
    res.push_back(n);
    return res;
}





int main() {
    std::vector<int> v;

    for (const std::vector<int> res = ale_1s(v,6); const auto i : res) {
        std::cout << i ;

    }
    return 0;
}
