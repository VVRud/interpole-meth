#ifndef SNTKURSACH_BASE_H
#define SNTKURSACH_BASE_H

#include <fstream>
#include <cstring>
#include "headers/Exceptions.h"

class Base {
protected:
    double xMin;
    double xMax;
    double yMin;
    double yMax;

    int countLines(std::ifstream &f) {
        int n = 0;
        auto *s = new char[500];
        while (!f.eof()) {
            f.getline(s, 500);
            if (strcmp(s, "") != 0) n++;
        }
        f.clear();
        f.seekg(0);
        delete[] s;
        return n;
    }

    void readDataFromFile(std::ifstream &f, double *x, double *y, int n) {
        double xC, yC;
        for (int i = 0; i < n; i++) {
            f >> xC;
            f >> yC;
            if (i == 0) {
                xMin = xMax = xC;
                yMin = yMax = yC;
            } else {
                if (xC < xMin) xMin = xC;
                if (xC > xMax) xMax = xC;
                if (yC < yMin) yMin = yC;
                if (yC > yMax) yMax = yC;
            }
            x[i] = xC;
            y[i] = yC;
        }
    }

    Base() = default;

    explicit Base(int n) {
        if (n <= 1) {
            Exceptions::error(Exceptions::FEW_POINTS);
            return;
        }
    }

public:
    double getXMin() const {
        return xMin;
    }

    double getXMax() const {
        return xMax;
    }

    double getYMin() const {
        return yMin;
    }

    double getYMax() const {
        return yMax;
    }
};

#endif //SNTKURSACH_BASE_H
