#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);

    ui->chart->addGraph();
    ui->chart->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    ui->chart->graph()->setLineStyle(QCPGraph::lsLine);

    ui->chart->xAxis->setLabel("X");
    ui->chart->yAxis->setLabel("Y");

    ui->chart->xAxis->setRange(-1000, 1000);
    ui->chart->yAxis->setRange(-1000, 1000);

    ui->chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

menu::~menu()
{
    delete ui;
}

void menu::on_plot_clicked()
{
    QVector<double> x = {10, 20, 30, 40, 50}, y = {1, 1, 2, 3, 5};

    ui->chart->graph(0)->setData(x, y);
    ui->chart->rescaleAxes();
    ui->chart->replot();
    ui->chart->update();

    setWindowTitle("Interactive QCustomPlot Example");
}


void menu::on_clear_clicked()
{
    ui->chart->graph(0)->data()->clear();
    ui->chart->replot();
    ui->chart->update();
}

