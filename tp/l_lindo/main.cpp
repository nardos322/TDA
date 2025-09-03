#include <iostream>
#include <string>


bool es_todo_l(const std::string& s, const char l) {

    for (size_t i = 0; i < s.length(); i++) {
        if (l != s[i]) return false;
    }
    return true;
}


int cant_movimientos_para_l(std::string& s, const char l) {

    if (es_todo_l(s, l)) return 0;
    int cant_movimientos = 0;

    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] != l)  {
            s[i] = l;
            cant_movimientos++;
        }
    }
    return cant_movimientos;
}

int l_lindo(const std::string& s, const char l) {

    if (s.length() == 1 && s[0] == l) {
        return 0;
    }

    if (s.length() == 1 && s[0] != l) {
        return 1;
    }

    std::string mitad_izq = s.substr(0, s.length() / 2);
    std::string mitad_der = s.substr(s.length() / 2);


    const int costo1 = cant_movimientos_para_l(mitad_izq, l) + l_lindo(mitad_der, l + 1);
    const int costo2 = cant_movimientos_para_l(mitad_der, l) + l_lindo(mitad_izq, l + 1);

    return std::min(costo1, costo2);



}

int main() {

    const std::string s = "aaaadcbb";
    const std::string s2 = "bbaaceaa";


    std::cout << l_lindo(s, 'a') << std::endl;

    return 0;
}


