#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>

//#include "helper_functions.cxx"

using namespace std;

//---------------------------//


std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

struct Event {
        // 6 lines * 5 values per line = 30 doubles total
        std::vector<double> inlep;
        std::vector<double> outlep;
        std::vector<double> inhad1;
        std::vector<double> outhad1;
        std::vector<double> inhad2;
        std::vector<double> outhad2;   // 6 lines each with 5 doubles
        double wgt;        // the single double on the 7th line
        double omega;
    };


int store_achilles_xsec() {

    //---------------------------//

    // I/O files

    TString fname = "test_FG_961_37p50";

    ifstream inFile("xsec_out_files/"+fname+".out");
    TFile *f = new TFile("../e4nu/Results_C/root/prediction_"+fname+".root" ,"recreate");
    
    //---------------------------//

    // variables & vectors

    double sum_wgts = 0.;
    double tot_xsec = 0.; //Actually already in nb/sr

    // 1) Read the very first line as a double
    if (!(inFile >> tot_xsec)) {
        std::cerr << "Unable to read the first line as a double.\n";
        return 1;
    }

    std::vector<Event> Events;

    while (true) {

        Event event;
        event.inlep.resize(5);
        event.outlep.resize(5);
        event.inhad1.resize(5);
        event.outhad1.resize(5);
        event.inhad2.resize(5);
        event.outhad2.resize(5);

        // A helper array to iterate easily
        std::vector<double>* lines[] = {
            &event.inlep, &event.outlep, &event.inhad1,
            &event.outhad1, &event.inhad2, &event.outhad2
        };

        bool readSuccess = true;
            for (int i = 0; i < 6; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (!(inFile >> (*lines[i])[j])) {
                        // If we fail to read enough values, we stop
                        readSuccess = false;
                        break;
                    }
                }
                if (!readSuccess) break;
            }
            if (!readSuccess) break;  // no more complete blocks

        // 3) Read the 7th line (single double)
        double xsec = 0.0;
        if (!(inFile >> xsec)) {
            // If we cannot read the seventh line, we stop
            break;
        }
        event.wgt = xsec;
        event.omega = (event.inlep.at(0) - event.outlep.at(0))/1000.; //convert to GeV
        sum_wgts += event.wgt;

        // Store the fully read event
        Events.push_back(event);
    }

    //---------------------------//

    int nevents = Events.size();

    int hbins = 100;
    double min = 0.; double max = 0.9;
    TH1D* h = new TH1D("prediction",";energy transfer",hbins,min,max);  

    for (int i = 0; i < nevents; i++) {

        double omega = Events.at(i).omega;
        double wgt = Events.at(i).wgt;


        h->Fill(omega,wgt);

    }

    //std::cout << "Bin width = " << h->GetBinWidth(2) << "\n";
    //std::cout << "tot xsec = " << tot_xsec << "\n";

    h->Scale(tot_xsec/(2*TMath::Pi() * sum_wgts * h->GetBinWidth(2))/1e3); // MeV->GeV 

    f->cd();
    h->Write();
    f->Close();
    return 1;
 
}

