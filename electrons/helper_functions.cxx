#include <TH1D.h>
#include <TGraph.h>
#include <TCanvas.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm> // Required for std::max_element

using namespace std;

//---------------------------//

const int text_font = 132;
const double text_size = 0.06;
const int ndivs = 6; 

//---------------------------//

TString int_to_string(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;
  
}

//---------------------------//

TString double_to_string(double num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

//---------------------------//

std::fstream& GotoLine(std::fstream& file, unsigned int num){

    file.seekg(std::ios::beg);

    for(int i=0; i < (int)(num - 1); ++i){

        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    }

    return file;

}

//---------------------------//

bool is_integer(double k){

  return std::floor(k) == k;

}

//---------------------------//

std::vector<std::string> split_line (const std::string &s, char delim) {

  std::vector<std::string> result;
  std::stringstream ss (s);
  std::string item;

  while (getline (ss, item, delim)) {
      result.push_back (item);
  }

  return result;
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
