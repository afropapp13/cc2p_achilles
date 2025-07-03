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
//2d helper functions
void Reweight2d(TH1D* h, std::vector< std::vector<int> > BinEdgeVector, std::vector< double> RowVector, std::vector< double> ElementVector, int dim=-1);
int Return2DNBins(std::vector< std::vector<int> > BinEdgeVector);
std::vector<double> Return2DBinIndices(std::vector< std::vector<int> > BinEdgeVector);
int Get2Dbin(double value_row, double value_element, std::vector< std::vector<int> > BinEdgeVector, std::vector< double> RowVector, std::vector< double> ElementVector);

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

	TH1D* TruePmultPlot[NInte];
        TH1D* TrueMuonCosTheta1pPlot[NInte];
        TH1D* TrueMuonCosTheta0pPlot[NInte];

        TH1D* SerialCosMuPmu0pPlot[NInte];  
        TH1D* SerialCosMuCosp1pPlot[NInte];

        TH1D* TruePp1Plot[NInte];
        TH1D* TruePp2Plot[NInte];
        TH1D* TruePp3Plot[NInte];
        TH1D* TruePp4Plot[NInte];

        TH1D* TrueCosp1Plot[NInte];
        TH1D* TrueCosp2Plot[NInte];
        TH1D* TrueCosp3Plot[NInte];
        TH1D* TrueCosp4Plot[NInte];

        TH1D* TrueDeltaPTPlot[NInte];
        TH1D* TrueDeltaAlphaTPlot[NInte];
        TH1D* TrueDeltaPhiTPlot[NInte];


        TH1D* Full[NInte];

        double TotalXs = 0;
        double TotalXs0pi = 0;
        double TotalXsTKI = 0;

std::vector<double> cosmu_0p_bins = {-1, -0.3, 0.3, 0.6, 0.7, 0.8, 0.85, 0.9, 0.94, 0.98, 1.0};
std::vector<double> pmu_0p_bins = {0.0, 0.3, 0.4, 0.5, 0.6, 0.65,0.7, 0.8, 1.0, 1.25, 1.5, 2.0, 3.0, 5.0, 30};

std::vector< std::vector< int > > cosmu_pmu_0p_2d_bins =
                  {{0,14},
                   {0,1,2,14},
                   {0,1,2,3,4,14},
                   {0,1,2,3,4,14},
                   {0,1,2,3,4, 6,7,14},
                   {0,2,3,4, 6,7,14},
                   {0,1,2,3,4, 6,7,8,14},
                   {0,2,3,4, 6,7,9,14},
                   {0,2,3,4, 6,7,8,9,10,11,14},
                   {0,3,5,7,9,11,12,13,14}};

std::vector<double> cosmu_1p_bins = {-1.0, -0.3, 0.3, 0.8, 0.1};
std::vector<double> cosp_1p_bins = {-1, 0.0, 0.3, 0.5, 0.75, 0.8, 0.85, 0.87, 0.94, 0.97, 1.0}; 

