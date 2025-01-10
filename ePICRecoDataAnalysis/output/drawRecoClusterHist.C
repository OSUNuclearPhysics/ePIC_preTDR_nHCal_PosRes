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
Int_t drawRecoClusterHist() {

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

	vector<TString> *list_Calos = new vector<TString>;


	// HcalEndcapNClusters
	list_Calos->push_back("h_nHCal_cluster_Rec_E");

	list_Calos->push_back("h_nHCal_nclusters_Rec");

	list_Calos->push_back("h_nHCal_cluster_Rec_pos_x");
	list_Calos->push_back("h_nHCal_cluster_Rec_pos_y");
	list_Calos->push_back("h_nHCal_cluster_Rec_pos_z");
	list_Calos->push_back("h_nHCal_cluster_Rec_pos_xy");

	list_Calos->push_back("h_nHCal_cluster_Rec_pos_rE");

	list_Calos->push_back("h_nHCal_clusters_Reco_eta_deltaRxy");

	// HcalEndcapNTruthClusters
	list_Calos->push_back("h_nHCal_cluster_MC_E");

	list_Calos->push_back("h_nHCal_nclusters_MC");

	list_Calos->push_back("h_nHCal_cluster_MC_pos_x");
	list_Calos->push_back("h_nHCal_cluster_MC_pos_y");
	list_Calos->push_back("h_nHCal_cluster_MC_pos_z");
	list_Calos->push_back("h_nHCal_cluster_MC_pos_xy");

	list_Calos->push_back("h_nHCal_cluster_MC_pos_rE");

	list_Calos->push_back("h_nHCal_clusters_MC_eta_deltaRxy");


	//TCanvas *cnv = new TCanvas();
	//cnv->cd();

	TString outputdir = "outputClu";

	gSystem->mkdir(outputdir);
	//gSystem->cd(outputdir);
	//cnv->cd()->SaveAs("hEventStat0.png");
	//gSystem->cd("../");

	//gSystem->mkdir("output/CalosClu/");
	gSystem->mkdir("outputClu/CalosCluTest/");

	//delete cnv;
	//file->Close();

	//drawAny("output/CalosClu/", "data/ep_noradcor.18x275_q2_0_1_run001.0000.eicrecon.tree_full.root", list_Calos);
	drawAny("outputClu/CalosCluTest/", "data/testClu_full.root", list_Calos);
	gSystem->cd("../");

	return 1.0;

}
