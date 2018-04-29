#ifndef SNTKURSACH_SPLINE_H
#define SNTKURSACH_SPLINE_H


#include <fstream>
#include <iostream>
#include "Base.hpp"

class Spline : public Base {
protected:
    Spline(int n) : Base(n) {
    }

    // Структура, описывающая сплайн на каждом сегменте сетки
    struct spline_tuple {
        double a, b, c, d, x;
    };

    spline_tuple *splines; // Сплайн
    int n; // Количество узлов сетки
    void free_mem() {
        delete[] splines;
        splines = nullptr;
    }


public:
    Spline() : Base() {
        splines = nullptr;
    }

    virtual void buildSpline(double *x, double *y, int n) {
    }

    virtual double calculate(double x) {
    }

    //TODO DELETE. ONLY DEBUG VERSION
    void print_coef() {
        std::cout << "A[k]\tB[k]\tC[k]\tD[k]" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << splines[i].a << "\t";
            std::cout << splines[i].b << "\t";
            std::cout << splines[i].c << "\t";
            std::cout << splines[i].d << std::endl;
        }
    }
    //-------------------------------

    virtual ~Spline() {
        free_mem();
    }
};

#endif //SNTKURSACH_SPLINE_H
