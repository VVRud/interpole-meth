#ifndef SNTKURSACH_BEZIER_H
#define SNTKURSACH_BEZIER_H


#include "../Base.hpp"

class Point {
protected:
    double x, y;

public:
    Point();

    Point(double _x, double _y);

    Point operator+(const Point &point) const;

    Point operator-(const Point &point) const;

    Point operator*(double v) const;

    void operator+=(const Point &point);

    void operator-=(const Point &point);

    double getX();

    double getY();

    void setX(double x);

    void setY(double y);

    void normalize();
};

class Segment {
public:
    Point points[4];

    void calculatePoint(double t, Point &p);

    double calculateY(double t);
};

class Bezier : public Base {
protected:
    Segment *seg_ar = nullptr;

    void free_mem();

    int n;

    void createPoints(double *x, double *y, int cnt, Point *points);

    double signum(double x);

public:
    Bezier();

    Bezier(double *x, double *y, int n);

    explicit Bezier(char *f);

    virtual ~Bezier();

    void buildSpline(double *x, double *y, int cnt);

    double calculateYfromX(double x);

    void calculatePointOnSegment(int s, double t, Point &p);

    int size();
};


#endif //SNTKURSACH_BEZIER_H
