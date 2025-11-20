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

	TFile* mc_file = TFile::Open("mc_output_files/FlatTreeAnalyzerOutput_AR23.root");

	TString h_name = "TrueDeltaPTPlot";
	if (var == "dat") { h_name = "TrueDeltaAlphaTPlot"; }	
	if (var == "dphit") { h_name = "TrueDeltaPhiTPlot"; }	

	TH1D* hmc = (TH1D*)(mc_file->Get(h_name));
	double scale = 1e-39;	

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

	// thstack
	vector<TString> InteractionLabels = {"QE","MEC","RES","DIS","COH"};
	vector<int> colors = {
		TColor::GetColor("#6BAED6"), // light blue
		TColor::GetColor("#74C476"), // light green
		TColor::GetColor("#FD8D3C"), // orange
		TColor::GetColor("#9E9AC8"), // lavender
		TColor::GetColor("#FDD0A2")  // beige
	};
	int ninte = InteractionLabels.size();
	vector<TH1D*> h_inte; h_inte.resize(ninte);

	THStack* thstack = new THStack("stack","stack");

	for (int iinte = 0; iinte < ninte; iinte++) {

		h_inte.at(iinte) = (TH1D*)(mc_file->Get(InteractionLabels.at(iinte) + h_name));
		h_inte.at(iinte)->SetLineColor( colors.at(iinte) );
		h_inte.at(iinte)->SetFillColor( colors.at(iinte) );	
		h_inte.at(iinte)->SetLineWidth(3);			
		h_inte.at(iinte)->Scale(scale);
		
		thstack->Add(h_inte.at(iinte));
		thstack->Draw("same hist");

	}

	thstack->Draw("same hist");
	hdata->Draw("e1 same");	

	//---------------------------//			

	// default mec plot

	TH1D* clone_mec = (TH1D*)(h_inte.at(1)->Clone("clone_mec"));
	clone_mec->SetLineColor(kMagenta);
	clone_mec->SetFillColor(0);	
	clone_mec->Draw("hist same");

	//---------------------------//	

	// new 2p2h model

	TFile* f_new2p2h = TFile::Open("mc_output_files/gst_analyzerOutput_noah_2p2h.root");
	TH1D* h_new2p2h = (TH1D*)(f_new2p2h->Get(h_name));
	h_new2p2h->SetLineColor(kRed);
	h_new2p2h->SetLineWidth(3);
	h_new2p2h->Scale(scale);
	h_new2p2h->Draw("hist same");

	//---------------------------//	
	
	// legend

	TLegend* leg = new TLegend(0.25,0.91,0.95,0.98);
	leg->SetBorderSize(0);
	leg->SetTextFont(text_font);
	leg->SetTextSize(0.04);
	leg->SetNColumns(4);	

	leg->AddEntry(hdata,"T2K Data","ep");
	leg->AddEntry(h_inte.at(0),"QE","l");
	leg->AddEntry(h_inte.at(1),"MEC","l");
	leg->AddEntry(h_inte.at(2),"RES","l");
	leg->AddEntry(h_inte.at(3),"DIS","l");	
	leg->AddEntry(h_inte.at(4),"COH","l");	
	leg->AddEntry(clone_mec,"default MEC","l");
	leg->AddEntry(h_new2p2h,"new 2p2h model","l");
	leg->Draw();

	//---------------------------//					

	// export as pdf

	gPad->RedrawAxis();
	TString NamePlot = "t2k_"+var;
	c->SaveAs("pdf/"+NamePlot+".pdf");			

} // end of the program