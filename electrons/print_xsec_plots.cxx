#include <iostream>
#include "TROOT.h"

void print_xsec_plots() {

gROOT->ProcessLine(".L extract_xsec.cxx+");
gROOT->ProcessLine("extract_xsec()");
//gROOT->ProcessLine(".q");

}
