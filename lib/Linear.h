#ifndef SNTKURSACH_LINEAR_H
#define SNTKURSACH_LINEAR_H

#include "Base.hpp"

class Linear : public Base {
protected:
    struct spline_tuple {
        double b, k, y, x;
    };

    spline_tuple* splines;
    int n;

    void free_mem();

public:
    Linear();

    Linear(double *x, double *y, int n);

    explicit Linear(char *f);

    virtual ~Linear();

    void build(double *x, double *y, int cnt);

    double calculate(double x);

    void print_coef();
};


#endif //SNTKURSACH_LINEAR_H
