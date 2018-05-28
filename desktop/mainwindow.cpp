#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "lib/headers/Linear.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        xDots(nullptr),
        yDots(nullptr) {
    ui->setupUi(this);
    fillComboBoxes();
    drawCords();
    ui->field->setBackground(QBrush(QColor("#f2f2f2")));
    ui->field->setInteraction(QCP::iRangeDrag, true);
    ui->field->setInteraction(QCP::iRangeZoom, true);
}

MainWindow::~MainWindow() {
    clearArrays();
    delete ui;
}

void MainWindow::fillComboBoxes() {
    QStringList list = QStringList() << tr("Solid Line") << tr("Dash Line") << tr("Dot Line") <<
                                     tr("Dash Dot Line") << tr("Dash Dot Dot Line");
    ui->lin_style_tb->addItems(list);
    ui->cub_style_tb->addItems(list);
    ui->lag_style_tb->addItems(list);
    ui->bez_style_tb->addItems(list);
}

void MainWindow::drawCords() {
    ui->field->xAxis->setLabel("X axis");
    ui->field->yAxis->setLabel("Y axis");
}

void MainWindow::focus() {
    double dx = fabs(lin.getXMin() - lin.getXMax());
    double dy = fabs(lin.getYMin() - lin.getYMax());

    ui->field->xAxis->setRange(lin.getXMin() - dx / 10,
                               lin.getXMax() + dx / 10);

    ui->field->yAxis->setRange(lin.getYMin() - dy / 10,
                               lin.getYMax() + dy / 10);
}

