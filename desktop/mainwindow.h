#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPainter>
#include <lib/QCustomPlot/qcustomplot.h>
#include "../lib/Interpolation.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
protected:
    void calc();

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    char *fileName;
    bool graphCreated = false;
    QVector<double> *xDots;
    QVector<double> *yDots;

    enum {
        DOTS, LINEAR, CUBIC, LAGRANJ, BEZIER,
        COUNT
    };

    Linear lin;
    CubicSpline cs;
    LagranjPolinome lp;
    Bezier bez;

    void createObjects();

    void createGraphs();

    void drawCords();

    void focus();

    void drawDots();

    void paint(double *x, double *y, int n, int s, QPen qp);

    int countLines(std::ifstream &f);

    void readDataFromFile(std::ifstream &f, QVector<double> *x, QVector<double> *y, int n);

    void fillArrays();

    void clearArrays();

    void showColorPicker(QWidget *pWidget, QWidget *pQWidget, QCPGraph *pGraph);

    void fillComboBoxes();

    void changePenStyle(QCPGraph *pGraph, int arg1);

    void changePenThickness(QCPGraph *pGraph, QSpinBox *spinBox);

private slots:

    void on_check_lin_stateChanged(int arg1);

    void on_check_cub_stateChanged(int arg1);

    void on_check_bez_stateChanged(int arg1);

    void on_check_lag_stateChanged(int arg1);

    void on_actionOpen_triggered();

    void on_actionSave_Plot_triggered();

    void on_spin_editingFinished();

    void on_lin_style_tb_activated(int arg1);

    void on_cub_style_tb_activated(int arg1);

    void on_lag_style_tb_activated(int arg1);

    void on_bez_style_tb_activated(int arg1);

    void on_lin_thick_tb_editingFinished();

    void on_cub_thick_tb_editingFinished();

    void on_lag_thick_tb_editingFinished();

    void on_bez_thick_tb_editingFinished();

    void on_lin_col_choose_clicked();

    void on_cub_col_choose_clicked();

    void on_lag_col_choose_clicked();

    void on_bez_col_choose_clicked();
};

#endif // MAINWINDOW_H
