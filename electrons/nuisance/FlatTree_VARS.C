#define FlatTree_VARS_cxx
#include "FlatTree_VARS.h"
#include "TH1D.h"
#include "TH2D.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "../helper_functions.cxx"

void FlatTree_VARS::Loop() {

	//--------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	//--------------------//

	// output file

	TString file_name = "nuisance_output.root";
	TFile* f = new TFile(file_name,"recreate");
	std::cout << std::endl << "File " << file_name << " to be created"<< std::endl << std::endl;

	//--------------------//

   // plot declaration

   // apapadop: add y axis labels
   TH1D* energy_transfer_plot = new TH1D("energy_transfer_plot",";energy transfer [GeV];",35,0,0.7);

   //--------------------//

   double angle_cv = 37.5; // deg
   double open_angle = 1.15;

	//--------------------//

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

	//--------------------//

   // loop over the events
   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

   	//--------------------// 
      
 		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

		//--------------------//

      // electron angular cut

      double theta_lep = TMath::ACos(CosLep) * 180/TMath::Pi(); // deg
      //if ( TMath::Abs(theta_lep - angle_cv) >  open_angle) { continue; }

      //--------------------//

      double energy_transfer = Enu_true - ELep;
      energy_transfer_plot->Fill(energy_transfer);


   } // end of the loop over the events
      
   //--------------------//      

   // scaling to get xsecs

   //double tot_xsec = 16717197.; // nb/sr
   //// code issue, Noah needs to fix it
   //energy_transfer_plot->Scale(1./4.); 

   double tot_xsec = 2468007.; // nb/sr   

   divide_bin_width(energy_transfer_plot);
   energy_transfer_plot->Scale(tot_xsec / (2.*TMath::Pi() * nentries) /1e6 ); // MeV->GeV


   // opening angle correction
   //double delta_angle = TMath::Abs( cos( (angle_cv + open_angle) *TMath::Pi() / 180.) - cos( (angle_cv - open_angle) *TMath::Pi() / 180.) );
   //energy_transfer_plot->Scale(1./delta_angle);

   //--------------------//      

   f->cd();
	f->Write();
	f->Close();

} // end of the main program