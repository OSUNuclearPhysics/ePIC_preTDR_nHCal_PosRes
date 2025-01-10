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
void compareHists(TString fileNameEmb = "embUps.root",
		TString fileNameData = "dataUps.root") {

	style();
	//gStyle->SetOptStat(0);
	gROOT->ForceStyle();

	Int_t padw = 600, padh = 400;

	const Int_t nPadX = 1;
	const Int_t nPadY = 1;

	TFile *fileEmb = new TFile(fileNameEmb, "READ");
	TFile *fileData = new TFile(fileNameData, "READ");
	//TFile *fileOut = new TFile("embTrkTest_1S.root", "recreate");
	TFile *fileOut = new TFile("comparison.root", "recreate");

	vector<TH1D*> *hists_emb = new vector<TH1D*>;
	vector<TH1D*> *hists_data = new vector<TH1D*>;
	vector<TCanvas*> *vec_cnv = new vector<TCanvas*>;

	vector<TString> *names_emb = new vector<TString>;
	vector<TString> *names_data = new vector<TString>;

	names_emb->push_back("h_UpsRecEmb_y");
	names_emb->push_back("h_UpsRecEmb_eta");

	names_data->push_back("h_UpsRecData_y");
	names_data->push_back("h_UpsRecData_eta");

	vec_cnv->push_back(new TCanvas("cnv_Ups_y", "Reconstructed Upsilon rapidity", nPadX*padw, nPadY*padh));
	vec_cnv->push_back(new TCanvas("cnv_Ups_eta", "Reconstructed Upsilon eta", nPadX*padw, nPadY*padh));

	for (int i = 0; i < names_data->size(); ++i) {

		TH1D *histEmb = (TH1D *)fileEmb->Get(names_emb->at(i));
		TH1D *histData = (TH1D *)fileData->Get(names_data->at(i));

		histEmb->SetName(Form("emb_%s", histEmb->GetName()));
		histData->SetName(Form("data_%s", histData->GetName()));

		//histEmb->Scale(1.0/histEmb->Integral());
		//histData->Scale(1.0/histData->Integral());

		hists_emb->push_back(histEmb);
		hists_data->push_back(histData);

	}


	TString mkdir = "outputComp";

	gSystem->MakeDirectory(mkdir.Data());
	gSystem->cd(mkdir.Data());

	for (int i = 0; i < hists_data->size(); ++i) {

		vec_cnv->at(i)->Divide(nPadX,nPadY);

		hists_emb->at(i)->Scale(1.0/hists_emb->at(i)->Integral());
		hists_data->at(i)->Scale(1.0/hists_data->at(i)->Integral());

		hists_emb->at(i)->SetLineColor(kRed);
		hists_data->at(i)->SetLineColor(kBlue);
		
		//hists_emb->at(i)->Rebin(2);
		//hists_data->at(i)->Rebin(2);

		TLegend *leg = new TLegend(0.7, 0.7, 1.0, 1.0);
		leg->AddEntry(hists_emb->at(i), "embedding");
		leg->AddEntry(hists_data->at(i), "data");

		vec_cnv->at(i)->cd(1);
		hists_emb->at(i)->Draw("e");
		hists_data->at(i)->Draw("samee");
		leg->Draw();


		vec_cnv->at(i)->cd(1)->SaveAs(Form("%s.png", hists_emb->at(i)->GetName()));

	}

	//--------------------------------------------

	gSystem->cd("../");

	fileOut->cd();
	fileOut->Write();

}