void MainWindow::drawDots() {
    ui->field->graph(DOTS)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->field->graph(DOTS)->setLineStyle(QCPGraph::lsNone);
    ui->field->graph(DOTS)->setPen(QPen(Qt::black));
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
    if (ui->groupBox->isEnabled()) {
        drawDots();
        double res = 0.01;
        double d = fabs(lin.getXMin() - lin.getXMax());

        auto dres = (int) (d / res) + 1;
        auto *x = new double[dres];
        auto *y = new double[dres];

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
            auto *xbez = new double[size];
            auto *ybez = new double[size];
            int pl = 0;
            for (int j = 0; j < bez.size(); ++j) {
                for (int i = 0; i < resBez; i++, pl++) {
                    Point p;
                    bez.calculatePointOnSegment(j, (double) i / (double) resBez, p);
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

void MainWindow::showColorPicker(QWidget *pWidget, QWidget *pQWidget, QCPGraph *pGraph) {
    QColor color = QColorDialog::getColor();
    if (color == nullptr) return;
    QString style = "background: " + color.name() + "; border: 1px solid grey;";

    QRect pWidGeom = pWidget->geometry();
    QRect pQWidGeom = pQWidget->geometry();
    QWidget *parWidget = pQWidget->parentWidget();

    pWidget = new QWidget(ui->colors);
    pWidget->setGeometry(pWidGeom);
    pWidget->setStyleSheet(style);

    pQWidget = new QWidget(parWidget);
    pQWidget->setGeometry(pQWidGeom);
    pQWidget->setStyleSheet(style);

    QPen pen = pGraph->pen();
    pen.setColor(color);
    pGraph->setPen(pen);

    ui->field->replot();
    pWidget->show();
    pQWidget->show();
}

void MainWindow::changePenStyle(QCPGraph *pGraph, int arg1) {
    QPen pen = pGraph->pen();
    QPen qpen(pen.color(), pen.width());

    switch (arg1 + 1) {
        default:
        case Qt::SolidLine:
            qpen.setStyle(Qt::SolidLine);
            break;
        case Qt::DashLine:
            qpen.setStyle(Qt::DashLine);
            break;
        case Qt::DotLine:
            qpen.setStyle(Qt::DotLine);
            break;
        case Qt::DashDotLine:
            qpen.setStyle(Qt::DashDotLine);
            break;
        case Qt::DashDotDotLine:
            qpen.setStyle(Qt::DashDotDotLine);
            break;
    }

    pGraph->setPen(qpen);
    ui->field->replot();
}

void MainWindow::changePenThickness(QCPGraph *pGraph, QSpinBox *spinBox) {
    QPen pen = pGraph->pen();
    pen.setWidth(spinBox->value());
    pGraph->setPen(pen);
    ui->field->replot();
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
    xDots->resize(n);
    yDots->resize(n);
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

void MainWindow::on_check_lin_stateChanged(int arg1) {
    ui->field->graph(LINEAR)->setVisible(arg1);
    ui->field->replot();
}

void MainWindow::on_check_cub_stateChanged(int arg1) {
    ui->field->graph(CUBIC)->setVisible(arg1);
    ui->field->replot();
}

void MainWindow::on_check_bez_stateChanged(int arg1) {
    ui->field->graph(BEZIER)->setVisible(arg1);
    ui->field->replot();
}

void MainWindow::on_check_lag_stateChanged(int arg1) {
    ui->field->graph(LAGRANJ)->setVisible(arg1);
    ui->field->replot();
}

void MainWindow::on_actionOpen_triggered() {
    ui->groupBox->setEnabled(false);
    ui->calc->setEnabled(false);
    ui->toolBox->setEnabled(false);
    QString f = QFileDialog::getOpenFileName(
            this,
            tr("Open File"), "",
            "All Files (*.*);;Text File (*.txt)");
    QByteArray ba = f.toLatin1();
    this->fileName = ba.data();
    if (strcmp(fileName, "") != 0) {
        clearArrays();
        fillArrays();
        createObjects();
        focus();
        ui->calc->setEnabled(true);
        ui->toolBox->setEnabled(true);
        ui->groupBox->setEnabled(true);
        ui->spin->setMaximum(lin.getXMax());
        ui->spin->setMinimum(lin.getXMin());
        if (!graphCreated) createGraphs();
        calc();
    }
}

void MainWindow::on_actionSave_Plot_triggered() {
    QString f = QFileDialog::getSaveFileName(
            this,
            tr("Save File"), "",
            "JPG File (*.jpg);;BMP file (*.bmp);;PNG File(*.png)"
    );

    if (f.count() > 0) {
        if (f.contains(".jpg"))
            ui->field->saveJpg(f);
        else if (f.contains(".bmp"))
            ui->field->saveBmp(f);
        else if (f.contains(".png"))
            ui->field->savePng(f);
        else
            ui->field->saveJpg(f + ".jpg");
    }
}

void MainWindow::on_spin_editingFinished() {
    if (ui->calc->isEnabled()) {
        double c = ui->spin->value();
        QString str;
        str = "Linear: " + QString::number(lin.calculate(c)) +
              "\nCubic: " + QString::number(cs.calculate(c)) +
              "\nLagranj: " + QString::number(lp.calculate(c)) + "\n";
        ui->calculated->setPlainText(str);
    }
}

void MainWindow::on_lin_col_choose_clicked() {
    showColorPicker(ui->lin_color, ui->lin_col_tb, ui->field->graph(LINEAR));
}

void MainWindow::on_cub_col_choose_clicked() {
    showColorPicker(ui->cub_color, ui->cub_col_tb, ui->field->graph(CUBIC));
}

void MainWindow::on_lag_col_choose_clicked() {
    showColorPicker(ui->lag_color, ui->lag_col_tb, ui->field->graph(LAGRANJ));
}

void MainWindow::on_bez_col_choose_clicked() {
    showColorPicker(ui->bez_color, ui->bez_col_tb, ui->field->graph(BEZIER));
}

void MainWindow::on_lin_style_tb_activated(int arg1) {
    changePenStyle(ui->field->graph(LINEAR), arg1);
}

void MainWindow::on_cub_style_tb_activated(int arg1) {
    changePenStyle(ui->field->graph(CUBIC), arg1);
}

void MainWindow::on_lag_style_tb_activated(int arg1) {
    changePenStyle(ui->field->graph(LAGRANJ), arg1);
}

void MainWindow::on_bez_style_tb_activated(int arg1) {
    changePenStyle(ui->field->graph(BEZIER), arg1);
}

void MainWindow::on_lin_thick_tb_editingFinished() {
    changePenThickness(ui->field->graph(LINEAR), ui->lin_thick_tb);
}

void MainWindow::on_cub_thick_tb_editingFinished() {
    changePenThickness(ui->field->graph(CUBIC), ui->cub_thick_tb);
}

void MainWindow::on_lag_thick_tb_editingFinished() {
    changePenThickness(ui->field->graph(LAGRANJ), ui->lag_thick_tb);
}

void MainWindow::on_bez_thick_tb_editingFinished() {
    changePenThickness(ui->field->graph(BEZIER), ui->bez_thick_tb);
}