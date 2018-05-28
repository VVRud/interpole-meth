#ifndef SNTKURSACH_BASE_H
#define SNTKURSACH_BASE_H

#include <fstream>
#include <cstring>
#include "lib/headers/Exceptions.h"

/** Base class contains basic functions for interpolation.
 *
 */
class Base {
protected:
    /** Minimum X value of the function to interpolate.
     */
    double xMin;

    /** Maximum X value of the function to interpolate.
     */
    double xMax;

    /** Minimum Y value of the function to interpolate.
     */
    double yMin;

    /** Maximum Y value of the function to interpolate.
     */
    double yMax;

    /** Method to count lines in file.
     *
     * @param f File stream to read lines from.
     * @return Number of lines in file
     */
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

    /** Read Points data from file stream.
     *
     * @param f File stream to read from.
     * @param x X array to fill.
     * @param y Y array to fill.
     * @param n number of lines in file.
     */
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

    /** Default constructor for Base class.
     *
     */
    Base() = default;

    /** Constructor to check number of points.
     *
     * @param n Number of points.
     */
    explicit Base(int n) {
        if (n <= 1) {
            Exceptions::error(Exceptions::FEW_POINTS);
            return;
        }
    }

public:
    /** Getter for minimum X function value.
     *
     * @return Minimum X value of function.
     */
    double getXMin() const {
        return xMin;
    }

    /** Getter for maximum X function value.
     *
     * @return Maximum X value of function.
     */
    double getXMax() const {
        return xMax;
    }

    /** Getter for minimum Y function value.
     *
     * @return Minimum Y value of function.
     */
    double getYMin() const {
        return yMin;
    }

    /** Getter for maximum Y function value.
     *
     * @return Maximum Y value of function.
     */
    double getYMax() const {
        return yMax;
    }
};

#endif //SNTKURSACH_BASE_H
