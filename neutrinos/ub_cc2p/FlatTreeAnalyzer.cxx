#define FlatTreeAnalyzer_cxx
#include "FlatTreeAnalyzer.h"

#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGraph.h>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

vector<double> ArrayNBinsDeltaPT = {0,0.1,0.2,0.3,0.4,0.5,0.6,1.0};
int NBinsDeltaPT = ArrayNBinsDeltaPT.size()-1;

vector<double> ArrayNBinsCosThetaMuSumP = {-1,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1};
int NBinsCosThetaMuSumP = ArrayNBinsCosThetaMuSumP.size()-1;

vector<double> ArrayNBinsCosThetaPLPR = {-1,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1};
int NBinsCosThetaPLPR = ArrayNBinsCosThetaPLPR.size()-1;

//----------------------------------------//

void FlatTreeAnalyzer::Loop() {

	//----------------------------------------//	

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	double Units = 1E38; // so that the extracted cross-section is in 10^{-38} cm^{2}
	double A = 40.; // so that we can have xsecs per nucleus

	int NInte = 6; // Interaction processes: All, QE, MEC, RES, DIS, COH
	std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS","COH"};

	//----------------------------------------//	

    // Output root files

	TString FileNameAndPath = "ub_cc2p_mc_files/FlatTreeAnalyzerOutput_"+fOutputFile+".root";
	TFile* file = new TFile(FileNameAndPath,"recreate");

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;
	std::cout << "File " << FileNameAndPath << " to be created" << std::endl << std::endl;
	
	//----------------------------------------//

	// 1D Nominal Binning

	TH1D* TrueDeltaPTPlot[NInte];
	TH1D* TrueDeltaAlphaTPlot[NInte];
	TH1D* TrueDeltaPhiTPlot[NInte];
	TH1D* TrueCosThetaMuSumPPlot[NInte];
	TH1D* TrueCosThetaPLPRPlot[NInte];				

	//----------------------------------------//

	// Loop over the interaction processes
	//for (int inte = 0; inte < NInte; inte++) {
	for (int inte = 0; inte < 1; inte++) {

	  //--------------------------------------------------//

	  // 1D Nominal Binning

	  TrueDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPTPlot",";",NBinsDeltaPT,&ArrayNBinsDeltaPT[0]);	
	  TrueCosThetaMuSumPPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCosThetaMuSumPPlot",";",NBinsCosThetaMuSumP,&ArrayNBinsCosThetaMuSumP[0]);
	  TrueCosThetaPLPRPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueCosThetaPLPRPlot",";",NBinsCosThetaPLPR,&ArrayNBinsCosThetaPLPR[0]);

	  //--------------------------------------------------//

	} // End of the loop over the interaction processes							

	//----------------------------------------//

	// Counters

	int CounterEventsPassedSelection = 0;

	//----------------------------------------//
	
	// Loop over the events
	cout << "nentries = " << nentries << endl;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

	  //----------------------------------------//	
	
	  Long64_t ientry = LoadTree(jentry);
	  if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;
	  if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

	  //----------------------------------------//				

	  double weight = fScaleFactor*Units*A*Weight;	

	  //----------------------------------------//	

	  // Signal definition

	  if (PDGLep != 13) { continue; } // make sure that we have only a muon in the final state

	  int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, MuonTagging = 0, TrueHeavierMesonCounter = 0;
	  int ElectronTagging = 0, PhotonTagging = 0;
	  vector <int> ProtonID; ProtonID.clear();
	  vector <int> MuonID; MuonID.clear();		

	  //----------------------------------------//	

	  // Loop over the final state particles / post FSI

	  for (int i = 0; i < nfsp; i++) {
		
	    double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
	  
            if (pdg[i] == 13 && (pf > 0.1 && pf < 1.2) ) {

			MuonTagging ++;
			MuonID.push_back(i);

	    }

	    if (pdg[i] == 2212 && (pf > 0.3 && pf < 1.) ) {

	      ProtonTagging ++;
	      ProtonID.push_back(i);

	      double eff_mass = TMath::Sqrt(E[i]*E[i] - pf*pf);

	    }

	    if (fabs(pdg[i]) == 211 && pf > 0.065)  {

	      ChargedPionTagging ++;

	    }

	    if (pdg[i] == 111)  {

	      NeutralPionTagging ++;

	    }

	  } // End of the loop over the final state particles / post FSI

	  //----------------------------------------//	

	  // Classify the events based on the interaction type

	  // https://arxiv.org/pdf/2106.15809.pdf

	  int genie_mode = -1.;

	  if (fOutputFile ==  "ACHILLES") {

	    genie_mode = 1; // ACHILLES has only QE for now

	  } else {

	    if (TMath::Abs(Mode) == 1) { genie_mode = 1; } // QE
	    else if (TMath::Abs(Mode) == 2) { genie_mode = 2; } // MEC
	    else if (
		   TMath::Abs(Mode) == 10 ||
		   TMath::Abs(Mode) == 11 || TMath::Abs(Mode) == 12 || TMath::Abs(Mode) == 13 ||
		   TMath::Abs(Mode) == 17 || TMath::Abs(Mode) == 22 || TMath::Abs(Mode) == 23
		   ) { genie_mode = 3; } // RES
	    else if (TMath::Abs(Mode) == 21 || TMath::Abs(Mode) == 26) { genie_mode = 4; } // DIS
	    else if (TMath::Abs(Mode) == 16) { genie_mode = 5;} // COH
	    else { continue; }  

	  }

	  // Feb 8 2022: Only case that is not covered is 15 = diffractive

	  //----------------------------------------//	

	  // If the signal definition post-FSI  is satisfied
	  if ( ProtonTagging == 2 && ChargedPionTagging == 0 
		&& NeutralPionTagging == 0 && MuonTagging == 1) { 

	    CounterEventsPassedSelection++;

	    // Kinematics of muon & proton in the final state

	    TLorentzVector Muon4Vector(px[MuonID[0]], py[MuonID[0]], pz[MuonID[0]], E[MuonID[0]]);
	    TLorentzVector PLProton4Vector(px[ProtonID[0]], py[ProtonID[0]], pz[ProtonID[0]], E[ProtonID[0]]);
	    TLorentzVector PRProton4Vector(px[ProtonID[1]], py[ProtonID[1]], pz[ProtonID[1]], E[ProtonID[1]]);		
	    TLorentzVector proton_sum = PLProton4Vector + PRProton4Vector;

		TVector3 muon_v = Muon4Vector.Vect();
		TVector3 pl_proton = PLProton4Vector.Vect();
		TVector3 pr_proton = PRProton4Vector.Vect();		
		TVector3 protomn_sum_v = proton_sum.Vect();

		double muon_mag = muon_v.Mag();
		double pl_proton_mag = pl_proton.Mag();
		double pr_proton_mag = pr_proton.Mag();	
		double protomn_sum_mag = protomn_sum_v.Mag();

	    //----------------------------------------//

	    // Variables of interest

	    double DeltaPT = proton_sum.Pt();
		double costheta_mu_sump =  muon_v.Dot(protomn_sum_v) / muon_mag / protomn_sum_mag;
		double costheta_pl_pr =  pl_proton.Dot(pr_proton) / pl_proton_mag / pr_proton_mag;		
	   
	    //----------------------------------------//	

	    // overflow
        if (DeltaPT > ArrayNBinsDeltaPT[NBinsDeltaPT]) { 

			DeltaPT = (ArrayNBinsDeltaPT[NBinsDeltaPT] + ArrayNBinsDeltaPT[NBinsDeltaPT-1])/2.; 

		}

	    //----------------------------------------//	

	    TrueDeltaPTPlot[0]->Fill(DeltaPT,weight);	
	    TrueCosThetaMuSumPPlot[0]->Fill(costheta_mu_sump,weight);
	    TrueCosThetaPLPRPlot[0]->Fill(costheta_pl_pr,weight);										

	  } // End of the post-FSI selection

	  //----------------------------------------//
	
	} // End of the loop over the events

	//----------------------------------------//	

	std::cout << "Percetage of events passing the selection cuts = " << 
	double(CounterEventsPassedSelection)/ double(nentries)*100. << " %" << std::endl; std::cout << std::endl;

	//----------------------------------------//		

	file->cd();
	file->Write();
	fFile->Close();

	std::cout << std::endl;
	std::cout << "File " << FileNameAndPath +" has been created" << std::endl; 
	std::cout << std::endl;

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;

	//----------------------------------------//		

} // End of the program