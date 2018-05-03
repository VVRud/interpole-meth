#include <iostream>
#include "lib/CubicSpline.h"
#include "lib/RSFNet.h"
#include "lib/LagranjPolinome.h"

int main() {
    LagranjPolinome s(const_cast<char *>("input"));
    std::cout << s.calculate(1.5);
    return 0;
}