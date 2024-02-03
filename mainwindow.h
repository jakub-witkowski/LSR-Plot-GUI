#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
// #include <QTableView>

#include "tdata.h"
#include "tsegment.h"
#include "tpolynomial.h"
#include "tplot.h"

#include "TApplication.h"
#include "TRootCanvas.h"
// #include "mymodel.h"

#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    TData* dataset{nullptr};
    std::vector<TSegment> segments{};
    bool is_overfitted{false};
    TPlot* plot{nullptr};

    // QTableView table;
    // MyModel data_for_display;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
