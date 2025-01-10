#include <exception>
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

#include "TString.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TFile.h"
#include "TArrayI.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TBranch.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TKey.h"
#include "TProfile.h"
#include "TGaxis.h"
#include "TList.h"

//Int_t padw = 800, padh = 600;

#include "style.C"
#include "DrawHistFileReco.h"
#include "HistDrawOptReco.h"

using namespace std;




/////////////////////////////////////////////////////////////
Int_t drawRecoHist() {

	style();
	//gStyle->SetOptStat(0);
	gROOT->ForceStyle();
	//gStyle->SetLineColor(kBlue);
	//gStyle->SetHistLineColor(kBlue);
	gStyle->SetHistLineColor(kBlack);
	gStyle->SetHistLineWidth(2);
	gStyle->SetOptTitle(1);
	gStyle->SetOptStat(1);

	TGaxis::SetExponentOffset(0.02, -0.07, "x");


	vector<TString> *list_Events = new vector<TString>;
	vector<TString> *list_MCpart = new vector<TString>;
	vector<TString> *list_MCpart_gen = new vector<TString>;
	vector<TString> *list_MCpart_sec = new vector<TString>;
	vector<TString> *list_MCpart_1stgen = new vector<TString>;
	vector<TString> *list_Calos = new vector<TString>;


	// Event
	list_Events->push_back("h_Events");

	list_Events->push_back("h_MCpart");

	list_Events->push_back("h_MCpart_nPion_p");
	list_Events->push_back("h_MCpart_nPion_n");
	list_Events->push_back("h_MCpart_nKaon_p");
	list_Events->push_back("h_MCpart_nKaon_n");
	list_Events->push_back("h_MCpart_nProton_p");
	list_Events->push_back("h_MCpart_nProton_n");
	list_Events->push_back("h_MCpart_nElectron_p");
	list_Events->push_back("h_MCpart_nElectron_n");

	list_Events->push_back("h_MCpart_nNeutron");
	list_Events->push_back("h_MCpart_nGamma");

	list_Events->push_back("h_MCpart_nGen");
	list_Events->push_back("h_MCpart_nSec");

	// MC particles
	list_MCpart->push_back("h_MCpart_mass");
	list_MCpart->push_back("h_MCpart_charge");
	list_MCpart->push_back("h_MCpart_E");
	list_MCpart->push_back("h_MCpart_p");
	list_MCpart->push_back("h_MCpart_pT");

	list_MCpart->push_back("h_MCpart_mom_x");
	list_MCpart->push_back("h_MCpart_mom_y");
	list_MCpart->push_back("h_MCpart_mom_z");

	list_MCpart->push_back("h_MCpart_eta");
	list_MCpart->push_back("h_MCpart_etaphi");

	list_MCpart->push_back("h_MCpart_xy");
	list_MCpart->push_back("h_MCpart_zr");

	list_MCpart->push_back("h_MCpart_end_p");
	list_MCpart->push_back("h_MCpart_end_pT");

	list_MCpart->push_back("h_MCpart_posEnd_xy");
	list_MCpart->push_back("h_MCpart_posEnd_zr");

	list_MCpart->push_back("h_MCpart_genStatus");

	// momentum
	list_MCpart->push_back("h_MCpart_Pion_p_p");
	list_MCpart->push_back("h_MCpart_Pion_n_p");
	list_MCpart->push_back("h_MCpart_Kaon_p_p");
	list_MCpart->push_back("h_MCpart_Kaon_n_p");
	list_MCpart->push_back("h_MCpart_Proton_p_p");
	list_MCpart->push_back("h_MCpart_Proton_n_p");
	list_MCpart->push_back("h_MCpart_Electron_p_p");
	list_MCpart->push_back("h_MCpart_Electron_n_p");

	list_MCpart->push_back("h_MCpart_Neutron_p");
	list_MCpart->push_back("h_MCpart_Gamma_p");

	// energy
	list_MCpart->push_back("h_MCpart_Pion_p_E");
	list_MCpart->push_back("h_MCpart_Pion_n_E");
	list_MCpart->push_back("h_MCpart_Kaon_p_E");
	list_MCpart->push_back("h_MCpart_Kaon_n_E");
	list_MCpart->push_back("h_MCpart_Proton_p_E");
	list_MCpart->push_back("h_MCpart_Proton_n_E");
	list_MCpart->push_back("h_MCpart_Electron_p_E");
	list_MCpart->push_back("h_MCpart_Electron_n_E");

	list_MCpart->push_back("h_MCpart_Neutron_E");
	list_MCpart->push_back("h_MCpart_Gamma_E");


	// eta, momentum
	list_MCpart->push_back("h_MCpart_pion_p_eta_p");
	list_MCpart->push_back("h_MCpart_pion_n_eta_p");
	list_MCpart->push_back("h_MCpart_Kaon_p_eta_p");
	list_MCpart->push_back("h_MCpart_Kaon_n_eta_p");
	list_MCpart->push_back("h_MCpart_proton_p_eta_p");
	list_MCpart->push_back("h_MCpart_proton_n_eta_p");
	list_MCpart->push_back("h_MCpart_Electron_p_eta_p");
	list_MCpart->push_back("h_MCpart_Electron_n_eta_p");

	list_MCpart->push_back("h_MCpart_Neutron_eta_p");
	list_MCpart->push_back("h_MCpart_Gamma_eta_p");

	// eta, energy
	list_MCpart->push_back("h_MCpart_Pion_p_eta_E");
	list_MCpart->push_back("h_MCpart_Pion_n_eta_E");
	list_MCpart->push_back("h_MCpart_Kaon_p_eta_E");
	list_MCpart->push_back("h_MCpart_Kaon_n_eta_E");
	list_MCpart->push_back("h_MCpart_Proton_p_eta_E");
	list_MCpart->push_back("h_MCpart_Proton_n_eta_E");
	list_MCpart->push_back("h_MCpart_Electron_p_eta_E");
	list_MCpart->push_back("h_MCpart_Electron_n_eta_E");

	list_MCpart->push_back("h_MCpart_Neutron_eta_E");
	list_MCpart->push_back("h_MCpart_Gamma_eta_E");



	// Generated MC particles
	list_MCpart_gen->push_back("h_MCpart_gen_mass");
	list_MCpart_gen->push_back("h_MCpart_gen_charge");
	list_MCpart_gen->push_back("h_MCpart_gen_E");
	list_MCpart_gen->push_back("h_MCpart_gen_p");
	list_MCpart_gen->push_back("h_MCpart_gen_pT");

	list_MCpart_gen->push_back("h_MCpart_gen_eta");
	list_MCpart_gen->push_back("h_MCpart_gen_etaphi");

	list_MCpart_gen->push_back("h_MCpart_gen_xy");
	list_MCpart_gen->push_back("h_MCpart_gen_zr");

	list_MCpart_gen->push_back("h_MCpart_gen_end_p");
	list_MCpart_gen->push_back("h_MCpart_gen_end_pT");

	list_MCpart_gen->push_back("h_MCpart_gen_posEnd_xy");
	list_MCpart_gen->push_back("h_MCpart_gen_posEnd_zr");


	// Secondary MC particles
	list_MCpart_sec->push_back("h_MCpart_sec_mass");
	list_MCpart_sec->push_back("h_MCpart_sec_charge");
	list_MCpart_sec->push_back("h_MCpart_sec_E");
	list_MCpart_sec->push_back("h_MCpart_sec_p");
	list_MCpart_sec->push_back("h_MCpart_sec_pT");

	list_MCpart_sec->push_back("h_MCpart_sec_eta");
	list_MCpart_sec->push_back("h_MCpart_sec_etaphi");

	list_MCpart_sec->push_back("h_MCpart_sec_xy");
	list_MCpart_sec->push_back("h_MCpart_sec_zr");

	list_MCpart_sec->push_back("h_MCpart_sec_end_p");
	list_MCpart_sec->push_back("h_MCpart_sec_end_pT");

	list_MCpart_sec->push_back("h_MCpart_sec_posEnd_xy");
	list_MCpart_sec->push_back("h_MCpart_sec_posEnd_zr");


	// MC particles - 1st generation daughters
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_mass");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_charge");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_E ");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_p");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_pT");

	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_etaphi");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_eta");

	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_xy");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_zr");

	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_end_p");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_end_pT");

	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_posEnd_xy");
	list_MCpart_1stgen->push_back("h_MCpart_1stgen_daughter_posEnd_zr");




	// EcalEndcapNHit
	list_Calos->push_back("h_nECal_hit_E");
	list_Calos->push_back("h_nECal_hit_Esum");

	list_Calos->push_back("h_nECal_nhits");

	// HcalEndcapNHit

	list_Calos->push_back("h_nHCal_hit_E");
	list_Calos->push_back("h_nHCal_hit_Esum");
	list_Calos->push_back("h_nCal_hit_delE_perevent");

	list_Calos->push_back("h_nHCal_nhits");

	list_Calos->push_back("h_nHCal_hit_pos_x");
	list_Calos->push_back("h_nHCal_hit_pos_y");
	list_Calos->push_back("h_nHCal_hit_pos_z");
	list_Calos->push_back("h_nHCal_hit_pos_xy");

	list_Calos->push_back("h_nHCal_hit_pos_rE");

	// nCals
	list_Calos->push_back("h_nCal_hits_Esum");


	//TCanvas *cnv = new TCanvas();
	//cnv->cd();

	//TString outputdir = "output";
	TString outputdir = "outputClu";

	gSystem->mkdir(outputdir);
	//gSystem->cd(outputdir);
	//cnv->cd()->SaveAs("hEventStat0.png");
	//gSystem->cd("../");
