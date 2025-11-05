#ifndef FlatTreeAnalyzer_h
#define FlatTreeAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TVector3.h>

class FlatTreeAnalyzer {

private:
	TFile* fFile;
	TString fInputFile;
	TString fOutputFile;

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Mode;
   Int_t           ResCode;
   Int_t           PDGnu;
   Float_t         Enu_true;
   Int_t           Nleptons;
   Float_t         MLep;
   Float_t         ELep;
   Float_t         TLep;
   Float_t         CosLep;
   Float_t         CosPmuPpip;
   Float_t         CosPmuPpim;
   Float_t         CosPmuPpi0;
   Float_t         CosPmuPprot;
   Float_t         CosPmuPneut;
   Int_t           Nprotons;
   Float_t         MPr;
   Float_t         EPr;
   Float_t         TPr;
   Float_t         CosPr;
   Float_t         CosPprotPneut;
   Int_t           Nneutrons;
   Float_t         MNe;
   Float_t         ENe;
   Float_t         TNe;
   Float_t         CosNe;
   Int_t           Npiplus;
   Float_t         MPiP;
   Float_t         EPiP;
   Float_t         TPiP;
   Float_t         CosPiP;
   Float_t         CosPpipPprot;
   Float_t         CosPpipPneut;
   Float_t         CosPpipPpim;
   Float_t         CosPpipPpi0;
   Int_t           Npineg;
   Float_t         MPiN;
   Float_t         EPiN;
   Float_t         TPiN;
   Float_t         CosPiN;
   Float_t         CosPpimPprot;
   Float_t         CosPpimPneut;
   Float_t         CosPpimPpi0;
   Int_t           Npi0;
   Float_t         MPi0;
   Float_t         EPi0;
   Float_t         TPi0;
   Float_t         CosPi0;
   Float_t         CosPi0Pprot;
   Float_t         CosPi0Pneut;
   Int_t           Nother;
   Float_t         Q2_true;
   Float_t         q0_true;
   Float_t         q3_true;
   Float_t         Emiss;
   TVector3        *pmiss;
   Float_t         Emiss_preFSI;
   TVector3        *pmiss_preFSI;
   Float_t         Enu_QE;
   Float_t         Q2_QE;
   Float_t         W_nuc_rest;
   Float_t         bjorken_x;
   Float_t         bjorken_y;
   Float_t         Erecoil_true;
   Float_t         Erecoil_charged;
   Float_t         Erecoil_minerva;
   TLorentzVector  *nu_4mom;
   TLorentzVector  *pmu_4mom;
   TLorentzVector  *hm_ppip_4mom;
   TLorentzVector  *hm_ppim_4mom;
   TLorentzVector  *hm_ppi0_4mom;
   TLorentzVector  *hm_pprot_4mom;
   TLorentzVector  *hm_pneut_4mom;
   Float_t         Weight;
   Float_t         InputWeight;
   Float_t         RWWeight;
   Float_t         FluxWeight;
   Double_t        fScaleFactor;
   Bool_t          flagCCINC;
   Bool_t          flagNCINC;
   Bool_t          flagCCQE;
   Bool_t          flagCC0pi;
   Bool_t          flagCCQELike;
   Bool_t          flagNCEL;
   Bool_t          flagNC0pi;
   Bool_t          flagCCcoh;
   Bool_t          flagNCcoh;
   Bool_t          flagCC1pip;
   Bool_t          flagNC1pip;
   Bool_t          flagCC1pim;
   Bool_t          flagNC1pim;
   Bool_t          flagCC1pi0;
   Bool_t          flagNC1pi0;
   Bool_t          ICARUS_1muNp0pi_IsSignal;
   Float_t         ICARUS_1muNp0pi_deltaPT;
   Float_t         ICARUS_1muNp0pi_deltaalphaT;
   Float_t         ICARUS_1muNp0pi_MuonCos;
   Float_t         ICARUS_1muNp0pi_MuonProtonCos;
   Bool_t          ICARUS_1mu2p0pi_IsSignal;
   Float_t         ICARUS_1mu2p0pi_HadronicOpeningAngle;
   Float_t         ICARUS_1mu2p0pi_MuonHadronAngle;
   Float_t         ICARUS_1mu2p0pi_DeltaPT;
   Float_t         ICARUS_1mu2p0pi_DeltaAlphaT;
   Float_t         ICARUS_1mu2p0pi_DeltaPhiT;
   Float_t         ICARUS_1mu2p0pi_DeltaPTT;
   Bool_t          ICARUS_1mu1pi0_IsSignal;
   Float_t         ICARUS_1mu1pi0_MuonP;
   Float_t         ICARUS_1mu1pi0_NeutralPionP;

