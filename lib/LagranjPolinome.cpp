#include <iostream>
#include <limits>
#include "LagranjPolinome.h"

LagranjPolinome::LagranjPolinome() : Base() {
}

LagranjPolinome::LagranjPolinome(double *x, double *y, int n) : Base(n) {
    buildSpline(x, y, n);
}

void LagranjPolinome::free_mem() {
    if (!splines) {
        delete[] splines;
        splines = nullptr;
    }
}

LagranjPolinome::~LagranjPolinome() {
    free_mem();
}

void LagranjPolinome::buildSpline(double *x, double *y, int cnt) {
    free_mem();
    this->n = cnt;
    splines = new spline_tuple[n];
    for (int i = 0; i < n; ++i) {
        splines[i].x = x[i];
        splines[i].y = y[i];
    }
}

double LagranjPolinome::calculate(double x) {
    if (!splines) {
        std::numeric_limits<double>::quiet_NaN();
    }

    double l = 0;
    double s;

    for (int i = 0; i < n; ++i) {
        s = 1.0;

        for (int j = 0; j < n; ++j) {
            if (i != j) s *= (x - splines[j].x) / (splines[i].x - splines[j].x);
        }

        l += splines[i].y * s;
    }

    return l;
}

void LagranjPolinome::print_coef() {
    std::cout << "X[k]\tY[k]" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << splines[i].x << "\t";
        std::cout << splines[i].y << std::endl;
    }
}

LagranjPolinome::LagranjPolinome(char *f) {
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
    buildSpline(x, y, n);
    delete[] x;
    delete[] y;
}

