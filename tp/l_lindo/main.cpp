#include <iostream>
#include <string>


size_t cant_movimientos_para_l(const std::string& s, const size_t ini, const size_t fin, const char l) {

    size_t cant_movimientos = 0;
    for (size_t i = ini; i < fin; i++) {
        if (s[i] != l) cant_movimientos++;
    }
    return cant_movimientos;
}

size_t l_lindo(const std::string& s, const size_t ini, const size_t fin,  const char l) {
    const size_t n = fin - ini;
    if (n == 1) {
        return (s[ini] == l ? 0 : 1 );
    }

    const size_t mid  =  ini + n/2;

    const size_t costo1 = cant_movimientos_para_l(s, ini, mid, l) + l_lindo(s, mid, fin, l + 1);
    const size_t costo2 = cant_movimientos_para_l(s, mid, fin, l) + l_lindo(s, ini, mid, l + 1);

    return std::min(costo1, costo2);



}

int main() {

    size_t tests;
    size_t length_string;
    std::string input_string;

    std::cin >> tests;
    for (size_t i = 0; i < tests; i++) {
        std::cin >> length_string;
        std::cin >> input_string;
        std::cout << l_lindo(input_string, 0, length_string, 'a') << std::endl;
    }



    return 0;
}


