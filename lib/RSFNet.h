#ifndef SNTKURSACH_RSFNET_H
#define SNTKURSACH_RSFNET_H

#include "Base.hpp"
#include "Eigen/Dense"

class RSFNet : public Base {
protected:

    Eigen::VectorXd weights;
    double *xV;
    int n;
    double r;
    double alpha;

    void free_mem();

    double gaussian(double x, double xV);

    double norm(double x, double xV);

    void alph();

public:
    RSFNet();

    RSFNet(double *x, double *y, int n, int r);

    explicit RSFNet(char *f, double r = 1.5);

    ~RSFNet();

    void build(double *x, double *y, int n);

    double calculate(double x);

    void print_coef();
};


#endif //SNTKURSACH_RSFNET_H
