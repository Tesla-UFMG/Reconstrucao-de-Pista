#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);


    ui->chart->xAxis->setLabel("X");
    ui->chart->yAxis->setLabel("Y");


    ui->chart->xAxis->setRange(-1000, 1000);
    ui->chart->yAxis->setRange(-1000, 1000);

    ui->chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    cursor = new QCPItemLine(ui->chart);

    cursor->setPen(QPen(Qt::red));
    cursor->start->setCoords(0, -1000);
    cursor->end->setCoords(0, 1000);

    ui->chart->setMouseTracking(true);

    connect(ui->chart, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(move_cursor(QMouseEvent*)));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_time()));
    timer->setInterval(1000);
    timer->start();
    currentTime = QTime(0, 0);
    update_time();

    ui->play->setIcon(QIcon("C:/Users/USER/Documents/reconstrucao_de_pista_funciona/icones/play.png"));
    ui->pause->setIcon(QIcon("C:/Users/USER/Documents/reconstrucao_de_pista_funciona/icones//pause.png"));
    ui->stop->setIcon(QIcon("C:/Users/USER/Documents/reconstrucao_de_pista_funciona/icones/stop.png"));

}

menu::~menu()
{
    delete ui;
}

void menu::on_plot_clicked()
{
    QString filtro = "Arquivos excel (*.xlsx)";
    QString abrirArquivos = QFileDialog::getOpenFileName(this, "Abrir arquivos", "C://Users/USER/Documents/Reconstrucao_de_Pista", filtro);

    QXlsx::Document xlsx(abrirArquivos);

    for (int row = 2; row <= xlsx.dimension().rowCount(); ++row) {

        x_t.append(xlsx.read(row, 1).toDouble());
    }
    for (int row = 2; row <= xlsx.dimension().rowCount(); ++row) {

        x_d.append(xlsx.read(row, 2).toDouble());
    }

    for (int col = 3; col <= xlsx.dimension().columnCount(); col++) {

        ui->chart->addGraph();

        ui->chart->graph(col-3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        ui->chart->graph(col-3)->setLineStyle(QCPGraph::lsLine);

        ui->chart->graph(col-3)->setPen(QPen(generate_random_color()));

        ui->chart->setInteraction(QCP::iSelectPlottables, true);

        ui->chart->graph()->setSelectable(QCP::stSingleData);
        ui->chart->graph()->setSelection(QCPDataSelection(ui->chart->graph(col-3)->data()->dataRange()));

        QVector<double> y_aux;
        for (int row = 2; row <= xlsx.dimension().rowCount(); ++row) {
            y_aux.append(xlsx.read(row, col).toDouble());
        }

        y.append(y_aux);
        ui->chart->graph(col-3)->setData(x_t, y_aux);
        ui->chart->xAxis->setLabel("time");
    }

    ui->chart->rescaleAxes();
    ui->chart->update();

    setWindowTitle("Interactive QCustomPlot Example");
}


void menu::on_clear_clicked()
{
    ui->chart->graph(0)->data()->clear();
    ui->chart->graph(1)->data()->clear();
    ui->chart->replot();
    ui->chart->update();
}

void menu::update_time()
{
    ui->showing->setText(currentTime.toString("hh:mm:ss"));
    currentTime = currentTime.addSecs(1);

}

void menu::on_play_clicked()
{
    timer->start();
}


void menu::on_stop_clicked()
{
    timer->stop();
    currentTime = QTime(0, 0);
    update_time();
}


void menu::on_pause_clicked()
{
    timer->stop();
}

void menu::move_cursor(QMouseEvent *event)
{
    double x = ui->chart->xAxis->pixelToCoord(event->pos().x());
    ui->chart->yAxis->pixelToCoord(event->pos().y());

    cursor->start->setCoords(x, ui->chart->yAxis->range().lower);
    cursor->end->setCoords(x, ui->chart->yAxis->range().upper);

    ui->chart->replot();
}

QColor menu::generate_random_color()
{
    std::random_device rd;

    std::mt19937 one(rd());
    std::uniform_int_distribution<> red(0, 255);

    std::mt19937 two(rd());
    std::uniform_int_distribution<> green(0, 255);

    std::mt19937 three(rd());
    std::uniform_int_distribution<> blue(0, 255);

    return QColor(red(one), green(two), blue(three));
}


void menu::on_x_value_currentIndexChanged(int index)
{
    if (index == 0){
        for (int i = 0; i < 2; ++i){
            ui->chart->graph(i)->setData(x_d, y[i]);
        }
        ui->chart->xAxis->setLabel("distance");
    }
    else if (index == 1){
        for (int i = 0; i < 2; ++i){
            ui->chart->graph(i)->setData(x_t, y[i]);
        }
        ui->chart->xAxis->setLabel("time");
    }

    ui->chart->rescaleAxes();
    ui->chart->replot();
}

