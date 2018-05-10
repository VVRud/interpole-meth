#ifndef SNTKURSACH_CUBICSPLINE_H
#define SNTKURSACH_CUBICSPLINE_H


#include <libio.h>
#include <fstream>
#include <cstdio>
#include "Spline.hpp"

class CubicSpline : public Spline {
protected:
    explicit CubicSpline(int n);

public:
    CubicSpline();

    ~CubicSpline() override;

    CubicSpline(double *x, double *y, int n);

    explicit CubicSpline(char *f);

    void buildSpline(double *x, double *y, int cnt) override;

    double calculate(double x) override;
};


#endif //SNTKURSACH_SPLINE_H
