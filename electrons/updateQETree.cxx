#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void updateQETree() {
 TFile *f = new TFile("./eQEupdated.root" ,"update");
 TTree *t = (TTree*)f->Get("qent");
// ifstream newInput("myTxt/E12_14_012_Inclusive_Ar40_E2222_Th15.txt");
// ifstream newInput("myTxt/E12_14_012_Inclusive_C12_E2222_Th15.txt");

// ifstream newInput("myTxt/E12_14_012_Inclusive_Al27_E2222_Th15.txt");
// ifstream newInput("myTxt/E12_14_012_Inclusive_Ti48_E2222_Th15.txt");
// ifstream newInput("myTxt/2H_Inclusive_All.txt");
// ifstream newInput("myTxt/Nicolescu_1999_Inclusive_1H_E2445_Th20.txt");
// ifstream newInput("myTxt/Nicolescu_1999_Inclusive_1H_E3245_Th26_98.txt");
// ifstream newInput("myTxt/E00_116_Inclusive_1H_E5500_Th41.txt");
// ifstream newInput("myTxt/Nicolescu_1999_Inclusive_2H_E2445_Th20.txt"); 
// ifstream newInput("myTxt/Nicolescu_1999_Inclusive_2H_E3245_Th26_98.txt");
// ifstream newInput("myTxt/E00_116_Inclusive_2H_E5500_Th41.txt");
// ifstream newInput("myTxt/SLAC_E61_Inclusive_1H_Th4.txt");
 ifstream newInput("myTxt/SLAC_E61_Inclusive_2H_Th4.txt");


 int A,Z;
 double E,v,theta,xsec,xsec_err;
 Char_t citation = 'a';
 
 t->SetBranchAddress("A", &A);
 t->SetBranchAddress("Z", &Z);
 t->SetBranchAddress("E", &E);
 t->SetBranchAddress("v", &v);
 t->SetBranchAddress("theta", &theta);
 t->SetBranchAddress("xsec", &xsec);
 t->SetBranchAddress("xsec_err", &xsec_err);
 t->SetBranchAddress("citation", &citation);

 string line;

 if (newInput.is_open())
  {
    while ( getline (newInput,line) )
    {
      cout << line << '\n';
      vector<string> words = split (line," ");
//      cout<<words[0]<<words[1]<<endl;
      Z = atoi(words[0].c_str());
      A = atoi(words[1].c_str());
      E = strtod(words[2].c_str(),NULL); 
      theta = strtod(words[3].c_str(),NULL);

//      v = E - strtod(words[4].c_str(),NULL); 
      v = strtod(words[4].c_str(),NULL); 

      xsec = strtod(words[5].c_str(),NULL);
      xsec_err = strtod(words[6].c_str(),NULL);
      t->Fill();
    }
    newInput.close();
  }
  t->Write();
  f->Write();
  f->Close();
 
}
