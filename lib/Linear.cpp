#include <iostream>
#include "headers/Linear.h"

Linear::Linear() : splines(nullptr) {
}

Linear::Linear(double *x, double *y, int n) : Base(n), splines(nullptr) {
    build(x, y, n);
}

Linear::Linear(char *f) : splines(nullptr) {
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
}

void Linear::free_mem() {
    if (!splines) {
        delete[] splines;
        splines = nullptr;
    }
}

Linear::~Linear() {
    free_mem();
}

void Linear::build(double *x, double *y, int cnt) {
    free_mem();
    this->n = cnt;
    this->splines = new spline_tuple[cnt];

    for (int i = 0; i < cnt; ++i) {
        this->splines[i].k = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
        this->splines[i].b = y[i] - this->splines[i].k * x[i];
        this->splines[i].x = x[i];
        this->splines[i].y = y[i];
    }
}

double Linear::calculate(double x) {
    if (!splines) {
        return NULL; // Если сплайны ещё не построены - возвращаем NaN
    }

    if (x <= splines[0].x)
        return splines[0].y;
    else if (x >= splines[n - 1].x)
        return splines[n - 1].y;

    for (int i = 0; i < n - 1; ++i)
        if (x == splines[i].x)
            return splines[i].y;

    for (int i = 0; i < n - 1; ++i)
        if (x >= splines[i].x && x <= splines[i + 1].x)
            return splines[i].k * x + splines[i].b;
}

void Linear::print_coef() {
    std::cout << "K[k]\tB[k]" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << splines[i].k << "\t";
        std::cout << splines[i].b << std::endl;
    }
}

