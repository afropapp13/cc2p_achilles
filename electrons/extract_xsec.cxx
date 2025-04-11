#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TGaxis.h>
#include <TROOT.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

TString ToString(double num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;
}

TString ToStringInt(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;
}

void extract_xsec() {

	int FontStyle = 132;
	int Ndivisions = 4;
	double TextSize = 0.07;
	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");
	TGaxis::SetExponentOffset(-0.05, 0., "y");

	// ---------------------------------------------------------------------------------------------

	// Data File

	TString PathToSamples = "./";
	TString PathToSimSamples = "./";
	TFile* DataFile = TFile::Open(PathToSamples+"electron_data_xsecs.root");
	TTree* DataTree = (TTree*)(DataFile->Get("qent"));

	// ---------------------------------------------------------------------------------------------

	// Simulation Files

	TString PathToXSec = "./";
	vector <TString> xsec_file;

	xsec_file.push_back(PathToXSec+"xsec_carbon12_spline_EMPlusMEC_GTEST19_10b_00_000.root");
//	xsec_file.push_back(PathToXSec+"xsec_oxygen16_spline_EMPlusMEC_GTEST19_10b_00_000.root"); 
//	xsec_file.push_back(PathToXSec+"xsec_argon40_spline_EMPlusMEC_GTEST19_10b_00_000.root");
//	xsec_file.push_back(PathToXSec+"xsec_calcium40_spline_EMPlusMEC_GTEST19_10b_00_000.root"); 
//	xsec_file.push_back(PathToXSec+"xsec_iron56_spline_EMPlusMEC_GTEST19_10b_00_000.root");

	vector <TFile*> SimulationFile;
	SimulationFile.clear();

	vector <TString> xsec_Eventfile;

//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_0_240_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_0_320_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_0_560_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_0_680_GeV_1M_master.root");
	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_0_961_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_1_299_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_1_501_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_1_930_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_2_222_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_3_595_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"carbon12_EMPlusMEC_G18_02a_00_000_E_4_045_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"oxygen16_EMPlusMEC_G18_02a_00_000_E_0_737_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"oxygen16_EMPlusMEC_G18_02a_00_000_E_1_080_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"oxygen16_EMPlusMEC_G18_02a_00_000_E_1_200_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"argon40_EMPlusMEC_G18_02a_00_000_E_2_222_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"calcium40_EMPlusMEC_G18_02a_00_000_E_0_560_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"calcium40_EMPlusMEC_G18_02a_00_000_E_0_681_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"iron56_EMPlusMEC_G18_02a_00_000_E_0_961_GeV_1M_master.root");
//	xsec_Eventfile.push_back(PathToSimSamples+"iron56_EMPlusMEC_G18_02a_00_000_E_1_299_GeV_1M_master.root");

	// ---------------------------------------------------------------------------------------------

	// TChain common for data & simulation

	vector <TChain*> event_chain;
	event_chain.push_back(new TChain("gst"));

	// ---------------------------------------------------------------------------------------------

	// Constants

	int NBins = 10;

//	double Energy = 0.24; TString EnergyString = "0_24"; // GeV
//	double Energy = 0.32; TString EnergyString = "0_32"; // GeV
//	double Energy = 0.56; TString EnergyString = "0_56"; // GeV // default
//	double Energy = 0.68; TString EnergyString = "0_68"; // GeV
//	double Energy = 0.681; TString EnergyString = "0_681"; // GeV
//	double Energy = 0.737; TString EnergyString = "0_737"; // GeV
	double Energy = 0.961; TString EnergyString = "0_961"; // GeV
//	double Energy = 1.080; TString EnergyString = "1_080"; // GeV
//	double Energy = 1.200; TString EnergyString = "1_200"; // GeV	
//	double Energy = 1.299; TString EnergyString = "1_299"; // GeV
//	double Energy = 1.501; TString EnergyString = "1_501"; // GeV
//	double Energy = 1.930; TString EnergyString = "1_930"; // GeV
//	double Energy = 2.222; TString EnergyString = "2_222"; // GeV
//	double Energy = 3.595; TString EnergyString = "3_595"; // GeV
//	double Energy = 4.045; TString EnergyString = "4_045"; // GeV	

	TString target = "C"; int Z = 6; int A = 12;
//	string target = "O"; int Z = 8; int A = 16;
//	string target = "Ar"; int Z = 18; int A = 40;
//	string target = "Ca"; int Z = 20; int A = 40;
//	string target = "Fe"; int Z = 26; int A = 56;

	double ThetaCut = 1.14592; // degrees
//	double ThetaCut = 2.; // degrees
	double ThetaCut_Rad = ThetaCut * TMath::Pi() / 180.; // degrees

	const TString dirname = "e-_"+target+ToStringInt(A);
	const TString xsec_spline_name = "tot_em";
//	const TString xsec_spline_name = "qel_em_p";

	// ---------------------------------------------------------------------------------------------

	// Vectors / Angles

	vector <double> angle;
	vector <TString> angleString;

	// E = 0.24 GeV
//	/*angle.push_back(36);*/ angle.push_back(60);
//	/*angleString.push_back("36");*/ angleString.push_back("60");
//	double min = 0.005; double max = 0.24;

	// E = 0.32 GeV
//	angle.push_back(60);
//	angleString.push_back("60");
//	double min = 0.; double max = 0.18;

	// default
	// E = 0.56 GeV 
//	angle.push_back(36); angle.push_back(60); angle.push_back(145);
//	angleString.push_back("36"); angleString.push_back("60"); angleString.push_back("145");
//	double min = 0.; double max = 0.48;
	
	// 40Ca
	// E = 0.56 GeV 
//	angle.push_back(60);
//	angleString.push_back("60");
//	double min = 0.; double max = 0.48;	

	// E = 0.68 GeV
//	angle.push_back(36);
//	angleString.push_back("36");
//	double min = 0.; double max = 0.5;

	// E = 0.681 GeV
//	angle.push_back(45.5);
//	angleString.push_back("45.5");
//	double min = 0.; double max = 0.5;

	// E = 0.737 GeV 
//	angle.push_back(37.1);
//	angleString.push_back("37.1");
//	double min = 0.; double max = 0.7;

	// E = 0.961
	angle.push_back(37.5); angleString.push_back("37_5");
	double min = 0.; double max = 0.7;

	// E = 1.080 GeV
//	angle.push_back(32); angleString.push_back("32");
//	double min = 0.0; double max = 0.8;
	
	// E = 1.200 GeV
//	angle.push_back(32); angleString.push_back("32");
//	double min = 0.0; double max = 0.9;	


	// E = 1.299 GeV
//	angle.push_back(37.5); angleString.push_back("37_5");
//	double min = 0.1; double max = 0.82;

	// E = 1.501 GeV
//	angle.push_back(37.5); angleString.push_back("37_5");
//	double min = 0.2; double max = 1.;

	// E = 1.930 GeV
//	angle.push_back(16); angleString.push_back("16");
//	double min = 0.0; double max = 0.6;


	// E = 2.222 GeV
//	angle.push_back(15.54); angleString.push_back("15_54");
//	double min = 0.; double max = 1.; 

	// E = 3.595 GeV
//	angle.push_back(25);angleString.push_back("25");
//	double min = 0.4; double max = 1.2;

//	angle.push_back(16);angleString.push_back("16");
//	double min = 0.2; double max = 1.6;

//	angle.push_back(20);angleString.push_back("20");
//	double min = 0.2; double max = 1.6;
	
	// E = 4.045 GeV
//	angle.push_back(55);
//	angleString.push_back("55");
//	double min = 2.2; double max = 3.2;	

	const int NAngles = angle.size();
	vector <vector <TString> > Title; Title.clear();
	vector <vector <TLatex*> > LatexTitle; LatexTitle.clear();
	vector <vector <TLegend*> > leg; leg.clear();
	vector <vector <TCanvas*> > can; can.clear();

	TH1D* hData[NAngles];

	// ---------------------------------------------------------------------------------------------

	for (int WhichSimFile = 0; WhichSimFile < (int)(xsec_file.size()); WhichSimFile++) {

		SimulationFile.push_back(TFile::Open(xsec_file[WhichSimFile]));

		vector <TString> CurrentTitle;
		vector <TLatex*> CurrentLatexTitle;
		vector <TCanvas*> CurrentCan;
		vector <TLegend*> CurrentLeg;

		event_chain[WhichSimFile]->Add(xsec_Eventfile[WhichSimFile]);

		for (int WhichAngle = 0; WhichAngle < NAngles; WhichAngle++) {

			// Create the legent, title etc

			CurrentTitle.push_back("^{"+ToString(A)+"}"+target+" @E = "+ToString(Energy)+" GeV & #it{#theta} = " + ToString(angle[WhichAngle]) + "^{o}");
//			CurrentTitle.push_back(target+"(e,e\'): "+ToString(Energy)+" GeV at " + ToString(angle[WhichAngle]) + "^{o}");
//			CurrentLatexTitle.push_back(new TLatex(0.2,0.92,CurrentTitle[WhichAngle]));
			CurrentLatexTitle.push_back(new TLatex(0.22,0.92,CurrentTitle[WhichAngle]));
//			CurrentLatexTitle.push_back(new TLatex(0.29,0.83,CurrentTitle[WhichAngle]));
			CurrentLatexTitle[WhichAngle]->SetNDC(kTRUE);
			CurrentLatexTitle[WhichAngle]->SetTextFont(FontStyle);
			CurrentLatexTitle[WhichAngle]->SetTextSize(TextSize);

			CurrentLeg.push_back(new TLegend(0.5,0.8,0.67,0.89));

			CurrentCan.push_back(new TCanvas(ToString(angle[WhichAngle]),ToString(angle[WhichAngle]),205,34,1024,768));

			// Declare the cuts

			double Emin = Energy - 0.002;
			double Emax = Energy + 0.002;

			// ---------------------------------------------------------------------------------------------

			// Data 

			int nData = DataTree->Draw("v:xsec:xsec_err","(E == "+ToString(Energy)+" && Z == "+ToString(Z)
				+" && A == "+ToString(A)+" && abs(theta - "+
				ToString(angle[WhichAngle])+") < "+ToString(ThetaCut)+")*xsec","goff"); 
			TGraphErrors *DataGraph = new TGraphErrors(nData,DataTree->GetV1(),DataTree->GetV2(),0,DataTree->GetV3());

			hData[WhichAngle] = new TH1D("hData"+ ToString(angle[WhichAngle]),";Ev - El;",NBins,min,max);

			DataTree->Draw("v>>hData"+ ToString(angle[WhichAngle]),"(E == "+ToString(Energy)+" && Z == "+ToString(Z)
				+" && A == "+ToString(A)+" && abs(theta - "+ToString(angle[WhichAngle])
				+") < "+ToString(ThetaCut)+")*xsec/1e3");

			double DataIntegral = DataGraph->GetHistogram()->GetMaximum();

			CurrentCan[WhichAngle]->cd();
			CurrentCan[WhichAngle]->SetBottomMargin(0.13);
			CurrentCan[WhichAngle]->SetLeftMargin(0.16);

			DataGraph->SetTitle("");
			DataGraph->SetMarkerStyle(20);
			DataGraph->SetMarkerSize(1.5);
			DataGraph->SetLineWidth(3);

			DataGraph->GetHistogram()->GetXaxis()->SetRangeUser(min,max);
			DataGraph->GetHistogram()->GetXaxis()->CenterTitle();
			DataGraph->GetHistogram()->GetXaxis()->SetTitle("Energy Transfer [GeV]");
			DataGraph->GetHistogram()->GetXaxis()->SetLabelSize(TextSize);
			DataGraph->GetHistogram()->GetXaxis()->SetTitleSize(TextSize);
			DataGraph->GetHistogram()->GetXaxis()->SetLabelFont(FontStyle);
			DataGraph->GetHistogram()->GetXaxis()->SetTitleFont(FontStyle);
			DataGraph->GetHistogram()->GetXaxis()->SetNdivisions(Ndivisions);
			DataGraph->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);

//			DataGraph->GetHistogram()->GetYaxis()->SetRangeUser(0,1.3*DataGraph->GetHistogram()->GetMaximum());
			DataGraph->GetHistogram()->GetYaxis()->SetRangeUser(0,1.05*DataGraph->GetHistogram()->GetMaximum());
			if (Energy == 0.24) { DataGraph->GetHistogram()->GetYaxis()->SetRangeUser(0,0.26*DataGraph->GetHistogram()->GetMaximum()); }
			
			
			DataGraph->GetHistogram()->GetYaxis()->CenterTitle();
			DataGraph->GetHistogram()->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [nb/sr/GeV]");
//			DataGraph->GetHistogram()->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [#mub/sr/GeV]");
			DataGraph->GetHistogram()->GetYaxis()->SetLabelSize(TextSize);
			DataGraph->GetHistogram()->GetYaxis()->SetTitleSize(TextSize);
			DataGraph->GetHistogram()->GetYaxis()->SetLabelFont(FontStyle);
			DataGraph->GetHistogram()->GetYaxis()->SetTitleFont(FontStyle);
			DataGraph->GetHistogram()->GetYaxis()->SetNdivisions(Ndivisions);
			DataGraph->GetYaxis()->SetTitleOffset(1.);

			DataGraph->Draw("ap");
			
			/*TString OutputFileString = "./"+TString(target)+ToString(A)+"_E_"+EnergyString+"_theta_"+angleString[WhichAngle]+".root";
			TFile* OutputFile = new TFile(OutputFileString,"recreate");
			OutputFile->cd();
			DataGraph->Write("Data");*/		

			// ---------------------------------------------------------------------------------------------

			// Simulation
/*
			SimulationFile[WhichSimFile]->cd();
			TDirectory * dir = (TDirectory*)SimulationFile[WhichSimFile]->Get(dirname);

			TGraph * xsec_em_gr = (TGraph*)dir->Get(xsec_spline_name);
			double xsec_em = xsec_em_gr->Eval(Energy);

			xsec_em *= (1E-5); // (1E-38  * units::cm2 / units::nb); // convert from cm2 to nbarn
//			xsec_em *= (1E-2); // (1E-38  * units::cm2 / units::nb); // convert from cm2 to microbarn   
						                                                             
			event_chain[WhichSimFile]->Draw("1", Form("(Ev>=%f)&&(Ev<%f)&&(Z==%d)&&(A==%d)&&(em)",Emin,Emax,Z,A), "GOFF");
			double nentries_all = event_chain[WhichSimFile]->GetSelectedRows();

			double dv = (max - min) / NBins;

			double scale = xsec_em / (nentries_all*dv * 2 * TMath::Pi() 
				       * abs( cos( (angle[WhichAngle] + ThetaCut) *TMath::Pi() / 180.) - cos( (angle[WhichAngle] - ThetaCut) *TMath::Pi() / 180.) ));

			const int ngraphs = 5;

                        TString StandardCuts = "Ev > " + ToString(Emin) +" && Ev < " + ToString(Emax)+" && Z == "+ToString(Z)+" && A == "+ToString(A);

			TString SimulationCuts = StandardCuts + " && abs(TMath::ACos(cthl)*180./TMath::Pi() - " + ToString(angle[WhichAngle]) +") < "+ToString(ThetaCut);

			TString cut = "ThetaCut";

			TString select_events_in_costheta_bin[ngraphs] = {
				SimulationCuts + " &&(em)", SimulationCuts + " &&(em && qel)", SimulationCuts + " &&(em && mec)", SimulationCuts + " &&(em && res)", 
				SimulationCuts + " &&(em && (!qel&&!mec&&!res))"
			};

			//TString label[ngraphs] = { "Total", "Quasi-elastic", "Meson Exchange", "Resonance", "Other"};
//			TString label[ngraphs] = { "GENIE (Total)", "QE", "MEC", "RES", "DIS"};
			TString label[ngraphs] = { "Total", "QE", "MEC", "RES", "DIS"};
//			int color[ngraphs] = { kBlack, kBlue,  kMagenta,   kRed,   kGreen };
			int color[ngraphs] = { kBlack, kBlue,  429,   410,   610 };
			int style[ngraphs] = { kSolid, kSolid, kSolid, kSolid, kSolid };
			int width[ngraphs] = { 2,      2,      2,       2,      2      };

			// ---------------------------------------------------------------------------------------------

			// Loop over the different interaction channels

			for(int igr = 0; igr < ngraphs; igr++) {

				TH1D * v_distribution = new TH1D("v_distribution_"+ToString(igr)+"_"+ToString(angle[WhichAngle]),"",NBins,min,max);
				event_chain[WhichSimFile]->Draw("Ev-El>>v_distribution_"+ToString(igr)+"_"+ToString(angle[WhichAngle]), select_events_in_costheta_bin[igr], "goff");
				double nentries = event_chain[WhichSimFile]->GetSelectedRows();
				v_distribution->GetXaxis()->SetRangeUser(min,max);

				v_distribution->Scale(scale);
				double * v = new double[NBins];
				double * d2sigma_dEpdOmega = new double[NBins];

				for(int i=0; i < NBins; i++) {

					v[i] = v_distribution->GetBinCenter(i+1);
					d2sigma_dEpdOmega[i] = v_distribution->GetBinContent(i+1);

				}

				TGraph * gr = new TGraph(NBins,v,d2sigma_dEpdOmega);

				CurrentCan[WhichAngle]->cd();
				gr->SetTitle("");
				gr->SetLineColor(color[igr]);
				gr->SetLineStyle(style[igr]);
				gr->SetLineWidth(3);
				gr->Draw("c same");

				CurrentLeg[WhichAngle]->AddEntry(gr,label[igr],"l");

				// ---------------------------------------------------------------------------------------------

				// Latex 

				TLatex* LatexProcess = new TLatex();
				LatexProcess->SetTextFont(FontStyle);
				LatexProcess->SetTextSize(TextSize);
				LatexProcess->SetTextColor(color[igr]);
//				if (label[igr] == "GENIE (Total)") { LatexProcess->DrawLatexNDC(0.45,0.7,label[igr]); }
//				if (label[igr] == "QE") { LatexProcess->DrawLatexNDC(0.28,0.35,label[igr]); }
//				if (label[igr] == "MEC") { LatexProcess->DrawLatexNDC(0.48,0.35,label[igr]); }
//				if (label[igr] == "RES") { LatexProcess->DrawLatexNDC(0.64,0.37,label[igr]); }
//				if (label[igr] == "DIS") { LatexProcess->DrawLatexNDC(0.7,0.22,label[igr]); }

//				if (igr == 4) { 

//					TLatex* LatexData = new TLatex();
//					LatexData->SetTextFont(FontStyle);
//					LatexData->SetTextSize(TextSize);
//					LatexData->SetTextColor(kBlack);
//					LatexData->DrawLatexNDC(0.33,0.54,"Data"); 

//				}

				// ---------------------------------------------------------------------------------------------

				delete [] v;
				delete [] d2sigma_dEpdOmega;
				delete v_distribution;
				
				if (igr == 0) {
				
					OutputFile->cd();
					gr->Write("Simulation");
					
				}	

			}
*/
			// Plot the data graph again so that the points are on top of the genie breakdown lines

			DataGraph->Draw("p");

			// ---------------------------------------------------------------------------------------------

			CurrentLatexTitle[WhichAngle]->Draw();

			// Export as pdf

			TString NamePlot = "Overlay_"+target+"_E_"+EnergyString+"_theta_"+angleString[WhichAngle];
			CurrentCan[WhichAngle]->SaveAs("./"+NamePlot+".pdf");

		    //---------------------------//			
		
			TFile* f = TFile::Open("achilles_mc_electrons_2p.root","readonly");
			TH1D* h = (TH1D*)(f->Get("cc2p"));

			CurrentCan[WhichAngle]->cd();
			h->SetLineColor(kRed);
			h->SetLineWidth(4);			
			h->Scale(1e3);			
			h->Draw("hist c same");

			// Legend

			CurrentLeg[WhichAngle]->SetBorderSize(0);
			CurrentLeg[WhichAngle]->SetNColumns(3);
			CurrentLeg[WhichAngle]->SetColumnSeparation(2.);
			CurrentLeg[WhichAngle]->SetTextFont(FontStyle);
			CurrentLeg[WhichAngle]->SetTextSize(TextSize);

			CurrentLeg[WhichAngle]->AddEntry(DataGraph,"Data","lep");

			TLegendEntry* lMC = CurrentLeg[WhichAngle]->AddEntry(h,"2p prediction","l");
			lMC->SetTextColor(kRed);	
			CurrentLeg[WhichAngle]->Draw();			

		    //---------------------------//			

		} // End of the loop over the angles

	} // End of the loop over the simulation files

} // End of the program
