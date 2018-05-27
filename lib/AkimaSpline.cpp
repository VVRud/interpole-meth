#include <cmath>
#include "headers/AkimaSpline.h"

AkimaSpline::AkimaSpline() : CubicSpline() {
}

AkimaSpline::~AkimaSpline() {
    free_mem();
}

AkimaSpline::AkimaSpline(double *x, double *y, int n) : CubicSpline(n) {
    buildSpline(x, y, n);
}

AkimaSpline::AkimaSpline(char *f) {
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
    delete[] x;
    delete[] y;
}

void AkimaSpline::buildSpline(double *x, double *y, int cnt) {
    free_mem();
    this->n = cnt;

    splines = new spline_tuple[n];
    auto *m = new double[n + 4];

    for (int i = 0; i < n; i++) {
        m[i + 2] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    }

    //Not Periodic
    m[0] = 3 * m[2] - 2 * m[3];
    m[1] = 2 * m[2] - 2 * m[3];
    m[n + 2] = 2 * m[n + 1] - 2 * m[n];
    m[n + 3] = 3 * m[n + 1] - 2 * m[n];

    //Periodic
/*
    m[0] = m[n];
    m[1] = 2 * m[n + 1];
    m[n + 2] = 2 * m[2];
    m[n + 3] = 3 * m[3];
*/

    auto *tL = new double[n + 1];
    auto *tR = new double[n + 1];

    double ne;
    for (int i = 0; i < n + 1; i++) {
        ne = fabs(m[i + 3] - m[i + 2]) + fabs(m[i + 1] - m[i]);
        if (ne > 0) {
            double alpha = fabs(m[i + 1] - m[i]) / ne;
            tL[i] = m[i + 1] + alpha * (m[i + 2] - m[i + 1]);
            tR[i] = tL[i];
        } else {
            tL[i] = m[i + 1];
            tR[i] = m[i + 2];
        }
    }

    for (int i = 0; i < n + 1; i++) {
        splines[i].x = x[i];
        splines[i].a = y[i];
        splines[i].b = tR[i];
        double h = x[i + 1] - x[i];
        splines[i].c = 1 / h * (3 * m[i + 2] - 2 * tR[i] - tL[i + 1]);
        splines[i].d = 1 / pow(h, 2) * (tR[i] + tL[i + 1] - 2 * m[i + 2]);
    }

    delete[] m;
    delete[] tL;
    delete[] tR;
}

