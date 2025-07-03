{
	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//
			
	WhichSample.push_back("/pnfs/uboone/persistent/users/mastbaum/tuning2022/mc/bnb_ub/flat/bnb.ub.num.genie_v3_00_06.flat.root"); WhichName.push_back("GENIE_v3_0_6");			 
	//----------------------------------------//

	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	//gROOT->ProcessLine(".q");
};
