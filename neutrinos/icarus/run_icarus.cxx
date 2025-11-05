{

    gROOT->ProcessLine(".L ../../electrons/helper_functions.cxx");
    gROOT->ProcessLine(".L icarus_extract_xsec.cxx");

    gROOT->ProcessLine("icarus_extract_xsec(\"dpt\")"); 
    gROOT->ProcessLine("icarus_extract_xsec(\"dat\")");   
    //gROOT->ProcessLine("icarus_extract_xsec(\"cosmu\")");    
    //gROOT->ProcessLine("icarus_extract_xsec(\"cosmup\")");           

}