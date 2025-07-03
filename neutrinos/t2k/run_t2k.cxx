{

    gROOT->ProcessLine(".L ../../electrons/helper_functions.cxx");
    gROOT->ProcessLine(".L t2k_extract_xsec.cxx");

    gROOT->ProcessLine("t2k_extract_xsec(\"dpt\")"); 
    gROOT->ProcessLine("t2k_extract_xsec(\"dat\")");       
    gROOT->ProcessLine("t2k_extract_xsec(\"dphit\")"); 

}