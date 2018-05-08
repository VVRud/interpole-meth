#include "RSFNet.h"

#include <iostream>

void RSFNet::free_mem() {
//    delete weights;
}

RSFNet::RSFNet() = default;

RSFNet::RSFNet(double *x, double *y, int n, int r) : Base(n), r(r) {
    build(x, y, n);
}

RSFNet::RSFNet(char *f, const double r) : Base(), r(r){
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

RSFNet::~RSFNet() {
    free_mem();
}

void RSFNet::build(double *x, double *y, int cnt) {
    free_mem();

    this->n = cnt;
    this->xV = x;

    Eigen::VectorXd yV(n);
    Eigen::MatrixXd matr(n, n);

    for (int i = 0; i < n; ++i) {
        yV[i] = y[i];
    }
    alph();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matr(i, j) = gaussian(x[i], x[j]);
        }
    }
    weights = (matr.transpose() * matr).inverse() * matr.transpose() * yV;
}

double RSFNet::calculate(double x) {
    Eigen::RowVectorXd h(n);

    for (int i = 0; i < n; ++i) {
        h[i] = gaussian(x, xV[i]);
    }

    return weights.dot(h);
}

double RSFNet::gaussian(double x, double x1) {
    return exp(-alpha * norm(x, x1));
}

double RSFNet::norm(double x, double xV) {
    return fabs(x - xV);
}

void RSFNet::alph() {
    this->alpha = 1 / (2 * pow(r, 2));
}


