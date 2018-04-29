#include <iostream>
#include "LagranjPolinome.h"

LagranjPolinome::LagranjPolinome() : Base() {
}

LagranjPolinome::LagranjPolinome(double *x, double *y, int n) : Base(n) {
    buildSpline(x, y, n);
}

void LagranjPolinome::free_mem() {
    delete[] splines;
    splines = nullptr;
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
        return NULL; // Если сплайны ещё не построены - возвращаем NaN
    }

    double l = 0;

    for (int i = 0; i < n; ++i) {
        l = 1;

        for (int j = 0; j < n; ++j) {
            if (i != j) l *= (x - splines[j].x) / (splines[i].x - splines[j].x);
        }

        l += splines[i].y * l;
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

