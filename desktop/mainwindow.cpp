#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "../lib/Linear.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    xDots(nullptr),
    yDots(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    clearArrays();
    delete ui;
}

void MainWindow::drawCords()
{
    ui->field->xAxis->setLabel("X axis");
    ui->field->xAxis->setRange(lin.getXMin() - fabs(lin.getXMin()) / 10,
                               lin.getXMax() + fabs(lin.getXMax() / 10));

    ui->field->yAxis->setLabel("Y axis");
    ui->field->yAxis->setRange(lin.getYMin() - fabs(lin.getYMin()) / 10,
                               lin.getYMax() + fabs(lin.getYMax() / 10));
}

void MainWindow::drawDots() {
    ui->field->graph(DOTS)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->field->graph(DOTS)->setLineStyle(QCPGraph::lsNone);
    ui->field->graph(DOTS)->setPen(QPen(Qt::black));
    xDots->resize(9);
    yDots->resize(9);
    ui->field->graph(DOTS)->setData(*xDots, *yDots);
}

void MainWindow::paint(double *x, double *y, int n, int s, QPen qp) {
    QVector<double> xVec(s);
    QVector<double> yVec(s);

    std::copy(x, x + s, std::begin(xVec));
    std::copy(y, y + s, std::begin(yVec));

    ui->field->graph(n)->setPen(qp);
    ui->field->graph(n)->setData(xVec, yVec);
}

void MainWindow::calc() {
    ui->field->setBackground(QBrush(QColor("#f2f2f2")));
    if (ui->groupBox->isEnabled()){
        drawCords();
        drawDots();
        double res = 0.01;
        double d = fabs(lin.getXMax()) + fabs(lin.getXMin());

        auto dres = (int)(d / res);
        auto * x = new double[dres];
        auto * y = new double[dres];

        if (ui->check_lin->isChecked()) {
            for (int i = 0; i < dres; i++) {
                x[i] = lin.getXMin() + i * res;
                y[i] = lin.calculate(x[i]);
            }
            paint(x, y, LINEAR, dres, QPen(Qt::red));
        } else ui->field->graph(LINEAR)->data().data()->clear();

        if (ui->check_cub->isChecked()) {
            for (int i = 0; i < dres; i++) {
                x[i] = cs.getXMin() + i * res;
                y[i] = cs.calculate(x[i]);
            }
            paint(x, y, CUBIC, dres, QPen(Qt::darkGreen));
        } else ui->field->graph(CUBIC)->data().data()->clear();

        if (ui->check_bez->isChecked()) {
            int resBez = 1000;
            int size = resBez * bez.size();
            auto * xbez = new double[size];
            auto * ybez = new double[size];
            int pl = 0;
            for (int j = 0; j < bez.size(); ++j) {
                for (int i = 0; i < resBez; i++, pl++) {
                    Point p;
                    bez.calculatePointOnSegment(j, (double)i / (double)resBez, p);
                    xbez[pl] = p.getX();
                    ybez[pl] = p.getY();
                }
            }
            paint(xbez, ybez, BEZIER, size, QPen(Qt::darkMagenta));
            delete[] xbez;
            delete[] ybez;
        } else ui->field->graph(BEZIER)->data().data()->clear();

        if (ui->check_lag->isChecked()) {
            for (int i = 0; i < dres; i++) {
                x[i] = lp.getXMin() + i * res;
                y[i] = lp.calculate(x[i]);
            }
            paint(x, y, LAGRANJ, dres, QPen(Qt::darkCyan));
        } else ui->field->graph(LAGRANJ)->data().data()->clear();

        delete[] x;
        delete[] y;
        ui->field->replot();
    }
}

void MainWindow::on_check_lin_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    calc();
}

void MainWindow::on_check_cub_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    calc();
}

void MainWindow::on_check_bez_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    calc();
}

void MainWindow::on_check_net_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    calc();
}

void MainWindow::on_check_lag_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    calc();
}

void MainWindow::on_actionOpen_triggered()
{
    QString f = QFileDialog::getOpenFileName(
                this,
                tr("Open File"), "",
                "All Files (*.*);;Text File (*.txt)");
    QByteArray ba = f.toLatin1();
    this->fileName = ba.data();
    if (strcmp(fileName, "") != 0) {
        clearArrays();
        fillArrays();
        ui->groupBox->setEnabled(true);
        createObjects();
        if (!graphCreated) createGraphs();
        calc();
    }
}

void MainWindow::createObjects() {
    lin = Linear(fileName);
    cs = CubicSpline(fileName);
    bez = Bezier(fileName);
    lp = LagranjPolinome(fileName);
}

void MainWindow::createGraphs() {
    for (int i = 0; i < COUNT; i++) {
        ui->field->addGraph();
    }
    graphCreated = true;
}

int MainWindow::countLines(std::ifstream &f) {
    int n = 0;
    auto *s = new char[500];
    while (!f.eof()) {
        f.getline(s, 500);
        n++;
    }
    f.clear();
    f.seekg(0);
    delete[] s;
    return n;
}

void MainWindow::readDataFromFile(std::ifstream &f, QVector<double> *x, QVector<double> *y, int n) {
    double xC, yC;
    for (int i = 0; i < n; i++) {
        f >> xC;
        f >> yC;

        x->insert(i, xC);
        y->insert(i, yC);
    }
}

void MainWindow::fillArrays() {
     std::ifstream file(fileName);
     int n = countLines(file);
     xDots = new QVector<double>(n);
     yDots = new QVector<double>(n);
     readDataFromFile(file, xDots, yDots, n);
     file.close();
}

void MainWindow::clearArrays() {
    if (xDots) {
        delete xDots;
        xDots = nullptr;
    }
    if (yDots) {
        delete yDots;
        yDots = nullptr;
    }
}