#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "TFile.h"

// ------------------ //

void hepmc_to_gst_converter() {

	const double e_mass = 0.000510998;
	const double m_prot = 0.9382720813, m_neut = 0.939565;
	const double m_pimi = 0.139570, m_pipl = 0.139570, m_pion = 0.139570;

	//open the nuhepmc file
	std::string hepmc_file_name = "C12_1159_e4v_DeltaCascade";
	//std::string hepmc_file_name = "C12_1159_e4v";  

	std::ifstream* fInputFile = new std::ifstream(hepmc_file_name+".hepmc", std::fstream::in);

	if( !fInputFile->good() ){
	
		std::cout<<"Can't read input nuhepmc file"<<std::endl;
	
	}

	// ------------------ //

	TString f_out_str = hepmc_file_name + ".gst.root";
	TFile *file_out = new TFile(f_out_str, "recreate");
	TTree* mytree = new TTree("gst","gst");

	Double_t        genie_q_l;
	Int_t           genie_RunNumber;

	Int_t           genie_iev;
	Int_t           genie_neu;
	Int_t           genie_fspl;
	Int_t           genie_tgt;
	Int_t           genie_Z;
	Int_t           genie_A;
	Int_t           genie_hitnuc;
	Int_t           genie_hitqrk;
	Int_t           genie_resid;
	Bool_t          genie_sea;
	Bool_t          genie_qel;
	Bool_t          genie_mec;
	Bool_t          genie_res;
	Bool_t          genie_dis;
	Bool_t          genie_coh;
	Bool_t          genie_dfr;
	Bool_t          genie_imd;
	Bool_t          genie_imdanh;
	Bool_t          genie_singlek;
	Bool_t          genie_nuel;
	Bool_t          genie_em;
	Bool_t          genie_CC;
	Bool_t          genie_nc;
	Bool_t          genie_charm;
	Int_t           genie_neut_code;
	Int_t           genie_nuance_code;
	Double_t        genie_wght;
	Double_t        genie_xs;
	Double_t        genie_ys;
	Double_t        genie_ts;
	Double_t        genie_Q2s;
	Double_t        genie_Ws;
	Double_t        genie_x;
	Double_t        genie_y;
	Double_t        genie_t;
	Double_t        genie_Q2reco;
	Double_t        genie_W;
	Double_t        genie_EvRF;
	Double_t        genie_Ev;
	Double_t        genie_pxv;
	Double_t        genie_pyv;
	Double_t        genie_pzv;
	Double_t        genie_En;
	Double_t        genie_pxn;
	Double_t        genie_pyn;
	Double_t        genie_pzn;
	Double_t        genie_El;
	Double_t        genie_pxl;
	Double_t        genie_pyl;
	Double_t        genie_pzl;
	Double_t        genie_pl;
	Double_t        genie_cthl;
	Double_t        genie_thetal;
	Double_t        genie_phil;

	Int_t           genie_nfp;
	Int_t           genie_nfn;
	Int_t           genie_nfpip;
	Int_t           genie_nfpim;
	Int_t           genie_nfpi0;
	Int_t           genie_nfkp;
	Int_t           genie_nfkm;
	Int_t           genie_nfk0;
	Int_t           genie_nfem;
	Int_t           genie_nfother;
	Int_t           genie_nip;
	Int_t           genie_nin;
	Int_t           genie_nipip;
	Int_t           genie_nipim;
	Int_t           genie_nipi0;
	Int_t           genie_nikp;
	Int_t           genie_nikm;
	Int_t           genie_nik0;
	Int_t           genie_niem;
	Int_t           genie_niother;
	Int_t           genie_ni;
	int InitialStateParticles = 2;
	Int_t           genie_pdgi[InitialStateParticles];   //[ni]
	Int_t           genie_resc[InitialStateParticles];   //[ni]
	Double_t        genie_Ei[InitialStateParticles];   //[ni]
	Double_t        genie_pxi[InitialStateParticles];   //[ni]
	Double_t        genie_pyi[InitialStateParticles];   //[ni]
	Double_t        genie_pzi[InitialStateParticles];   //[ni]
	Int_t           genie_nf;
	const int FinalStateParticles = 120;
	Int_t           genie_pdgf[FinalStateParticles];   //[nf]
	Double_t        genie_Ef[FinalStateParticles];   //[nf]
	Double_t        genie_pxf[FinalStateParticles];   //[nf]
	Double_t        genie_pyf[FinalStateParticles];   //[nf]
	Double_t        genie_pzf[FinalStateParticles];   //[nf]
	Double_t        genie_pf[FinalStateParticles];   //[nf]
	Double_t        genie_cthf[FinalStateParticles];   //[nf]
	Double_t        genie_thetaf[FinalStateParticles];   //[nf]
	Double_t        genie_phif[FinalStateParticles];   //[nf]

	Double_t        genie_vtxx;
	Double_t        genie_vtxy;
	Double_t        genie_vtxz;
	Double_t        genie_vtxt;
	Double_t        genie_sumKEf;
	Double_t        genie_calresp0;

	mytree->Branch("q_l", &genie_q_l, "q_l/D");
	mytree->Branch("RunNumber", &genie_RunNumber, "RunNumber/I");

	mytree->Branch("iev", &genie_iev, "iev/I");
	mytree->Branch("neu", &genie_neu, "neu/I");
	mytree->Branch("fspl", &genie_fspl, "fspl/I");
	mytree->Branch("tgt", &genie_tgt, "tgt/I");
	mytree->Branch("Z", &genie_Z, "Z/I");
	mytree->Branch("A", &genie_A, "A/I");
	mytree->Branch("hitnuc", &genie_hitnuc, "hitnuc/I");
	mytree->Branch("hitqrk", &genie_hitqrk, "hitqrk/I");
	mytree->Branch("resid", &genie_resid, "resid/I");
	mytree->Branch("sea", &genie_sea, "sea/O");
	mytree->Branch("qel", &genie_qel, "qel/O");
	mytree->Branch("mec", &genie_mec, "mec/O");
	mytree->Branch("res", &genie_res, "res/O");
	mytree->Branch("dis", &genie_dis, "dis/O");
	mytree->Branch("coh", &genie_coh, "coh/O");
	mytree->Branch("dfr", &genie_dfr, "dfr/O");
	mytree->Branch("imd", &genie_imd, "imd/O");
	mytree->Branch("imdanh", &genie_imdanh, "imdanh/O");
	mytree->Branch("singlek", &genie_singlek, "singlek/O");
	mytree->Branch("nuel", &genie_nuel, "nuel/O");
	mytree->Branch("em", &genie_em, "em/O");
	mytree->Branch("cc", &genie_CC, "cc/O");
	mytree->Branch("nc", &genie_nc, "nc/O");
	mytree->Branch("charm", &genie_charm, "charm/O");
	mytree->Branch("neut_code", &genie_neut_code, "neut_code/I");
	mytree->Branch("nuance_code", &genie_nuance_code, "nuance_code/I");
	mytree->Branch("wght", &genie_wght, "wght/D");
	mytree->Branch("xs", &genie_xs, "xs/D");
	mytree->Branch("ys", &genie_ys, "ys/D");
	mytree->Branch("ts", &genie_ts, "ts/D");
	mytree->Branch("Q2s", &genie_Q2s, "Q2s/D");
	mytree->Branch("Ws", &genie_Ws, "Ws/D");
	mytree->Branch("x", &genie_x, "x/D");
	mytree->Branch("y", &genie_y, "x/D");
	mytree->Branch("t", &genie_t, "t/D");
	mytree->Branch("Q2", &genie_Q2reco, "Q2/D");
	mytree->Branch("W", &genie_W, "W/D");
	mytree->Branch("EvRF", &genie_EvRF, "EvRF/D");
	mytree->Branch("Ev", &genie_Ev, "Ev/D");
	mytree->Branch("pxv", &genie_pxv, "pxv/D");
	mytree->Branch("pyv", &genie_pyv, "pyv/D");
	mytree->Branch("pzv", &genie_pzv, "pzv/D");
	mytree->Branch("En", &genie_En, "En/D");
	mytree->Branch("pxn", &genie_pxn, "pxn/D");
	mytree->Branch("pyn", &genie_pyn, "pyn/D");
	mytree->Branch("pzn", &genie_pzn, "pzn/D");
	mytree->Branch("El", &genie_El, "El/D");
	mytree->Branch("pxl", &genie_pxl, "pxl/D");
	mytree->Branch("pyl", &genie_pyl, "pyl/D");
	mytree->Branch("pzl", &genie_pzl, "pzl/D");
	mytree->Branch("pl", &genie_pl, "pl/D");
	mytree->Branch("cthl", &genie_cthl, "cthl/D");
	mytree->Branch("thetal", &genie_thetal, "thetal/D");
	mytree->Branch("phil", &genie_phil, "phil/D");

	mytree->Branch("nfp", &genie_nfp, "nfp/I");
	mytree->Branch("nfn", &genie_nfn, "nfn/I");
	mytree->Branch("nfpip", &genie_nfpip, "nfpip/I");
	mytree->Branch("nfpim", &genie_nfpim, "nfpim/I");
	mytree->Branch("nfpi0", &genie_nfpi0, "nfpi0/I");
	mytree->Branch("nfkp", &genie_nfkp, "nfkp/I");
	mytree->Branch("nfkm", &genie_nfkm, "nfkm/I");
	mytree->Branch("nfk0", &genie_nfk0, "nfk0/I");
	mytree->Branch("nfem", &genie_nfem, "nfem/I");
	mytree->Branch("nfother", &genie_nfother, "nfother/I");
	mytree->Branch("nip", &genie_nip, "nip/I");
	mytree->Branch("nin", &genie_nin, "nin/I");
	mytree->Branch("nipip", &genie_nipip, "nipip/I");
	mytree->Branch("nipim", &genie_nipim, "nipim/I");
	mytree->Branch("nipi0", &genie_nipi0, "nipi0/I");
	mytree->Branch("nikp", &genie_nikp, "nikp/I");
	mytree->Branch("nikm", &genie_nikm, "nikm/I");
	mytree->Branch("nik0", &genie_nik0, "nik0/I");
	mytree->Branch("niem", &genie_niem, "niem/I");
	mytree->Branch("niother", &genie_niother, "niother/I");
	mytree->Branch("ni", &genie_ni, "ni/I");
	mytree->Branch("pdgi", &genie_pdgi,"pdgi[2]/I");
	mytree->Branch("resc", &genie_resc, "resc[2]/I");
	mytree->Branch("Ei", &genie_Ei, "Ei[2]/D");
	mytree->Branch("pxi", &genie_pxi, "pxi[2]/D");
	mytree->Branch("pyi", &genie_pyi, "pyi[2]/D");
	mytree->Branch("pzi", &genie_pzi, "pzi[2]/D");
	mytree->Branch("nf", &genie_nf, "nf/I");

	mytree->Branch("pdgf", &genie_pdgf, "pdgf[120]/I");
	mytree->Branch("Ef", &genie_Ef, "Ef[120]/D");
	mytree->Branch("pxf", &genie_pxf, "pxf[120]/D");
	mytree->Branch("pyf", &genie_pyf, "pyf[120]/D");
	mytree->Branch("pzf", &genie_pzf, "pzf[120]/D");
	mytree->Branch("pf", &genie_pf, "pf[120]/D");
	mytree->Branch("cthf", &genie_cthf, "cthf[120]/D");
	mytree->Branch("thetaf", &genie_thetaf, "thetaf[120]/D");
	mytree->Branch("phif", &genie_phif, "phif[120]/D");

	mytree->Branch("vtxx", &genie_vtxx, "vtxx/D");
	mytree->Branch("vtxy", &genie_vtxy, "vtxy/D");
	mytree->Branch("vtxz", &genie_vtxz, "vtxz/D");
	mytree->Branch("vtxt", &genie_vtxt, "vtxt/D");
	mytree->Branch("sumKEf", &genie_sumKEf, "sumKEf/D");
	mytree->Branch("calresp0", &genie_calresp0, "calresp0/D");

  	// ------------------ //

  	std::string dummy_string1;
	std::string dummy_string2;
	int event_no = -1;
	int dummy_int1 = 0;
	int dummy_int2 = 0;
	int dummy_int3 = 0;

	//start to read the file
	std::string oneLine;
	std::getline(*fInputFile, oneLine);
	std::istringstream inputLine;
	inputLine.str(oneLine);
	bool flag_end=false;
	int event_count=0;

	//read until we get to the first event
	while(1){

		inputLine >> dummy_string1 >> event_no;

		if(dummy_string1=="E") { break; }
		std::getline(*fInputFile, oneLine);
		inputLine.clear();
		inputLine.str(oneLine);

	}

	double tot_xs=0;
	double sum_weights=0;

	double weight = 0;
	int pdg = 0;
	double p_x = 0;
	double p_y = 0;
	double p_z = 0;
	double E = 0;
	double mass = 0;
	int status = -1;

	// loop over the events
  	while(flag_end==false){

        if (event_count % 1000 == 0) std::cout << "entry " << event_count << std::endl;

		// Burn a line
		std::getline(*fInputFile, oneLine);
		// Now get the weight
		std::getline(*fInputFile, oneLine);
		inputLine.clear();
		inputLine.str(oneLine);
		inputLine >> dummy_string1 >> weight;
		sum_weights+=weight;
		//cout << "weight = " << weight << endl;

		// Burn a line
		std::getline(*fInputFile, oneLine);
		
		// Save the total xs
		std::getline(*fInputFile, oneLine);
		inputLine.clear();
		inputLine.str(oneLine);
		inputLine >> dummy_string1 >> dummy_int1 >> dummy_string2 >> tot_xs;

		// Burn one more lines
		std::getline(*fInputFile, oneLine);		

		// Store the process / interaction		
		std::getline(*fInputFile, oneLine);
		inputLine.clear();
		inputLine.str(oneLine);		
		inputLine  >> dummy_string1 >> dummy_int1 >> dummy_string2 >> dummy_int2;

		if ( dummy_int2 >= 200 && dummy_int2 <= 299) { genie_qel = 1; } 
		else { genie_qel = 0; }

		if ( dummy_int2 >= 300 && dummy_int2 <= 399) { genie_mec = 1; } 
		else { genie_mec = 0; }
		
		if ( dummy_int2 >= 400 && dummy_int2 <= 499) { genie_res = 1; } 
		else { genie_res = 0; }		

		if ( dummy_int2 >= 500 && dummy_int2 <= 699) { genie_dis = 1; } 
		else { genie_dis = 0; }

      	// loop over the final state particles

		int fs_counter = 0;

      	while(1){

			std::getline(*fInputFile, oneLine);
			inputLine.clear();
			inputLine.str(oneLine);
			inputLine >> dummy_string1;
				
			if( dummy_string1 == "HepMC::Asciiv3-END_EVENT_LISTING" ) {

				flag_end=true; 
				break;
			
			}

			else if(dummy_string1=="V") continue;
			
			else if(dummy_string1=="E") break;

			inputLine  >> dummy_int1 >> dummy_int2 >> pdg >> p_x >> p_y >> p_z >> E >> mass >> status;
			if(status!=1) continue;

			//cout << "pdg = " << pdg << " p_x = " << p_x << " p_y = " << p_y << " p_z = " << p_z << endl;
		
			TVector3 particle(p_x/1e3,p_y/1e3,p_z/1e3); // GeV
			double part_p = particle.Mag(); // GeV
			//cout << "part_p = " << part_p << endl;

			// outgoing electron
			if (pdg == 11) {

				genie_pl = part_p; // GeV
				genie_pxl = particle.X(); // GeV
				genie_pyl = particle.Y(); // GeV
				genie_pzl = particle.Z(); // GeV	
				genie_El = TMath::Sqrt( part_p*part_p +  e_mass*e_mass); // GeV						

			}

			// final state hadrons
			else {

				genie_pdgf[fs_counter] = pdg;
				genie_pf[fs_counter] = part_p; // GeV	
				genie_pxf[fs_counter] = particle.X(); // GeV	
				genie_pyf[fs_counter] = particle.Y(); // GeV	
				genie_pzf[fs_counter] = particle.Z(); // GeV															

				fs_counter++;

			}


		} // end of loop over particles in a given event

		genie_nf = fs_counter;
		genie_wght = 1.;

    	event_count++;

		mytree->Fill();

   	} // end of the loop over the events

	cout << "sum_weights = " << sum_weights << endl;
	cout << "tot_xs = " << tot_xs << endl;	

   	file_out->cd();
   	mytree->Write();
   	file_out->Close();

}