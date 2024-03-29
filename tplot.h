#ifndef TPLOT_H
#define TPLOT_H

class TSegment;

/* include ROOT classes */
#include "TGraph.h" // ROOT class enabling the creation of plots with X and Y axes and a set of points
#include "TCanvas.h" // ROOT graphics class
#include "TMultiGraph.h" // A TMultiGraph allows to manipulate a set of graphs as a single entity (from ROOT documentation)
#include "TAxis.h"

/* include STL header files */
#include <vector>

class TPlot
{
    public:
    TPlot();
    TPlot(TSegment);
    ~TPlot();
    TCanvas* cnv = new TCanvas("cnv", "LSR-Plot output", 0, 0, 1200, 800);

    void copy_ages_to_plot();
    void copy_depths_to_plot();
    void copy_fit_line_to_plot();
    void copy_lsr_plot_values_to_plot();
    void copy_smoothed_lsr_plot_values_to_plot();
    void copy_lsr_plot_ages_to_plot();
    void display_ages_vector();
    void delete_ptrs();
    void plot();
    void plot_to_png(std::string);

    void set_ages(double);
    void set_depths(double);
    void set_fit_line(double);
    void set_lsr_plot_values(double);
    void set_smoothed_lsr_plot_values(double);
    void set_lsr_plot_ages(double);

    void set_segm_ptr(TSegment*);
    void set_g1_ptr();
    void set_g2_ptr();
    void set_g3_ptr();
    void set_g4_ptr();

    size_t get_ages_vector_size();
    size_t get_lsr_ages_vector_size();
    double get_lsr_plot_age(int);

    private:
    std::vector<double> depths{};
    std::vector<double> ages{};
    std::vector<double> fit_line{};
    std::vector<double> lsr_plot_values{};
    std::vector<double> smoothed_lsr_plot_values{};
    std::vector<double> lsr_plot_ages{};

    TSegment* segm_ptr{nullptr};
    TMultiGraph* multi1 = new TMultiGraph();
    TMultiGraph* multi2 = new TMultiGraph();
    TGraph* g1{nullptr};
    TGraph* g2{nullptr};
    TGraph* g3{nullptr};
    TGraph* g4{nullptr};
};

#endif
