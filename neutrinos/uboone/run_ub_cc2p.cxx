{

    gROOT->ProcessLine(".L ../../electrons/helper_functions.cxx");
    gROOT->ProcessLine(".L ub_cc2p_extract_xsec.cxx");

    gROOT->ProcessLine("ub_cc2p_extract_xsec(\"delta_p_t\")");
    gROOT->ProcessLine("ub_cc2p_extract_xsec(\"cos(Mu,P_sum)\")");
    gROOT->ProcessLine("ub_cc2p_extract_xsec(\"cos(P_L,P_R)\")");        

}