{

	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//
	
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/noah_t2k_2p2h/14_1000060120_CCMEC_v3_4_2_G18_02a_00_000.gst.root");WhichName.push_back("noah_2p2h");

	//----------------------------------------//

	gROOT->ProcessLine(".L gst_analyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("gst_analyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	//gROOT->ProcessLine(".q");
};
