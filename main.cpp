#include <iostream>
#include "lib/CubicSpline.h"
#include "lib/RSFNet.h"
#include "lib/Bezier.h"

int main() {
    Bezier s(const_cast<char *>("input"));
    std::cout << s.calculateYfromX(1.7);

    return 0;
}