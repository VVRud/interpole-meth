#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "../lib/Linear.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPixmap pixmap(ui->field->width(), ui->field->height());
    pixmap.fill(QColor("white"));
    painter.begin(&pixmap);

    if (ui->check_lin->isChecked()) {
        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    } else if (ui->check_cub->isChecked()) {
        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    } else if (ui->check_ak->isChecked()) {
        painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    } else if (ui->check_bez->isChecked()) {

    } else if (ui->check_net->isChecked()) {

    } else if (ui->check_lag->isChecked()) {

    } else {

    }
    painter.drawEllipse(100, 50, 150, 150);
    painter.end();
    ui->field->setPixmap(pixmap);
}

void MainWindow::on_check_lin_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    repaint();
}

void MainWindow::on_check_cub_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    repaint();
}

void MainWindow::on_check_ak_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    repaint();
}

void MainWindow::on_check_bez_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    repaint();
}

void MainWindow::on_check_net_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    repaint();
}

void MainWindow::on_check_lag_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    repaint();
}

void MainWindow::on_actionOpen_triggered()
{
    QString f = QFileDialog::getOpenFileName(
                this,
                tr("Open File"), "",
                "All Files (*.*);;Text File (*.txt)");
    QByteArray ba = f.toLatin1();
    this->fileName = ba.data();
    createObjects();
    ui->groupBox->setEnabled(1);
}

void MainWindow::createObjects() {
    lin = Linear(fileName);
}
