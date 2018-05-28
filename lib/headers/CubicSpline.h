#ifndef SNTKURSACH_CUBICSPLINE_H
#define SNTKURSACH_CUBICSPLINE_H


#include <libio.h>
#include <fstream>
#include <cstdio>
#include "lib/Spline.hpp"

/** CubicSpline class represents interpolated function.
 * Interpolation function builds between every 2 points.
 *
 * @extends Spline
 */
class CubicSpline : public Spline {
protected:

    /** Class to check if points are enough for interpolation.
     *
     * @param n Number of points.
     */
    explicit CubicSpline(int n);

public:

    /** Constructor without parameters.
     */
    CubicSpline();

    /** Destructor.
     */
    ~CubicSpline() override;

    /** Constructor to create Spline and interpolate it on fly.
     *
     * @param x Array of X coordinates for function.
     * @param y Array of Y coordinates for function.
     * @param n Number of points in both X and Y arrays.
     */
    CubicSpline(double *x, double *y, int n);

    /** Constructor with reading data from file.
     *
     * @param f File name to read data from.
     */
    explicit CubicSpline(char *f);

    /** Main interpolation method.
     * Here coefficients for spline will be found using
     * sweep method.
     *
     * @param x Array of X coordinates for function.
     * @param y Array of Y coordinates for function.
     * @param cnt Number of points in both X and Y arrays.
     */
    void buildSpline(double *x, double *y, int cnt) override;

    /** Calculation function value after coefficient were created.
     *
     * @param x X coordinate to get responding Y coordinate.
     * @return Y coordinate.
     */
    double calculate(double x) override;
};


#endif //SNTKURSACH_SPLINE_H
