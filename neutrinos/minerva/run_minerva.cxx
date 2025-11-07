{

    gROOT->ProcessLine(".L ../../electrons/helper_functions.cxx");
    gROOT->ProcessLine(".L minerva_extract_xsec.cxx");

    gROOT->ProcessLine("minerva_extract_xsec(\"dpt\")"); 
    gROOT->ProcessLine("minerva_extract_xsec(\"dalphat\")");       
    gROOT->ProcessLine("minerva_extract_xsec(\"dphit\")"); 

}