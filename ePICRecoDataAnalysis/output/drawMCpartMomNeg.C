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
#include "TProfile.h"

#include "style.C"

using namespace std;

/////////////////////////////////////////////////////////////
void drawMCpartMomNeg() {

	style();
	gStyle->SetOptStat(0);
	gROOT->ForceStyle();

	Int_t padw = 750, padh = 500;

	const Int_t nPadX = 1;
	const Int_t nPadY = 1;

	const Int_t nFiles = 6;

	vector<TFile*> *files = new vector<TFile*>;
/*
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_full.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_full.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_full.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_full.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_full.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_full.root"));
*/
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_primary_hcal_etaOnly.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_primary_hcal_etaOnly.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_primary_hcal_etaOnly.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_primary_hcal_etaOnly.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_primary_hcal_etaOnly.root"));
	files->push_back(TFile::Open("data/pythia8NCDIS_18x275_minQ2=1_primary_hcal_etaOnly.root"));

	TString mkdir = "outputSpectra";
	gSystem->MakeDirectory(mkdir.Data());
	gSystem->cd(mkdir);
	TFile *fileOut = new TFile("outputMomNeg.root", "recreate");
	fileOut->cd();
	gSystem->cd("../");


	vector<TH1D*> *hists = new vector<TH1D*>;
	vector<TCanvas*> *vec_cnv = new vector<TCanvas*>;
	vector<TLegend*> *legends = new vector<TLegend*>;
	vector<TString> *names = new vector<TString>;
	vector<int> *colors = new vector<int>;
	vector<TString> *drawOpt = new vector<TString>;
	vector<TString> *labels = new vector<TString>;
	vector<bool> *log = new vector<bool>;
	vector<int> *rebin = new vector<int>;
	vector<double> *range_hi = new vector<double>;
	vector<double> *range_lo = new vector<double>;

	//names->push_back("h_MCpart_Pion_p_p");
	names->push_back("h_MCpart_Pion_n_p");
	//names->push_back("h_MCpart_Kaon_p_p");
	names->push_back("h_MCpart_Kaon_n_p");
	//names->push_back("h_MCpart_Proton_p_p");
	names->push_back("h_MCpart_Proton_n_p");
	//names->push_back("h_MCpart_Electron_p_p");
	names->push_back("h_MCpart_Electron_n_p");
	names->push_back("h_MCpart_Neutron_p");
	names->push_back("h_MCpart_Gamma_p");

	log->push_back(true);

	colors->push_back(kBlue);
	colors->push_back(kMagenta);
	colors->push_back(kGreen);
	colors->push_back(kRed);
	colors->push_back(kBlack);
	colors->push_back(kTeal);

	drawOpt->push_back("e");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");
	drawOpt->push_back("samee");

	legends->push_back(new TLegend(0.8, 0.45, 1.0, 1.0));
	//legends->push_back(new TLegend(0.7, 0.7, 1.0, 1.0));

	labels->push_back("#pi^{-}");
	labels->push_back("K^{-}");
	labels->push_back("p^{-}");
	labels->push_back("e^{-}");
	labels->push_back("n");
	labels->push_back("#gamma");

	rebin->push_back(1);
	rebin->push_back(1);
	rebin->push_back(1);
	rebin->push_back(1);
	rebin->push_back(1);
	rebin->push_back(1);

	range_hi->push_back(18.0);
	range_lo->push_back(0.0);

	vec_cnv->push_back(new TCanvas("cnv_p", "MCparticle momentum", nPadX*padw, nPadY*padh));

	for (int i = 0; i < names->size(); ++i) {

		TH1D *hist = (TH1D *)files->at(i%nFiles)->Get(names->at(i));

		//hist->SetName(Form("data_%s", hist->GetName()));

		hist->Rebin(rebin->at(i));

		hist->GetXaxis()->SetRangeUser(range_lo->at(i/nFiles),range_hi->at(i/nFiles));

		hists->push_back(hist);

		cout<<i<<endl;
	}


	gSystem->cd(mkdir.Data());

	for (int i = 0; i < hists->size(); ++i) {

		cout<<i<<endl;

		vec_cnv->at(i/nFiles)->Divide(nPadX,nPadY);

		//hists->at(i)->Scale(1.0/hists->at(i)->Integral());

		hists->at(i)->SetLineColor(colors->at(i%nFiles));
		
		legends->at(i/nFiles)->AddEntry(hists->at(i), labels->at(i));

		if(log->at(i/nFiles)) vec_cnv->at(i/nFiles)->cd(1)->SetLogy();
		if(!log->at(i/nFiles)) vec_cnv->at(i/nFiles)->cd(1);
		hists->at(i)->Draw(drawOpt->at(i%nFiles));
		legends->at(i/nFiles)->Draw("same");


		//vec_cnv->at(i/nFiles)->cd(1)->SaveAs(Form("%s.png", hists->at(i)->GetName()));
		hists->at(i)->Write();
	}

	vec_cnv->at(0)->cd(1)->SaveAs(Form("%s.png", "h_MCpart_neg_p"));

	//--------------------------------------------

	gSystem->cd("../");

	//fileOut->cd();
	fileOut->Write();

}
