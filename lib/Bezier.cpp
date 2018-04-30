#include <cmath>
#include "Bezier.h"

#define EPSILON 1.0e-5

Point::Point() : x(0.0), y(0.0) {

}

Point::Point(double _x, double _y) : x(_x), y(_y) {

}

Point Point::operator+(const Point &point) const {
    return {x + point.x, y + point.y};
}

Point Point::operator-(const Point &point) const {
    return {x - point.x, y - point.y};
}

Point Point::operator*(double v) const {
    return {x * v, y * v};
}

void Point::operator+=(const Point &point) {
    x += point.x;
    y += point.y;
}

void Point::operator-=(const Point &point) {
    x -= point.x;
    y -= point.y;
}

void Point::normalize() {
    double l = sqrt(x * x + y * y);
    x /= l;
    y /= l;
}

double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}

void Point::setX(double x) {
    this->x = x;
}

void Point::setY(double y) {
    this->y = y;
}

void Segment::calculatePoint(double t, Point &p) {
    double t2 = t * t;
    double t3 = t2 * t;
    double nt = 1.0 - t;
    double nt2 = nt * nt;
    double nt3 = nt2 * nt;
    p.setX(nt3 * points[0].getX() +
           3.0 * t * nt2 * points[1].getX() +
           3.0 * t2 * nt * points[2].getX() +
           t3 * points[3].getX());
    p.setY(nt3 * points[0].getY() +
           3.0 * t * nt2 * points[1].getY() +
           3.0 * t2 * nt * points[2].getY() +
           t3 * points[3].getY());
}

double Segment::calculate(double t) {
    double t2 = t * t;
    double t3 = t2 * t;
    double nt = 1.0 - t;
    double nt2 = nt * nt;
    double nt3 = nt2 * nt;

    return nt3 * points[0].getY() +
           3.0 * t * nt2 * points[1].getY() +
           3.0 * t2 * nt * points[2].getY() +
           t3 * points[3].getY();
}

Bezier::Bezier() : seg_ar(nullptr) {
}

Bezier::Bezier(double *x, double *y, int n) : Base(n) {
    buildSpline(x, y, n);
}

Bezier::Bezier(char *f) {
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
}

void Bezier::free_mem() {
    delete[] seg_ar;
    seg_ar = nullptr;
}

Bezier::~Bezier() {
    free_mem();
}

void Bezier::createPoints(double *x, double *y, int cnt, Point *points) {
    for (int i = 0; i < cnt; ++i) {
        points[i] = Point(x[i], y[i]);
    }
}

void Bezier::buildSpline(double *x, double *y, int cnt) {
    free_mem();
    this->n = cnt - 1;
    Point values[cnt];
    createPoints(x, y, cnt, values);

    seg_ar = new Segment[n];

    Point tgL;
    Point tgR;
    Point cur;
    Point next = values[1] - values[0];
    next.normalize();

    double l1, l2, tmp, d;

    for (int i = 0; i < n; ++i) {
        seg_ar[i].points[0] = seg_ar[i].points[1] = values[i];
        seg_ar[i].points[2] = seg_ar[i].points[3] = values[i + 1];

        tgL = tgR;
        cur = next;

        if (i + 1 < n) {
            next = values[i + 2] - values[i + 1];
            next.normalize();

            tgR = cur + next;
            tgR.normalize();
        } else {
            tgR.setX(0.0);
            tgR.setY(0.0);
        }

        if (fabs(values[i + 1].getY() - values[i].getY()) < EPSILON) {
            l1 = l2 = 0.0;
        } else {
            tmp = values[i + 1].getX() - values[i].getX();
            l1 = fabs(tgL.getX()) > EPSILON ? tmp / (2.0 * tgL.getX()) : 1.0;
            l2 = fabs(tgR.getX()) > EPSILON ? tmp / (2.0 * tgR.getX()) : 1.0;
        }

        if (fabs(tgL.getX()) > EPSILON && fabs(tgR.getX()) > EPSILON) {
            tmp = tgL.getY() / tgL.getX() - tgR.getY() / tgR.getX();
            if (fabs(tmp) > EPSILON) {
                d = (values[i + 1].getY() - tgR.getY() / tgR.getX() *
                                            values[i + 1].getX() - values[i].getY() + tgL.getY() / tgL.getX() *
                                                                                      values[i].getX()) / tmp;
                if (d > values[i].getX() && d < values[i + 1].getX()) {
                    if (tgL.getY() > 0.0) {
                        if (l1 > l2)
                            l1 = 0.0;
                        else
                            l2 = 0.0;
                    } else {
                        if (l1 < l2)
                            l1 = 0.0;
                        else
                            l2 = 0.0;
                    }
                }
            }
        }

        seg_ar[i].points[1] += tgL * l1;
        seg_ar[i].points[2] -= tgR * l2;
    }
}

double Bezier::calculateYfromX(double x) {
    Segment segment;
    if (x <= seg_ar[0].points[0].getX()) {
        return seg_ar[0].points[0].getY();
    } else if (x >= seg_ar[n - 1].points[3].getX()) {
        return seg_ar[n - 1].points[3].getY();
    } else {
        for (int i = 0; i < n; ++i) {
            if (x >= seg_ar[i].points[0].getX() && x <= seg_ar[i].points[3].getX()) {
                segment = seg_ar[i];
            }
        }
    }

    //Cubic equasion solving
    double p = segment.points[0].getX() + 3 * segment.points[1].getX()
               - 3 * segment.points[2].getX() + segment.points[3].getX();
    double a = (3 * segment.points[0].getX() + 6 * segment.points[1].getX()
                + 3 * segment.points[2].getX()) / p;
    double b = (-3 * segment.points[0].getX() + 3 * segment.points[1].getX()) / p;
    double c = (segment.points[0].getX() - x) / p;

    double q = (pow(a, 2) - 3 * b) / 9;
    double r = (2 * pow(a, 3) - 9 * a * b + 27 * c) / 54;
    double q3 = pow(q, 3);
    double s = q3 - pow(r, 2);

    double t = 0, f;
    if (s > 0) {
        double t1, t2, t3;

        f = acos(r / sqrt(q3)) / 3;

        t1 = -2 * sqrt(q) * cos(f) - a / 3;
        t2 = -2 * sqrt(q) * cos(f + 2 * M_PI / 3) - a / 3;
        t3 = -2 * sqrt(q) * cos(f - 2 * M_PI / 3) - a / 3;

        if (t1 >= 0 && t1 <= 1) t = t1;
        else if (t2 >= 0 && t2 <= 1) t = t2;
        else if (t3 >= 0 && t3 <= 1) t = t3;
    } else if (s < 0) {
        if (q >= 0) {
            f = acosh(fabs(r) / sqrt(q3)) / 3;
            t = -2 * signum(r) * sqrt(q) * cosh(f) - a / 3;
        } else {
            f = asinh(fabs(r) / sqrt(fabs(q3))) / 3;
            t = -2 * signum(r) * sqrt(fabs(q)) * sinh(f) - a / 3;
        }
    } else {
        double t1, t2;

        t1 = -2 * pow(r, 1 / 3) - a / 3;
        t2 = pow(r, 1 / 3) - a / 3;

        if (t1 >= 0 && t1 <= 1) t = t1;
        else if (t2 >= 0 && t2 <= 1) t = t2;
    }

    return segment.calculate(t);
}

double Bezier::signum(double x) {
    return (x > 0) - (x < 0);
}

int Bezier::size() {
    return this->n;
}

void Bezier::calculatePointOnSegment(int s, int t, Point &p) {
    seg_ar[s].calculatePoint(t, p);
}
