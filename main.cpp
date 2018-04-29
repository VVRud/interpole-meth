#include <iostream>
#include "lib/CubicSpline.h"
#include "lib/AkimaSpline.h"

int main() {
    AkimaSpline s(const_cast<char *>("input"));
    s.print_coef();
    std::cout << s.calculate(2);

    return 0;
}