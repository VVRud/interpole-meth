#include "lib/Interpolation.h"

int main(int argc, char *argv[]) {
    RBFNet rbfNet("input.txt", 5);

    double n = rbfNet.calculate(0);
    std::cout << n;
    return 0;
}
