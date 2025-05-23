//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 22 11:17:04 2025 by ROOT version 6.28/12
// from TTree FlatTree_VARS/FlatTree_VARS
// found on file: /pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_6_0_achilles/calculation/11_1000060120_EMMEC_v3_6_0_G18_02a_00_000.flat.root
//////////////////////////////////////////////////////////

#ifndef FlatTree_VARS_h
#define FlatTree_VARS_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"

class FlatTree_VARS {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Mode;
   Int_t           GENIEResCode;
   Char_t          cc;
   Int_t           PDGnu;
   Float_t         Enu_true;
   Int_t           tgt;
   Int_t           tgta;
   Int_t           tgtz;
   Int_t           PDGLep;
   Float_t         ELep;
   Float_t         CosLep;
   Float_t         Q2;
   Float_t         q0;
   Float_t         q3;
   Float_t         Enu_QE;
   Float_t         Q2_QE;
   Float_t         W_nuc_rest;
   Float_t         W;
   Float_t         W_genie;
   Float_t         x;
   Float_t         y;
   Float_t         Erecoil_minerva;
   Float_t         Erecoil_charged;
   Float_t         EavAlt;
   Float_t         Emiss;
   TVector3        *pmiss;
   Float_t         Emiss_preFSI;
   TVector3        *pmiss_preFSI;
   Float_t         CosThetaAdler;
   Float_t         PhiAdler;
   Float_t         dalphat;
   Float_t         dpt;
   Float_t         dphit;
   Float_t         pnreco_C;
   Int_t           nfsp;
   Float_t         px[4];   //[nfsp]
   Float_t         py[4];   //[nfsp]
   Float_t         pz[4];   //[nfsp]
   Float_t         E[4];   //[nfsp]
   Int_t           pdg[4];   //[nfsp]
   Int_t           pdg_rank[4];   //[nfsp]
   Int_t           ninitp;
   Float_t         px_init[5];   //[ninitp]
   Float_t         py_init[5];   //[ninitp]
   Float_t         pz_init[5];   //[ninitp]
   Float_t         E_init[5];   //[ninitp]
   Int_t           pdg_init[5];   //[ninitp]
   Int_t           nvertp;
   Float_t         px_vert[7];   //[nvertp]
   Float_t         py_vert[7];   //[nvertp]
   Float_t         pz_vert[7];   //[nvertp]
   Float_t         E_vert[7];   //[nvertp]
   Int_t           pdg_vert[7];   //[nvertp]
   Float_t         Weight;
   Float_t         InputWeight;
   Float_t         RWWeight;
   Double_t        fScaleFactor;
   Float_t         CustomWeight;
   Float_t         CustomWeightArray[6];
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
   Bool_t          flagCC0piMINERvA;
   Bool_t          flagCC0Pi_T2K_AnaI;
   Bool_t          flagCC0Pi_T2K_AnaII;

   // List of branches
   TBranch        *b_Mode;   //!
   TBranch        *b_GENIEResCode;   //!
   TBranch        *b_cc;   //!
   TBranch        *b_PDGnu;   //!
   TBranch        *b_Enu_true;   //!
   TBranch        *b_tgt;   //!
   TBranch        *b_tgta;   //!
   TBranch        *b_tgtz;   //!
   TBranch        *b_PDGLep;   //!
   TBranch        *b_ELep;   //!
   TBranch        *b_CosLep;   //!
   TBranch        *b_Q2;   //!
   TBranch        *b_q0;   //!
   TBranch        *b_q3;   //!
   TBranch        *b_Enu_QE;   //!
   TBranch        *b_Q2_QE;   //!
   TBranch        *b_W_nuc_rest;   //!
   TBranch        *b_W;   //!
   TBranch        *b_W_genie;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_Erecoil_minerva;   //!
   TBranch        *b_Erecoil_charged;   //!
   TBranch        *b_EavAlt;   //!
   TBranch        *b_Emiss;   //!
   TBranch        *b_pmiss;   //!
   TBranch        *b_Emiss_preFSI;   //!
   TBranch        *b_pmiss_preFSI;   //!
   TBranch        *b_CosThetaAdler;   //!
   TBranch        *b_PhiAdler;   //!
   TBranch        *b_dalphat;   //!
   TBranch        *b_dpt;   //!
   TBranch        *b_dphit;   //!
   TBranch        *b_pnreco_C;   //!
   TBranch        *b_nfsp;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_E;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_pdg_rank;   //!
   TBranch        *b_ninitp;   //!
   TBranch        *b_px_init;   //!
   TBranch        *b_py_init;   //!
   TBranch        *b_pz_init;   //!
   TBranch        *b_E_init;   //!
   TBranch        *b_pdg_init;   //!
   TBranch        *b_nvertp;   //!
   TBranch        *b_px_vert;   //!
   TBranch        *b_py_vert;   //!
   TBranch        *b_pz_vert;   //!
   TBranch        *b_E_vert;   //!
   TBranch        *b_pdg_vert;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_InputWeight;   //!
   TBranch        *b_RWWeight;   //!
   TBranch        *b_fScaleFactor;   //!
   TBranch        *b_CustomWeight;   //!
   TBranch        *b_CustomWeightArray;   //!
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
   TBranch        *b_flagCC0piMINERvA;   //!
   TBranch        *b_flagCC0Pi_T2K_AnaI;   //!
   TBranch        *b_flagCC0Pi_T2K_AnaII;   //!

   FlatTree_VARS(TTree *tree=0);
   virtual ~FlatTree_VARS();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef FlatTree_VARS_cxx
FlatTree_VARS::FlatTree_VARS(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_6_0_achilles/calculation/11_1000060120_EMMEC_v3_6_0_G18_02a_00_000.flat.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_6_0_achilles/calculation/11_1000060120_EMMEC_v3_6_0_G18_02a_00_000.flat.root");
      }
      f->GetObject("FlatTree_VARS",tree);

   }
   Init(tree);
}

