#include <iostream>
#include <fstream>
#include <vector>
#include <TFile.h>
#include <TH1D.h>

int convert_flux_to_TH1D() {
    std::string filename = "corrected_flux_fhc_numu_BinWidthDivided.dat";
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<double> xvals;
    std::vector<double> yvals;

    double x, y;
    while (infile >> x >> y) {
        xvals.push_back(x);
        yvals.push_back(y);
    }
    infile.close();

    if (xvals.empty()) {
        std::cerr << "Error: no data read from file." << std::endl;
        return 1;
    }

    // Assume uniform binning — use midpoints to infer edges
    int nbins = xvals.size();
    std::vector<double> edges;
    for (int i = 0; i < nbins - 1; ++i) {
        double edge = 0.5 * (xvals[i] + xvals[i + 1]);
        edges.push_back(edge);
    }

    // Extrapolate first and last bin edges
    double first_edge = xvals.front() - 0.5 * (xvals[1] - xvals[0]);
    double last_edge  = xvals.back()  + 0.5 * (xvals.back() - xvals[nbins - 2]);
    edges.insert(edges.begin(), first_edge);
    edges.push_back(last_edge);

    TH1D* hflux = new TH1D("hflux", "Corrected FHC #nu_{#mu} Flux;E_{#nu} [GeV];Flux", nbins, &edges[0]);

    for (int i = 0; i < nbins; ++i)
        hflux->SetBinContent(i + 1, yvals[i]);

    TFile* fout = new TFile("flux_hist_numi_icarus_fhc.root", "RECREATE");
    hflux->Write();
    fout->Close();

    std::cout << "Histogram written to flux_hist_icarus_fhc.root as hflux" << std::endl;
    return 0;
}