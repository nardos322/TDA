#include <iostream>
#include <string>


bool es_todo_l(const std::string& s, const char l) {

    for (size_t i = 0; i < s.length(); i++) {
        if (l != s[i]) return false;
    }
    return true;
}



void l_lindo(const std::string& s, const char l) {

    if (s.length() == 1 && s[0] == l) return;

    const std::string mitad_izq = s.substr(0, s.length() / 2);
    const std::string mitad_der = s.substr(s.length() / 2);
    std::cout << s << std::endl;
    //std::string mitad_l =
}

int main() {

    const std::string a = "axyxwwww";

    const std::string mitad_izq = a.substr(0, a.length() / 2);

    const std::string mitad_der = a.substr(a.length() / 2);


    std::cout << mitad_izq << " " << mitad_der << std::endl;

    return 0;
}