   // List of branches
   TBranch        *b_Mode;   //!
   TBranch        *b_ResCode;   //!
   TBranch        *b_PDGnu;   //!
   TBranch        *b_Enu_true;   //!
   TBranch        *b_Nleptons;   //!
   TBranch        *b_MLep;   //!
   TBranch        *b_ELep;   //!
   TBranch        *b_TLep;   //!
   TBranch        *b_CosLep;   //!
   TBranch        *b_CosPmuPpip;   //!
   TBranch        *b_CosPmuPpim;   //!
   TBranch        *b_CosPmuPpi0;   //!
   TBranch        *b_CosPmuPprot;   //!
   TBranch        *b_CosPmuPneut;   //!
   TBranch        *b_Nprotons;   //!
   TBranch        *b_MPr;   //!
   TBranch        *b_EPr;   //!
   TBranch        *b_TPr;   //!
   TBranch        *b_CosPr;   //!
   TBranch        *b_CosPprotPneut;   //!
   TBranch        *b_Nneutrons;   //!
   TBranch        *b_MNe;   //!
   TBranch        *b_ENe;   //!
   TBranch        *b_TNe;   //!
   TBranch        *b_CosNe;   //!
   TBranch        *b_Npiplus;   //!
   TBranch        *b_MPiP;   //!
   TBranch        *b_EPiP;   //!
   TBranch        *b_TPiP;   //!
   TBranch        *b_CosPiP;   //!
   TBranch        *b_CosPpipProt;   //!
   TBranch        *b_CosPpipPneut;   //!
   TBranch        *b_CosPpipPpim;   //!
   TBranch        *b_CosPpipPpi0;   //!
   TBranch        *b_Npineg;   //!
   TBranch        *b_MPiN;   //!
   TBranch        *b_EPiN;   //!
   TBranch        *b_TPiN;   //!
   TBranch        *b_CosPiN;   //!
   TBranch        *b_CosPpimPprot;   //!
   TBranch        *b_CosPpimPneut;   //!
   TBranch        *b_CosPpimPpi0;   //!
   TBranch        *b_Npi0;   //!
   TBranch        *b_MPi0;   //!
   TBranch        *b_EPi0;   //!
   TBranch        *b_TPi0;   //!
   TBranch        *b_CosPi0;   //!
   TBranch        *b_CosPi0Pprot;   //!
   TBranch        *b_CosPi0Pneut;   //!
   TBranch        *b_Nother;   //!
   TBranch        *b_Q2_true;   //!
   TBranch        *b_q0_true;   //!
   TBranch        *b_q3_true;   //!
   TBranch        *b_Emiss;   //!
   TBranch        *b_pmiss;   //!
   TBranch        *b_Emiss_preFSI;   //!
   TBranch        *b_pmiss_preFSI;   //!
   TBranch        *b_Enu_QE;   //!
   TBranch        *b_Q2_QE;   //!
   TBranch        *b_W_nuc_rest;   //!
   TBranch        *b_bjorken_x;   //!
   TBranch        *b_bjorken_y;   //!
   TBranch        *b_Erecoil_true;   //!
   TBranch        *b_Erecoil_charged;   //!
   TBranch        *b_Erecoil_minerva;   //!
   TBranch        *b_nu_4mom;   //!
   TBranch        *b_pmu_4mom;   //!
   TBranch        *b_hm_ppip_4mom;   //!
   TBranch        *b_hm_ppim_4mom;   //!
   TBranch        *b_hm_ppi0_4mom;   //!
   TBranch        *b_hm_pprot_4mom;   //!
   TBranch        *b_hm_pneut_4mom;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_InputWeight;   //!
   TBranch        *b_RWWeight;   //!
   TBranch        *b_FluxWeight;   //!
   TBranch        *b_fScaleFactor;   //!
   TBranch        *b_flagCCINC;   //!
   TBranch        *b_flagNCINC;   //!
   TBranch        *b_flagCCQE;   //!
   TBranch        *b_flagCC0pi;   //!
   TBranch        *b_flagCCQELike;   //!
   TBranch        *b_flagNCEL;   //!
   TBranch        *b_flagNC0pi;   //!
   TBranch        *b_flagCCcoh;   //!
   TBranch        *b_flagNCcoh;   //!
   TBranch        *b_flagCC1pip;   //!
   TBranch        *b_flagNC1pip;   //!
   TBranch        *b_flagCC1pim;   //!
   TBranch        *b_flagNC1pim;   //!
   TBranch        *b_flagCC1pi0;   //!
   TBranch        *b_flagNC1pi0;   //!
   TBranch        *b_ICARUS_1muNp0pi_IsSignal;   //!
   TBranch        *b_ICARUS_1muNp0pi_deltaPT;   //!
   TBranch        *b_ICARUS_1muNp0pi_deltaalphaT;   //!
   TBranch        *b_ICARUS_1muNp0pi_MuonCos;   //!
   TBranch        *b_ICARUS_1muNp0pi_MuonProtonCos;   //!
   TBranch        *b_ICARUS_1mu2p0pi_IsSignal;   //!
   TBranch        *b_ICARUS_1mu2p0pi_HadronicOpeningAngle;   //!
   TBranch        *b_ICARUS_1mu2p0pi_MuonHadronAngle;   //!
   TBranch        *b_ICARUS_1mu2p0pi_DeltaPT;   //!
   TBranch        *b_ICARUS_1mu2p0pi_DeltaAlphaT;   //!
   TBranch        *b_ICARUS_1mu2p0pi_DeltaPhiT;   //!
   TBranch        *b_ICARUS_1mu2p0pi_DeltaPTT;   //!
   TBranch        *b_ICARUS_1mu1pi0_IsSignal;   //!
   TBranch        *b_ICARUS_1mu1pi0_MuonP;   //!
   TBranch        *b_ICARUS_1mu1pi0_NeutralPionP;   //!

