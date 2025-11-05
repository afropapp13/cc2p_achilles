{
	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//
			
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_4_2_AR23_20i_00_000_CC/14_1000180400_CC_v3_4_2_AR23_20i_00_000.flat.root"); WhichName.push_back("AR23");	
			 
	//----------------------------------------//

	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	//gROOT->ProcessLine(".q");
};
