#include <iostream>
#include "lib/CubicSpline.h"
#include "lib/RSFNet.h"

int main() {
    RSFNet s(const_cast<char *>("input"), 1.5);
    s.print_coef();
    std::cout << s.calculate(2);

    return 0;
}