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

    QString filtro = "Arquivos excel (*.xlsx)";
    QString abrirArquivos = QFileDialog::getOpenFileName(this, "Abrir arquivos", "C://", filtro);

    QXlsx::Document xlsx(abrirArquivos);

    QVector<QVector<QString>> data;

    for (int row = 1; row <= xlsx.dimension().rowCount(); ++row) {
        QVector<QString> rowData;
        for (int col = 1; col <= 2; ++col) {
            rowData.append(xlsx.read(row, col).toString());
        }
        data.append(rowData);
    }

    QVector<double> x, y;
    for (int i = 0; i < data.size(); ++i) {
        QVariant x_ = data[i][0];
        QVariant y_ = data[i][1];
        x.append(x_.toDouble());
        y.append(y_.toDouble());
    }

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

