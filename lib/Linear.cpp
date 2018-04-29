#include <iostream>
#include "Linear.h"

Linear::Linear() : splines(nullptr) {
}

Linear::Linear(double *x, double *y, int n) : Base(n) {
    buildSpline(x, y, n);
}

Linear::Linear(char *f) {
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
}

void Linear::free_mem() {
    delete[] splines;
    splines = nullptr;
}

Linear::~Linear() {
    free_mem();
}

void Linear::buildSpline(double *x, double *y, int cnt) {
    free_mem();
    this->n = cnt;
    splines = new spline_tuple[n];
    for (int i = 0; i < n; ++i) {
        splines[i].k = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
        splines[i].b = y[i] - splines[i].k * x[i];
    }
}

double Linear::calculate(double x) {
    if (!splines) {
        return NULL; // Если сплайны ещё не построены - возвращаем NaN
    }

    spline_tuple *s;
    if (x <= splines[0].x)
        s = splines + 1;
    else if (x >= splines[n - 1].x)
        s = splines + n - 1;
    else {
        int i = 0, j = n - 1;
        while (i + 1 < j) {
            int k = i + (j - i) / 2;
            if (x <= splines[k].x)
                j = k;
            else
                i = k;
        }
        s = splines + j;
    }

    return s->k * x + s->b;
}

void Linear::print_coef() {
    std::cout << "K[k]\tB[k]" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << splines[i].k << "\t";
        std::cout << splines[i].b << std::endl;
    }
}

