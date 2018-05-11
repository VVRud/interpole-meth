#ifndef SNTKURSACH_RSFNET_H
#define SNTKURSACH_RSFNET_H

#include "Base.hpp"
#include "Eigen/Dense"

class RBFNet : public Base {

protected:
    int numRBFNeurons;
    bool normalize;
    double beta;

    //TODO
    void free_mem();

public:
    explicit RBFNet(int numRBFNeurons = 10, bool normalize = true, double sigma = 10);

    explicit RBFNet(char *f,
                    int numRBFNeurons = 10,
                    bool normalize = true,
                    double sigma = 10);

    RBFNet(double *x, double *y, int n,
           int numRBFNeurons = 10,
           bool normalize = true,
           double sigma = 10);

    ~RBFNet();

    //TODO
    void build(double *x, double *y, int n);

    //TODO
    double calculate(double x);
};


#endif //SNTKURSACH_RSFNET_H
