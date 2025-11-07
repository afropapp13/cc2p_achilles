{

	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//
	
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/noah_minerva_all_interactions/NuMILE_FHC_numu_C8H8_GENIEv3_AR23_20i_00_000_1M_0000_NUISFLAT.root");WhichName.push_back("AR23");

	//----------------------------------------//

	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	
	gROOT->ProcessLine(".q");
};
