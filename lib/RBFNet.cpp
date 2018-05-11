#include "RBFNet.h"

#include <iostream>

RBFNet::RBFNet(int numRBFNeurons, bool normalize, double sigma) : Base(),
                                                                  numRBFNeurons(numRBFNeurons),
                                                                  normalize(normalize),
                                                                  beta(1 / (2 * pow(sigma, 2))) {

}

RBFNet::RBFNet(double *x, double *y, int n,
               int numRBFNeurons,
               bool normalize,
               double sigma) : RBFNet(numRBFNeurons, normalize, sigma) {
    build(x, y, n);
}

RBFNet::RBFNet(char *f, int numRBFNeurons, bool normalize, double sigma) :
        RBFNet(numRBFNeurons, normalize, sigma) {
    std::ifstream file(f);
    if (!file) {
        Exceptions::error(Exceptions::FILE_ERROR);
        return;
    }
    int n = countLines(file);
    if (n <= 1) {
        Exceptions::error(Exceptions::FEW_POINTS);
        return;
    }
    auto *x = new double[n];
    auto *y = new double[n];
    readDataFromFile(file, x, y, n);
    file.close();
    build(x, y, n);
    delete[] x;
    delete[] y;
}

RBFNet::~RBFNet() {
    free_mem();
}
