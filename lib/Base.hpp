#ifndef SNTKURSACH_BASE_H
#define SNTKURSACH_BASE_H

#include <fstream>
#include "Exceptions.h"

class Base {
protected:
    int countLines(std::ifstream &f) {
        int n = 0;
        auto *s = new char[500];
        while (!f.eof()) {
            f.getline(s, 500);
            n++;
        }
        f.clear();
        f.seekg(0);
        return n;
    }

    void readDataFromFile(std::ifstream &f, double *x, double *y, int n) {
        for (int i = 0; i < n; i++) {
            f >> x[i];
            f >> y[i];
        }
    }

    Base() = default;

    explicit Base(int n) {
        if (n <= 1) {
            Exceptions::error(Exceptions::FEW_POINTS);
            return;
        }
    }
};

#endif //SNTKURSACH_BASE_H
