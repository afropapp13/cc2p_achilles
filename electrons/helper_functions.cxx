#include <TH1D.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

//---------------------------//

bool is_integer(double k){

  return std::floor(k) == k;

}

//---------------------------//

vector<string> split (string s, string delimiter) {

  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> res;

  while ( (pos_end = s.find (delimiter, pos_start)) != string::npos ) {

    token = s.substr (pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back (token);
    
  }

  res.push_back (s.substr (pos_start));
  return res;

}

//----------------------------------------//

//Function to divide by the bin width and to get xsecs
void divide_bin_width(TH1D* h, double SF = 1.) {

  int NBins = h->GetXaxis()->GetNbins();

  for (int i = 0; i < NBins; i++) {

    double CurrentEntry = h->GetBinContent(i+1);
    double NewEntry = SF * CurrentEntry / h->GetBinWidth(i+1);

    double CurrentError = h->GetBinError(i+1);
    double NewError = SF * CurrentError / h->GetBinWidth(i+1);

    h->SetBinContent(i+1,NewEntry); 
    h->SetBinError(i+1,NewError); 
    //h->SetBinError(i+1,0.000001); 

  }

}

//----------------------------------------//
