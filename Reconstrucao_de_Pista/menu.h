#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

#include <QVector>
#include <QVariant>

#include "qcustomplot.h"
#include "xlsxdocument.h"
#include "upload_file.h"

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

private:
    Ui::menu *ui;
    QCustomPlot* customPlot;
    QCPGraph* scatter;

};
#endif // MENU_H
