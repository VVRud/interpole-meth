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
    void paintEvent(QPaintEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    char* fileName;
    QPainter painter;

    Linear lin;
    CubicSpline cs;
    AkimaSpline as;
    LagranjPolinome lp;
    RSFNet net;
    Bezier bez;

    void createObjects();

private slots:
    void on_check_lin_stateChanged(int arg1);
    void on_check_cub_stateChanged(int arg1);
    void on_check_ak_stateChanged(int arg1);
    void on_check_bez_stateChanged(int arg1);
    void on_check_net_stateChanged(int arg1);
    void on_check_lag_stateChanged(int arg1);
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