FlatTree_VARS::~FlatTree_VARS()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t FlatTree_VARS::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t FlatTree_VARS::LoadTree(Long64_t entry)
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

void FlatTree_VARS::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pmiss = 0;
   pmiss_preFSI = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Mode", &Mode, &b_Mode);
   fChain->SetBranchAddress("GENIEResCode", &GENIEResCode, &b_GENIEResCode);
   fChain->SetBranchAddress("cc", &cc, &b_cc);
   fChain->SetBranchAddress("PDGnu", &PDGnu, &b_PDGnu);
   fChain->SetBranchAddress("Enu_true", &Enu_true, &b_Enu_true);
   fChain->SetBranchAddress("tgt", &tgt, &b_tgt);
   fChain->SetBranchAddress("tgta", &tgta, &b_tgta);
   fChain->SetBranchAddress("tgtz", &tgtz, &b_tgtz);
   fChain->SetBranchAddress("PDGLep", &PDGLep, &b_PDGLep);
   fChain->SetBranchAddress("ELep", &ELep, &b_ELep);
   fChain->SetBranchAddress("CosLep", &CosLep, &b_CosLep);
   fChain->SetBranchAddress("Q2", &Q2, &b_Q2);
   fChain->SetBranchAddress("q0", &q0, &b_q0);
   fChain->SetBranchAddress("q3", &q3, &b_q3);
   fChain->SetBranchAddress("Enu_QE", &Enu_QE, &b_Enu_QE);
   fChain->SetBranchAddress("Q2_QE", &Q2_QE, &b_Q2_QE);
   fChain->SetBranchAddress("W_nuc_rest", &W_nuc_rest, &b_W_nuc_rest);
   fChain->SetBranchAddress("W", &W, &b_W);
   fChain->SetBranchAddress("W_genie", &W_genie, &b_W_genie);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("Erecoil_minerva", &Erecoil_minerva, &b_Erecoil_minerva);
   fChain->SetBranchAddress("Erecoil_charged", &Erecoil_charged, &b_Erecoil_charged);
   fChain->SetBranchAddress("EavAlt", &EavAlt, &b_EavAlt);
   fChain->SetBranchAddress("Emiss", &Emiss, &b_Emiss);
   fChain->SetBranchAddress("pmiss", &pmiss, &b_pmiss);
   fChain->SetBranchAddress("Emiss_preFSI", &Emiss_preFSI, &b_Emiss_preFSI);
   fChain->SetBranchAddress("pmiss_preFSI", &pmiss_preFSI, &b_pmiss_preFSI);
   fChain->SetBranchAddress("CosThetaAdler", &CosThetaAdler, &b_CosThetaAdler);
   fChain->SetBranchAddress("PhiAdler", &PhiAdler, &b_PhiAdler);
   fChain->SetBranchAddress("dalphat", &dalphat, &b_dalphat);
   fChain->SetBranchAddress("dpt", &dpt, &b_dpt);
   fChain->SetBranchAddress("dphit", &dphit, &b_dphit);
   fChain->SetBranchAddress("pnreco_C", &pnreco_C, &b_pnreco_C);
   fChain->SetBranchAddress("nfsp", &nfsp, &b_nfsp);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("pdg", pdg, &b_pdg);
   fChain->SetBranchAddress("pdg_rank", pdg_rank, &b_pdg_rank);
   fChain->SetBranchAddress("ninitp", &ninitp, &b_ninitp);
   fChain->SetBranchAddress("px_init", px_init, &b_px_init);
   fChain->SetBranchAddress("py_init", py_init, &b_py_init);
   fChain->SetBranchAddress("pz_init", pz_init, &b_pz_init);
   fChain->SetBranchAddress("E_init", E_init, &b_E_init);
   fChain->SetBranchAddress("pdg_init", pdg_init, &b_pdg_init);
   fChain->SetBranchAddress("nvertp", &nvertp, &b_nvertp);
   fChain->SetBranchAddress("px_vert", px_vert, &b_px_vert);
   fChain->SetBranchAddress("py_vert", py_vert, &b_py_vert);
   fChain->SetBranchAddress("pz_vert", pz_vert, &b_pz_vert);
   fChain->SetBranchAddress("E_vert", E_vert, &b_E_vert);
   fChain->SetBranchAddress("pdg_vert", pdg_vert, &b_pdg_vert);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("InputWeight", &InputWeight, &b_InputWeight);
   fChain->SetBranchAddress("RWWeight", &RWWeight, &b_RWWeight);
   fChain->SetBranchAddress("fScaleFactor", &fScaleFactor, &b_fScaleFactor);
   fChain->SetBranchAddress("CustomWeight", &CustomWeight, &b_CustomWeight);
   fChain->SetBranchAddress("CustomWeightArray", CustomWeightArray, &b_CustomWeightArray);
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
   fChain->SetBranchAddress("flagCC0piMINERvA", &flagCC0piMINERvA, &b_flagCC0piMINERvA);
   fChain->SetBranchAddress("flagCC0Pi_T2K_AnaI", &flagCC0Pi_T2K_AnaI, &b_flagCC0Pi_T2K_AnaI);
   fChain->SetBranchAddress("flagCC0Pi_T2K_AnaII", &flagCC0Pi_T2K_AnaII, &b_flagCC0Pi_T2K_AnaII);
   Notify();
}

Bool_t FlatTree_VARS::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void FlatTree_VARS::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t FlatTree_VARS::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef FlatTree_VARS_cxx
