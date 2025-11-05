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

void Reweight(TH1D* h);
TH1D* Multiply(TH1D* True, TH2D* SmearMatrix);

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

	TString h_name = "TrueDeltaPTPlot";
	if (var == "cos(Mu,P_sum)") { h_name = "TrueCosThetaMuSumPPlot"; }	
	if (var == "cos(P_L,P_R)") { h_name = "TrueCosThetaPLPRPlot"; }	

	TH1D* hmc = (TH1D*)(mc_file->Get(h_name));	

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
	hdata->GetYaxis()->SetTitleSize(text_size-0.01);
	hdata->GetYaxis()->SetLabelFont(text_font);
	hdata->GetYaxis()->SetTitleFont(text_font);
	hdata->GetYaxis()->SetNdivisions(ndivs);
	hdata->GetYaxis()->SetLabelOffset(0.01);	
	hdata->GetYaxis()->SetTitleOffset(1.1);

	double maxY = hdata->GetMaximum();
	hdata->GetYaxis()->SetRangeUser(0.,1.3*maxY);		

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
		h_inte.at(iinte) = Multiply(h_inte.at(iinte), reg);	
		Reweight(h_inte.at(iinte));	
		
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
	
	// legend

	TLegend* leg = new TLegend(0.15,0.91,0.75,0.98);
	leg->SetBorderSize(0);
	leg->SetTextFont(text_font);
	leg->SetTextSize(0.04);
	leg->SetNColumns(4);	

	leg->AddEntry(hdata,"ICARUS Data","ep");
	leg->AddEntry(h_inte.at(0),"QE","l");
	leg->AddEntry(h_inte.at(1),"MEC","l");
	leg->AddEntry(h_inte.at(2),"RES","l");
	leg->AddEntry(h_inte.at(3),"DIS","l");	
	leg->AddEntry(h_inte.at(4),"COH","l");	
	leg->AddEntry(clone_mec,"default MEC","l");
	leg->Draw();	

	//---------------------------//					

	// export as pdf

	gPad->RedrawAxis();
	TString NamePlot = "ub_cc2p_"+var;
	c->SaveAs("pdf/"+NamePlot+".pdf");			

} // end of the program

//----------------------------------------//

void TV2H(const TVectorD vec, TH1D* histo)
{
    // Fill vector to histogram,
    for(Int_t i=0; i<vec.GetNrows(); i++)
    {
        histo->SetBinContent(i+1, vec(i));
    }
}

//----------------------------------------//

void TH2M(const TH2D* histo, TMatrixD& mat, bool rowcolumn) {

    // Fill 2D histogram into matrix
    // If TH2D(i, j) = Matrix(i, j), rowcolumn = kTRUE, else rowcolumn = kFALSE

    for (Int_t i=0; i<histo->GetNbinsX(); i++) {

        for (Int_t j=0; j<histo->GetNbinsY(); j++) {

            if (rowcolumn) { mat(i, j) = histo->GetBinContent(i+1, j+1); }
            else { mat(j, i) = histo->GetBinContent(i+1, j+1); }

        }

    }

}

//----------------------------------------//

void TH2V(const TH1D* histo, TVectorD& vec)
{
    // Fill 1D histogram into matrix
    for(Int_t i=0; i<histo->GetNbinsX(); i++)
    {
        vec(i) = histo->GetBinContent(i+1);
    }
}

//----------------------------------------//                                                                                               

TH1D* Multiply(TH1D* True, TH2D* SmearMatrix) {

  TH1D* TrueClone = (TH1D*)(True->Clone());

  int XBins = SmearMatrix->GetXaxis()->GetNbins();
  int YBins = SmearMatrix->GetYaxis()->GetNbins();

  if (XBins != YBins) { std::cout << "Not symmetric matrix" << std::endl; }

  TVectorD signal(XBins);
  TMatrixD response(XBins,XBins);

  TH2V(TrueClone, signal);
  TH2M(SmearMatrix, response, kTRUE);

  TVectorD RecoSpace = response * signal;
  TV2H(RecoSpace, TrueClone);

  return TrueClone;

}

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
