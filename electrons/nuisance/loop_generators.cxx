{

	gROOT->ProcessLine(".L FlatTree_VARS.C+");
	gROOT->ProcessLine("FlatTree_VARS().Loop()");
	gROOT->ProcessLine(".q");

};
