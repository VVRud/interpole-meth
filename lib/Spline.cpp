//
// Created by vrudenko on 29/04/18.
//

#include "Spline.h"
#include "Exceptions.h"


using namespace std;
//TODO DELETE. ONLY DEBUG VERSION
#include <iostream>
//-------------------------------

Spline::Spline() : splines(nullptr) {

}

int Spline::countLines(ifstream &f){
    int n = 0;
    auto * s = new char[500];
    while(!f.eof()) {
        f.getline(s, 500);
        n++;
    }
    f.clear();
    f.seekg(0);
    return n;
}

void Spline::readDataFromFile(ifstream &f, double *x, double *y, int n) {
    for (int i = 0; i < n; i++) {
        f >> x[i];
        f >> y[i];
    }
}

void Spline::buildSpline(double *x, double *y, int n) {
}

double Spline::calculate(double x) {
}

//TODO DELETE. ONLY DEBUG VERSION
void Spline::print_coef() {
    cout << "A[k]\tB[k]\tC[k]\tD[k]" << endl;
    for (int i = 0; i < n; ++i) {
        cout << splines[i].a << "\t";
        cout << splines[i].b << "\t";
        cout << splines[i].c << "\t";
        cout << splines[i].d << endl;
    }
}
//-------------------------------

void Spline::free_mem() {
    delete[] splines;
    splines = nullptr;
}

Spline::~Spline() {
    free_mem();
}

Spline::Spline(int n) {
    if(n<=1){
        Exceptions::error(Exceptions::FEW_POINTS);
        return;
    }
}
