#ifndef SNTKURSACH_RSFNET_H
#define SNTKURSACH_RSFNET_H

#include "../Base.hpp"
#include "../Eigen/Dense"

class KMeans {
private:
    int numRBFNeurons;
    int iters;
    Eigen::Map<Eigen::VectorXd> *centroids;

    void free_mem();
    void permutate(Eigen::Map<Eigen::VectorXd>);
    Eigen::VectorXd findClosestCentroids(double* x_tr, int m);
    void computeCentroids(double* x_tr, int m, Eigen::VectorXd memberships);

public:
    explicit KMeans(int numRBFNeurons, int iters = 100);
    void initCentroids(double* x_tr, int n);
    void run(double* x_tr, int m, int iters = 100);

    Eigen::VectorXd getCentroids();
};

class RBFNet : public Base {

protected:
    int numRBFNeurons;
    double beta;
    Eigen::Map<Eigen::VectorXd> *theta;
    KMeans *kMeans;

    void free_mem();
    Eigen::VectorXd getActivations(Eigen::VectorXd centroids, double input);

public:
    explicit RBFNet(int numRBFNeurons = 10, double sigma = 10);

    explicit RBFNet(char *f,
                    int numRBFNeurons = 10,
                    double sigma = 10);

    RBFNet(double *x, double *y, int n,
           int numRBFNeurons = 10,
           double sigma = 10);

    ~RBFNet();

    void build(double *x, double *y, int n);
    double calculate(double x);
};


#endif //SNTKURSACH_RSFNET_H