/*
	gSystem->mkdir("output/Events/");
	gSystem->mkdir("output/MCpart/");
	gSystem->mkdir("output/MCpart_gen/");
	gSystem->mkdir("output/MCpart_sec/");
	gSystem->mkdir("output/MCpart_1stgen/");
	gSystem->mkdir("output/Calos/");
*/
	gSystem->mkdir("outputClu/Events/");
	gSystem->mkdir("outputClu/MCpart/");
	gSystem->mkdir("outputClu/MCpart_gen/");
	gSystem->mkdir("outputClu/MCpart_sec/");
	gSystem->mkdir("outputClu/MCpart_1stgen/");
	gSystem->mkdir("outputClu/Calos/");

	//delete cnv;
	//file->Close();
/*
	drawAny("output/Events/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_Events);
	gSystem->cd("../");
	drawAny("output/MCpart/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_MCpart);
	gSystem->cd("../");
	drawAny("output/MCpart_gen/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_MCpart_gen);
	gSystem->cd("../");
	drawAny("output/MCpart_sec/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_MCpart_sec);
	gSystem->cd("../");
	drawAny("output/MCpart_1stgen/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_MCpart_1stgen);
	gSystem->cd("../");
	drawAny("output/Calos/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_Calos);
	gSystem->cd("../");
*/


	drawAny("outputClu/Events/", "data/testClu_full.root", list_Events);
	gSystem->cd("../");
	drawAny("outputClu/MCpart/", "data/testClu_full.root", list_MCpart);
	gSystem->cd("../");
	drawAny("outputClu/MCpart_gen/", "data/testClu_full.root", list_MCpart_gen);
	gSystem->cd("../");
	drawAny("outputClu/MCpart_sec/", "data/testClu_full.root", list_MCpart_sec);
	gSystem->cd("../");
	drawAny("outputClu/MCpart_1stgen/", "data/testClu_full.root", list_MCpart_1stgen);
	gSystem->cd("../");
	drawAny("outputClu/Calos/", "data/testClu_full.root", list_Calos);
	gSystem->cd("../");

	return 1.0;

}
