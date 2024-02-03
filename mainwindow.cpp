#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "tplot.h"
// #include <string>
// #include <memory>

#include <QFileDialog>

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
}

void MainWindow::on_pushButton_2_clicked()
{
    if (dataset)
        dataset->find_hiatus();
}


void MainWindow::on_pushButton_3_clicked()
{
    if (dataset)
    {
        for (int i = 0; i < dataset->get_segment_indexes_size(); i++)
        {
            segments.push_back(TSegment(dataset, dataset->get_index(i).first, dataset->get_index(i).second));
            segments[i].copy_ages_to_segment();
            segments[i].copy_depths_to_segment();
            segments[i].set_g1_ptr();
            segments[i].compute_lsr_values();
            segments[i].set_g3_ptr();
        }

        for (int i = 0; i < segments.size(); i++)
        {
            for (int j = 0; j < 10; j++)
            {
                segments[i].add_to_fit_vector(j);
            }

            segments[i].perform_fitting();
            segments[i].get_fit_line_for_plot(segments[i].find_the_best_fit(0));

            is_overfitted = segments[i].test_for_overfitting();
            int index{1};
            while (is_overfitted == true)
            {
                segments[i].clear_fit_line_vector();
                segments[i].get_fit_line_for_plot(segments[i].find_the_best_fit(index));
                index++;
                is_overfitted = segments[i].test_for_overfitting();
            }

            /* linear sedimentation rates are smoothed using the selected polynomial fit */
            segments[i].set_g2_ptr();
            segments[i].lsr_smoothing();
            segments[i].set_g4_ptr();
        }

        TApplication app("app", nullptr, nullptr);

        /* determine the number of segments and plot the results */
        if (segments.size() == 1)
        {
            plot = new TPlot(segments[0]);
            plot->display_ages_vector();
            plot->plot();
            TRootCanvas *rc = (TRootCanvas *)plot->cnv->GetCanvasImp();
            rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
            // segments[0].plot_to_png("plot.png");
        }
        else if (segments.size() > 1)
        {
            // TApplication app("app", &argc, argv);
            plot = new TPlot();

            for (int i = 0; i < segments.size(); i++)
            {
                plot->set_segm_ptr(&segments[i]);
                plot->copy_ages_to_plot();
                plot->copy_depths_to_plot();
                plot->set_g1_ptr();
                plot->copy_fit_line_to_plot();
                plot->set_g2_ptr();

                /* modifications to the data vectors to reflect hiatuses between segments */
                if (segments.size() > 1)
                    if ((i > 0) && (i <= segments.size() - 1))
                        plot->set_lsr_plot_values(0);

                plot->copy_lsr_plot_values_to_plot();

                if (segments.size() > 1)
                    if ((i >= 0) && (i < segments.size() - 1))
                        plot->set_lsr_plot_values(0);

                if (segments.size() > 1)
                    if ((i > 0) && (i <= segments.size() - 1))
                        plot->set_lsr_plot_ages(segments[i].get_lsr_plot_age(0)); // repeat first element from the segment to be copied

                plot->copy_lsr_plot_ages_to_plot();

                if (segments.size() > 1)
                    if ((i >= 0) && (i < segments.size() - 1))
                        plot->set_lsr_plot_ages(plot->get_lsr_plot_age(plot->get_lsr_ages_vector_size() - 1));

                plot->set_g3_ptr();

                if (segments.size() > 1)
                    if ((i > 0) && (i <= segments.size() - 1))
                        plot->set_smoothed_lsr_plot_values(0);

                plot->copy_smoothed_lsr_plot_values_to_plot();

                if (segments.size() > 1)
                    if ((i >= 0) && (i < segments.size() - 1))
                        plot->set_smoothed_lsr_plot_values(0);

                plot->set_g4_ptr();
            }

            // plot->plot_to_png("plot.png");
            // plot->delete_ptrs();
            plot->plot();
            TRootCanvas *rc = (TRootCanvas *)plot->cnv->GetCanvasImp();
            rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
        }

        app.Run();
    }
}

