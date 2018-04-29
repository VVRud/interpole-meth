#ifndef SNTKURSACH_LAGRANJPOLINOME_H
#define SNTKURSACH_LAGRANJPOLINOME_H

#include "Base.hpp"

class LagranjPolinome : public Base {
protected:
    struct spline_tuple {
        double y, x;
    };

    spline_tuple *splines; // Сплайн
    int n;

    void free_mem();

public:
    LagranjPolinome();

    ~LagranjPolinome();

    explicit LagranjPolinome(char *f);

    LagranjPolinome(double *x, double *y, int n);

    void buildSpline(double *x, double *y, int n);

    double calculate(double x);

    void print_coef();
};


#endif //SNTKURSACH_LAGRANJPOLINOME_H
