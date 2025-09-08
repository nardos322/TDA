#include <iostream>
#include <vector>



bool b_convertibilidad(const long long x, const long long y, std::vector<long long>& cadena) {

    if (x == y) {
        return true;
    }

    if (x > y) {
        return false;
    }

    cadena.push_back(2*x);
    if (b_convertibilidad(2*x, y, cadena)) return true;
    cadena.pop_back();

    cadena.push_back(10*x + 1);
    if (b_convertibilidad(10*x + 1, y, cadena)) return true;
    cadena.pop_back();

    return false;


}




int main() {
    std::vector<long long> cadena;
    long long x;
    long long y;
    std::cin >> x >> y;
    cadena.push_back(x);

    if (!b_convertibilidad(x, y, cadena)) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << "YES" <<  std::endl;
        std::cout << cadena.size() << std::endl;
        for (const auto i : cadena) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}