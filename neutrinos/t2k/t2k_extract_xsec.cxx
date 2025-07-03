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
#include <TROOT.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

void t2k_extract_xsec(TString var) {

	//--------------------//

	// data file

	TFile* data_file = TFile::Open("neutrino_t2k_data_files/"+var+"Results.root");

	TH1D* hdata = (TH1D*)(data_file->Get("Result"));
	TH2D* cov = (TH2D*)(data_file->Get("Covariance"));

	//--------------------//

	// mc file

	TFile* mc_file = TFile::Open("mc_output_files/FlatTreeAnalyzerOutput_gibuu20251_soft_inmed_DS3_30.root");

	TH1D* hmc = (TH1D*)(mc_file->Get("TrueDeltaPTPlot"));
	if (var == "dphit") { hmc = (TH1D*)(mc_file->Get("TrueDeltaPhiTPlot")); }
	if (var == "dat") { hmc = (TH1D*)(mc_file->Get("TrueDeltaAlphaTPlot")); }	

	//--------------------//

	// canvas

	TCanvas* c = new TCanvas();
	c->SetBottomMargin(0.15);
	c->SetLeftMargin(0.15);
	c->SetRightMargin(0.05);	

	//--------------------//

	// plot data graph	

	hdata->SetTitle("");
	hdata->SetMarkerStyle(20);
	hdata->SetMarkerSize(1.);
	hdata->SetLineColor(kBlack);	

	hdata->GetXaxis()->CenterTitle();
	hdata->GetXaxis()->SetLabelSize(text_size);
	hdata->GetXaxis()->SetTitleSize(text_size);
	hdata->GetXaxis()->SetLabelFont(text_font);
	hdata->GetXaxis()->SetTitleFont(text_font);
	hdata->GetXaxis()->SetNdivisions(ndivs);
	hdata->GetXaxis()->SetTitleOffset(1.);
			
	hdata->GetYaxis()->CenterTitle();
	hdata->GetYaxis()->SetLabelSize(text_size);
	hdata->GetYaxis()->SetTitleSize(text_size);
	hdata->GetYaxis()->SetLabelFont(text_font);
	hdata->GetYaxis()->SetTitleFont(text_font);
	hdata->GetYaxis()->SetNdivisions(ndivs);
	hdata->GetYaxis()->SetLabelOffset(0.01);	
	hdata->GetYaxis()->SetTitleOffset(1.1);

	double maxY = hdata->GetMaximum();
	hdata->GetYaxis()->SetRangeUser(0.,1.25*maxY);		

	hdata->Draw("e1");	

	//---------------------------//		

	// mc plot

	hmc->Scale(1e-39);
	hmc->SetLineColor(kOrange+7);
	hmc->Draw("hist same");

	//---------------------------//					

	// export as pdf

	TString NamePlot = "t2k_"+var;
	c->SaveAs("pdf/"+NamePlot+".pdf");			

} // end of the program