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

#include "helper_functions.cxx"

using namespace std;

//---------------------------//

void store_achilles_xsec() {

  //---------------------------//

  // I/O files

  TFile *f = new TFile("achilles_mc_electrons_2p.root" ,"recreate");
  ifstream input("test_FG_961_37p00_2_an1_jtot_formatted.out");

  //---------------------------//

  // variables & vectors

  double xsec_sum = 0.;
  double tot_xsec = 0.; // mbarns, so needs convertion to μbarns
  int number_of_lines = 0;  
  string line;

  vector<double> xsec;

  vector<double> init_lepton_energy;
  vector<double> final_lepton_energy;  

  vector<double> init_lead_nucleon_energy;
  vector<double> final_lead_nucleon_energy;   

  vector<double> init_recoil_nucleon_energy;
  vector<double> final_recoil_nucleon_energy;  

  //---------------------------//  

  // loop over the file

  while ( std::getline(input, line) ) { 

//if (number_of_lines > 23) {break;}

    //---------------------------//

    ++number_of_lines; 
    vector<string> words = split (line," ");

    //---------------------------//    

    // first line is the total xsec

    if (number_of_lines == 1) { 
      
      tot_xsec = strtod(words[0].c_str(),NULL); 
      //cout << "tot_xsec = " << tot_xsec << endl;
    
    } 

    //---------------------------//

    // then we have blocks of seven

    // 1st line in block is incoming probe 

    if ( number_of_lines == 2 || (number_of_lines > 7 && is_integer((number_of_lines-2)/7.) ) ) {

      init_lepton_energy.push_back( strtod(words[0].c_str(),NULL)/1e3 ); //GeV
      //cout << "line # = " << number_of_lines << " init_lepton_energy = " << init_lepton_energy.back() << endl;

    }

    //---------------------------//  
 
    if ( number_of_lines == 3 || (number_of_lines > 7 && is_integer((number_of_lines-3)/7.) ) ) {

      final_lepton_energy.push_back( strtod(words[0].c_str(),NULL)/1e3 ); //GeV
      //cout << "line # = " << number_of_lines << " final_lepton_energy = " << final_lepton_energy.back() << endl;

    }    
    
    //---------------------------//      

    if ( number_of_lines == 4 || (number_of_lines > 7 && is_integer((number_of_lines-4)/7.) ) ) {

      init_lead_nucleon_energy.push_back( strtod(words[0].c_str(),NULL)/1e3 ); //GeV
      //cout << "line # = " << number_of_lines << " init_lead_nucleon_energy = " << init_lead_nucleon_energy.back() << endl;

    }  

    //---------------------------//  

    if ( number_of_lines == 5 || (number_of_lines > 7 && is_integer((number_of_lines-5)/7.) ) ) {

      final_lead_nucleon_energy.push_back( strtod(words[0].c_str(),NULL)/1e3 ); //GeV
      //cout << "line # = " << number_of_lines << " final_lead_nucleon_energy = " << final_lead_nucleon_energy.back() << endl;

    }  

    //---------------------------//  

    if ( number_of_lines == 6 || (number_of_lines > 7 && is_integer((number_of_lines-6)/7.) ) ) {

      init_recoil_nucleon_energy.push_back( strtod(words[0].c_str(),NULL)/1e3 ); //GeV
      //cout << "line # = " << number_of_lines << " init_recoil_nucleon_energy = " << init_recoil_nucleon_energy.back() << endl;

    }  

    //---------------------------//  
 
    if ( number_of_lines == 7 || (number_of_lines > 7 && is_integer((number_of_lines-7)/7.) ) ) {

      final_recoil_nucleon_energy.push_back( strtod(words[0].c_str(),NULL)/1e3 ); //GeV
      //cout << "line # = " << number_of_lines << " final_recoil_nucleon_energy = " << final_recoil_nucleon_energy.back() << endl;

    }      
    
    //---------------------------// 

    if ( number_of_lines == 8 || (number_of_lines > 7 && is_integer((number_of_lines-8)/7.) ) ) {

      xsec_sum += strtod(words[0].c_str(),NULL);
      xsec.push_back( strtod(words[0].c_str(),NULL) / (1e6) ); // MeV -> GeV, mb->μb
      //cout << "line # = " << number_of_lines << " xsec = " << xsec.back() << endl;

    }      
    
    //---------------------------//     

  }

  std::cout << "Number of lines in text file: " << number_of_lines << endl;

  //---------------------------//

  int nbins = xsec.size();
  cout << "nbins = " << nbins << endl;
  vector<double> omega; omega.resize(nbins);
  vector<double> diff_xsec; diff_xsec.resize(nbins);    

  int hbins = 20;
  double min = 0.; double max = 0.7;
  TH1D* h = new TH1D("cc2p",";energy transfer",hbins,min,max);  

  for (int i = 0; i < nbins; i++) {

    omega.at(i) = init_lepton_energy.at(i) - final_lepton_energy.at(i);
    //cout << "i bin, omega = " << omega.at(i) << endl;
    diff_xsec.at(i) = xsec.at(i) * (tot_xsec / xsec_sum) / (2*TMath::Pi());
    //cout << "i bin, xsec = " << diff_xsec.at(i) << endl << endl;    

    h->Fill(omega.at(i),diff_xsec.at(i));

  }

  // bin width division
  divide_bin_width(h);
  // per carbon nucleus ( A = 12)
  h->Scale(1/12.);
  //h->Draw();  

  f->cd();
  h->Write();
  f->Close();
 
}
