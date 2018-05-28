#ifndef SNTKURSACH_SPLINE_H
#define SNTKURSACH_SPLINE_H


#include <fstream>
#include <iostream>
#include "Base.hpp"

/** Basic class for splines as Cubic spline or Akima spline.
 * This class stores arrays of Spline segments.
 *
 * @extends Base
 */
class Spline : public Base {
protected:
    /** Basic constructor to check quantity of points.
     *
     * @param n Number of points.
     */
    Spline(int n) : Base(n) {
    }

    /** @struct spline_tuple
     *  @brief Structure represent interpolated function sector between 2 points.
     *  @var spline_tuple::a
     *  @var spline_tuple::b
     *  @var spline_tuple::c
     *  @var spline_tuple::d
     *  @var spline_tuple::x
     */
    struct spline_tuple {
        double a, b, c, d, x;
    };

    /** Array of spline coefficients for every curve between 2 points.
     */
    spline_tuple *splines;

    /** Number of splines in Splines array.
     */
    int n;

    /** Method to cleanup memory.
     */
    void free_mem() {
        if (!splines) {
            delete[] splines;
            splines = nullptr;
        }
    }


public:
    /** Default constructor without parameters for Splines.
     */
    Spline() : Base(), splines(nullptr){}

    /** Virtual function to be initialized in derived classes.
     *
     * @param x Array of function X values.
     * @param y Array of function Y values.
     * @param n Number of points in both X and Y arrays.
     */
    virtual void buildSpline(double *x, double *y, int n) {
    }

    /** Calculate corresponding X for Y.
     *
     * @param x Value X to get corresponding Y.
     * @return
     */
    virtual double calculate(double x) {
    }

    /** Destructor for spline.
     */
    virtual ~Spline() {
        free_mem();
    }
};

#endif //SNTKURSACH_SPLINE_H
