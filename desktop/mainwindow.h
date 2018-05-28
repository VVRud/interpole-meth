#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPainter>
#include <lib/QCustomPlot/qcustomplot.h>
#include "../lib/Interpolation.h"

/** User interface namespace.
 *
 */
namespace Ui {
    class MainWindow;
}

/** Class MainWindow helps to work with ui.
 * The main purpose is to create a window for demonstration of
 * interpolation methods. Window is created by template MainWindow.ui.
 *
 * @extends QMainWindow
 */
class MainWindow : public QMainWindow {
Q_OBJECT
protected:
    /** Function to start calculations after file was chosen.
     *
     */
    void calc();

public:

    /** Main constructor for window.
     *
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = 0);

    /* Destructor for MainWindow object.
     *
     */
    ~MainWindow();

private:
    /** MainWindow object.
     */
    Ui::MainWindow *ui;

    /** Name of file to read data from.
     */
    char *fileName;

    /** Indicator for graphs creation.
     */
    bool graphCreated = false;

    /** Container to store X coordinates of function to be interpolated.
     */
    QVector<double> *xDots;

    /** Container to store Y coordinates of function to be interpolated.
     */
    QVector<double> *yDots;

    /** Enumeration of graph layers and quantity to be created.
     */
    enum {
        DOTS, LINEAR, CUBIC, LAGRANJ, BEZIER,
        COUNT
    };

    /** Linear interpolation object.
     */
    Linear lin;

    /** Cubic spline interpolation object.
     */
    CubicSpline cs;

    /** Lagranj polinome interpolation object.
     */
    LagranjPolinome lp;

    /** Bezier curve interpolation object.
     */
    Bezier bez;

    /** Create all interpolation objects from file.
     */
    void createObjects();

    /** Fill graphs to show all interpolation methods plus dots.
     */
    void createGraphs();

    /** Set labels to X and Y axis.
     */
    void drawCords();

    /** Show graph in the center of window after interpolation.
     */
    void focus();

    /** Draw original dots to graphic.
     */
    void drawDots();

    /** Paint interpolated function.
     *
     * @param x X points array for function.
     * @param y Y points array for function.
     * @param n Number of graph to draw on.
     * @param s Number of points in both X and Y arrays.
     * @param qp QPen to draw with.
     */
    void paint(double *x, double *y, int n, int s, QPen qp);

    /** Count number of lines (number of points) in file.
     *
     * @param f File stream to read from.
     * @return Number of lines in file.
     */
    int countLines(std::ifstream &f);

    /** Read data from file and fill arrays to interpolate.
     *
     * @param f File stream to read from.
     * @param x Container to store X coordinates of function.
     * @param y Container to store Y coordinates of function.
     * @param n Number of lines in file.
     */
    void readDataFromFile(std::ifstream &f, QVector<double> *x, QVector<double> *y, int n);

    /** Fill Containers of points.
     */
    void fillArrays();

    /** Clear containers.
     */
    void clearArrays();

    /** Show color picker window and change color.
     *
     * @param pWidget Widget from information block to change color.
     * @param pQWidget Widget from settings block.
     * @param pGraph Graph to change color.
     */
    void showColorPicker(QWidget *pWidget, QWidget *pQWidget, QCPGraph *pGraph);

    /** Fill boxes with line style.
     */
    void fillComboBoxes();

    /** Change pen style to one from combo box of styles.
     *
     * @param pGraph Graph to change pen style.
     * @param arg1 Style to set.
     */
    void changePenStyle(QCPGraph *pGraph, int arg1);

    /** Change Pen thickness of the graph.
     *
     * @param pGraph Graph to change thickness.
     * @param spinBox Spin Bos to get value from.
     */
    void changePenThickness(QCPGraph *pGraph, QSpinBox *spinBox);

private slots:

    /** Show and hide linear interpolation graphic.
     *
     * @param arg1 State of checkbox.
     */
    void on_check_lin_stateChanged(int arg1);

    /** Show and hide Cubic interpolation graphic.
     *
     * @param arg1 State of checkbox.
     */
    void on_check_cub_stateChanged(int arg1);

    /** Show and hide Bezier interpolation graphic.
     *
     * @param arg1 State of checkbox.
     */
    void on_check_bez_stateChanged(int arg1);

    /** Show and hide Lagranj interpolation graphic.
     *
     * @param arg1 State of checkbox.
     */
    void on_check_lag_stateChanged(int arg1);

    /** After pushing button show window with file chooser.
     * Set all toolboxes enabled.
     */
    void on_actionOpen_triggered();

    /** After pushing button show save file window.
     * File can be saved in:
     *      -JPG;
     *      -BMP;
     *      -PNG.
     */
    void on_actionSave_Plot_triggered();

    /** When editing of spin box finished, show interpolated
     * points using every method in text box below.
     */
    void on_spin_editingFinished();

    /** Change line style for Linear graphic.
     *
     * @param arg1 Style to choose.
     */
    void on_lin_style_tb_activated(int arg1);

    /** Change line style for Cubic graphic.
     *
     * @param arg1 Style to choose.
     */
    void on_cub_style_tb_activated(int arg1);

    /** Change line style for Bezier graphic.
     *
     * @param arg1 Style to choose.
     */
    void on_bez_style_tb_activated(int arg1);

    /** Change line style for Lagranj graphic.
     *
     * @param arg1 Style to choose.
     */
    void on_lag_style_tb_activated(int arg1);

    /** Change line thickness for Linear graphic.
     */
    void on_lin_thick_tb_editingFinished();

    /** Change line thickness for Cubic graphic.
     */
    void on_cub_thick_tb_editingFinished();

    /** Change line thickness for Lagranj graphic.
     */
    void on_lag_thick_tb_editingFinished();

    /** Change line thickness for Bezier graphic.
     */
    void on_bez_thick_tb_editingFinished();

    /** Change line color for Linear graphic.
     */
    void on_lin_col_choose_clicked();

    /** Change line color for Cubic graphic.
     */
    void on_cub_col_choose_clicked();

    /** Change line color for Lagranj graphic.
     */
    void on_lag_col_choose_clicked();

    /** Change line color for Bezier graphic.
     */
    void on_bez_col_choose_clicked();
};

#endif // MAINWINDOW_H
