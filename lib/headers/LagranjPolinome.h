#ifndef SNTKURSACH_LAGRANJPOLINOME_H
#define SNTKURSACH_LAGRANJPOLINOME_H

#include "lib/Base.hpp"

/** LagranjPolinome class represents interpolation method using Lagranj polinomes.
 *
 * @extends Base
 */
class LagranjPolinome : public Base {
protected:

    /** Structure representing Lagranj polinome between 2 points.
     */
    struct spline_tuple {
        double y, x;
    };

    /** Array of interpolated sectors.
     */
    spline_tuple *splines; // Сплайн

    /** Number of sectors in array.
     */
    int n;

    /** Clean memory method.
     */
    void free_mem();

public:

    /** Basic constructor for Lagranj polinome method of interpolation.
     */
    LagranjPolinome();

    /** Destructor.
     */
    ~LagranjPolinome();

    /** Constructor for interpolation function using data in file.
     * This constructor reads data from file and interpolating function on fly.
     *
     * @param f File name to read data from
     */
    explicit LagranjPolinome(char *f);

    /** Constructor for interpolation function using data.
     *
     * @param x Array of function X values.
     * @param y Array of function Y values.
     * @param n Number of points in both X and Y arrays.
     */
    LagranjPolinome(double *x, double *y, int n);

    /** Main Method for function interpolation using Lagranj polinome.
     *
     * @param x Array of function X values.
     * @param y Array of function X values.
     * @param n Number of points in both X and Y arrays.
     */
    void buildSpline(double *x, double *y, int n);

    /** Calculation function value after coefficient were created.
     *
     * @param x X coordinate to get responding Y coordinate.
     * @return Y coordinate.
     */
    double calculate(double x);
};


#endif //SNTKURSACH_LAGRANJPOLINOME_H
