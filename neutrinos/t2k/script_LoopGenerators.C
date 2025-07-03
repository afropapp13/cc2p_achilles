{

	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_soft_inmed_DS3_01_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_soft_inmed_DS3_01");
	WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_soft_inmed_DS3_30_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_soft_inmed_DS3_30");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_soft_inmed_DS3_00_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_soft_inmed_DS3_00");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_soft_inmed_DS3_0_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_soft_inmed_DS3_0");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_soft_inmed_DS3_3_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_soft_inmed_DS3_3");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/ME_ODW_1_inmed_DS3_4_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_inmed_DS3_4");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_inmed_DS3_3_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_inmed_DS3_3");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/ME_ODW_1_inmed_DS3_1_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_inmed_DS3_1");
	//WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_inmed_DS3_0_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_inmed_DS3_0");


        //WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_inmed_noadjust_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_inmed_T0T0_noadjust");
        //WhichSample.push_back("/exp/uboone/data/users/bbogart/t2k_ME_ODW_1_T0T0_soft_inmed_noadjust_GiBUU2025/gibuu20251");WhichName.push_back("gibuu20251_inmed_soft_T0T0_noadjust");

        //WhichSample.push_back("/exp/uboone/data/users/bbogart/g_25_t2k_ME_ODW_1_T1T0/gibuu20251");WhichName.push_back("gibuu20251_T1T0");
        //WhichSample.push_back("/exp/uboone/data/users/bbogart/g_25_t2k_ME_ODW_1_T1T0_soft_inmed/gibuu20251");WhichName.push_back("gibuu20251_inmed_soft_T1T0");
        //WhichSample.push_back("/exp/uboone/data/users/bbogart/g_25_t2k_ME_ODW_1_T0T0_soft_inmed/gibuu20251");WhichName.push_back("gibuu20251_inmed_soft_T0T0");

        //WhichSample.push_back("/exp/uboone/app/users/bbogart/test_BuildGenerators/BuildEventGenerators/ubt/t2k_fhc_flat");WhichName.push_back("GENIE");

        //WhichSample.push_back("/exp/uboone/app/users/bbogart/nuisance_ncpi0/BuildEventGenerators/jobcards/samples/14_1000060120_CC_v3_4_0_G18_10a_02_11a.flat");WhichName.push_back("GENIE");
        //WhichSample.push_back("/exp/uboone/app/users/bbogart/nuisance_ncpi0/BuildEventGenerators/jobcards/samples/NuWro_CC_C_t2kFlux_full.flat");WhichName.push_back("NuWro");
        //WhichSample.push_back("/exp/uboone/data/users/bbogart/g25_t2k_ME_ODW_1_ma12_soft_inmed/gibuu20251");WhichName.push_back("gibuu20251_inmed_ma12_soft");

	//WhichSample.push_back("/exp/uboone/data/users/bbogart/samples/GiBUU_2023_flagInMedium_carbon/GiBUU_2023_flagInMedium_carbon.flat"); WhichName.push_back("GiBUU_flagInMedium");			
        //WhichSample.push_back("/exp/uboone/data/users/bbogart/samples/GiBUU_2023_carbon/GiBUU_2023_carbon.flat"); WhichName.push_back("GiBUU");
        //WhichSample.push_back("/exp/uboone/data/users/bbogart/samples/GiBUU_2023_flagInMedium_MA_1p2_carbon/GiBUU_2023_flagInMedium_MA_1p2_carbon.flat"); WhichName.push_back("GiBUU_flagInMedium_MA_1p2");
	//----------------------------------------//

	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	//gROOT->ProcessLine(".q");
};
