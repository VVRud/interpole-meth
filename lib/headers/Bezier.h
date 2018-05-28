#ifndef SNTKURSACH_BEZIER_H
#define SNTKURSACH_BEZIER_H


#include "lib/Base.hpp"

/** Class Point created to represent a point on the 2D field.
 * This class helps to adjust interactions in Segment class and Bezier class.
 * Class Point can also represent vector coordinates.
 */
class Point {
protected:
    /** X coordinate for Point.
     */
    double x;

    /** Y coordinate for Point.
     */
    double y;

public:
    /** Constructor for Point without parameters.
     * This constructor can be used for creating a Point representaition
     * when getting approximated data.
     */
    Point();

    /** Constructor for Point with double type parameters.
     *
     * @param _x Representation for Point on x axis for 2D field.
     * @param _y Representation for Point on y axis for 2D field.
     */
    Point(double _x, double _y);

    /** Reloaded adding points operator.
     *
     * @param point Point to add.
     * @return Point, which contains added coordinates for both axis.
     */
    Point operator+(const Point &point) const;

    /** Reloaded substraction Point operator.
     *
     * @param point Point to substract.
     * @return Point that contains substracted coordinates for both axis.
     */
    Point operator-(const Point &point) const;

    /** Multiplying Point on constant.
     *
     * @param v Constant for Point to be multiplied.
     * @return Point that contains multiplied coordinates for both axis.
     */
    Point operator*(double v) const;

    /** Reloaded assignment operator for Point adding.
     *
     * @param point Point to add.
     */
    void operator+=(const Point &point);

    /** Reloaded assignment operator for Point substraction.
     *
     * @param point Point to substract.
     */
    void operator-=(const Point &point);

    /** Getter for Point X coordinate.
     *
     * @return X coordinate.
     */
    double getX();

    /** Getter for Point Y coordinate.
     *
     * @return Y coordinate
     */
    double getY();

    /** Setter for Point X coordinate.
     *
     * @param x Double type X coordinate to set.
     */
    void setX(double x);

    /** Setter for Point Y coordinate.
     *
     * @param y Double type Y coordinate to set.
     */
    void setY(double y);

    /** Normalization process for Point representing a vector.
     *  Geometric normalization process using formulas:
     *  \f{eqnarray*}{
     *      x_n &=& \frac{x}{\sqrt{x^2+y^2}}
     *      y_n &=& \frac{y}{\sqrt{x^2+y^2}}
     *  \f}
     */
    void normalize();
};

/** Segment class represents interpolated Bezier segment between 2 points from an array.
 * Segments quantity will be \f$ s_num-1 \f$.
 *
 */
class Segment {
public:
    /** Array of Points to represent interpolated function.
     * Third-order Bezier curve points are stored here.
     */
    Point points[4];

    /** Method to calculate Point coordinates for interpolated function.
     *
     * @param t T parameter for Bezier curve.
     * @param p Point to store interpolated coordinates.
     */
    void calculatePoint(double t, Point &p);

    /** Method to get only Y coordinate of Point.
     *
     * @param t T parameter for Bezier curve.
     * @return Value for Y coordinate.
     */
    double calculateY(double t);
};

/** Bezier class represents function interpolation method using third-order Bezier curves.
 * Formula for this curve is
 * \mathbf{B}(t) = (1-t)^3\mathbf{P}_0 + 3t(1-t)^2\mathbf{P}_1 + 3t^2(1-t)\mathbf{P}_2 + t^3\mathbf{P}_3, \quad t \in [0,1]
 */
class Bezier : public Base {
protected:
    /** Array of interpolated functions between 2 points.
     *
     */
    Segment *seg_ar = nullptr;

    /** Function for memory cleaning.
     *
     */
    void free_mem();

    /** Number of segments in array.
     *
     */
    int n;

    /** This function fills array of Points by creating them.
     *
     * @param x Array of X values for function.
     * @param y Array fo Y values for function.
     * @param cnt Number of point in both arrays.
     * @param points Array of Points to be filled.
     */
    void createPoints(double *x, double *y, int cnt, Point *points);

    /** Signum function.
     *
     * @param x
     * @return Return value equals:
     *      - 1 if x > 0;
     *      - 0 if x = 0;
     *      - -1 if x < 0.
     */
    double signum(double x);

public:
    /** Constructor for Bezier curve without parameters.
     *
     */
    Bezier();

    /** Constructor to create Bezier function and interpolate it on fly.
     *
     * @param x Array of X values for function.
     * @param y Array of Y values for function.
     * @param n Nuber of points in both X and Y arrays.
     */
    Bezier(double *x, double *y, int n);

    /** Constructor for Bezier curve created from values in file.
     *
     * @param f File name to read X and Y from.
     */
    explicit Bezier(char *f);

    /** Destructor for Bezier class object.
     *
     */
    virtual ~Bezier();

    /** Main interpolation function.
     * //TODO
     *
     * @param x Array of X values for function.
     * @param y Array of Y values for function.
     * @param cnt Number of Points in X and Y arrays.
     */
    void buildSpline(double *x, double *y, int cnt);

    /** Method for calculating Y value responding to X.
     * Cubic equation is solved here for getting T value responding to X.
     *
     * @param x X value responding to Y.
     * @return Value of Y responding to X.
     *
     * @bug Cubic equation is not solved right.
     */
    double calculateYfromX(double x);

    /** Calculating point corresponding to segment.
     *
     * @param s Number o Segment.
     * @param t Parametric T value for Bezier curve.
     * @param p Point to store calculated X and Y.
     */
    void calculatePointOnSegment(int s, double t, Point &p);

    /** Getter for n value.
     *
     * @return Number of segments in array.
     */
    int size();
};


#endif //SNTKURSACH_BEZIER_H