std::vector< std::vector< int > > cosmu_cosp_1p_2d_bins =
                  {{0,7,8,9,10},
                   {0,4,6,8,10},
                   {0,2,3,5,10},
                   {0,1,2,5,10}};



	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

          double pmultbins[4] = {0, 1, 2, 1000000};
          TruePmultPlot[inte] = new TH1D(InteractionLabels[inte]+"TruePmultPlot",";P mult",3,pmultbins);          

          double CosTheta1pbins[5] = {-1.,  -0.3,  0.3,  0.8,  1.};
          TrueMuonCosTheta1pPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosTheta1pPlot",";cos(#theta_{#mu})",4,CosTheta1pbins);

          double CosTheta0pbins[11] = {-1.0, -0.3, 0.3, 0.6, 0.7, 0.8, 0.85, 0.9, 0.94, 0.98, 1.0};
          TrueMuonCosTheta0pPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosTheta0pPlot",";cos(#theta_{#mu})",10,CosTheta0pbins);

          double DeltaPTbins[9] = {0, 0.0800,0.120, 0.155, 0.200, 0.260, 0.360, 0.510, 1.1};
          TrueDeltaPTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPTPlot",";DeltaPT",8,DeltaPTbins);

          double DeltaAlphaTbins[9] = {0, 0.47000, 1.0200, 1.5400, 1.9800, 2.3400, 2.6400, 2.8900, 3.1416};
          TrueDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaAlphaTPlot",";DeltaAlphaT",8,DeltaAlphaTbins);

          double DeltaPhiTbins[9] = {0, 0.067000, 0.14000, 0.22500, 0.34000, 0.52000, 0.85000, 1.5000, 3.1416};
          TrueDeltaPhiTPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueDeltaPhiTPlot",";DeltaPhiT",8,DeltaPhiTbins);

          int nbins0p = Return2DNBins(cosmu_pmu_0p_2d_bins);
          int xmin0p = 1;
          int xmax0p = nbins0p+1;
          SerialCosMuPmu0pPlot[inte] = new TH1D(InteractionLabels[inte]+"SerialCosMuPmu0pPlot","Bin Index",nbins0p,xmin0p,xmax0p);

          int nbins1p = Return2DNBins(cosmu_cosp_1p_2d_bins);
          int xmin1p = 1;
          int xmax1p = nbins1p+1;
          SerialCosMuCosp1pPlot[inte] = new TH1D(InteractionLabels[inte]+"SerialCosMuCosp1pPlot","Bin Index",nbins1p,xmin1p,xmax1p);

          double pp1bins[5] = {0.5, 0.68, 0.78, 0.9, 30};
          TruePp1Plot[inte] = new TH1D(InteractionLabels[inte]+"TruePp1Plot",";Pp",4,pp1bins);
          double pp2bins[6] = {0.5, 0.6, 0.7, 0.8, 0.9, 30};
          TruePp2Plot[inte] = new TH1D(InteractionLabels[inte]+"TruePp2Plot",";Pp",5,pp2bins);
          double pp3bins[6] = {0.5, 0.6, 0.7, 0.8, 1.0, 30};
          TruePp3Plot[inte] = new TH1D(InteractionLabels[inte]+"TruePp3Plot",";Pp",5,pp3bins);
          double pp4bins[7] = {0.5, 0.6, 0.7, 0.8, 0.9, 1.1, 30};
          TruePp4Plot[inte] = new TH1D(InteractionLabels[inte]+"TruePp4Plot",";Pp",6,pp4bins);

          double cosp1bins[5] = {-1.0, 0.87, 0.94, 0.97, 1.0};
          TrueCosp1Plot[inte] = new TH1D(InteractionLabels[inte]+"TrueCosp1Plot",";Cosp",4,cosp1bins);
          double cosp2bins[5] = {-1.0, 0.75, 0.85, 0.94, 1.0};
          TrueCosp2Plot[inte] = new TH1D(InteractionLabels[inte]+"TrueCosp2Plot",";Cosp",4,cosp2bins);
          double cosp3bins[5] = {-1.0, 0.3, 0.5, 0.8,  1.0};
          TrueCosp3Plot[inte] = new TH1D(InteractionLabels[inte]+"TrueCosp3Plot",";Cosp",4,cosp3bins);
          double cosp4bins[5] = {-1.0, 0.0, 0.3, 0.8, 1.0};
          TrueCosp4Plot[inte] = new TH1D(InteractionLabels[inte]+"TrueCosp4Plot",";Cosp",4,cosp4bins);

          Full[inte] = new TH1D(InteractionLabels[inte]+"Full",";Bin Index",122,0,122);

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
	  //if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

	  //----------------------------------------//	
		
	  double weight = fScaleFactor*Units*A*Weight;	

          double t2kweight = 1.;
          TFile* fweights_file = nullptr;
          TTree* tweights = nullptr;
          float cv_weight = -99.;

          if (fOutputFile == "ubt") {

            fweights_file = TFile::Open("/exp/uboone/app/users/bbogart/nuisance_ncpi0/BuildEventGenerators/carbon_ubt/ubt_weights.root");
            tweights->GetEntry(jentry); t2kweight = cv_weight;

          }
   
          weight *= t2kweight;


          if(fOutputFile=="GiBUU_flagInMedium") { weight=weight/60; }
          if(fOutputFile=="GiBUU") { weight=weight/55; }
          if(fOutputFile=="GiBUU_flagInMedium_MA_1p2") { weight=weight/67; }
          if(fOutputFile=="gibuu20251_inmed_ma12_soft") { weight=weight/99; }
          if(fOutputFile=="gibuu20251_inmed_soft_T0T0") { weight=weight/100; }
          if(fOutputFile=="gibuu20251_inmed_soft_T1T0") { weight=weight/100; }
          if(fOutputFile=="gibuu20251_T1T0") { weight=weight/100; }
          if(fOutputFile=="gibuu20251_inmed_soft_T0T0_noadjust") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_inmed_T0T0_noadjust") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_inmed_DS3_4") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_inmed_DS3_3") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_inmed_DS3_1") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_inmed_DS3_0") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_soft_inmed_DS3_3") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_soft_inmed_DS3_0") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_soft_inmed_DS3_00") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_soft_inmed_DS3_30") { weight=weight/60; }
          if(fOutputFile=="gibuu20251_soft_inmed_DS3_01") { weight=weight/38; }
	  //----------------------------------------//	


	  // Signal definition

	  if (PDGLep != 13) { continue; } // make sure that we have only a muon in the final state
	  if (cc != 1) { continue; } // make sure that we have only CC interactions		

          TotalXs += weight;

	  int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, MuonTagging = 0, ProtonTaggingTKI = 0;
          int ElectronTagging = 0, PhotonTagging = 0;

          TVector3 P3Vector(0,0,0);
          double Pp = 0;
          double CosP = -999;

          TVector3 Muon3Vector(0,0,0);
          double Pmu = 0;

	  vector <int> ProtonID; ProtonID.clear();
	  vector <int> MuonID; MuonID.clear();		

	  // Example selection with CC1p0pi (units in GeV/c)
	  // Loop over final state particles

	  for (int i = 0; i < nfsp; i++) {
		
	    double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);

	    if (pdg[i] == 13) {

	      MuonTagging ++;
	      MuonID.push_back(i);
              Pmu = pf;
              Muon3Vector.SetXYZ(px[i],py[i],pz[i]);

	    }

	    if (pdg[i] == 2212 && pf > 0.5 ) {

	      ProtonTagging ++;
	      ProtonID.push_back(i);

	    }
            // for TKI
            if (pdg[i] == 2212) {
              ProtonTaggingTKI++;
              if (pf > Pp) { Pp=pf; CosP=pz[i]/pf; P3Vector.SetXYZ(px[i],py[i],pz[i]);}
            }

	    if (fabs(pdg[i]) == 211)  {

	      ChargedPionTagging ++;

	    }

	    if (pdg[i] == 111)  {

	      NeutralPionTagging ++;

	    }

	    if (fabs(pdg[i]) == 11)  {

	      ElectronTagging ++;

	    }

	    if (fabs(pdg[i]) == 22)  {

	      PhotonTagging ++;

	    }


	  } // End of the loop over the final state particles

	  // If the signal definition is not satisfied, continue

         bool flag_0pi = false;
         bool flag_tki = false;
	  if (ChargedPionTagging == 0 && NeutralPionTagging == 0 && MuonTagging ==1) { flag_0pi=true; }
          if (ChargedPionTagging == 0 && NeutralPionTagging == 0 && MuonTagging == 1 && Pmu>0.25 && CosLep>-0.6 && Pp>0.45 && Pp<1 && CosP>0.4) { flag_tki=true; }

	  //----------------------------------------//	

	
	  // Classify the events based on the interaction type

	  int genie_mode = -1.;
          if(flag_0pi){
            TotalXs0pi+=weight;
            CounterEventsPassedSelection++;
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
          }
	  //----------------------------------------//


          if(flag_0pi){
	    TruePmultPlot[0]->Fill(ProtonTagging,weight);
	    TruePmultPlot[genie_mode]->Fill(ProtonTagging,weight);
            if(ProtonTagging==1){
              TrueMuonCosTheta1pPlot[0]->Fill(CosLep,weight);
              TrueMuonCosTheta1pPlot[genie_mode]->Fill(CosLep,weight);
              if(CosLep>-0.3 && CosLep<0.3 && CosP>0.85 && CosP<0.94){
                TruePp1Plot[0]->Fill(Pp,weight);
                TruePp1Plot[genie_mode]->Fill(Pp,weight);
              }
              if(CosLep>0.3 && CosLep<0.8 && CosP>0.5 && CosP<0.8){
                TruePp2Plot[0]->Fill(Pp,weight);
                TruePp2Plot[genie_mode]->Fill(Pp,weight);
              }
              if(CosLep>0.3 && CosLep<0.8 && CosP>0.8){
                TruePp3Plot[0]->Fill(Pp,weight);
                TruePp3Plot[genie_mode]->Fill(Pp,weight);
              }
              if(CosLep>0.8 && CosP>0.3 && CosP<0.8){
                TruePp4Plot[0]->Fill(Pp,weight);
                TruePp4Plot[genie_mode]->Fill(Pp,weight);
              }
              if(CosLep>-1 && CosLep<-0.3){
                TrueCosp1Plot[0]->Fill(CosP,weight);
                TrueCosp1Plot[genie_mode]->Fill(CosP,weight);
              }
              if(CosLep>-0.3 && CosLep<0.3){
                TrueCosp2Plot[0]->Fill(CosP,weight);
                TrueCosp2Plot[genie_mode]->Fill(CosP,weight);
              }
              if(CosLep>0.3 && CosLep<0.8){
                TrueCosp3Plot[0]->Fill(CosP,weight);
                TrueCosp3Plot[genie_mode]->Fill(CosP,weight);
              }
              if(CosLep>0.8){
                TrueCosp4Plot[0]->Fill(CosP,weight);
                TrueCosp4Plot[genie_mode]->Fill(CosP,weight);
              }
              SerialCosMuCosp1pPlot[0]->Fill(Get2Dbin(CosLep,CosP,cosmu_cosp_1p_2d_bins,cosmu_1p_bins,cosp_1p_bins),weight);
              SerialCosMuCosp1pPlot[genie_mode]->Fill(Get2Dbin(CosLep,CosP,cosmu_cosp_1p_2d_bins,cosmu_1p_bins,cosp_1p_bins),weight);
            }
            if(ProtonTagging==0){
              TrueMuonCosTheta0pPlot[0]->Fill(CosLep,weight);
              TrueMuonCosTheta0pPlot[genie_mode]->Fill(CosLep,weight);
              SerialCosMuPmu0pPlot[0]->Fill(Get2Dbin(CosLep,Pmu,cosmu_pmu_0p_2d_bins,cosmu_0p_bins,pmu_0p_bins),weight);
              SerialCosMuPmu0pPlot[genie_mode]->Fill(Get2Dbin(CosLep,Pmu,cosmu_pmu_0p_2d_bins,cosmu_0p_bins,pmu_0p_bins),weight);
            }
          }
          if(flag_tki){
            TotalXsTKI+=weight;
            // STV Calculation              

            TVector3 MuonVectorTrans;
            MuonVectorTrans.SetXYZ(Muon3Vector.X(),Muon3Vector.Y(),0.);
            double MuonVectorTransMag = MuonVectorTrans.Mag();

            TVector3 MuonVectorLong;
            MuonVectorLong.SetXYZ(0.,0.,Muon3Vector.Z());
            double MuonVectorLongMag = MuonVectorLong.Mag();

            TVector3 ProtonVectorTrans;
            ProtonVectorTrans.SetXYZ(P3Vector.X(),P3Vector.Y(),0.);
            double ProtonVectorTransMag = ProtonVectorTrans.Mag();

            TVector3 ProtonVectorLong;
            ProtonVectorLong.SetXYZ(0.,0.,P3Vector.Z());
            double ProtonVectorLongMag = ProtonVectorLong.Mag();

            TVector3 PtVector = MuonVectorTrans + ProtonVectorTrans;

            double Pt = PtVector.Mag();

            double DeltaAlphaT = TMath::ACos( (- MuonVectorTrans * PtVector) / ( MuonVectorTransMag * Pt ) );
            if (DeltaAlphaT > 3.1416) { DeltaAlphaT -= 3.1416; }
            if (DeltaAlphaT < 0.) { DeltaAlphaT += 3.1416; }

            double DeltaPhiT = TMath::ACos( (- MuonVectorTrans * ProtonVectorTrans) / ( MuonVectorTransMag * ProtonVectorTransMag ) );
            if (DeltaPhiT > 3.1416) { DeltaPhiT -= 3.1416; }
            if (DeltaPhiT < 0.) { DeltaPhiT += 3.1416; }

            TrueDeltaPTPlot[0]->Fill(Pt,weight);
            TrueDeltaPTPlot[genie_mode]->Fill(Pt,weight);
            TrueDeltaAlphaTPlot[0]->Fill(DeltaAlphaT,weight);
            TrueDeltaAlphaTPlot[genie_mode]->Fill(DeltaAlphaT,weight);
            TrueDeltaPhiTPlot[0]->Fill(DeltaPhiT,weight);
            TrueDeltaPhiTPlot[genie_mode]->Fill(DeltaPhiT,weight);
          }

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

	//----------------------------------------//	

	// Division by bin width to get the cross sections	
	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

                int offset = 0;
                for(int bin=0; bin<SerialCosMuPmu0pPlot[inte]->GetNbinsX(); bin++){
                  Full[inte]->SetBinContent(bin+1,SerialCosMuPmu0pPlot[inte]->GetBinContent(bin+1));
                }
                offset+=SerialCosMuPmu0pPlot[inte]->GetNbinsX();
                for(int bin=0; bin<TrueCosp1Plot[inte]->GetNbinsX(); bin++){
                  Full[inte]->SetBinContent(bin+1+offset,TrueCosp1Plot[inte]->GetBinContent(bin+1));
                }
                offset+=TrueCosp1Plot[inte]->GetNbinsX();
                int temp_offset=0;
                for(int bin=0; bin<TrueCosp2Plot[inte]->GetNbinsX(); bin++){
                  if(bin==2){
                    for(int temp_bin=0; temp_bin<TruePp1Plot[inte]->GetNbinsX(); temp_bin++){
                      Full[inte]->SetBinContent(temp_bin+bin+1+offset,TruePp1Plot[inte]->GetBinContent(temp_bin+1));
                    }
                    temp_offset+=TruePp1Plot[inte]->GetNbinsX()-1;
                  }  
                  else { Full[inte]->SetBinContent(bin+1+offset+temp_offset,TrueCosp2Plot[inte]->GetBinContent(bin+1));}
                }
                offset+=TrueCosp2Plot[inte]->GetNbinsX()-1+TruePp1Plot[inte]->GetNbinsX();
                temp_offset=0;
                for(int bin=0; bin<TrueCosp3Plot[inte]->GetNbinsX(); bin++){
                  if(bin==2){
                    for(int temp_bin=0; temp_bin<TruePp2Plot[inte]->GetNbinsX(); temp_bin++){
                      Full[inte]->SetBinContent(temp_bin+bin+1+offset+temp_offset,TruePp2Plot[inte]->GetBinContent(temp_bin+1));
                    }
                    temp_offset+=TruePp2Plot[inte]->GetNbinsX()-1;
                  }
                  else if(bin==3){
                    for(int temp_bin=0; temp_bin<TruePp3Plot[inte]->GetNbinsX(); temp_bin++){
                      Full[inte]->SetBinContent(temp_bin+bin+1+offset+temp_offset,TruePp3Plot[inte]->GetBinContent(temp_bin+1));
                    }
                    temp_offset+=TruePp3Plot[inte]->GetNbinsX()-1;
                  }
                  else{ Full[inte]->SetBinContent(bin+1+offset+temp_offset,TrueCosp3Plot[inte]->GetBinContent(bin+1));}
                }
                offset+=TrueCosp3Plot[inte]->GetNbinsX()-2+TruePp2Plot[inte]->GetNbinsX()+TruePp3Plot[inte]->GetNbinsX();
                temp_offset=0;
                for(int bin=0; bin<TrueCosp4Plot[inte]->GetNbinsX(); bin++){
                  if(bin==2){
                    for(int temp_bin=0; temp_bin<TruePp4Plot[inte]->GetNbinsX(); temp_bin++){
                      Full[inte]->SetBinContent(temp_bin+bin+1+offset,TruePp4Plot[inte]->GetBinContent(temp_bin+1));
                    }
                    temp_offset+=TruePp4Plot[inte]->GetNbinsX()-1;
                  }
                  else{ Full[inte]->SetBinContent(bin+1+offset+temp_offset,TrueCosp4Plot[inte]->GetBinContent(bin+1));}
                }
                offset+=TrueCosp4Plot[inte]->GetNbinsX()-1+TruePp4Plot[inte]->GetNbinsX();
                Full[inte]->SetBinContent(1+offset,TruePmultPlot[inte]->GetBinContent(2));

	        Reweight(TrueMuonCosTheta1pPlot[inte]);
                Reweight(TrueMuonCosTheta0pPlot[inte]);

                Reweight(TrueDeltaPhiTPlot[inte]);
                Reweight(TrueDeltaPTPlot[inte]);
                Reweight(TrueDeltaAlphaTPlot[inte]);

                Reweight2d(SerialCosMuPmu0pPlot[inte],cosmu_pmu_0p_2d_bins,cosmu_0p_bins,pmu_0p_bins,1);
                Reweight2d(SerialCosMuCosp1pPlot[inte],cosmu_cosp_1p_2d_bins,cosmu_1p_bins,cosp_1p_bins,1);

                Reweight(TruePp1Plot[inte]);
                Reweight(TruePp2Plot[inte]);
                Reweight(TruePp3Plot[inte]);
                Reweight(TruePp4Plot[inte]);

                Reweight(TrueCosp1Plot[inte]);
                Reweight(TrueCosp2Plot[inte]);
                Reweight(TrueCosp3Plot[inte]);
                Reweight(TrueCosp4Plot[inte]);

	} // End of the loop over the interaction processes		

	//----------------------------------------//		
	std::cout << "TotalXs: "<<TotalXs<<std::endl;
        std::cout << "TotalXs0pi: "<<TotalXs0pi<<std::endl;
        std::cout << "TotalXsTKI: "<<TotalXsTKI<<std::endl;
        std::cout<<std::endl;

        std::cout << "Full"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<Full[0]->GetNbinsX(); i++){
            if (i==0) std::cout << Full[0]->GetBinContent(i+1);
            else std::cout << ", " << Full[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TruePmultPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TruePmultPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TruePmultPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << TruePmultPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl; 

        std::cout << "TrueMuonCosTheta1pPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueMuonCosTheta1pPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueMuonCosTheta1pPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueMuonCosTheta1pPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;
	
        std::cout << "TrueMuonCosTheta0pPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueMuonCosTheta0pPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueMuonCosTheta0pPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueMuonCosTheta0pPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueDeltaPTPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueDeltaPTPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueDeltaPTPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueDeltaPTPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueDeltaAlphaTPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueDeltaAlphaTPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueDeltaAlphaTPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueDeltaAlphaTPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueDeltaPhiTPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueDeltaPhiTPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueDeltaPhiTPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueDeltaPhiTPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "SerialCosMuPmu0pPlot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<SerialCosMuPmu0pPlot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << SerialCosMuPmu0pPlot[0]->GetBinContent(i+1);
            else std::cout << ", " << SerialCosMuPmu0pPlot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TruePp1Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TruePp1Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TruePp1Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TruePp1Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TruePp2Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TruePp2Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TruePp2Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TruePp2Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TruePp3Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TruePp3Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TruePp3Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TruePp3Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TruePp4Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TruePp4Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TruePp4Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TruePp4Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueCosp1Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueCosp1Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueCosp1Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueCosp1Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueCosp2Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueCosp2Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueCosp2Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueCosp2Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueCosp3Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueCosp3Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueCosp3Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueCosp3Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;

        std::cout << "TrueCosp4Plot"<<std::endl;;
        std::cout << "y = [";
        for(int i=0; i<TrueCosp4Plot[0]->GetNbinsX(); i++){
            if (i==0) std::cout << TrueCosp4Plot[0]->GetBinContent(i+1);
            else std::cout << ", " << TrueCosp4Plot[0]->GetBinContent(i+1);
        }
        std::cout << "]" << std::endl;
        std::cout<<std::endl;


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

//----------------------------------------//	

void Reweight2d(TH1D* h, std::vector< std::vector<int> > BinEdgeVector, std::vector< double> RowVector, std::vector< double> ElementVector, int dim){

        int index=1;

        int nrows = RowVector.size();

        for(int irow=0; irow<nrows-1; irow++){
                int nelements = BinEdgeVector.at(irow).size();

                double row_scale = RowVector.at(irow+1) - RowVector.at(irow);

                for(int ielement=0; ielement<nelements-1; ielement++){

                        int element_index_low = BinEdgeVector.at(irow).at(ielement);
                        int element_index_high = BinEdgeVector.at(irow).at(ielement+1);
                        double element_scale = ElementVector.at(element_index_high) - ElementVector.at(element_index_low);

                        double CurrentEntry = h->GetBinContent(index);
                        double CurrentError = h->GetBinError(index);

                        double NewEntry = CurrentEntry / row_scale / element_scale;
                        double NewError = CurrentError / row_scale / element_scale;
                        if(dim==1){
                          NewEntry = CurrentEntry / element_scale;
                          NewError = CurrentError / element_scale;
                        }
//std::cout<<"element_scale: "<<element_scale<<"    row_scale: "<<row_scale<<std::endl;
                        h->SetBinContent(index,NewEntry);
                        h->SetBinError(index,NewError);

                        index++;
                }
        }

}



int Return2DNBins(std::vector< std::vector<int> > BinEdgeVector) {

        int NBins = 0;
        int VectorRowSize = BinEdgeVector.size();

        for (int irow = 0; irow < VectorRowSize; irow++) {

                int NElements = BinEdgeVector.at(irow).size();

                // Number of bins for each subvector
                NBins += NElements-1;

        }
        return NBins;

}

std::vector<double> Return2DBinIndices(std::vector< std::vector<int> > BinEdgeVector) {

        int BinCounter = 0;
        int VectorRowSize = BinEdgeVector.size();
        std::vector<double> BinIndices;
        //double BinIndices[VectorRowSize];


        for (int irow = 0; irow < VectorRowSize; irow++) {

                int NElements = BinEdgeVector.at(irow).size();

                for (int ielement = 0; ielement < NElements-1; ielement++) {

                        // Lower bin edges in the form of indices
                        // + 0.5 so that the bins are centered at an integer (e.g. Bin 1, 2, 3 et al)
                        //BinIndices[BinCounter] = BinCounter+0.5;
                        BinIndices.push_back(BinCounter+0.5);
                        BinCounter++;

                }

        }

        // Upper bin edge
        BinIndices.push_back(BinCounter+0.5);
        //BinIndices[BinCounter] = BinCounter+0.5;
        return BinIndices;

}

int Get2Dbin(double value_row, double value_element, std::vector< std::vector<int> > BinEdgeVector, std::vector< double> RowVector, std::vector< double> ElementVector){
        int bin_row = -1;
        int bin_element = -1;
        int bin = 1;

        int nrows = RowVector.size();

        for(int irow=0;  irow<nrows-1; irow++){
                int nelements = BinEdgeVector.at(irow).size();

                int row_index_low = irow;
                int row_index_high = irow+1;
                if(value_row>=RowVector.at(row_index_low) && value_row<RowVector.at(row_index_high)){

                        bin_row = irow;

                        for (int ielement = 0; ielement < nelements-1; ielement++) {
                                int element_index_low = BinEdgeVector.at(irow).at(ielement);
                                int element_index_high = BinEdgeVector.at(irow).at(ielement+1);
                                if(value_element>=ElementVector.at(element_index_low) && value_element<ElementVector.at(element_index_high)){ bin_element=ielement;  return bin; }
                                 bin++;
                        }
                        return -1;//overflow catch 

                }

                bin+=nelements-1;

        }
        return -1;//overflow catch
}
	
