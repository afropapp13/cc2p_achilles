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

	double Units = 1E39; // so that the extracted cross-section is in 10^{-38} cm^{2}
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

	TH1D* TrueMuonCosThetaPlot[NInte];
	TH1D* TrueMuonProtonCosThetaPlot[NInte];
	TH1D* TrueDeltaPTPlot[NInte];
	TH1D* TrueDeltaAlphaTPlot[NInte];

	std::vector<double> cos_mu_bins = {-1, 0.1516, 0.5282, 0.7320, 0.8446, 0.9122, 0.9518, 0.9780, 1.0};
	std::vector<double> cos_p_bins = {-1, -0.5806, -0.3628, -0.1926, -0.0424, 0.0814, 0.2018, 0.3286, 0.4878, 0.7016, 1.0};
	std::vector<double> delta_pt_bins = {0.0, 0.0800, 0.1700, 0.2500, 0.3500, 0.5500,0.8000};
	std::vector<double> delta_alphat_bins = {0., 25, 60, 100, 130, 160, 180};

	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

		TrueMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaPlot",";cos#theta_{#mu}",cos_mu_bins.size()-1,&cos_mu_bins[0]);
		TrueMuonProtonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonProtonCosThetaPlot",";cos#theta_{p}",cos_p_bins.size()-1,&cos_p_bins[0]);
		TrueDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPTPlot",";#deltp_{T}",delta_pt_bins.size()-1,&delta_pt_bins[0]);
		TrueDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaAlphaTPlot",";#delt#alpha_{T}",delta_alphat_bins.size()-1,&delta_alphat_bins[0]);            

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

		if ( !ICARUS_1muNp0pi_IsSignal ) { continue; }
		CounterEventsPassedSelection++;
	  
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
		
		// do we need undeflow/overflow bins / treatment?

		//----------------------------------------//

		TrueMuonCosThetaPlot[0]->Fill(ICARUS_1muNp0pi_MuonCos,weight);
		TrueMuonProtonCosThetaPlot[0]->Fill(ICARUS_1muNp0pi_MuonProtonCos,weight);       
		TrueDeltaPTPlot[0]->Fill(ICARUS_1muNp0pi_deltaPT,weight);
		TrueDeltaAlphaTPlot[0]->Fill(ICARUS_1muNp0pi_deltaalphaT,weight);       
		
		TrueMuonCosThetaPlot[genie_mode]->Fill(ICARUS_1muNp0pi_MuonCos,weight);
		TrueMuonProtonCosThetaPlot[genie_mode]->Fill(ICARUS_1muNp0pi_MuonProtonCos,weight);       
		TrueDeltaPTPlot[genie_mode]->Fill(ICARUS_1muNp0pi_deltaPT,weight);
		TrueDeltaAlphaTPlot[genie_mode]->Fill(ICARUS_1muNp0pi_deltaalphaT,weight);           

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

	  Reweight(TrueMuonCosThetaPlot[inte]);
	  Reweight(TrueMuonProtonCosThetaPlot[inte]);
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