#include <iostream>



long long ale_1s(const long long n, const long long l, const long long r, long long& indice) {
    long long contador_1s = 0;

    if (n > 1) contador_1s += ale_1s(n / 2, l, r, indice);

    indice++;

    if (indice >= l && indice <= r && (n % 2) == 1) contador_1s++;

    //std::cout << n << ":"<< indice << ", "<< resto  << " " << "["<<l << ":" << r << "]"<< std::endl;
    if (n > 1) contador_1s += ale_1s(n / 2, l, r, indice);


    return contador_1s;


}


void solve(std::istream& in, std:: ostream& out) {
    long long n, l, r;
    while (in >> n >> l >> r) {
        long long contador = 0;
        const long long res = ale_1s(n, l, r, contador);
        out << res << '\n';
    }
}


#define LOCAL
#ifndef LOCAL

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve(std::cin, std::cout);

    return 0;
}
#else
#include <sstream>
#include <cassert>

static std::string run_solve(const std::string& input) {
    std::istringstream in (input);
    std::ostringstream out;
    solve(in, out);
    return out.str();
}

int main() {

    assert(run_solve("6 1 7\n") == "6\n");  // inorder 6: [1,3,1,6,1,3,1]
    assert(run_solve("6 3 6\n") == "3\n");  // [1,6,1,3] => 3 impares
    assert(run_solve("4 1 7\n") == "4\n");  // [1,2,1,4,1,2,1]
    assert(run_solve("3 1 3\n") == "3\n");  // [1,3,1]
    assert(run_solve("3 10 20\n") == "0\n");// rango fuera -> 0
    assert(run_solve("9 4 11\n") == "5\n");

    std::cerr << "Tests LOCAL OK\n";
    return 0;

}



#endif
