#include "headers/RBFNet.h"

#include <iostream>

KMeans::KMeans(int numRBFNeurons, int iters) :  centroids(nullptr),
                                                numRBFNeurons(numRBFNeurons),
                                                iters(iters) {

}

void KMeans::run(double *x_tr, int m, int iters) {
    if (this->iters < 1 && iters < 1) this->iters = 100;
    else if (this->iters < 0) this->iters = 100;
    else if (iters > this->iters) this->iters = iters;

    int k = (int)(centroids->size());

    Eigen::VectorXd prevCentr = *centroids;

    for (int i = 0; i < this->iters; ++i) {
        Eigen::VectorXd memb = findClosestCentroids(x_tr, m);
        computeCentroids(x_tr, m, memb);

        if (prevCentr == *centroids) break;
        prevCentr = *centroids;
    }
}

void KMeans::initCentroids(double *x_tr, int n) {
    Eigen::Map<Eigen::VectorXd> vector(x_tr, n);
    permutate(vector);
    centroids = new Eigen::Map<Eigen::VectorXd>(vector.array().data(), numRBFNeurons);
}

Eigen::VectorXd KMeans::findClosestCentroids(double *x_tr, int m) {
    int k = (int)(centroids->size());
    Eigen::Map<Eigen::VectorXd> x(x_tr, m);
    Eigen::MatrixXd distances = Eigen::MatrixXd::Zero(m, k);
    Eigen::VectorXd diffs(m);

    for (int i = 0; i < k; i++) {
        diffs = Eigen::VectorXd::Zero(m);

        diffs = x.array() - (*centroids)[i];
        diffs = diffs.array().pow(2);
        distances.col(i) = diffs;
    }
    Eigen::VectorXd v(m);
    for (int i = 0; i < m; ++i) {
        Eigen::MatrixXd::Index minRow;
        distances.row(i).minCoeff(&minRow);
        v[i] = minRow;
    }

    return v;
}

void KMeans::computeCentroids(double *x_tr, int m, Eigen::VectorXd memberships) {
    int k = (int)(centroids->size());
    Eigen::Map<Eigen::VectorXd> vector(x_tr, m);

    for (int i = 0; i < k; ++i) {
        if((memberships.array() == i).any()) {
            double d = (memberships.array() == i).select(vector.array(), 0).mean();
            (*centroids)[i] = d;
        }
    }
}

void KMeans::permutate(Eigen::Map<Eigen::VectorXd> vec) {
    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm(vec.size());
    perm.setIdentity();
    std::random_shuffle(perm.indices().data(), perm.indices().data()+perm.indices().size());
    vec = perm * vec;
}

Eigen::VectorXd KMeans::getCentroids() {
    return *centroids;
}

void KMeans::free_mem() {
    if(centroids) delete centroids;
    centroids = nullptr;
}

RBFNet::RBFNet(int numRBFNeurons, double sigma) : Base(),
                                                                  numRBFNeurons(numRBFNeurons),
                                                                  beta(1 / (2 * pow(sigma, 2))) {
    kMeans = nullptr;
}

RBFNet::RBFNet(double *x, double *y, int n,
               int numRBFNeurons,
               double sigma) : RBFNet(numRBFNeurons, sigma) {
    build(x, y, n);
}

RBFNet::RBFNet(char *f, int numRBFNeurons, double sigma) :
        RBFNet(numRBFNeurons, sigma) {
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
    delete[] x;
    delete[] y;
}

RBFNet::~RBFNet() {
    free_mem();
}

void RBFNet::build(double *x, double *y, int n) {
    kMeans = new KMeans(numRBFNeurons);
    kMeans->initCentroids(x, n);
    kMeans->run(x ,n);

    Eigen::VectorXd centr = kMeans->getCentroids();
    Eigen::MatrixXd act = Eigen::MatrixXd::Zero(n, numRBFNeurons);

    for (int i = 0; i < n; ++i) {
        act.block(i, 0, 1, numRBFNeurons) = getActivations(centr, x[i]).transpose();
    }

    Eigen::VectorXd tmp = act.rowwise().sum();
    act.array().colwise() / tmp.array();

    Eigen::MatrixXd X_act(n, act.cols() + 1);
    X_act << Eigen::VectorXd::Ones(n), act;

    Eigen::Map<Eigen::VectorXd> y_tr(y, n);

    Eigen::MatrixXd X_act_tr = X_act.transpose();
    Eigen::MatrixXd X_act_inv = X_act_tr * X_act;
    Eigen::MatrixXd X_act_fin = X_act_inv * X_act_tr;
    Eigen::VectorXd final = X_act_fin * y_tr;

    this->theta = new Eigen::Map<Eigen::VectorXd>(final.array().data(), numRBFNeurons + 1);
}

double RBFNet::calculate(double x) {
    Eigen::VectorXd phis = getActivations(kMeans->getCentroids(), x);

    phis = phis / phis.array().sum();

    Eigen::VectorXd phis_n(theta->size());
    phis_n << 1, phis;

    return (*theta).dot(phis_n);
}

Eigen::VectorXd RBFNet::getActivations(Eigen::VectorXd centroids, double input) {
    Eigen::VectorXd sqrdDists = (centroids.array() - input).pow(2);
    Eigen::VectorXd e(centroids.size());
    e = (-beta * sqrdDists).array().exp();
    return e;
}

void RBFNet::free_mem() {
    if (theta) delete theta;
    if (kMeans) delete kMeans;
    theta = nullptr;
    kMeans = nullptr;
}
