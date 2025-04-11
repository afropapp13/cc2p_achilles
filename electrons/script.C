#include <iostream>
#include "TROOT.h"

void script(){
gROOT->ProcessLine(".L ToyModel.cxx+");
gROOT->ProcessLine("ToyModel()");
//gROOT->ProcessLine(".q");
}
