#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

#include <QVector>
#include <QVariant>
#include <QTimer>
#include <QTime>
#include <random>

#include "C:/Users/USER/Downloads/QCustomPlot.tar/QCustomPlot-/qcustomplot.h"
#include "xlsxdocument.h"

QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QMainWindow
{
    Q_OBJECT

public:
    menu(QWidget *parent = nullptr);
    ~menu();

private slots:

    void on_plot_clicked();
    void on_clear_clicked();

    void update_time();

    void on_play_clicked();
    void on_stop_clicked();
    void on_pause_clicked();

    void move_cursor(QMouseEvent *event);

    QColor generate_random_color();


    void on_x_value_currentIndexChanged(int index);

private:
    Ui::menu *ui;
    QTimer *timer;
    QTime currentTime;
    QCPItemLine *cursor;
    QCPItemLine *cursor_2;
    QVector<double> x_t, x_d;
    QVector<QVector<double>> y;
    int nrow, ncolumn;

};
#endif // MENU_H
