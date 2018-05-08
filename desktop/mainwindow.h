#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPainter>
#include "../lib/Interpolation.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void calc();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    char* fileName;
    bool graphCreated = false;
    QVector<double> * xDots;
    QVector<double> * yDots;

    enum {DOTS, LINEAR, CUBIC, LAGRANJ, BEZIER,
            COUNT};

    Linear lin;
    CubicSpline cs;
    AkimaSpline as;
    LagranjPolinome lp;
    Bezier bez;

    void createObjects();
    void createGraphs();
    void drawCords();
    void drawDots();
    void paint(double* x, double* y, int n, int s, QPen qp);
    int countLines(std::ifstream &f);
    void readDataFromFile(std::ifstream &f, QVector<double> *x, QVector<double> *y, int n);
    void fillArrays();
    void clearArrays();

private slots:
    void on_check_lin_stateChanged(int arg1);
    void on_check_cub_stateChanged(int arg1);
    void on_check_bez_stateChanged(int arg1);
    void on_check_net_stateChanged(int arg1);
    void on_check_lag_stateChanged(int arg1);
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
