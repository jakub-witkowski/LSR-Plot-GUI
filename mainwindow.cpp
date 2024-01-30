#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>

#include <QFileDialog>

#include "tdata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "~/",
                                                    "Comma-Separated Value files (*.csv)");

    dataset = new TData(filename.toStdString());
    dataset->load_input();
    dataset->display_raw_data();
}
