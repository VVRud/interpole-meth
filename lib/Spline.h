//
// Created by vrudenko on 29/04/18.
//

#ifndef SNTKURSACH_SPLINE_H
#define SNTKURSACH_SPLINE_H


#include <fstream>

class Spline {
protected:
    Spline(int n);
    // Структура, описывающая сплайн на каждом сегменте сетки
    struct spline_tuple {
        double a, b, c, d, x;
    };

    spline_tuple *splines; // Сплайн
    int n; // Количество узлов сетки
    virtual void free_mem(); // Освобождение памяти
    int countLines(std::ifstream &f);
    void readDataFromFile(std::ifstream &f, double *x, double *y, int n);

public:
    Spline(); //конструктор
    virtual ~Spline();
//    Spline(double *x, double *y, int n);

    //TODO DELETE. ONLY DEBUG VERSION
    void print_coef();

    virtual //-------------------------------
    void buildSpline(double *x, double *y, int cnt);

    virtual double calculate(double x);

};


#endif //SNTKURSACH_SPLINE_H
