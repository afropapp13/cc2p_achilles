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

void ub_cc2p_extract_xsec(TString var) {

	//--------------------//

	// data file

	TFile* data_file = TFile::Open("ub_cc2p_files/NuisanceInput_WSVD_2ndDeriv.root");

	TH1D* hdata = (TH1D*)(data_file->Get("reco_"+var+"/reco_"+var+"_DataHist"));
	TH2D* cov = (TH2D*)(data_file->Get("reco_"+var+"/reco_"+var+"_CovMat"));
	TH2D* reg = (TH2D*)(data_file->Get("reco_"+var+"/reco_"+var+"_AC"));	

	int nrows = reg->GetNbinsX();
	int ncols = reg->GetNbinsY();
	TMatrixD* fSmearingMatrix = new TMatrixD(nrows, ncols);
	for (int i=0; i<nrows; i++) {
		for (int j=0; j<ncols; j++) {
		(*fSmearingMatrix)(i,j) = reg->GetBinContent(i+1, j+1);
		}
	}	

	//--------------------//

	// mc file

	TFile* mc_file = TFile::Open("ub_cc2p_mc_files/FlatTreeAnalyzerOutput_GENIE_v3_0_6.root");

	TH1D* hmc = (TH1D*)(mc_file->Get("TrueDeltaPTPlot"));
	if (var == "cos(Mu,P_sum)") { hmc = (TH1D*)(mc_file->Get("TrueCosThetaMuSumPPlot")); }
	if (var == "cos(P_L,P_R)") { hmc = (TH1D*)(mc_file->Get("TrueCosThetaPLPRPlot")); }	

	int nBins = hmc->GetNbinsX();

	// First convert to TVectorD
	TVectorD MC_PreSmear(nBins);
	for (int iBin=0;iBin<nBins;iBin++) {
		MC_PreSmear(iBin) = hmc->GetBinContent(iBin+1);
	}

	// Apply smearing
	TVectorD MC_PostSmear = (*fSmearingMatrix) * MC_PreSmear;

	TH1D* hmc_clone = (TH1D*)(hmc->Clone());

	// Then copy results back to histogram
	for (int iBin=0;iBin<nBins;iBin++) {
		hmc_clone->SetBinContent(iBin+1, MC_PostSmear(iBin)/hmc->GetBinWidth(iBin+1));
	}	

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

	hmc_clone->SetLineColor(kOrange+7);
	hmc_clone->Draw("hist same");

	//---------------------------//					

	// export as pdf

	TString NamePlot = "ub_cc2p_"+var;
	c->SaveAs("pdf/"+NamePlot+".pdf");			

} // end of the program