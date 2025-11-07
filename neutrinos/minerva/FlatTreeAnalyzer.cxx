#define FlatTreeAnalyzer_cxx
#include "FlatTreeAnalyzer.h"

#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

//Function to divide by the bin width and to get xsecs
void Reweight(TH1D* h);

//----------------------------------------//

void FlatTreeAnalyzer::Loop() {

	//----------------------------------------//	

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	double Units = 1E39; // so that the extracted cross-section is in 10^{-39} cm^{2}
	double A = 1.; // so that we can have xsecs per nucleon

	int NInte = 6; // Interaction processes: All, QE, MEC, RES, DIS, COH
	std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS","COH"};

	//----------------------------------------//	

        // Output file

	TString FileNameAndPath = "mc_output_files/FlatTreeAnalyzerOutput_"+fOutputFile+".root";
	TFile* file = new TFile(FileNameAndPath,"recreate");

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;
	std::cout << "File " << FileNameAndPath << " to be created" << std::endl << std::endl;
	
	//----------------------------------------//

	// Plot declaration

  TH1D* TrueDeltaPTPlot[NInte];
  TH1D* TrueDeltaAlphaTPlot[NInte];
  TH1D* TrueDeltaPhiTPlot[NInte];

  std::vector<double> dpt_bins = {-0.001, 0, 0.025, 0.05, 0.075, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25, 0.275, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.8, 1, 1.2, 2, 2.02};
  std::vector<double> dalphat_bins = {-0.1, 0, 20, 40, 60, 80, 100, 120, 130, 140, 150, 160, 170, 180};
  std::vector<double> dphit_bins = {-0.1, 0, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 22.5, 25, 27.5, 30, 35, 40, 45, 50, 55, 60, 70, 85, 105, 130, 180};

	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

          TrueDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPTPlot",";#deltap_{T}",dpt_bins.size()-1,dpt_bins.data());
          TrueDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaAlphaTPlot",";DeltaAlphaT",dalphat_bins.size()-1,dalphat_bins.data());
          TrueDeltaPhiTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPhiTPlot",";DeltaPhiT",dphit_bins.size()-1,dphit_bins.data());

  } // End of the loop over the interaction processes							

	//----------------------------------------//

	// Counters

	int CounterEventsPassedSelection = 0;
	int CounterQEEventsPassedSelection = 0;
	int CounterMECEventsPassedSelection = 0;
	int CounterRESEventsPassedSelection = 0;
	int CounterDISEventsPassedSelection = 0;
	int CounterCOHEventsPassedSelection = 0;	

	//----------------------------------------//

  // Hard-code the cuts
  double MuonMinCut = 1.50; // GeV
  double MuonMaxCut = 10.0; // GeV
  double MuonThetaCut = 20; // degrees  
  double ProtonMinCut = 0.450; // GeV
  double ProtonMaxCut = 1.200; // GeV
  double ProtonThetaCut = 70; // degrees  

	//----------------------------------------//
	
	// Loop over the events

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
	  if (cc != 1) { continue; } // make sure that we have only CC interactions		

	  int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, MuonTagging = 0, ProtonTaggingTKI = 0;
    int ElectronTagging = 0, PhotonTagging = 0;

    double Pp = 0.;  
    TVector3 P3Vector(0,0,0);
    TVector3 Muon3Vector(0,0,0);

	  // Loop over final state particles

	  for (int i = 0; i < nfsp; i++) {
		
      TVector3 pf_v(px[i],py[i],pz[i]);
	    double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
      double theta = TMath::ACos(pf_v.CosTheta()) * 180./TMath::Pi();

	    if (pdg[i] == 13 && theta < MuonThetaCut  && pf > MuonMinCut && pf < MuonMaxCut) {

	      MuonTagging++;
        Muon3Vector = pf_v;

	    }

	    if (pdg[i] == 2212 && pf > ProtonMinCut && pf < ProtonMaxCut && theta < ProtonThetaCut) {

	      ProtonTagging ++;

        if (pf > Pp) { 
          
          Pp = pf;
          P3Vector = pf_v;
        
        }      

	    }

	    if (fabs(pdg[i]) == 211)  {

	      ChargedPionTagging++;

	    }

	    if (pdg[i] == 111)  {

	      NeutralPionTagging++;

	    }

	  } // End of the loop over the final state particles

	  // If the signal definition is not satisfied, continue

    if ( !(ChargedPionTagging == 0 && NeutralPionTagging == 0 && MuonTagging == 1 && ProtonTagging > 0) ) { continue; }
    CounterEventsPassedSelection++;

	  //----------------------------------------//	

	  // Classify the events based on the interaction type

	  int genie_mode = -1.;
	  if (TMath::Abs(Mode) == 1) { CounterQEEventsPassedSelection++; genie_mode = 1; } // QE
	  else if (TMath::Abs(Mode) == 2) { CounterMECEventsPassedSelection++; genie_mode = 2; } // MEC
	  else if (
		   TMath::Abs(Mode) == 10 ||
		   TMath::Abs(Mode) == 11 || TMath::Abs(Mode) == 12 || TMath::Abs(Mode) == 13 ||
		   TMath::Abs(Mode) == 17 || TMath::Abs(Mode) == 22 || TMath::Abs(Mode) == 23
	  	   ) { CounterRESEventsPassedSelection++; genie_mode = 3; } // RES
	  else if (TMath::Abs(Mode) == 21 || TMath::Abs(Mode) == 26) { CounterDISEventsPassedSelection++; genie_mode = 4; } // DIS
	  else if (TMath::Abs(Mode) == 16) { CounterCOHEventsPassedSelection++; genie_mode = 5;} // COH
	  else { genie_mode = 3; }  
    
    //----------------------------------------//           

    TVector3 MuonVectorTrans;
    MuonVectorTrans.SetXYZ(Muon3Vector.X(),Muon3Vector.Y(),0.);
    double MuonVectorTransMag = MuonVectorTrans.Mag();

    TVector3 ProtonVectorTrans;
    ProtonVectorTrans.SetXYZ(P3Vector.X(),P3Vector.Y(),0.);
    double ProtonVectorTransMag = ProtonVectorTrans.Mag();

    TVector3 PtVector = MuonVectorTrans + ProtonVectorTrans;
    double Pt = PtVector.Mag();

    double DeltaAlphaT = TMath::ACos( (- MuonVectorTrans * PtVector) / ( MuonVectorTransMag * Pt ) ) * 180./TMath::Pi();
    double DeltaPhiT = TMath::ACos( (- MuonVectorTrans * ProtonVectorTrans) / ( MuonVectorTransMag * ProtonVectorTransMag ) ) * 180./TMath::Pi();

    TrueDeltaPTPlot[0]->Fill(Pt,weight);
    TrueDeltaPTPlot[genie_mode]->Fill(Pt,weight);
    TrueDeltaAlphaTPlot[0]->Fill(DeltaAlphaT,weight);
    TrueDeltaAlphaTPlot[genie_mode]->Fill(DeltaAlphaT,weight);
    TrueDeltaPhiTPlot[0]->Fill(DeltaPhiT,weight);
    TrueDeltaPhiTPlot[genie_mode]->Fill(DeltaPhiT,weight);

	  //----------------------------------------//
	
	} // End of the loop over the events

	//----------------------------------------//	

	std::cout << "Percetage of events passing the selection cuts = " << 
	double(CounterEventsPassedSelection)/ double(nentries)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting QE events = " << 
	double(CounterQEEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting MEC events = " << 
	double(CounterMECEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting RES events = " << 
	double(CounterRESEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting DIS events = " << 
	double(CounterDISEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;

	std::cout << "Success percetage in selecting COH events = " << 
	double(CounterCOHEventsPassedSelection)/ double(CounterEventsPassedSelection)*100. << " %" << std::endl; std::cout << std::endl;	

	//----------------------------------------//	

	// Division by bin width to get the cross sections	
	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

    Reweight(TrueDeltaPhiTPlot[inte]);
    Reweight(TrueDeltaPTPlot[inte]);
    Reweight(TrueDeltaAlphaTPlot[inte]);

	} // End of the loop over the interaction processes		

	file->cd();
	file->Write();
	fFile->Close();

	std::cout << std::endl;
	std::cout << "File " << FileNameAndPath +" has been created created " << std::endl; 
	std::cout << std::endl;

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;

	//----------------------------------------//		

} // End of the program

//----------------------------------------//		

void Reweight(TH1D* h) {

  int NBins = h->GetXaxis()->GetNbins();

  for (int i = 0; i < NBins; i++) {

    double CurrentEntry = h->GetBinContent(i+1);
    double NewEntry = CurrentEntry / h->GetBinWidth(i+1);

    double CurrentError = h->GetBinError(i+1);
    double NewError = CurrentError / h->GetBinWidth(i+1);

    h->SetBinContent(i+1,NewEntry); 
    h->SetBinError(i+1,NewError); 
    //h->SetBinError(i+1,0.000001); 

  }

}