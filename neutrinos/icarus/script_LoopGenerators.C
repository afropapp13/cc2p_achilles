{

	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//
	
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/noah_t2k_all_interactions/icarus_numi_fhc");WhichName.push_back("AR23");

	//----------------------------------------//

	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}

	gROOT->ProcessLine(".q");
};
