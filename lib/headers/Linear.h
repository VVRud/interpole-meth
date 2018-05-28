#ifndef SNTKURSACH_LINEAR_H
#define SNTKURSACH_LINEAR_H

#include "lib/Base.hpp"

/** Linear class represents piecewise linear function interpolation.
 *
 */
class Linear : public Base {
protected:

    /** Structure represents linear sector between 2 points.
     */
    struct spline_tuple {
        double b, k, y, x;
    };

    /** Array of spline sectors.
     */
    spline_tuple *splines;

    /** Number of interpolated sectors.
     *
     */
    int n;

    /** Clean memory function.
     */
    void free_mem();

public:

    /** Basic constructor for Linear method of interpolation.
     */
    Linear();

    /** Destructor.
     */
    virtual ~Linear();

    /** Constructor for interpolation function using data.
     *
     * @param x Array of function X values.
     * @param y Array of function Y values.
     * @param n Number of points in both X and Y arrays.
     */
    Linear(double *x, double *y, int n);

    /** Constructor for interpolation function using data in file.
     * This constructor reads data from file and interpolating function on fly.
     *
     * @param f File name to read data from
     */
    explicit Linear(char *f);

    /** Main Method for function interpolation using Linear interpolation.
     *
     * @param x Array of function X values.
     * @param y Array of function X values.
     * @param n Number of points in both X and Y arrays.
     */
    void build(double *x, double *y, int cnt);

    /** Calculation function value after coefficient were created.
     *
     * @param x X coordinate to get responding Y coordinate.
     * @return Y coordinate.
     */
    double calculate(double x);
};


#endif //SNTKURSACH_LINEAR_H