   FlatTreeAnalyzer(TString in, TString out, TTree *tree=0);
   virtual ~FlatTreeAnalyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FlatTreeAnalyzer_cxx
FlatTreeAnalyzer::FlatTreeAnalyzer(TString InputFile, TString OutputFile, TTree *tree) : fChain(0) 
{

	fInputFile = InputFile;
	fOutputFile = OutputFile;
	TString FullName = fInputFile;

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(FullName+".root");
      if (!f || !f->IsOpen()) {
         f = new TFile(FullName+".root");
      }
      f->GetObject("FlatTree_VARS",tree);
      fFile = f;

   }
   Init(tree);
}

FlatTreeAnalyzer::~FlatTreeAnalyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FlatTreeAnalyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FlatTreeAnalyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void FlatTreeAnalyzer::Init(TTree *tree)
{

   // Set object pointer
   pmiss = 0;
   pmiss_preFSI = 0;
   nu_4mom = 0;
   pmu_4mom = 0;
   hm_ppip_4mom = 0;
   hm_ppim_4mom = 0;
   hm_ppi0_4mom = 0;
   hm_pprot_4mom = 0;
   hm_pneut_4mom = 0;   

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Mode", &Mode, &b_Mode);
   fChain->SetBranchAddress("ResCode", &ResCode, &b_ResCode);
   fChain->SetBranchAddress("PDGnu", &PDGnu, &b_PDGnu);
   fChain->SetBranchAddress("Enu_true", &Enu_true, &b_Enu_true);
   fChain->SetBranchAddress("Nleptons", &Nleptons, &b_Nleptons);
   fChain->SetBranchAddress("MLep", &MLep, &b_MLep);
   fChain->SetBranchAddress("ELep", &ELep, &b_ELep);
   fChain->SetBranchAddress("TLep", &TLep, &b_TLep);
   fChain->SetBranchAddress("CosLep", &CosLep, &b_CosLep);
   fChain->SetBranchAddress("CosPmuPpip", &CosPmuPpip, &b_CosPmuPpip);
   fChain->SetBranchAddress("CosPmuPpim", &CosPmuPpim, &b_CosPmuPpim);
   fChain->SetBranchAddress("CosPmuPpi0", &CosPmuPpi0, &b_CosPmuPpi0);
   fChain->SetBranchAddress("CosPmuPprot", &CosPmuPprot, &b_CosPmuPprot);
   fChain->SetBranchAddress("CosPmuPneut", &CosPmuPneut, &b_CosPmuPneut);
   fChain->SetBranchAddress("Nprotons", &Nprotons, &b_Nprotons);
   fChain->SetBranchAddress("MPr", &MPr, &b_MPr);
   fChain->SetBranchAddress("EPr", &EPr, &b_EPr);
   fChain->SetBranchAddress("TPr", &TPr, &b_TPr);
   fChain->SetBranchAddress("CosPr", &CosPr, &b_CosPr);
   fChain->SetBranchAddress("CosPprotPneut", &CosPprotPneut, &b_CosPprotPneut);
   fChain->SetBranchAddress("Nneutrons", &Nneutrons, &b_Nneutrons);
   fChain->SetBranchAddress("MNe", &MNe, &b_MNe);
   fChain->SetBranchAddress("ENe", &ENe, &b_ENe);
   fChain->SetBranchAddress("TNe", &TNe, &b_TNe);
   fChain->SetBranchAddress("CosNe", &CosNe, &b_CosNe);
   fChain->SetBranchAddress("Npiplus", &Npiplus, &b_Npiplus);
   fChain->SetBranchAddress("MPiP", &MPiP, &b_MPiP);
   fChain->SetBranchAddress("EPiP", &EPiP, &b_EPiP);
   fChain->SetBranchAddress("TPiP", &TPiP, &b_TPiP);
   fChain->SetBranchAddress("CosPiP", &CosPiP, &b_CosPiP);
   fChain->SetBranchAddress("CosPpipPprot", &CosPpipPprot, &b_CosPpipProt);
   fChain->SetBranchAddress("CosPpipPneut", &CosPpipPneut, &b_CosPpipPneut);
   fChain->SetBranchAddress("CosPpipPpim", &CosPpipPpim, &b_CosPpipPpim);
   fChain->SetBranchAddress("CosPpipPpi0", &CosPpipPpi0, &b_CosPpipPpi0);
   fChain->SetBranchAddress("Npineg", &Npineg, &b_Npineg);
   fChain->SetBranchAddress("MPiN", &MPiN, &b_MPiN);
   fChain->SetBranchAddress("EPiN", &EPiN, &b_EPiN);
   fChain->SetBranchAddress("TPiN", &TPiN, &b_TPiN);
   fChain->SetBranchAddress("CosPiN", &CosPiN, &b_CosPiN);
   fChain->SetBranchAddress("CosPpimPprot", &CosPpimPprot, &b_CosPpimPprot);
   fChain->SetBranchAddress("CosPpimPneut", &CosPpimPneut, &b_CosPpimPneut);
   fChain->SetBranchAddress("CosPpimPpi0", &CosPpimPpi0, &b_CosPpimPpi0);
   fChain->SetBranchAddress("Npi0", &Npi0, &b_Npi0);
   fChain->SetBranchAddress("MPi0", &MPi0, &b_MPi0);
   fChain->SetBranchAddress("EPi0", &EPi0, &b_EPi0);
   fChain->SetBranchAddress("TPi0", &TPi0, &b_TPi0);
   fChain->SetBranchAddress("CosPi0", &CosPi0, &b_CosPi0);
   fChain->SetBranchAddress("CosPi0Pprot", &CosPi0Pprot, &b_CosPi0Pprot);
   fChain->SetBranchAddress("CosPi0Pneut", &CosPi0Pneut, &b_CosPi0Pneut);
   fChain->SetBranchAddress("Nother", &Nother, &b_Nother);
   fChain->SetBranchAddress("Q2_true", &Q2_true, &b_Q2_true);
   fChain->SetBranchAddress("q0_true", &q0_true, &b_q0_true);
   fChain->SetBranchAddress("q3_true", &q3_true, &b_q3_true);
   fChain->SetBranchAddress("Emiss", &Emiss, &b_Emiss);
   fChain->SetBranchAddress("pmiss", &pmiss, &b_pmiss);
   fChain->SetBranchAddress("Emiss_preFSI", &Emiss_preFSI, &b_Emiss_preFSI);
   fChain->SetBranchAddress("pmiss_preFSI", &pmiss_preFSI, &b_pmiss_preFSI);
   fChain->SetBranchAddress("Enu_QE", &Enu_QE, &b_Enu_QE);
   fChain->SetBranchAddress("Q2_QE", &Q2_QE, &b_Q2_QE);
   fChain->SetBranchAddress("W_nuc_rest", &W_nuc_rest, &b_W_nuc_rest);
   fChain->SetBranchAddress("bjorken_x", &bjorken_x, &b_bjorken_x);
   fChain->SetBranchAddress("bjorken_y", &bjorken_y, &b_bjorken_y);
   fChain->SetBranchAddress("Erecoil_true", &Erecoil_true, &b_Erecoil_true);
   fChain->SetBranchAddress("Erecoil_charged", &Erecoil_charged, &b_Erecoil_charged);
   fChain->SetBranchAddress("Erecoil_minerva", &Erecoil_minerva, &b_Erecoil_minerva);
   fChain->SetBranchAddress("nu_4mom", &nu_4mom, &b_nu_4mom);
   fChain->SetBranchAddress("pmu_4mom", &pmu_4mom, &b_pmu_4mom);
   fChain->SetBranchAddress("hm_ppip_4mom", &hm_ppip_4mom, &b_hm_ppip_4mom);
   fChain->SetBranchAddress("hm_ppim_4mom", &hm_ppim_4mom, &b_hm_ppim_4mom);
   fChain->SetBranchAddress("hm_ppi0_4mom", &hm_ppi0_4mom, &b_hm_ppi0_4mom);
   fChain->SetBranchAddress("hm_pprot_4mom", &hm_pprot_4mom, &b_hm_pprot_4mom);
   fChain->SetBranchAddress("hm_pneut_4mom", &hm_pneut_4mom, &b_hm_pneut_4mom);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("InputWeight", &InputWeight, &b_InputWeight);
   fChain->SetBranchAddress("RWWeight", &RWWeight, &b_RWWeight);
   fChain->SetBranchAddress("FluxWeight", &FluxWeight, &b_FluxWeight);
   fChain->SetBranchAddress("fScaleFactor", &fScaleFactor, &b_fScaleFactor);
   fChain->SetBranchAddress("flagCCINC", &flagCCINC, &b_flagCCINC);
   fChain->SetBranchAddress("flagNCINC", &flagNCINC, &b_flagNCINC);
   fChain->SetBranchAddress("flagCCQE", &flagCCQE, &b_flagCCQE);
   fChain->SetBranchAddress("flagCC0pi", &flagCC0pi, &b_flagCC0pi);
   fChain->SetBranchAddress("flagCCQELike", &flagCCQELike, &b_flagCCQELike);
   fChain->SetBranchAddress("flagNCEL", &flagNCEL, &b_flagNCEL);
   fChain->SetBranchAddress("flagNC0pi", &flagNC0pi, &b_flagNC0pi);
   fChain->SetBranchAddress("flagCCcoh", &flagCCcoh, &b_flagCCcoh);
   fChain->SetBranchAddress("flagNCcoh", &flagNCcoh, &b_flagNCcoh);
   fChain->SetBranchAddress("flagCC1pip", &flagCC1pip, &b_flagCC1pip);
   fChain->SetBranchAddress("flagNC1pip", &flagNC1pip, &b_flagNC1pip);
   fChain->SetBranchAddress("flagCC1pim", &flagCC1pim, &b_flagCC1pim);
   fChain->SetBranchAddress("flagNC1pim", &flagNC1pim, &b_flagNC1pim);
   fChain->SetBranchAddress("flagCC1pi0", &flagCC1pi0, &b_flagCC1pi0);
   fChain->SetBranchAddress("flagNC1pi0", &flagNC1pi0, &b_flagNC1pi0);
   fChain->SetBranchAddress("ICARUS_1muNp0pi_IsSignal", &ICARUS_1muNp0pi_IsSignal, &b_ICARUS_1muNp0pi_IsSignal);
   fChain->SetBranchAddress("ICARUS_1muNp0pi_deltaPT", &ICARUS_1muNp0pi_deltaPT, &b_ICARUS_1muNp0pi_deltaPT);
   fChain->SetBranchAddress("ICARUS_1muNp0pi_deltaalphaT", &ICARUS_1muNp0pi_deltaalphaT, &b_ICARUS_1muNp0pi_deltaalphaT);
   fChain->SetBranchAddress("ICARUS_1muNp0pi_MuonCos", &ICARUS_1muNp0pi_MuonCos, &b_ICARUS_1muNp0pi_MuonCos);
   fChain->SetBranchAddress("ICARUS_1muNp0pi_MuonProtonCos", &ICARUS_1muNp0pi_MuonProtonCos, &b_ICARUS_1muNp0pi_MuonProtonCos);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_IsSignal", &ICARUS_1mu2p0pi_IsSignal, &b_ICARUS_1mu2p0pi_IsSignal);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_HadronicOpeningAngle", &ICARUS_1mu2p0pi_HadronicOpeningAngle, &b_ICARUS_1mu2p0pi_HadronicOpeningAngle);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_MuonHadronAngle", &ICARUS_1mu2p0pi_MuonHadronAngle, &b_ICARUS_1mu2p0pi_MuonHadronAngle);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_DeltaPT", &ICARUS_1mu2p0pi_DeltaPT, &b_ICARUS_1mu2p0pi_DeltaPT);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_DeltaAlphaT", &ICARUS_1mu2p0pi_DeltaAlphaT, &b_ICARUS_1mu2p0pi_DeltaAlphaT);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_DeltaPhiT", &ICARUS_1mu2p0pi_DeltaPhiT, &b_ICARUS_1mu2p0pi_DeltaPhiT);
   fChain->SetBranchAddress("ICARUS_1mu2p0pi_DeltaPTT", &ICARUS_1mu2p0pi_DeltaPTT, &b_ICARUS_1mu2p0pi_DeltaPTT);
   fChain->SetBranchAddress("ICARUS_1mu1pi0_IsSignal", &ICARUS_1mu1pi0_IsSignal, &b_ICARUS_1mu1pi0_IsSignal);
   fChain->SetBranchAddress("ICARUS_1mu1pi0_MuonP", &ICARUS_1mu1pi0_MuonP, &b_ICARUS_1mu1pi0_MuonP);
   fChain->SetBranchAddress("ICARUS_1mu1pi0_NeutralPionP", &ICARUS_1mu1pi0_NeutralPionP, &b_ICARUS_1mu1pi0_NeutralPionP);

   Notify();
}

Bool_t FlatTreeAnalyzer::Notify()
{

   return kTRUE;
}

void FlatTreeAnalyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FlatTreeAnalyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FlatTreeAnalyzer_cxx
